/*
OpenGL Shell - open source C++ wrapper for use in OOP programs.
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

// Τΰιλ: /GL/GL/FrameBuffer.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "FrameBuffer.h"
#include "Texture.h"

namespace GL
{
    //
    // Constructor
    //
    CFrameBuffer::TCaps::TCaps():
		MaxPixels( 0 ),
		MaxWidth( 0 ),
		MaxHeight( 0 )
	{
	}

    //
    // Constructor
    //
    CFrameBuffer::CFrameBuffer( 
                               GLenum ColorFormat, GLenum DepthStencilFormat, GLuint SamplesCount, GLuint AuxBuffersCount, ELayerType LayerType, 
                               GLsizei Width, GLsizei Height 
                               ):
        IFrameBuffer( FBT_FRAMEBUFFER_OBJECT, Width, Height ),

    #ifdef _WIN32
        m_DC( NULL ),
        m_Context( NULL ),
        m_PixelFormat( NULL ),

        m_Pbuffer( NULL )
    #elif defined (__linux__)
        //
    #endif // _WIN32
    {
        //
        // Non-portable Window-System dependent codepath.
        //

    #ifdef _WIN32
        if (!m_Extensions->WindowSystem->ARB_pbuffer)
        {
            throw CExtensionException( this, "::CFrameBuffer()", "WGL_ARB_pbuffer." );
        }

        if (Width < 1)
            throw Sys::CDeveloperException( this, "::CFrameBuffer() : Invalid <Width> parameter." );
        if (Height < 1)
            throw Sys::CDeveloperException( this, "::CFrameBuffer() : Invalid <Height> parameter." );

        HDC PrevDC = wglGetCurrentDC();
        HGLRC PrevContext = wglGetCurrentContext();
        if (!PrevDC)
            throw Sys::CException( this, "::CFrameBuffer() : Failed to obtain current DC." );

        TPixelFormatDesc Desc;
        vector<int> Attribs;

        ChoosePixelFormat( ColorFormat, DepthStencilFormat, &Desc );

        Attribs.push_back( WGL_DRAW_TO_WINDOW_ARB );
        Attribs.push_back( GL_FALSE );
        Attribs.push_back( WGL_DRAW_TO_BITMAP_ARB );
        Attribs.push_back( GL_FALSE );
        Attribs.push_back( WGL_DRAW_TO_PBUFFER_ARB );
        Attribs.push_back( GL_TRUE );
        Attribs.push_back( WGL_ACCELERATION_ARB );
        Attribs.push_back( WGL_FULL_ACCELERATION_ARB );
        Attribs.push_back( WGL_SUPPORT_GDI_ARB );
        Attribs.push_back( GL_FALSE );
        Attribs.push_back( WGL_SUPPORT_OPENGL_ARB );
        Attribs.push_back( GL_TRUE );
        Attribs.push_back( WGL_DOUBLE_BUFFER_ARB );
        if (LayerType == LT_SINGLE_BUFFER)
            Attribs.push_back( GL_FALSE );
        else 
        {
            Attribs.push_back( GL_TRUE );
            if (m_Extensions->NV_register_combiners || m_Extensions->NV_vertex_program) // Make sure we are on NVIDIA hardware (ATI have a lot of bugs).
            {
                Attribs.push_back( WGL_SWAP_METHOD_ARB );
                Attribs.push_back( WGL_SWAP_EXCHANGE_ARB );
            }
        }
        Attribs.push_back( WGL_STEREO_ARB );
        Attribs.push_back( GL_FALSE );
        Attribs.push_back( WGL_PIXEL_TYPE_ARB );
        if (Desc.PixelType == PT_INTEGER)
            Attribs.push_back( WGL_TYPE_RGBA_ARB );
        else 
        {
			if (m_Extensions->WindowSystem->ARB_pixel_format_float || m_Extensions->WindowSystem->ATI_pixel_format_float)
                Attribs.push_back( WGL_TYPE_RGBA_FLOAT_ARB ); // WGL_TYPE_RGBA_FLOAT_ATI the same.
			else if (m_Extensions->WindowSystem->NV_float_buffer) 
            {
                Attribs.push_back( WGL_TYPE_RGBA_ARB );
                Attribs.push_back( WGL_FLOAT_COMPONENTS_NV ); // Old NVIDIA CineFX hardware.
                Attribs.push_back( GL_TRUE );
            }
			else 
            {
                throw Sys::CDeveloperException( this, "::CFrameBuffer() : Floating-point P-buffers unsupported." );
			}
        }
		Attribs.push_back( WGL_COLOR_BITS_ARB ); 
		Attribs.push_back( Desc.ColorBitsCount );
        Attribs.push_back( WGL_RED_BITS_ARB );
        Attribs.push_back( Desc.RedBitsCount );
        Attribs.push_back( WGL_GREEN_BITS_ARB );
        Attribs.push_back( Desc.GreenBitsCount );
        Attribs.push_back( WGL_BLUE_BITS_ARB );
        Attribs.push_back( Desc.BlueBitsCount );
        Attribs.push_back( WGL_ALPHA_BITS_ARB );
        Attribs.push_back( Desc.AlphaBitsCount );
        Attribs.push_back( WGL_DEPTH_BITS_ARB );
        Attribs.push_back( Desc.DepthBitsCount );
        Attribs.push_back( WGL_STENCIL_BITS_ARB );
        Attribs.push_back( Desc.StencilBitsCount );
        Attribs.push_back( WGL_AUX_BUFFERS_ARB );
        Attribs.push_back( AuxBuffersCount );
        if (SamplesCount > 0) 
        {
            Attribs.push_back( WGL_SAMPLE_BUFFERS_ARB );
            Attribs.push_back( 1 );
            Attribs.push_back( WGL_SAMPLES_ARB );
            Attribs.push_back( SamplesCount );
        }
        Attribs.push_back( 0 );

        UINT uNumFormats = 0;

        if (!wglChoosePixelFormatARB( PrevDC, &Attribs[0], NULL, 1, &m_PixelFormat, &uNumFormats ))
            throw Sys::CException( this, "::CFrameBuffer() : Failed to choose pixel format." );
        if (uNumFormats == 0)
            throw Sys::CException( this, "::CFrameBuffer() : Appropriate pixel format not found." );

        int Attrib = WGL_ACCELERATION_ARB, Value = 0;

        // Make sure that this is an ICD pixel format.
		if (!wglGetPixelFormatAttribivARB( PrevDC, m_PixelFormat, 0, 1, &Attrib, &Value ))
            throw Sys::CException( this, "::CFrameBuffer() : Failed to query pixel format attributes." );
        if (Value != WGL_FULL_ACCELERATION_ARB)
            throw Sys::CException( this, "::CFrameBuffer() : Accelerated pixel format not found." );

        try 
        {
            vector<int> Attribs;
        
            Attribs.push_back( WGL_PBUFFER_LARGEST_ARB );
            Attribs.push_back( GL_FALSE );
            Attribs.push_back( 0 );

            m_Pbuffer = wglCreatePbufferARB( PrevDC, m_PixelFormat, Width, Height, &Attribs[0] );
            if (!m_Pbuffer)
                throw CWGLException( this, "::CFrameBuffer() : Failed to create P-buffer." );
            m_DC = wglGetPbufferDCARB( m_Pbuffer );
            if (!m_DC)
                throw CWGLException( this, "::CFrameBuffer() : Failed to get P-buffer DC." );

            m_Context = wglCreateContext( m_DC );
            if (!m_Context)
                throw CWGLException( this, "::CFrameBuffer() : Failed to create rendering context." );
            if (!wglMakeCurrent( m_DC, m_Context ))
                throw CWGLException( this, "::CFrameBuffer() : Failed to make rendering context current." );
            if (!wglShareLists( PrevContext, m_Context ))
                throw CWGLException( this, "::CFrameBuffer() : Failed to share lists between multiple rendering contexts." );
        }
        catch (const Sys::CException& Ex) 
        {
            if (m_Context) 
            {
				wglMakeCurrent( m_DC, NULL );
				wglDeleteContext( m_Context );	
			}

            if (m_DC)
                wglReleasePbufferDCARB( m_Pbuffer, m_DC );
            if (m_Pbuffer)
                wglDestroyPbufferARB( m_Pbuffer );
       
			wglMakeCurrent( PrevDC, PrevContext );

            m_DC = NULL;
            m_Context = NULL;
            m_Pbuffer = NULL;

            throw Ex;
        }
    #elif defined (__linux__)
        
    //
    // TODO:
    //

    #endif // _WIN32

        glEnable( GL_DEPTH_TEST );
        glDepthFunc( GL_LESS );
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );
    }

    //
    // Destructor
    //
    CFrameBuffer::~CFrameBuffer()
    {
    #ifdef _WIN32
        if (wglGetCurrentContext() == m_Context)
			wglMakeCurrent( m_DC, NULL );
		wglDeleteContext( m_Context );

        wglReleasePbufferDCARB( m_Pbuffer, m_DC );
        wglDestroyPbufferARB( m_Pbuffer );
    #elif defined (__linux__)

        //

    #endif // _WIN32
    }

    /*
    //
    // GetWidth
    //
    GLsizei CFrameBuffer::GetWidth() const 
    {
        int Width;

    #ifdef _WIN32
        wglQueryPbufferARB( m_Pbuffer, WGL_PBUFFER_WIDTH_ARB, &Width );
    #elif defined (__linux__)
        //
    #endif // _WIN32
        return static_cast<GLsizei>( Width );
    }

    //
    // GetHeight
    //
    GLsizei CFrameBuffer::GetHeight() const 
    { 
        int Height;

    #ifdef _WIN32
        wglQueryPbufferARB( m_Pbuffer, WGL_PBUFFER_HEIGHT_ARB, &Height );
    #elif defined (__linux__)
        //
    #endif // _WIN32
        return static_cast<GLsizei>( Height );
    }
    */

    //
    // IsLost
    //
    bool CFrameBuffer::IsLost() const
    {
        int Lost;

    #ifdef _WIN32
        wglQueryPbufferARB( m_Pbuffer, WGL_PBUFFER_LOST_ARB, &Lost );
        return Lost == TRUE;
    #elif defined (__linux__)
        //
    #endif // _WIN32
	}

    //
    // GetCaps
    //
    void CFrameBuffer::GetCaps( 
                               TCaps *Caps 
                               ) const
	{
        int Values[ 3 ];

    #ifdef _WIN32
		const int Attribs[ 3 ] = 
        {
			WGL_MAX_PBUFFER_PIXELS_ARB,
			WGL_MAX_PBUFFER_WIDTH_ARB,
			WGL_MAX_PBUFFER_HEIGHT_ARB
		};

        wglGetPixelFormatAttribivARB( m_DC, m_PixelFormat, 0, 3, Attribs, Values );
    #elif defined (__linux__)
        //
    #endif // _WIN32

        Caps->MaxPixels = Values[ 0 ];
		Caps->MaxWidth = Values[ 1 ];
		Caps->MaxHeight = Values[ 2 ];
	}

    //
    // SetTexture1D
    //
    void CFrameBuffer::SetTexture1D( 
                                    GLenum Attachment, GLint MipLevel, Ptr<CTexture1D> Texture 
                                    )
    {
        if (Attachment != GL_FRONT && Attachment != GL_BACK && (Attachment < GL_AUX0 || Attachment > GL_AUX3))
            throw Sys::CDeveloperException( this, "::SetTexture1D() : Invalid <Attachment> parameter." );

        if (!Texture)
        {
            m_DrawBuffers.erase( Attachment );
            m_Attachments.erase( Attachment );
        }
        else 
        {
            TAttachmentState State;

            State.Texture = Texture;
            State.MipLevel = MipLevel;

            m_DrawBuffers.insert( Attachment );
			m_Attachments[ Attachment ] = State;
        }
    }

    //
    // SetTexture2D
    //
    void CFrameBuffer::SetTexture2D( 
                                    GLenum Attachment, GLint MipLevel, Ptr<CTexture2D> Texture 
                                    )
    {
        if (Attachment != GL_FRONT && Attachment != GL_BACK && (Attachment < GL_AUX0 || Attachment > GL_AUX3))
            throw Sys::CDeveloperException( this, "::SetTexture2D() : Invalid <Attachment> parameter." );

        if (!Texture)
        {
            m_DrawBuffers.erase( Attachment );
            m_Attachments.erase( Attachment );
        }
        else 
        {
            TAttachmentState State;

            State.Texture = Texture;
            State.MipLevel = MipLevel;

            m_DrawBuffers.insert( Attachment );
			m_Attachments[ Attachment ] = State;
        }
    }
    
    //
    // SetTextureRectangle
    //
    void CFrameBuffer::SetTextureRectangle( 
                                           GLenum Attachment, Ptr<CTextureRectangle> Texture 
                                           )
    {
        if (Attachment != GL_FRONT && Attachment != GL_BACK && (Attachment < GL_AUX0 || Attachment > GL_AUX3))
            throw Sys::CDeveloperException( this, "::SetTextureRectangle() : Invalid <Attachment> parameter." );

        if (!Texture)
        {
            m_DrawBuffers.erase( Attachment );
            m_Attachments.erase( Attachment );
        }
        else 
        {
            TAttachmentState State;

            State.Texture = Texture;
            State.MipLevel = 0;

            m_DrawBuffers.insert( Attachment );
			m_Attachments[ Attachment ] = State;
        }
    }

    //
    // SetTexture3D
    //
    void CFrameBuffer::SetTexture3D( 
                                    GLenum Attachment, GLint MipLevel, GLint zOffset, Ptr<CTexture3D> Texture
                                    )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetTexture3D() : This method is not implemented, and should not be used." );
    }

    //
    // SetTextureCubeMap
    //
    void CFrameBuffer::SetTextureCubeMap( 
                                         GLenum Attachment, GLenum Face, GLint MipLevel, Ptr<CTextureCubeMap> Texture
                                         )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetTextureCubeMap() : This method is not implemented, and should not be used." );
    }

    //
    // CheckStatus
    //
    void CFrameBuffer::CheckStatus() const
    {
        // TODO: Additional checks here?
    }

    //
    // Present
    //
    void CFrameBuffer::Present() const
    {
    #ifdef _DEBUG
        if (!m_Current)
        {
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL,
                "::Present() : Framebuffer must be bound to pipeline." );
        }
    #endif

    #ifdef _DEBUG
        glClearErrors();
    #endif

        for (CONST_MAP_ITERATION( GLenum, TAttachmentState, m_Attachments, i ))
        {
            Ptr<CTexture> Texture = i->second.Texture;

            glActiveTexture( GL_TEXTURE0 );     
            glReadBuffer( i->first );

            switch (Texture->m_Target) 
            {
            case GL_TEXTURE_1D:
                glBindTexture( GL_TEXTURE_1D, Texture->m_Texture );
                glCopyTexSubImage1D( GL_TEXTURE_1D, i->second.MipLevel, 0, 0, 0, m_Width );
                break;
            case GL_TEXTURE_2D:
            case GL_TEXTURE_RECTANGLE_ARB:
                glBindTexture( Texture->m_Target, Texture->m_Texture );
                glCopyTexSubImage2D( Texture->m_Target, i->second.MipLevel, 0, 0, 0, 0, m_Width, m_Height );
                break;
            case GL_TEXTURE_3D:
                // TODO:
                break;
            }
        }

    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Present() : An OpenGL error has occured." );
    #endif
    }

    //
    // SwapBuffers
    //
    void CFrameBuffer::SwapBuffers() const
    {
    #ifdef _WIN32
        if (!wglSwapLayerBuffers( m_DC, WGL_SWAP_MAIN_PLANE ))
            throw CWGLException( this, "::SwapBuffers() : Failed to swap buffers." );
    #elif defined (__linux__)
        glXSwapBuffers( m_Display, m_Drawable );
    #endif
    }

    //
    // ChoosePixelFormat
    //
    void CFrameBuffer::ChoosePixelFormat( 
                                         GLenum ColorFormat, GLenum DepthStencilFormat, 
                                         TPixelFormatDesc *Desc
                                         ) const
    {
        memset( Desc, 0, sizeof( TPixelFormatDesc ) );

        Desc->PixelType = PT_INTEGER;

        switch (ColorFormat)
        {
        case GL_ALPHA:
        case GL_ALPHA8:
            Desc->AlphaBitsCount = 8;
            break;
        case GL_RGBA:
        case GL_RGBA8:
            Desc->AlphaBitsCount = 8;
        case GL_RGB:
        case GL_RGB8:
            Desc->RedBitsCount = 8;
            Desc->GreenBitsCount = 8;
            Desc->BlueBitsCount = 8;
            break;
        case GL_RGBA16F_ARB:
            Desc->AlphaBitsCount = 16;
        case GL_RGB16F_ARB:
            Desc->RedBitsCount = 16;
            Desc->GreenBitsCount = 16;
            Desc->BlueBitsCount = 16;
            Desc->PixelType = PT_FLOAT;
            break;
        case GL_RGBA32F_ARB:
            Desc->AlphaBitsCount = 32;
        case GL_RGB32F_ARB:
            Desc->RedBitsCount = 32;
            Desc->GreenBitsCount = 32;
            Desc->BlueBitsCount = 32;
            Desc->PixelType = PT_FLOAT;
            break;
        default:
            throw Sys::CDeveloperException( this, "::ChoosePixelFormat() : Unknown <ColorFormat> parameter.\nFIXME." );
        }

        switch (DepthStencilFormat)
        {
        case GL_DEPTH_COMPONENT16:
            Desc->DepthBitsCount = 16;
            break;
        case GL_DEPTH_COMPONENT24:
            Desc->DepthBitsCount = 24;
            break;
        case GL_DEPTH_COMPONENT32:
            Desc->DepthBitsCount = 32;
            break;
        case GL_DEPTH_STENCIL_EXT:
        case GL_DEPTH24_STENCIL8_EXT:
            Desc->DepthBitsCount = 24;
            Desc->StencilBitsCount = 8;
            break;
        default:
            throw Sys::CDeveloperException( this, "::ChoosePixelFormat() : Unknown <DepthStencilFormat> parameter.\nFIXME." );
        }
    }

    //
    // Set
    //
    void CFrameBuffer::Set() const
    {
    #ifdef _WIN32
        if (!wglMakeCurrent( m_DC, m_Context ))
            throw CWGLException( this, "::Set() : Failed to make rendering context current." );
    #elif defined (__linux__)
        //
    #endif // _WIN32

        glViewport( 0, 0, m_Width, m_Height );
    }
}