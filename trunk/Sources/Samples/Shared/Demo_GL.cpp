// Τΰιλ: /Samples/Shared/Demo_GL.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Demo.h"

namespace Demo
{
    //
    // Constructor
    //
    CDemo_GL::CDemo_GL( 
                       HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                       ):
        IDemo( Instance, Width, Height, Caption )
    {
        try
        {
            CreateRender();
        }
        catch (const Sys::CException& Ex)
        {
            DestroyRender();
            
            throw Ex;
        }

        //
        // Driver description.
        //

        GL::CDriver::GetDesc( &m_DriverDesc );

        //
        // Font
        //

        GL::IFont::TDesc Desc;

        Desc.Height = 14;
        Desc.Width = 0;
        Desc.Weight = FW_NORMAL;
        Desc.Italic = false;
        Desc.Underline = false;
        Desc.CharSet = DEFAULT_CHARSET;
        Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
        Desc.Quality = ANTIALIASED_QUALITY;//DEFAULT_QUALITY;
        Desc.PitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
        wcscpy( Desc.FaceName, L"Microsoft Sans Serif" );

        m_Font = new GL::CFont( Desc );
    }

    //
    // Constructor
    //
    CDemo_GL::~CDemo_GL()
    {
        DestroyRender();
    }

    //
    // CreateRender
    //
    void CDemo_GL::CreateRender()
    {
        GL::CWindowSwapChain::TPixelFormatDesc Desc;

        Desc.Flags = GL::CWindowSwapChain::WSC_DOUBLE_BUFFER;
        Desc.PixelType = GL::CWindowSwapChain::PT_RGBA;
        
        Desc.NumColorBits = GetDeviceCaps( m_DC, BITSPIXEL );
        if (Desc.NumColorBits >= 32)
        {
            Desc.NumRedBits = 8;
            Desc.RedShift = 0;
            Desc.NumGreenBits = 8;
            Desc.GreenShift = 0;
            Desc.NumBlueBits = 8;
            Desc.BlueShift = 0;
            Desc.NumAlphaBits = 8;
            Desc.AlphaShift = 0;
        }
        else
        {
            Desc.NumRedBits = 5;
            Desc.RedShift = 0;
            Desc.NumGreenBits = 6;
            Desc.GreenShift = 0;
            Desc.NumBlueBits = 5;
            Desc.BlueShift = 0;
            Desc.NumAlphaBits = 0;
            Desc.AlphaShift = 0;
        }
        Desc.NumAccumBits = 0;
        Desc.NumAccumRedBits = 0;
        Desc.NumAccumGreenBits = 0;
        Desc.NumAccumBlueBits = 0;
        Desc.NumAccumAlphaBits = 0;
        Desc.NumDepthBits = 24;
        Desc.NumStencilBits = 8;
        Desc.NumAuxBuffers = 0;
        Desc.SampleDesc.NumBuffers = 1;
        Desc.SampleDesc.NumSamples = 4;

        try
        {
            m_WSSwapChain = new GL::CWindowSwapChain( m_Window, Desc, m_Width, m_Height );
        }
        catch (...)
        {
            Desc.SampleDesc.NumBuffers = 0;
            Desc.SampleDesc.NumSamples = 0;

            m_WSSwapChain = new GL::CWindowSwapChain( m_Window, Desc, m_Width, m_Height );
        }

        if (glewInit() != GLEW_OK)
            throw Sys::CFatalException( this, "::CreateRender() : Failed to initialize OpenGL entry points." );

        m_WSSwapChain->SetVSync( false );

        UINT Flags = 0;
    #ifdef _DEBUG
        Flags = GL::CREATE_DEBUG_RENDER_DEVICE;
    #endif

        GL::CreateShellAPI( Flags, &m_RenderDevice, &m_Extensions );
        if (!m_Extensions->OpenGL_2_0)
            throw Sys::CFatalException( this, "::CreateRender() : No OpenGL 2.0 support detected." );

    #ifdef _DEBUG
        m_RenderDevice = new GL::CRenderDeviceDebug();
    #else
        m_RenderDevice = new GL::CRenderDeviceRelease();
    #endif

        //
        // Common OpenGL states
        //
        
        glViewport( 0, 0, m_Width, m_Height );
    
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 60.0, (double)m_Width / (double)m_Height, 1.0, 1000.0 );
        glMatrixMode( GL_MODELVIEW );

        glEnable( GL_DEPTH_TEST );
        glDepthFunc( GL_LESS );
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );
        glEnable( GL_POINT_SMOOTH );
        glEnable( GL_LINE_SMOOTH );
    }

    //
    // DestroyRender
    //
    void CDemo_GL::DestroyRender()
    {
         m_WSSwapChain = NULL;
    }

    //
    // LoadStringFromFile
    //
    string CDemo_GL::LoadStringFromFile( 
                                        const string& FileName
                                        ) const
    {
        FILE *Stream = fopen( FileName.c_str(), "r" );
        if (!Stream)
            throw Sys::CException( this, "::LoadStringFromFile() : Failed to open file \"%s\"", FileName.c_str() );

        string ShaderStr;

        while (feof( Stream ) == 0) 
        {
            static char Buffer[ 4096 ];

            if (!fgets( Buffer, 4096, Stream )) 
            {
                if (ferror( Stream )) 
                {
                    fclose( Stream );
                    throw Sys::CException( "::LoadStringFromFile() : Failed to read string." );
                }
            }
            
            ShaderStr += Buffer;
        }

        fclose( Stream );
        
        return ShaderStr;
    }
    
    //
    // BeginOrthoView
    //
    void CDemo_GL::BeginOrthoView(  
                                  GLenum Mode 
                                  ) const
    {

        GLint Viewport[ 4 ];

        glGetIntegerv( GL_VIEWPORT, Viewport );

        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        glLoadIdentity(); 
        glOrtho( 0.0, Viewport[ 2 ], 0.0, Viewport[ 3 ], -1.0, 1.0 );

        if (Mode == GL_UPPER_LEFT) 
        {
            glScalef( 1.0f, -1.0f, 1.0f );
            glTranslatef( 0.0f, -Viewport[ 3 ] + 1.0f, 0.0f );
        }

        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();
    }

    //
    // EndOrthoView
    //
    void CDemo_GL::EndOrthoView() const
    {
        glMatrixMode( GL_PROJECTION );
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();
    }
}