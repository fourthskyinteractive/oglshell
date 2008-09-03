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

// Τΰιλ: /GL/GL/FrameBufferObject.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "FrameBuffer.h"
#include "Extensions.h"
#include "Texture.h"

namespace GL
{
    //
    // Constructor
    //
    CFrameBufferObject::CFrameBufferObject( 
                                           GLenum Target, GLsizei Width, GLsizei Height 
                                           ):
        IFrameBuffer( FBT_FRAMEBUFFER_OBJECT, Width, Height ),

        m_Framebuffer( 0 ),
        m_Target( Target ),
        m_Width( Width ),
        m_Height( Height )
    {
        if (!m_Extensions->EXT_framebuffer_object)
        {
            throw CExtensionException( this, "::CFrameBufferObject()", "GL_EXT_framebuffer_object." );
        }

        switch (m_Target) 
        {
        case GL_FRAMEBUFFER_EXT:
            break;
        case GL_READ_FRAMEBUFFER_EXT:
        case GL_DRAW_FRAMEBUFFER_EXT:
            if (!m_Extensions->EXT_framebuffer_blit)
                throw CExtensionException( this, "::CFrameBufferObject()", "GL_EXT_framebuffer_blit." );
            break;

        default:
            throw Sys::CDeveloperException( this, "::CFrameBufferObject() : Invalid <Target> parameter." );
        }

        if (Width < 1)
            throw Sys::CDeveloperException( this, "::CFrameBufferObject() : Invalid <Width> parameter." );
        if (Height < 1)
            throw Sys::CDeveloperException( this, "::CFrameBufferObject() : Invalid <Height> parameter." );

        glGenFramebuffersEXT( 1, &m_Framebuffer );
        glBindFramebufferEXT( m_Target, m_Framebuffer );    
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
        {
            glBindFramebufferEXT( m_Target, 0 );
            glDeleteFramebuffersEXT( 1, &m_Framebuffer );

            throw CException( this, Error, "::CFrameBufferObject() : Failed to create framebuffer object." );
        }
    }
                     
    //
    // Destructor
    //
    CFrameBufferObject::~CFrameBufferObject()
    {
        glClearErrors();
        glDeleteFramebuffersEXT( 1, &m_Framebuffer );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CFrameBufferObject() : Failed to delete framebuffer object." );
    }

    //
    // EnumColorBufferFormats 
    //
    void CFrameBufferObject::EnumColorBufferFormats( 
                                                    vector<CInternalFormat> *Formats 
                                                    )
    {
        throw Sys::CDeveloperException( "GL::CFrameBufferObject", Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::EnumColorBufferFormats() : This method is not implemented, and should not be used." );
    }

    //
    // SetTexture1D
    //
    void CFrameBufferObject::SetTexture1D( 
                                          GLenum Attachment, GLint MipLevel, Ptr<CTexture1D> Texture 
                                          )
    {
		if (Attachment < GL_COLOR_ATTACHMENT0_EXT || Attachment > GL_DEPTH_ATTACHMENT_EXT)
            throw Sys::CDeveloperException( this, "::SetTexture1D() : Invalid <Attachment> parameter." );

        glClearErrors();
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glFramebufferTexture1DEXT( m_Target, Attachment, GL_TEXTURE_1D, Texture ? Texture->m_Texture : 0, MipLevel );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::SetTexture1D() : An OpenGL error has occured." );

        SetTextureAttachment( Attachment, Texture );
    }

    //
    // SetTexture2D
    //
    void CFrameBufferObject::SetTexture2D( 
                                          GLenum Attachment, GLint MipLevel, Ptr<CTexture2D> Texture 
                                          )
    {
        if (Attachment < GL_COLOR_ATTACHMENT0_EXT || Attachment > GL_DEPTH_ATTACHMENT_EXT)
            throw Sys::CDeveloperException( this, "::SetTexture2D() : Invalid <Attachment> parameter." );

        glClearErrors();
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glFramebufferTexture2DEXT( m_Target, Attachment, GL_TEXTURE_2D, Texture ? Texture->m_Texture : 0, MipLevel );   
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::SetTexture2D() : An OpenGL error has occured." );

        SetTextureAttachment( Attachment, Texture );
    }

    //
    // SetTextureRectangle 
    //
    void CFrameBufferObject::SetTextureRectangle( 
                                                 GLenum Attachment, Ptr<CTextureRectangle> Texture
                                                 )
    {
        if (Attachment < GL_COLOR_ATTACHMENT0_EXT || Attachment > GL_DEPTH_ATTACHMENT_EXT)
            throw Sys::CDeveloperException( this, "::SetTextureRectangle() : Invalid <Attachment> parameter." );

        glClearErrors();
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glFramebufferTexture2DEXT( m_Target, Attachment, GL_TEXTURE_RECTANGLE_ARB, Texture ? Texture->m_Texture : 0, 0 );      
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::SetTextureRectangle() : An OpenGL error has occured." );

        SetTextureAttachment( Attachment, Texture );
    }

    //
    // SetTexture3D 
    //
    void CFrameBufferObject::SetTexture3D( 
                                          GLenum Attachment, GLint MipLevel, GLint zOffset, Ptr<CTexture3D> Texture 
                                          )
    {
		if (Attachment < GL_COLOR_ATTACHMENT0_EXT || Attachment > GL_DEPTH_ATTACHMENT_EXT)
            throw Sys::CDeveloperException( this, "::SetTexture3D() : Invalid <Attachment> parameter." );

        glClearErrors();
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glFramebufferTexture3DEXT( m_Target, Attachment, GL_TEXTURE_3D, Texture ? Texture->m_Texture : 0, MipLevel, zOffset );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::SetTexture3D() : An OpenGL error has occured." );

        SetTextureAttachment( Attachment, Texture );
    }

    //
    // SetTextureCubeMap 
    //
    void CFrameBufferObject::SetTextureCubeMap( 
                                               GLenum Attachment, GLenum Face, GLint MipLevel, Ptr<CTextureCubeMap> Texture 
                                               )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetTextureCubeMap() : This method is not implemented, and should not be used." );
    }

    //
    // SetRenderBuffer 
    //
    void CFrameBufferObject::SetRenderBuffer( 
                                             GLenum Attachment, Ptr<CRenderBuffer> Buffer 
                                             )
    {
        if (Attachment < GL_COLOR_ATTACHMENT0_EXT || Attachment > GL_STENCIL_ATTACHMENT_EXT)
            throw Sys::CDeveloperException( this, "::SetRenderBuffer() : Invalid <Attachment> parameter." );

        glClearErrors(); 
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glFramebufferRenderbufferEXT( m_Target, Attachment, GL_RENDERBUFFER_EXT, Buffer ? Buffer->m_Renderbuffer : 0 ); 
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::SetRenderBuffer() : An OpenGL error has occured." );
        
        if (Attachment <= GL_COLOR_ATTACHMENT15_EXT) 
        {
            if (!Buffer)
                m_DrawBuffers.erase( Attachment );
            else
                m_DrawBuffers.insert( Attachment );
        }

        if (Attachment <= GL_COLOR_ATTACHMENT15_EXT)
            m_Buffers[ Attachment - GL_COLOR_ATTACHMENT0_EXT ] = Buffer; // 0..15
        else 
        {
            if (Attachment == GL_DEPTH_ATTACHMENT_EXT)
                m_Buffers[ 16 ] = Buffer;
            else if (Attachment == GL_STENCIL_ATTACHMENT_EXT)
                m_Buffers[ 17 ] = Buffer;
        } 
    }

    //
    // CheckStatus 
    //
    void CFrameBufferObject::CheckStatus() const
    {      
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        if (m_DrawBuffers.size() == 0) 
        {
            glDrawBuffer( GL_NONE );
            glReadBuffer( GL_NONE );
        }

        GLenum Status = glCheckFramebufferStatusEXT( m_Target );
        switch (Status) 
        {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            // Success.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_FORMATS\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n::CheckStatus() : Incomplete framebuffer." );
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_UNSUPPORTED\n::CheckStatus() : Unsupported framebuffer." );
        // GL_EXT_framebuffer_multisample
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
            throw Sys::CException( this, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n::CheckStatus() : Incomplete framebuffer." );

        default:
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_ENUM,
                "::CheckStatus() : Unknown framebuffer status." );
        }
    }

    //
    // Present 
    //
    void CFrameBufferObject::Present() const
	{
    #ifdef _DEBUG
        if (!m_Current)
        {
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL,
                "::Present() : Framebuffer must be bound to pipeline." );
        }
    #endif
	}

    //
    // SwapBuffers 
    //
    void CFrameBufferObject::SwapBuffers() const
	{
	}

    //
    // SetTextureAttachment 
    //
    void CFrameBufferObject::SetTextureAttachment( 
                                                  GLenum Attachment, Ptr<CTexture> Texture 
                                                  )
    {
        if (Attachment <= GL_COLOR_ATTACHMENT15_EXT) 
        {
            if (!Texture)
                m_DrawBuffers.erase( Attachment );
            else
                m_DrawBuffers.insert( Attachment );
        }

        if (Attachment <= GL_COLOR_ATTACHMENT15_EXT)
            m_Textures[ Attachment - GL_COLOR_ATTACHMENT0_EXT ] = Texture; // 0..15
        else 
        {
            if (Attachment == GL_DEPTH_ATTACHMENT_EXT)
                m_Textures[ 16 ] = Texture;
            else if (Attachment == GL_STENCIL_ATTACHMENT_EXT)
                m_Textures[ 17 ] = Texture;
        }
    }

    //
    // Set
    //
    void CFrameBufferObject::Set() const
    {
        glBindFramebufferEXT( m_Target, m_Framebuffer );
        glViewport( 0, 0, m_Width, m_Height );
    }

    //
    // Constructor
    //
    CRenderBuffer::TDesc::TDesc():
        RedSize( 0 ),
        GreenSize( 0 ),
        BlueSize( 0 ),
        AlphaSize( 0 ),
        DepthSize( 0 ),
        StencilSize( 0 )
    {
    }

    //
    // Constructor 
    //
    CRenderBuffer::CRenderBuffer( 
                                 GLenum InternalFormat, GLubyte Samples, GLsizei Width, GLsizei Height 
                                 ):
        m_Renderbuffer( 0 )
    {
        if (!m_Extensions->EXT_framebuffer_object)
            throw CExtensionException( this, "::CRenderBuffer()", "GL_EXT_framebuffer_object." );
        if (Samples > 0 && !m_Extensions->EXT_framebuffer_multisample)
            throw CExtensionException( this, "::CRenderBuffer()", "GL_EXT_framebuffer_multisample." );

        glGenRenderbuffersEXT( 1, &m_Renderbuffer );
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        if (Samples == 0)
            glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, InternalFormat, Width, Height );
        else
            glRenderbufferStorageMultisampleEXT( GL_RENDERBUFFER_EXT, Samples, InternalFormat, Width, Height );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
        {
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
            glDeleteRenderbuffersEXT( 1, &m_Renderbuffer );

            throw CException( this, Error, "::CRenderBuffer() : Failed to create renderbuffer." );
        }
    }

    //
    // Destructor 
    //
    CRenderBuffer::~CRenderBuffer()
    {
        glDeleteRenderbuffersEXT( 1, &m_Renderbuffer );
    }

    //
    // EnumInternalFormats 
    //
    void CRenderBuffer::EnumInternalFormats( 
                                            EEnumFormatType EnumType, vector<CInternalFormat> *Formats
                                            )
    {
        if (!m_Extensions->EXT_framebuffer_object)
            throw CExtensionException( "GL::CRenderBuffer", "::CRenderBuffer()", "GL_EXT_framebuffer_object." );
        if (EnumType == EFT_MULTISAMPLE_FORMATS && !m_Extensions->EXT_framebuffer_multisample)
            throw CExtensionException( "GL::CRenderBuffer", "::CRenderBuffer()", "GL_EXT_framebuffer_multisample." );

        Formats->clear();

        GLuint Renderbuffer;

        glClearErrors();
        glGenRenderbuffersEXT( 1, &Renderbuffer );
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, Renderbuffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
        {
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
            glDeleteRenderbuffersEXT( 1, &Renderbuffer );

            throw CException( "GL::CRenderBuffer", Error, "::EnumInternalFormats() : Failed to create renderbuffer." );
        }
    
        for (int i = 0; m_InternalFormats[i].GetSizedFormat() != GL_NONE; ++i) 
        {
            if (EnumType == EFT_FORMATS)
                glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, m_InternalFormats[ i ].GetSizedFormat(), 32, 32 );
            else // EFT_MULTISAMPLE_FORMATS
                glRenderbufferStorageMultisampleEXT( GL_RENDERBUFFER_EXT, 2, m_InternalFormats[ i ].GetSizedFormat(), 32, 32 );
            if (glGetError() == GL_NO_ERROR) 
            {
                GLint InternalFormat;
                glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_INTERNAL_FORMAT_EXT, &InternalFormat );
                if (InternalFormat == m_InternalFormats[i].GetSizedFormat())
                    Formats->push_back( m_InternalFormats[i] );
            }
        }
   
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
        glDeleteRenderbuffersEXT( 1, &Renderbuffer );

        if (!Formats->size())
            throw Sys::CException( 0, "GL::CRenderBuffer", "::EnumInternalFormats() : Supported formats are not found." );
    }

    //
    // EnumSampleCounts
    //
    void CRenderBuffer::EnumSampleCounts( 
                                         GLenum InternalFormat, vector<GLsizei> *SampleCounts
                                         )
    {
        const int MAX_SAMPLES = 16;

        if (!m_Extensions->EXT_framebuffer_multisample)
            throw CExtensionException( "GL::CRenderBuffer", "::EnumSampleCounts()", "GL_EXT_framebuffer_multisample." );

        SampleCounts->clear();

        GLuint Renderbuffer;

        glClearErrors();
        glGenRenderbuffersEXT( 1, &Renderbuffer );
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, Renderbuffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
        {
            glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
            glDeleteRenderbuffersEXT( 1, &Renderbuffer );

            throw CException( "GL::CRenderBuffer", Error, "::EnumSampleCounts() : Failed to create renderbuffer." );
        }
    
        for (int i = 0; i <= MAX_SAMPLES; ++i) 
        {
            glRenderbufferStorageMultisampleEXT( GL_RENDERBUFFER_EXT, i, InternalFormat, 32, 32 );
            if (glGetError() == GL_NO_ERROR) 
            {
                GLint Samples = 0;
                glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_SAMPLES_EXT, &Samples );
                if (i == Samples)
                    SampleCounts->push_back( Samples );
            }
        }

        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
        glDeleteRenderbuffersEXT( 1, &Renderbuffer );
        if (SampleCounts->size() == 0)
            throw Sys::CException( 0, "GL::CRenderBuffer", "::EnumSampleCounts() : Supported multisample formats are not found." );
    }

    //
    // GetWidth 
    //
    GLsizei CRenderBuffer::GetWidth() const
    {
        glClearErrors();
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        GLint Width;
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_WIDTH_EXT, &Width );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWidth() : An OpenGL error has occured." );

        return Width;
    }

    //
    // GetHeight 
    //
    GLsizei CRenderBuffer::GetHeight() const
    {
        glClearErrors();
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        GLint Height;
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_HEIGHT_EXT, &Height );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetHeight() : An OpenGL error has occured." );

        return Height;
    }

    //
    // GetInternalFormat
    //
    GLenum CRenderBuffer::GetInternalFormat() const
    {
        glClearErrors();
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        GLint InternalFormat;
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_INTERNAL_FORMAT_EXT, &InternalFormat );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetInternalFormat() : An OpenGL error has occured." );

        return InternalFormat;
    }

    //
    // GetSampleCount
    //
    GLsizei CRenderBuffer::GetSampleCount() const
    {
        if (!m_Extensions->EXT_framebuffer_multisample)
            return 0;

        glClearErrors();
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        GLint Samples;
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_SAMPLES_EXT, &Samples );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetSampleCount() : An OpenGL error has occured." );

        return Samples;
    }

    //
    // GetDesc 
    //
    void CRenderBuffer::GetDesc( 
                                TDesc *Desc 
                                ) const
    {
        glClearErrors();
        glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_Renderbuffer );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_RED_SIZE_EXT, &Desc->RedSize );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_BLUE_SIZE_EXT, &Desc->BlueSize );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_GREEN_SIZE_EXT, &Desc->GreenSize );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_ALPHA_SIZE_EXT, &Desc->AlphaSize );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_DEPTH_SIZE_EXT, &Desc->DepthSize );
        glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_STENCIL_SIZE_EXT, &Desc->StencilSize );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetDesc() : An OpenGL error has occured." );
    }
} 