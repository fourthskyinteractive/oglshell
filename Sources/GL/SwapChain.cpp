/*
OpenGL Shell - convenient OpenGL wrapper for use in OOP programs.
Copyright (C) 2005-2008 Victor Coda.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library. If not, see http://www.gnu.org/licenses

e-mail: victor.coda@gmail.com
*/

// Файл: /GL/SwapChain.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "SwapChain.h"
#include "Texture.h"

namespace GL
{
    //
    // Constructor
    //
    CWindowSwapChain::TSampleDesc::TSampleDesc():
        NumBuffers( 0 ),
        NumSamples( 0 )
    {
    }

    //
    // Constructor
    //
    CWindowSwapChain::TPixelFormatDesc::TPixelFormatDesc():
        Flags( 0 ),
        PixelType( PT_RGBA ),

        NumColorBits( 0 ),
        NumRedBits( 0 ),
        RedShift( 0 ),
        NumGreenBits( 0 ),
        GreenShift( 0 ),
        NumBlueBits( 0 ),
        BlueShift( 0 ),
        NumAlphaBits( 0 ),
        AlphaShift( 0 ),
        NumAccumBits( 0 ),
        NumAccumRedBits( 0 ),
        NumAccumGreenBits( 0 ),
        NumAccumBlueBits( 0 ),
        NumAccumAlphaBits( 0 ),
        NumDepthBits( 0 ),
        NumStencilBits( 0 ),

        NumAuxBuffers( 0 )
    {
    }

    //
    // Non-portable Window-System dependent codepath.
    //

    #ifdef _WIN32

    //
    // Constructor
    //
    CWindowSwapChain::CWindowSwapChain( 
                                       HWND Window, const TPixelFormatDesc& Desc, GLsizei Width, GLsizei Height  
                                       ):
        CObject( 0 ),

        m_Width( Width ),
        m_Height( Height ),

        m_Window( Window ),
        m_DC( NULL ),
        m_Context( NULL ),
        m_PixelFormat( 0 )
    {
        if (Width < 1)
            throw Sys::CDeveloperException( this, "::CWindowSwapChain() : Invalid <Width> parameter." );
        if (Height < 1)
            throw Sys::CDeveloperException( this, "::CWindowSwapChain() : Invalid <Height> parameter." );

        m_DC = GetDC( m_Window );
		if (!m_DC)
            throw Sys::CException( this, "::CWindowSwapChain() : Failed to obtain window DC." );
    
		HDC PrevDC = wglGetCurrentDC();
		HGLRC PrevContext = wglGetCurrentContext();

		try 
        {
			PIXELFORMATDESCRIPTOR Pfd;

			ZeroMemory( &Pfd, sizeof( PIXELFORMATDESCRIPTOR ) );

			Pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );    
			Pfd.nVersion = 1;
			Pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
            if (Desc.Flags & WSC_DOUBLE_BUFFER)
                Pfd.dwFlags |= PFD_DOUBLEBUFFER;
            if (Desc.Flags & WSC_STEREO)
                Pfd.dwFlags |= PFD_STEREO;
            Pfd.iPixelType = PFD_TYPE_RGBA; // ?
            Pfd.cColorBits = Desc.NumColorBits;
            Pfd.cRedBits = Desc.NumRedBits;
            Pfd.cRedShift = Desc.RedShift;
            Pfd.cGreenBits = Desc.NumGreenBits;
            Pfd.cGreenShift = Desc.GreenShift;
            Pfd.cBlueBits = Desc.NumBlueBits;
            Pfd.cBlueShift = Desc.BlueShift;
            Pfd.cAlphaBits = Desc.NumAlphaBits;
            Pfd.cAlphaShift = Desc.AlphaShift;
            Pfd.cAccumBits = Desc.NumAccumBits;
            Pfd.cAccumRedBits = Desc.NumAccumRedBits;
            Pfd.cAccumGreenBits = Desc.NumAccumGreenBits;
            Pfd.cAccumBlueBits = Desc.NumAccumBlueBits;
            Pfd.cAccumAlphaBits = Desc.NumAccumAlphaBits;
            Pfd.cDepthBits = Desc.NumDepthBits;
            Pfd.cStencilBits = Desc.NumStencilBits;
            Pfd.cAuxBuffers = Desc.NumAuxBuffers; // На NVidia всегда выделяется lazily 4+ aux буфера, не зависимо от заданного кол-ва.
            Pfd.iLayerType = PFD_MAIN_PLANE;
            Pfd.bReserved = 0;
            Pfd.dwLayerMask = 0;
            Pfd.dwVisibleMask = 0;
            Pfd.dwDamageMask = 0;

            if (Desc.SampleDesc.NumSamples > 0)
                m_PixelFormat = ChoosePixelFormatEx( m_DC, Desc );
            else
            {        
				m_PixelFormat = ChoosePixelFormat( m_DC, &Pfd );
				if (m_PixelFormat == 0)
                    throw Sys::CException( this, "::CWindowSwapChain() : Appropriate windowed pixel format not found." );
            }

			if (!SetPixelFormat( m_DC, m_PixelFormat, &Pfd )) 
				throw CWGLException( this, "::CWindowSwapChain() : Failed to set pixel format." );

			m_Context = wglCreateContext( m_DC );
			if (!m_Context)
				throw CWGLException( this, "::CWindowSwapChain() : Failed to create rendering context." );   
			if (!wglMakeCurrent( m_DC, m_Context ))
				throw CWGLException( this, "::CWindowSwapChain() : Failed to make rendering context current." );
		}
		catch (const Sys::CException& Ex)
        {
			if (m_Context) 
            {
				wglMakeCurrent( m_DC, NULL );
				wglDeleteContext( m_Context );	
			}

			ReleaseDC( m_Window, m_DC );

			m_DC = NULL;
			m_Context = NULL;

			if (PrevContext != NULL)
                wglMakeCurrent( PrevDC, PrevContext );

			throw Ex;
		}
    }

    //
    // MakeCurrent
    //
    void CWindowSwapChain::MakeCurrent() const
    {
        if (m_Extensions->EXT_framebuffer_blit)
        {
            glBindFramebufferEXT( GL_READ_FRAMEBUFFER_EXT, 0 );
            glBindFramebufferEXT( GL_DRAW_FRAMEBUFFER_EXT, 0 ); 
        }
        else if (m_Extensions->EXT_framebuffer_object) 
        {
            glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        }

        if (!wglMakeCurrent( m_DC, m_Context ))
            throw CWGLException( this, "::MakeCurrent() : Failed to make rendering context current." );
        
        glViewport( 0, 0, m_Width, m_Height );
    }

    //
    // SwapBuffers
    //
    void CWindowSwapChain::SwapBuffers()
    {
        if (!::SwapBuffers( m_DC ))
            throw Sys::CException( this, "::SwapBuffers() : Failed to swap buffers." );
    }

    //
    // SetVSync
    //
    void CWindowSwapChain::SetVSync( 
                                    bool Sync 
                                    )
    {
        if (!wglGetSwapIntervalEXT)
            return;

        if (Sync) 
        {
            if (wglGetSwapIntervalEXT() == 0) 
                wglSwapIntervalEXT( 1 );
        }
        else 
        {
            if (wglGetSwapIntervalEXT() > 0) 
                wglSwapIntervalEXT( 0 );
        }
    }
        
    //
    // IsVSynced
    //
    bool CWindowSwapChain::IsVSynced() const
    {
        if (!wglGetSwapIntervalEXT)
            return false;

        return wglGetSwapIntervalEXT() != 0;
    }

    //
    // ChoosePixelFormatEx
    //
    int CWindowSwapChain::ChoosePixelFormatEx( 
                                              HDC DC, const TPixelFormatDesc& Desc 
                                              ) const
    {
        const WCHAR *DUMMY_CLASS_NAME = L"Dummy Window"; // See Licensee.h in Doom III SDK.
        
        HINSTANCE Instance = GetModuleHandle( NULL );
        HWND DummyWnd = 0;
        HDC DummyDC = 0;
        HGLRC DummyContext = 0;

        int PixelFormat = 0;

        try 
        {
            DummyWnd = CreateDummyWindow( Instance, DUMMY_CLASS_NAME );
            DummyDC = GetDC( DummyWnd );
            if (!DummyDC)
                throw Sys::CException( this, "::ChoosePixelFormatEx() : Failed to obtain dummy DC." );

            PIXELFORMATDESCRIPTOR Pfd;

			ZeroMemory( &Pfd, sizeof( PIXELFORMATDESCRIPTOR ) );

			Pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );    
			Pfd.nVersion = 1;
			Pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
            Pfd.iPixelType = PFD_TYPE_RGBA;
			Pfd.cColorBits = GetDeviceCaps( DummyDC, BITSPIXEL );
			Pfd.cRedBits = 8;
			Pfd.cRedShift = 0;
			Pfd.cGreenBits = 8;
			Pfd.cGreenShift = 0;
			Pfd.cBlueBits = 8;
			Pfd.cBlueShift = 0;
			Pfd.cAlphaBits = 0;
			Pfd.cAlphaShift = 0;
			Pfd.cAccumBits = 0;
			Pfd.cAccumRedBits = 0;
			Pfd.cAccumGreenBits = 0;
			Pfd.cAccumBlueBits = 0;
			Pfd.cAccumAlphaBits = 0;
			Pfd.cDepthBits = 0; 
			Pfd.cStencilBits = 0;
			Pfd.cAuxBuffers = 0;
			Pfd.iLayerType = PFD_MAIN_PLANE;
			Pfd.bReserved = 0;
            Pfd.dwLayerMask = 0;
            Pfd.dwVisibleMask = 0;
            Pfd.dwDamageMask = 0;

            PixelFormat = ChoosePixelFormat( DummyDC, &Pfd );	
            if (PixelFormat == 0)
                throw CWGLException( this, "::ChoosePixelFormatEx() : Failed to choose dummy pixel format." );

			if (!SetPixelFormat( DummyDC, PixelFormat, &Pfd )) 
				throw CWGLException( this, "::ChoosePixelFormatEx() : Failed to set dummy pixel format." );
        
			DummyContext = wglCreateContext( DummyDC );
			if (!DummyContext)
                throw CWGLException( this, "::ChoosePixelFormatEx() : Failed to create rendering context." );
            if (!wglMakeCurrent( DummyDC, DummyContext ))
                throw CWGLException( this, "::ChoosePixelFormatEx() : Failed to make rendering context current." );

            wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress( "wglChoosePixelFormatARB" );
            if (!wglChoosePixelFormatARB)
                throw Sys::CException( this, "::ChoosePixelFormatEx() : Failed to obtain wglChoosePixelFormatARB entry point." );

            vector<int> Attribs;

            Attribs.push_back( WGL_DRAW_TO_WINDOW_ARB );
            Attribs.push_back( GL_TRUE );
            Attribs.push_back( WGL_DRAW_TO_BITMAP_ARB );
            Attribs.push_back( GL_FALSE );
            Attribs.push_back( WGL_ACCELERATION_ARB );
            Attribs.push_back( WGL_FULL_ACCELERATION_ARB );
            Attribs.push_back( WGL_SUPPORT_GDI_ARB );
            Attribs.push_back( GL_FALSE );
            Attribs.push_back( WGL_SUPPORT_OPENGL_ARB );
            Attribs.push_back( GL_TRUE );
            Attribs.push_back( WGL_DOUBLE_BUFFER_ARB );
            if (!(Desc.Flags & WSC_DOUBLE_BUFFER))
                Attribs.push_back( GL_FALSE );
            else 
            {
                Attribs.push_back( GL_TRUE );
                //Attribs.push_back( WGL_SWAP_METHOD_ARB );
                //Attribs.push_back( WGL_SWAP_EXCHANGE_ARB );
            }
            Attribs.push_back( WGL_STEREO_ARB );
            Attribs.push_back( (Desc.Flags & WSC_STEREO) ? GL_TRUE : GL_FALSE );
            Attribs.push_back( WGL_PIXEL_TYPE_ARB );
            Attribs.push_back( WGL_TYPE_RGBA_ARB ); // ?
            Attribs.push_back( WGL_COLOR_BITS_ARB );
            Attribs.push_back( Desc.NumColorBits );
            Attribs.push_back( WGL_RED_BITS_ARB );
            Attribs.push_back( Desc.NumRedBits );
            //Attribs.push_back( WGL_RED_SHIFT_ARB );
            //Attribs.push_back( Desc.RedShift );
            Attribs.push_back( WGL_GREEN_BITS_ARB );
            Attribs.push_back( Desc.NumGreenBits );
            //Attribs.push_back( WGL_GREEN_SHIFT_ARB );
            //Attribs.push_back( Desc.GreenShift );
            Attribs.push_back( WGL_BLUE_BITS_ARB );
            Attribs.push_back( Desc.NumBlueBits );
            //Attribs.push_back( WGL_BLUE_SHIFT_ARB );
            //Attribs.push_back( Desc.BlueShift );
            Attribs.push_back( WGL_ALPHA_BITS_ARB );
            Attribs.push_back( Desc.NumAlphaBits );
            //Attribs.push_back( WGL_ALPHA_SHIFT_ARB );
            //Attribs.push_back( Desc.AlphaShift );
            Attribs.push_back( WGL_ACCUM_BITS_ARB );
            Attribs.push_back( Desc.NumAccumBits );
            Attribs.push_back( WGL_ACCUM_RED_BITS_ARB );
            Attribs.push_back( Desc.NumAccumRedBits );
            Attribs.push_back( WGL_ACCUM_GREEN_BITS_ARB );
            Attribs.push_back( Desc.NumAccumGreenBits );
            Attribs.push_back( WGL_ACCUM_BLUE_BITS_ARB );
            Attribs.push_back( Desc.NumAccumBlueBits );
            Attribs.push_back( WGL_ACCUM_ALPHA_BITS_ARB  );
            Attribs.push_back( Desc.NumAccumAlphaBits );
            Attribs.push_back( WGL_DEPTH_BITS_ARB );
            Attribs.push_back( Desc.NumDepthBits );
            Attribs.push_back( WGL_STENCIL_BITS_ARB );
            Attribs.push_back( Desc.NumStencilBits );
            Attribs.push_back( WGL_AUX_BUFFERS_ARB ); 
            Attribs.push_back( Desc.NumAuxBuffers );
            Attribs.push_back( WGL_SAMPLE_BUFFERS_ARB );
            Attribs.push_back( Desc.SampleDesc.NumBuffers );
            Attribs.push_back( WGL_SAMPLES_ARB );
            Attribs.push_back( Desc.SampleDesc.NumSamples );
            Attribs.push_back( 0 );

            UINT NumFormats = 0;

            if (!wglChoosePixelFormatARB( DC, &Attribs[0], NULL, 1, &PixelFormat, &NumFormats ))
                throw CWGLException( this, "::ChoosePixelFormatEx() : Failed to choose pixel format." );
            if (NumFormats == 0)
                throw Sys::CException( this, "::ChoosePixelFormatEx() : Appropriate windowed pixel format not found." );

            wglMakeCurrent( DummyDC, NULL );
            wglDeleteContext( DummyContext );

            ReleaseDC( DummyWnd, DummyDC );
            DestroyWindow( DummyWnd );

            UnregisterClass( DUMMY_CLASS_NAME, Instance );
        }
        catch (const Sys::CException& Ex) 
        {
            if (DummyContext) 
            {
                if (wglGetCurrentContext() == DummyContext)
                    wglMakeCurrent( DummyDC, NULL );
                wglDeleteContext( DummyContext );
            }

            if (DummyDC)
                ReleaseDC( DummyWnd, DummyDC );
            if (DummyWnd)
                DestroyWindow( DummyWnd );

            UnregisterClass( DUMMY_CLASS_NAME, Instance );
         
            throw Ex;
        }

        return PixelFormat;
    }

    //
    // CreateDummyWindow
    //
    HWND CWindowSwapChain::CreateDummyWindow( 
                                             HINSTANCE Instance, const WCHAR *ClassName 
                                             ) const
	{
		WNDCLASS WndClass =
        {
            CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            DefWindowProc,
            0,
            0,
            Instance,
            NULL,
            NULL,
            NULL,
            NULL,
            ClassName
        };

		if (!RegisterClass( &WndClass ))
            throw Sys::CException( this, "::CreateDummyWindow() : Failed to register window class." );

		HWND Window = CreateWindow( 
            WndClass.lpszClassName, 
			L"Window",
			WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			NULL, 
			NULL, 
			WndClass.hInstance, 
			NULL );

		if (!Window)
            throw Sys::CException( this, "::CreateDummyWindow() : Failed to create window." );

		return Window;
	}

    #elif defined (__linux__)

    //
    // Constructor
    //
    CWindowSwapChain::CWindowSwapChain( 
                                       const TPixelFormatDesc& Desc 
                                       )
    {
    }

    //
    // MakeCurrent
    //
    void CWindowSwapChain::MakeCurrent() const
    {
    }

    //
    // SwapBuffers
    //
    void CWindowSwapChain::SwapBuffers()
    {
    }

    //
    // SetVSync
    //
    void CWindowSwapChain::SetVSync( 
                                    bool Sync 
                                    )
    {
    }
        
    //
    // IsSync
    //
    bool CWindowSwapChain::IsVSync() const
    {
        return false;
    }

    #endif // _WIN32

    //
    // GetPixelFormatDesc
    //
    void CWindowSwapChain::GetPixelFormatDesc( 
                                              TPixelFormatDesc *Desc 
                                              ) const
    {
        *Desc = m_Desc;
    }

    //
    // CopySubImage1D
    //
    void CWindowSwapChain::CopySubImage1D( 
                                          GLenum Buffer, GLint Level, 
                                          GLint xOffset, GLint x, GLint y, GLsizei Width, 
                                          Ptr<class CTexture1D> Texture 
                                          ) const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif

        glActiveTexture( GL_TEXTURE0 );      
        glBindTexture( GL_TEXTURE_1D, Texture->m_Texture );
        glReadBuffer( Buffer );
        glCopyTexSubImage1D( GL_TEXTURE_1D, Level, xOffset, x, y, Width );

    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CopySubImage1D() : An OpenGL error has occured." );
    #endif
    }
        
    //
    // CopySubImage2D
    //
    void CWindowSwapChain::CopySubImage2D( 
                                          GLenum Buffer, GLint Level, 
                                          GLint xOffset, GLint yOffset, GLint x, GLint y, GLsizei Width, GLsizei Height, 
                                          Ptr<class CTexture> Texture
                                          ) const
    {
        if (Texture->m_Target != GL_TEXTURE_2D && Texture->m_Target != GL_TEXTURE_RECTANGLE_ARB) 
            throw Sys::CDeveloperException( this, "::CopySubImage2D() : Invalid <Texture> parameter.\nTexture target should be GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE." );

    #ifdef _DEBUG
        glClearErrors();
    #endif

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( Texture->m_Target, Texture->m_Texture );
        glReadBuffer( Buffer );
        glCopyTexSubImage2D( Texture->m_Target, Level, xOffset, yOffset, x, y, Width, Height );

    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::CopySubImage2D() : An OpenGL error has occured." );
    #endif
    }
}