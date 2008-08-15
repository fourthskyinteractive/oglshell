// Файл: /Samples/Sample07/Sample07.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample07.h"

namespace Demo
{
    //
    // Constructor
    //
    CSample07::CSample07( 
                         HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                         ):
        CDemo_GL( Instance, Width, Height, Caption )
    {
        if (!m_Extensions->EXT_bindable_uniform)
            throw GL::CExtensionException( this, "::CSample07()", "GL_EXT_bindable_uniform" );

        //
        // OpenGL objects
        //

        CreateShaders();
        CreateVertexBuffers();
    }

    //
    // Draw
    //
    void CSample07::Draw()
    {
        m_WSSwapChain->MakeCurrent();

        //
        // Frame begin
        //

        glClearColor( 90.0f / 255.0f, 135.0f / 255.0f, 178.0f / 255.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        glLoadIdentity();
        gluLookAt( 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
        
        //
        // Triangle
        //
        
        m_RenderDevice->SetVertexStructure( m_VSPos3 );
        m_RenderDevice->SetVertexBuffer( 0, m_VB );
        m_RenderDevice->SetShadingProgram( m_Program );
        
        m_RenderDevice->DrawArrays( GL_TRIANGLES, 0, 3 );
        
        m_RenderDevice->SetVertexBuffer( 0, NULL );
        m_RenderDevice->SetShadingProgram( NULL );
        
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
    void CSample07::CreateShaders()
    {
        Ptr<GL::CVertexShader> VS;
        Ptr<GL::CFragmentShader> FS;

        VS = new GL::CVertexShader( LoadStringFromFile( "../MEDIA/GLSL/MVPBindableColor.vsh" ) );         
        FS = new GL::CFragmentShader( LoadStringFromFile( "../MEDIA/GLSL/Color.fsh" ) ); 

        m_Program = new GL::CShadingProgram();
        m_Program->AttachShader( VS );
        m_Program->AttachShader( FS );
        m_Program->BindAttribLocation( "In_Vertex", 0 );
        m_Program->Link();
        m_Program->GetBindableUniform( "Buffer", &m_Uniform );
        
        // Узнаём размер буфера. 
        GLsizei Size = m_Uniform->GetBufferSize();    
        // Создаём буфер юниформов.
        m_UB = new GL::CGenericBuffer( GL_UNIFORM_BUFFER_EXT, Size, GL_STREAM_DRAW, NULL );
        // Привязываем буфер к переменной шейдера.
        m_Uniform->AttachBuffer( m_UB );
         
        const float Color[ 3 ] =
        {
            139.0f / 255.0f,
            247.0f / 255.0f,
            136.0f / 255.0f,
        };
        
        BYTE *Buffer = (BYTE *)m_UB->Map( GL_WRITE_ONLY );
        
        for (int i = 0; i < 3; ++i)
        {
            // Т. к. в расширении GL_EXT_bindable_uniform не определён memory layout для отдельных элементов буфера,
            // это единственно правильный метод обновления отдельных элементов. Кроме того, можно просто вычислить stride 
            // между двумя соседними элементами, т. к. гарантируется, что для всех элементов он одинаков.
            GLintptr Offset = m_Uniform->GetElementOffset( i );
            *(float *)(Buffer + Offset) = Color[ i ];
        }
       
        m_UB->UnMap();
    }
        
    //
    // CreateVertexBuffers
    //
    void CSample07::CreateVertexBuffers()
    {
        Vec3<float> Vertices[ 3 ] =
        {
            Vec3<float>( -1.0f, -1.0f, 0.0f ),
            Vec3<float>( 1.0f, -1.0f, 0.0f ),
            Vec3<float>( 0.0f, 1.0f, 0.0f ),
        };

        m_VB = new GL::CVertexBuffer( 3, sizeof( Vec3<float> ), GL_STATIC_DRAW, Vertices );

        GL::CVertexStructure::TDesc Attribs[] =
        {
            0, GL::CVertexStructure::VA_ATTRIB0, 3, GL_FLOAT, GL_FALSE,
        };
        
        m_VSPos3 = new GL::CVertexStructure( Attribs, 1 );
    }

    //
    // OnKeyDown
    //
    void CSample07::OnKeyDown( 
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