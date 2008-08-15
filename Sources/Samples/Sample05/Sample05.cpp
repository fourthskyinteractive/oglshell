// Файл: /Samples/Sample05/Sample05.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample05.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample05::CSample05( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
        //
        // OpenGL objects
        //

        if (MessageBox( m_Window, L"Press \"Yes\" button to use Framebuffer Object or \"No\" to use P-Buffer.", L"Sample 05", MB_YESNO | MB_ICONQUESTION ) == IDYES)
            CreateFrameBuffer( true );
        else
            CreateFrameBuffer( false );
        CreateShaders();
        CreateVertexBuffers();
        CreateIndexBuffers();
    }

    //
    // Draw
    //
    void CSample05::Draw()
    {
        static float Angle = 0.0f;

        float Time = m_Timer->GetElapsedTime();
        Angle += Time * 5.0f;

        RenderToTexture();

        m_WSSwapChain->MakeCurrent();

        //
        // Frame begin
        //

        glClearColor( 90.0f / 255.0f, 135.0f / 255.0f, 178.0f / 255.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 60.0, (double)m_Width / (double)m_Height, 1.0, 10.0 );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt( 0.0, 0.0, 1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

        //
        // Quad
        //

        glDisable( GL_CULL_FACE );

        m_RenderDevice->SetVertexStructure( m_VSPos3TexCoord2 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB[ 2 ] ); // Позиция вершины + текстурные координаты.
        m_RenderDevice->SetIndexBuffer( m_IB[ 1 ] );
        m_RenderDevice->SetShadingProgram( m_Programs[ 1 ] );

        m_UTexture->EnableSampler();

        glPushMatrix();
        glRotatef( Angle, 0.0f, 1.0f, 0.0f );

        m_RenderDevice->DrawElements( GL_TRIANGLE_STRIP, 0, 4 );

        glPopMatrix();

        m_UTexture->DisableSampler();

        m_RenderDevice->SetVertexBuffer( 0, NULL );
        m_RenderDevice->SetIndexBuffer( NULL );
        m_RenderDevice->SetShadingProgram( NULL );

        glEnable( GL_CULL_FACE );

        //
        // Text
        //

        BeginOrthoView( GL_LOWER_LEFT );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glColor4f( 0.0f, 1.0f, 1.0f, 0.8f );
        m_Font->DrawText( 20, m_Height - 20 - 14, "Vendor: " + m_DriverDesc.Vendor );
        m_Font->DrawText( 20, m_Height - 35 - 14, "Renderer: " + m_DriverDesc.Renderer );
        glColor4f( 1.0f, 1.0f, 1.0f, 0.8f ); 
        m_Font->DrawFormatText( 20, m_Height - 85 - 14, "FPS: %d", m_FrameCounter->GetFramesPerSecond() );
        m_Font->DrawFormatText( 20, m_Height - 115 - 14, "Using render target: %s", m_FBO ? "Framebuffer Object" : "P-Buffer" );

        glDisable( GL_BLEND );

        EndOrthoView();

        //
        // Frame end
        //

        m_WSSwapChain->SwapBuffers();

        m_FrameCounter->AddFrame();
    }

    //
    // RenderToTexture
    //
    void CSample05::RenderToTexture()
    {
        static float Angle = 0.0f;

        float Time = m_Timer->GetElapsedTime();
        Angle += Time * 10.0f;

        // Устанавливаем кадровый буфер. Обычно весь процесс рисования в современных приложениях представляет собой
        // вывод в разные текстуры, а в окно приложения выводится только конечный результат.
        m_RenderDevice->SetFrameBuffer( m_FrameBuffer );

        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 60.0, (double)m_FrameBuffer->GetFrameWidth() / (double)m_FrameBuffer->GetFrameHeight(), 1.0, 10.0 );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt( 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

        m_RenderDevice->SetVertexStructure( m_VSPos3Color3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB[ 0 ] ); // Первый vertex stream - позиция.
        m_RenderDevice->SetVertexBuffer( 1, m_VB[ 1 ] ); // Второй vertex stream - цвет.
        m_RenderDevice->SetIndexBuffer( m_IB[ 0 ] );
        m_RenderDevice->SetShadingProgram( m_Programs[ 0 ] );

        glPushMatrix();
        glRotatef( Angle, 1.0f, 0.0f, 0.0f );
        glRotatef( Angle, 0.0f, 1.0f, 0.0f );
        glRotatef( Angle, 0.0f, 0.0f, 1.0f );

        m_RenderDevice->DrawElements( GL_TRIANGLES, 0, NUM_CUBE_INDICES );

        glPopMatrix();

        m_RenderDevice->SetShadingProgram( NULL );

        // После того, как закончен вывод в текстуру, необходимо вызвать метод ::Present() 
        // активного буфера кадра. Если используется FBO - вызов будет пустым, если P-buffer - 
        // будет осуществлено копирование пикселей из контекста рендеринга в текстуру.
        m_FrameBuffer->Present();
    }

    //
    // CreateFrameBuffer
    // 
    void CSample05::CreateFrameBuffer( bool FBO )
    {
        m_Texture = new GL::CTexture2D( GL_RGBA8, FB_WIDTH, FB_HEIGHT );
        m_Texture->SetFilter( GL_LINEAR, GL_LINEAR );
        m_Texture->SetWrap( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );

        // Выбираем тип создаваемого буфера кадров. В программе можно использовать одновременно 
        // как FBO, так и P-buffer, например если нужен multisampling, но расширение 
        // GL_EXT_framebuffer_multisample не поддерживается.

        if (FBO)
        {
            Ptr<GL::CRenderBuffer> Depth = new GL::CRenderBuffer( GL_DEPTH_COMPONENT24, 0, FB_WIDTH, FB_HEIGHT );
            Ptr<GL::CFrameBufferObject> FrameBuffer = new GL::CFrameBufferObject( GL_FRAMEBUFFER_EXT, FB_WIDTH, FB_HEIGHT );
            
            FrameBuffer->SetTexture2D( GL_COLOR_ATTACHMENT0_EXT, 0, m_Texture );
            FrameBuffer->SetRenderBuffer( GL_DEPTH_ATTACHMENT_EXT, Depth );
            FrameBuffer->CheckStatus();

            m_FrameBuffer = FrameBuffer;
        }
        else
        {
            Ptr<GL::CFrameBuffer> FrameBuffer = new GL::CFrameBuffer( GL_RGBA8, GL_DEPTH_COMPONENT24, 
                0, 0, GL::IFrameBuffer::LT_SINGLE_BUFFER, FB_WIDTH, FB_HEIGHT );

            FrameBuffer->SetTexture2D( GL_FRONT, 0, m_Texture );

            m_FrameBuffer = FrameBuffer;
        }

        m_FBO = FBO;
    }

    //
    // CreateShaders
    //
    void CSample05::CreateShaders()
    {
        Ptr<GL::CCgShader> VS, FS;
       
        string SourceStr = LoadStringFromFile( "../MEDIA/Cg/MVPColor.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_Programs[ 0 ] = new GL::CCgShadingProgram();
        m_Programs[ 0 ]->AttachShader( VS );
        m_Programs[ 0 ]->AttachShader( FS );
        m_Programs[ 0 ]->Link();

        SourceStr = LoadStringFromFile( "../MEDIA/Cg/Texture.cg" );

        VS = new GL::CCgVertexShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBVP1, "VS" );
        FS = new GL::CCgFragmentShader( CG_SOURCE, SourceStr, CG_PROFILE_ARBFP1, "FS" );

        m_Programs[ 1 ] = new GL::CCgShadingProgram();
        m_Programs[ 1 ]->AttachShader( VS );
        m_Programs[ 1 ]->AttachShader( FS );
        m_Programs[ 1 ]->Link();
        m_Programs[ 1 ]->GetSamplerUniform( "Tex0", &m_UTexture );

        m_UTexture->SetSampler( m_Texture );
    }
        
    //
    // CreateVertexBuffers
    //
    void CSample05::CreateVertexBuffers()
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

        GL::CVertexStructure::TDesc Attribs0[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
            1, GL::CVertexStructure::VA_ATTRIB1, 3, GL_FLOAT, GL_FALSE,
        };
        
        m_VSPos3Color3 = new GL::CVertexStructure( Attribs0, 2 );

        //

        struct TQuadVertex
        {
            Vec3<float> Position;
            Vec2<float> TexCoord;
        };

        TQuadVertex QuadVertices[ 4 ] =
        {
            {
                Vec3<float>( 0.0f, 0.0f, 0.0f ),
                Vec2<float>( 0.0f, 0.0f ),
            },
            {
                Vec3<float>( 1.0f, 0.0f, 0.0f ),
                Vec2<float>( 1.0f, 0.0f ),
            },
            {
                Vec3<float>( 1.0f, 1.0f, 0.0f ),
                Vec2<float>( 1.0f, 1.0f ),
            },
            {
                Vec3<float>( 0.0f, 1.0f, 0.0f ),
                Vec2<float>( 0.0f, 1.0f ),
            }
        };

        for (int i = 0; i < 4; ++i)
            QuadVertices[ i ].Position -= Vec3<float>( 0.5f, 0.5f, 0.0f );

        m_VB[ 2 ] = new GL::CVertexBuffer( 4, sizeof( TQuadVertex ), GL_STATIC_DRAW, QuadVertices );

        GL::CVertexStructure::TDesc Attribs1[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
            0, GL::CVertexStructure::VA_ATTRIB1, 2, GL_FLOAT, GL_FALSE
        };
        
        m_VSPos3TexCoord2 = new GL::CVertexStructure( Attribs1, 2 );
    }
        
    //
    // CreateIndexBuffers
    //
    void CSample05::CreateIndexBuffers()
    {
        const GLushort CubeIndices[ NUM_CUBE_INDICES ] =
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

        m_IB[ 0 ] = new GL::CIndexBuffer( NUM_CUBE_INDICES, GL_UNSIGNED_SHORT, GL_STATIC_DRAW, CubeIndices ); 

        const GLushort QuadIndices[ 4 ] =
        {
            3, 0, 2, 1
        };

        m_IB[ 1 ] = new GL::CIndexBuffer( 4, GL_UNSIGNED_SHORT, GL_STATIC_DRAW, QuadIndices ); 
    }

    //
    // OnKeyDown
    //
    void CSample05::OnKeyDown( 
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