// Τΰιλ: /Samples/Sample01/Sample01.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample01.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample01::CSample01( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
        Ptr<GL::CCgShader> VS, FS;
        string SourceStr;
       
        //
        // WVP Shader
        //

        SourceStr = LoadStringFromFile( "../MEDIA/Cg/WVP.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_CgWVP = new GL::CCgShadingProgram();
        m_CgWVP->AttachShader( VS );
        m_CgWVP->AttachShader( FS );
        m_CgWVP->Link();
        m_CgWVP->GetUniform( "WorldViewProj", &m_UWorldViewProj );
        m_CgWVP->GetUniform( "Color", &m_UColor );
    }

    //
    // Draw
    //
    void CSample01::Draw()
    {
        m_WSSwapChain->MakeCurrent();

        //
        // Frame begin
        //

        glClearColor( 90.0f / 255.0f, 135.0f / 255.0f, 178.0f / 255.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        //
        // Text
        //

        m_RenderDevice->SetShadingProgram( m_CgWVP );

        m_UWorldViewProj->SetFloatMat4( m_Ortho, GL::IUniform::MO_COLUMN_MAJOR );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        m_UColor->SetFloat4( 0.0f, 1.0f, 1.0f, 0.8f );
        m_Font->DrawText( 20, m_Height - 20 - 14, "Vendor: " + m_DriverDesc.Vendor );
        m_Font->DrawText( 20, m_Height - 35 - 14, "Renderer: " + m_DriverDesc.Renderer );
        m_UColor->SetFloat4( 1.0f, 1.0f, 1.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 85 - 14, "FPS: %d", m_FrameCounter->GetFramesPerSecond() );

        glDisable( GL_BLEND );

        //
        // Frame end
        //

        m_WSSwapChain->SwapBuffers();

        m_FrameCounter->AddFrame();
    }

    //
    // OnKeyDown
    //
    void CSample01::OnKeyDown( 
                              UINT Key, int Repeat, UINT Flags 
                              )
    {
        switch (Key) 
        {
        case VK_ESCAPE:
            OnClose();
            break;
        }
    }
}