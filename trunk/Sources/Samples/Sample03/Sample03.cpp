// Τΰιλ: /Samples/Sample03/Sample03.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample03.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample03::CSample03( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
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
    void CSample03::Draw()
    {
        static float Angle = 0.0f;

        m_WSSwapChain->MakeCurrent();

        //
        // Frame begin
        //

        glClearColor( 90.0f / 255.0f, 135.0f / 255.0f, 178.0f / 255.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glLoadIdentity();
        gluLookAt( 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

        //
        // Cube 01
        //

        m_RenderDevice->SetVertexStructure( m_VSPos3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB );
        m_RenderDevice->SetIndexBuffer( m_IB );
        m_RenderDevice->SetShadingProgram( m_Program );

        Mat3 RotMat = m_TrackBall->GetRotMat();

        glPushMatrix();
        GL::glMultMatrixf( RotMat );
        glScalef( 2.0f, 2.0f, 0.1f );

        m_UColor->SetFloatVec4( Vec4<float>( 122.0f / 255.0f, 1.0f, 66.0f / 255.0f, 1.0f ) );
        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        glPopMatrix();

        //
        // Cube 02
        //

        glPushMatrix();
        glTranslatef( 0.0f, 0.0f, -2.0f );
        glScalef( 2.0f, 2.0f, 0.1f );

        m_UColor->SetFloatVec4( Vec4<float>( 1.0f, 1.0f, 0.0f, 1.0f ) );
        m_OcclusionQuery->BeginQuery( GL_SAMPLES_PASSED );
        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );
        m_OcclusionQuery->EndQuery();

        glPopMatrix();

        m_RenderDevice->SetVertexBuffer( 0, NULL );
        m_RenderDevice->SetIndexBuffer( NULL );
        m_RenderDevice->SetShadingProgram( NULL );

        //
        //
        //

        BeginOrthoView( GL_LOWER_LEFT );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        //
        // TrackBall
        //

        glColor4f( 1.0f, 1.0f, 1.0f, 0.1f );
        m_TrackBall->DrawSchematic();// true );

        //
        // Text
        //

        glColor4f( 0.0f, 1.0f, 1.0f, 0.8f );
        m_Font->DrawText( 20, m_Height - 20 - 14, "Vendor: " + m_DriverDesc.Vendor );
        m_Font->DrawText( 20, m_Height - 35 - 14, "Renderer: " + m_DriverDesc.Renderer );
        glColor4f( 1.0f, 1.0f, 1.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 85 - 14, "FPS: %d", m_FrameCounter->GetFramesPerSecond() );

        GLuint SamplesPassed;
        m_OcclusionQuery->GetResult( &SamplesPassed );

        glColor4f( 1.0f, 1.0f, 0.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 115 - 14, "Num samples passed: %d", SamplesPassed );

        glDisable( GL_BLEND );

        EndOrthoView();

        //
        // Frame end
        //

        m_WSSwapChain->SwapBuffers();

        m_FrameCounter->AddFrame();
    }

    //
    // CreateShaders
    //
    void CSample03::CreateShaders()
    {
        Ptr<GL::CCgShader> VS, FS;
       
        string SourceStr = LoadStringFromFile( "../MEDIA/Cg/MVPUniformColor.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_Program = new GL::CCgShadingProgram();
        m_Program->AttachShader( VS );
        m_Program->AttachShader( FS );
        m_Program->Link();
        m_Program->GetUniform( "Color", &m_UColor );
    }
        
    //
    // CreateVertexBuffers
    //
    void CSample03::CreateVertexBuffers()
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
    void CSample03::CreateIndexBuffers()
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
    void CSample03::OnKeyDown( 
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
    void CSample03::OnMouseMove( 
                                int PosX, int PosY 
                                )
    {
        m_TrackBall->Rotate( Vec2<float>( PosX, m_Height - PosY ) );
    }

    //
    // OnMouseLButton
    //
    void CSample03::OnMouseLButton(
                                   bool Down, int PosX, int PosY 
                                   )
    {
        if (Down)
            m_TrackBall->Touch( Vec2<float>( PosX, PosY ) );
        else
            m_TrackBall->Release();
    }
}