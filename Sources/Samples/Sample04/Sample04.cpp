// Τΰιλ: /Samples/Sample04/Sample04.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample04.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample04::CSample04( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
        if (!m_Extensions->NV_conditional_render && !m_Extensions->NVX_conditional_render)
            throw GL::CExtensionException( this, "::CSample04()", "GL_NV[X]_conditional_render" );

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

        m_OcclusionQuery = new GL::CQuery();

        //
        // App
        //

        m_TrackBall = new UI::CTrackBall( Vec2<float>( m_Width / 2.0f, m_Height / 2.0f ), 250.0f, UI::CTrackBall::RT_TRACKBALL );
    }

    //
    // Draw
    //
    void CSample04::Draw()
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

        //
        // Cube 01
        //

        m_RenderDevice->SetVertexStructure( m_VSPos3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB );
        m_RenderDevice->SetIndexBuffer( m_IB );
        m_RenderDevice->SetShadingProgram( m_CgWVP );

        Mat3 RotMat = m_TrackBall->GetRotMat();

        m_Stack->Push();
        m_Stack->Multiply( RotMat );
        m_Stack->Scale( 2.0f, 2.0f, 0.1f );

        m_UColor->SetFloatVec4( Vec4<float>( 122.0f / 255.0f, 1.0f, 66.0f / 255.0f, 1.0f ) );
        m_UWorldViewProj->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        m_Stack->Pop();

        //
        // Cube 02
        //

        m_Stack->Push();
        m_Stack->Translate( 0.0f, 0.0f, -2.0f );
        m_Stack->Scale( 2.0f, 2.0f, 0.1f );

        m_UColor->SetFloatVec4( Vec4<float>( 1.0f, 1.0f, 0.0f, 1.0f ) );
        m_UWorldViewProj->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_OcclusionQuery->BeginQuery( GL_SAMPLES_PASSED );
        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );
        m_OcclusionQuery->EndQuery();

        m_Stack->Pop();

        //
        // Conditional rendering
        //

        m_RenderDevice->BeginConditionalRender( m_OcclusionQuery, GL_QUERY_WAIT_NV );

        m_Stack->Push();
        m_Stack->Translate( -3.0f, 0.0f, -2.0f );

        m_UColor->SetFloatVec4( Vec4<float>( 1.0f, 0.0f, 0.0f, 1.0f ) );
        m_UWorldViewProj->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        m_Stack->Pop();

        m_Stack->Push();
        m_Stack->Translate( 3.0f, 0.0f, -2.0f );

        m_UColor->SetFloatVec4( Vec4<float>( 0.0f, 0.0f, 1.0f, 1.0f ) );
        m_UWorldViewProj->SetFloatMat4( 
            m_Stack->GetTop( GLU::CMatrixStack::MAT_WORLDVIEW_PROJECTION ), 
            GL::IUniform::MO_COLUMN_MAJOR 
            );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        m_Stack->Pop();

        m_RenderDevice->EndConditionalRender();

        m_RenderDevice->SetVertexBuffer( 0, NULL );
        m_RenderDevice->SetIndexBuffer( NULL );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        m_UWorldViewProj->SetFloatMat4( m_Ortho, GL::IUniform::MO_COLUMN_MAJOR );

        //
        // TrackBall
        //

        m_UColor->SetFloat4( 1.0f, 1.0f, 1.0f, 0.1f );
        m_TrackBall->DrawSchematic();// true );

        //
        // Text
        //

        m_UColor->SetFloat4( 0.0f, 1.0f, 1.0f, 0.8f );
        m_Font->DrawText( 20, m_Height - 20 - 14, "Vendor: " + m_DriverDesc.Vendor );
        m_Font->DrawText( 20, m_Height - 35 - 14, "Renderer: " + m_DriverDesc.Renderer );
        m_UColor->SetFloat4( 1.0f, 1.0f, 1.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 85 - 14, "FPS: %d", m_FrameCounter->GetFramesPerSecond() );

        GLuint SamplesPassed;
        m_OcclusionQuery->GetResult( &SamplesPassed );

        m_UColor->SetFloat4( 1.0f, 1.0f, 0.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 115 - 14, "Num samples passed: %d", SamplesPassed );

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
    void CSample04::CreateShaders()
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
    }
        
    //
    // CreateVertexBuffers
    //
    void CSample04::CreateVertexBuffers()
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

        m_VB = new GL::CVertexBuffer( NUM_CUBE_VERTICES, sizeof( Vec3<float> ), GL_STATIC_DRAW, Vertices );

        GL::CVertexStructure::TDesc Attribs0[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
        };
        
        m_VSPos3 = new GL::CVertexStructure( Attribs0, 1 );
    }
        
    //
    // CreateIndexBuffers
    //
    void CSample04::CreateIndexBuffers()
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
    void CSample04::OnKeyDown( 
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

    //
    // OnMouseMove
    //
    void CSample04::OnMouseMove( 
                                int PosX, int PosY 
                                )
    {
        m_TrackBall->Rotate( Vec2<float>( PosX, m_Height - PosY ) );
    }

    //
    // OnMouseLButton
    //
    void CSample04::OnMouseLButton(
                                   bool Down, int PosX, int PosY 
                                   )
    {
        if (Down)
            m_TrackBall->Touch( Vec2<float>( PosX, PosY ) );
        else
            m_TrackBall->Release();
    }
}