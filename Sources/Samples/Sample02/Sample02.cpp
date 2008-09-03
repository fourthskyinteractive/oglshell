// Файл: /Samples/Sample02/Sample02.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample02.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample02::CSample02( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
        Vec3<float> Eye( 0.0f, 0.0f, 5.0f );
        Vec3<float> At( 0.0f, 0.0f, 0.0f );
        Vec3<float> Up( 0.0f, 1.0f, 0.0f );

        m_View.LookAtRH( Eye, At, Up ); 

        //
        // OpenGL objects
        //

        CreateShaders();
        CreateVertexBuffers();
        CreateIndexBuffers();
    }

    //
    // Draw
    //
    void CSample02::Draw()
    {
        static float Angle = 0.0f;

        m_WSSwapChain->MakeCurrent();

        //
        // Frame begin
        //

        glClearColor( 90.0f / 255.0f, 135.0f / 255.0f, 178.0f / 255.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        m_Stack->Select( GLU::CMatrixStack::MAT_PROJECTION );
        m_Stack->Set( m_Proj );
        m_Stack->Select( GLU::CMatrixStack::MAT_VIEW );
        m_Stack->Set( m_View );
        m_Stack->Select( GLU::CMatrixStack::MAT_WORLD );
        m_Stack->SetIdentity();

        float Time = m_Timer->GetElapsedTime();
        Angle += Time * 60.0f;

        //
        // Cube 01
        //

        m_RenderDevice->SetVertexStructure( m_VSPos3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB[ 0 ] );
        m_RenderDevice->SetIndexBuffer( m_IB );

        m_RenderDevice->SetShadingProgram( m_CgWVP );

        m_Stack->Push();
        m_Stack->Translate( -1.0f, 0.0f, 0.0f );
        m_Stack->Rotate( 1.0f, 0.0f, 0.0f, Angle );
        m_Stack->Rotate( 0.0f, 1.0f, 0.0f, Angle );
        m_Stack->Rotate( 0.0f, 0.0f, 1.0f, Angle );

        m_UColor->SetFloat4( 1.0f, 1.0f, 0.0f, 1.0f );
        m_UWorldViewProj->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        m_Stack->Pop();

        //
        // Cube 02
        //

        m_RenderDevice->SetVertexStructure( m_VSPos3Color3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB[ 0 ] ); // Первый vertex stream - позиция.
        m_RenderDevice->SetVertexBuffer( 1, m_VB[ 1 ] ); // Второй vertex stream - цвет.
        m_RenderDevice->SetIndexBuffer( m_IB );
        m_RenderDevice->SetShadingProgram( m_CgWVPColor );

        m_Stack->Push();
        m_Stack->Translate( 1.0f, 0.0f, 0.0f );
        m_Stack->Rotate( 1.0f, 0.0f, 0.0f, -Angle * 2.0f );
        m_Stack->Rotate( 0.0f, 1.0f, 0.0f, -Angle * 2.0f );
        m_Stack->Rotate( 0.0f, 0.0f, 1.0f, -Angle * 2.0f );

        m_UWorldViewProj2->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        m_Stack->Pop();

        m_RenderDevice->SetShadingProgram( NULL );
        m_RenderDevice->SetVertexBuffer( 0, NULL );
        m_RenderDevice->SetVertexBuffer( 1, NULL );
        m_RenderDevice->SetIndexBuffer( NULL );

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
    // CreateShaders
    //
    void CSample02::CreateShaders()
    {
        Ptr<GL::CCgShader> VS, FS;
       
        string SourceStr = LoadStringFromFile( "../MEDIA/Cg/WVP.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_CgWVP = new GL::CCgShadingProgram();
        m_CgWVP->AttachShader( VS );
        m_CgWVP->AttachShader( FS );
        m_CgWVP->Link();
        m_CgWVP->GetUniform( "WorldViewProj", &m_UWorldViewProj );
        m_CgWVP->GetUniform( "Color", &m_UColor );

        SourceStr = LoadStringFromFile( "../MEDIA/Cg/WVPColor.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_CgWVPColor = new GL::CCgShadingProgram();
        m_CgWVPColor->AttachShader( VS );
        m_CgWVPColor->AttachShader( FS );
        m_CgWVPColor->Link();
        m_CgWVPColor->GetUniform( "WorldViewProj", &m_UWorldViewProj2 );
    }
        
    //
    // CreateVertexBuffers
    //
    void CSample02::CreateVertexBuffers()
    {
        Vec3<float> Vertices[ NUM_CUBE_VERTICES ] =
        {
            Vec3<float>( 0.0f, 0.0f, 0.0f ),
            Vec3<float>( 1.0f, 0.0f, 0.0f ),
            Vec3<float>( 1.0f, 0.0f, 1.0f ),
            Vec3<float>( 0.0f, 0.0f, 1.0f ),
            Vec3<float>( 0.0f, 1.0f, 0.0f ),
            Vec3<float>( 1.0f, 1.0f, 0.0f ),
            Vec3<float>( 1.0f, 1.0f, 1.0f ),
            Vec3<float>( 0.0f, 1.0f, 1.0f ),
        };

        for (int i = 0; i < NUM_CUBE_VERTICES; ++i)
            Vertices[ i ] -= Vec3<float>( 0.5f, 0.5f, 0.5f );

        m_VB[ 0 ] = new GL::CVertexBuffer( NUM_CUBE_VERTICES, sizeof( Vec3<float> ), GL_STATIC_DRAW, Vertices );

        GL::CVertexStructure::TDesc Attribs0[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
        };
        
        m_VSPos3 = new GL::CVertexStructure( Attribs0, 1 );

        //

        const Vec3<float> Colors[ NUM_CUBE_VERTICES ] =
        {
            Vec3<float>( 1.0f, 0.0f, 0.0f ),
            Vec3<float>( 1.0f, 1.0f, 0.0f ),
            Vec3<float>( 0.0f, 1.0f, 0.0f ),
            Vec3<float>( 0.0f, 0.0f, 1.0f ),
            Vec3<float>( 1.0f, 0.0f, 1.0f ),
            Vec3<float>( 0.0f, 1.0f, 1.0f ),
            Vec3<float>( 1.0f, 1.0f, 1.0f ),
            Vec3<float>( 0.0f, 0.0f, 0.0f ),
        };

        m_VB[ 1 ] = new GL::CVertexBuffer( NUM_CUBE_VERTICES, sizeof( Vec3<float> ), GL_STATIC_DRAW, Colors );

        GL::CVertexStructure::TDesc Attribs1[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
            1, GL::CVertexStructure::VA_ATTRIB1, 3, GL_FLOAT, GL_FALSE,
        };

        m_VSPos3Color3 = new GL::CVertexStructure( Attribs1, 2 );
    }
        
    //
    // CreateIndexBuffers
    //
    void CSample02::CreateIndexBuffers()
    {
        const GLushort Indices[ NUM_CUBE_INDICES ] =
        {
            0, 1, 2,
            0, 2, 3,
            4, 7, 6,
            4, 6, 5,
            0, 4, 1,
            1, 4, 5,
            1, 5, 2,
            2, 5, 6,
            2, 6, 3,
            3, 6, 7,
            3, 7, 0,
            0, 7, 4,
        };

        m_IB = new GL::CIndexBuffer( NUM_CUBE_INDICES, GL_UNSIGNED_SHORT, GL_STATIC_DRAW, Indices ); 
    }

    //
    // OnKeyDown
    //
    void CSample02::OnKeyDown( 
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