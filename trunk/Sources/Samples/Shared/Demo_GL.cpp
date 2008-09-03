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
        Vec3<float> Eye( 0.0f, 50.0f, 120.0f );
        Vec3<float> At( 0.0f, 0.0f, 0.0f );
        Vec3<float> Up( 0.0f, 1.0f, 0.0f );

        m_View.LookAtRH( Eye, At, Up ); 
        m_Proj.PerspectiveRH( 60.0f, (float)m_Width / (float)m_Height, 1.0f, 1000.0f );
        m_Ortho.Ortho2DRH( 0.0f, m_Width, 0.0f, m_Height );

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
        // Render
        //

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
        // Driver description
        //

        GL::CDriver::GetDesc( &m_DriverDesc );

        //
        // Font
        //

        GLU::CFont::TDesc Desc;

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

        m_Font = new GLU::CBitmapFont( Desc );

        m_Stack = new GLU::CMatrixStack();
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
        GLW::CWindowSwapChain::TPixelFormatDesc Desc;

        //
        // Window Pixel Format
        //

        Desc.Flags = GLW::CWindowSwapChain::WSC_DOUBLE_BUFFER;
        Desc.ColorBitsCount = GetDeviceCaps( m_DC, BITSPIXEL );
        if (Desc.ColorBitsCount >= 32)
        {
            Desc.RedBitsCount = 8;
            Desc.RedShift = 0;
            Desc.GreenBitsCount = 8;
            Desc.GreenShift = 0;
            Desc.BlueBitsCount = 8;
            Desc.BlueShift = 0;
            Desc.AlphaBitsCount = 8;
            Desc.AlphaShift = 0;
        }
        else
        {
            Desc.RedBitsCount = 5;
            Desc.RedShift = 0;
            Desc.GreenBitsCount = 6;
            Desc.GreenShift = 0;
            Desc.BlueBitsCount = 5;
            Desc.BlueShift = 0;
            Desc.AlphaBitsCount = 0;
            Desc.AlphaShift = 0;
        }
        Desc.AccumBitsCount = 0;
        Desc.AccumRedBitsCount = 0;
        Desc.AccumGreenBitsCount = 0;
        Desc.AccumBlueBitsCount = 0;
        Desc.AccumAlphaBitsCount = 0;
        Desc.DepthBitsCount = 24;
        Desc.StencilBitsCount = 8;
        Desc.AuxBuffersCount = 0;
        Desc.SampleDesc.BuffersCount = 1;
        Desc.SampleDesc.SamplesCount = 0;
        Desc.SampleDesc.QuincunxFilterNV = GL_TRUE;

        try
        {
            m_WSSwapChain = new GLW::CWindowSwapChain( m_Window, Desc, m_Width, m_Height );
        }
        catch (...)
        {
            Desc.SampleDesc.SamplesCount = 0;

            m_WSSwapChain = new GLW::CWindowSwapChain( m_Window, Desc, m_Width, m_Height );
        }

        if (glewInit() != GLEW_OK)
            throw Sys::CFatalException( this, "::CreateRender() : Failed to initialize OpenGL entry points." );

        m_WSSwapChain->SetVSync( false );

        //
        // Shell Library
        //

        UINT Flags = 0;
    #ifdef _DEBUG
        Flags = GL::CREATE_DEBUG_RENDER_DEVICE;
    #endif

        GL::CreateShellAPI( Flags, &m_RenderDevice, &m_Extensions );
        if (!m_Extensions->OpenGL_2_0)
            throw Sys::CFatalException( this, "::CreateRender() : No OpenGL 2.0 support detected." );

        //
        // States
        //
        
        glViewport( 0, 0, m_Width, m_Height );

        // Rasterizer State
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );
        glEnable( GL_POINT_SMOOTH );
        glEnable( GL_LINE_SMOOTH );
        // Depth State
        glEnable( GL_DEPTH_TEST );
        glDepthFunc( GL_LESS );
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
}