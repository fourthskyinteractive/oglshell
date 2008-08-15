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

// Файл: /GL/FrameBuffer.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_FRAME_BUFFER_H__												
#define __GL_FRAME_BUFFER_H__

namespace GL
{
	//  Буфер кадра, предоставляемый оконной системой (WGL/GLX/AGL).

	class DLLAPI CFrameBuffer : public IFrameBuffer
	{
    public:
        struct DLLAPI TCaps
        {
                                TCaps           ();

            GLint               MaxWidth;
            GLint               MaxHeight;
            GLint               MaxPixels;
        };

    private:
        enum EPixelType
        {
            PT_INTEGER = 0,
            PT_FLOAT
        };

        struct TPixelFormatDesc
        {
            EPixelType          PixelType;

            GLubyte             NumColorBits;
            GLubyte             NumRedBits;
            GLubyte             NumGreenBits;
            GLubyte             NumBlueBits;
            GLubyte             NumAlphaBits;
            GLubyte             NumDepthBits;
            GLubyte             NumStencilBits;
        };

		struct TAttachmentState
        {
            Ptr<CTexture>       Texture;
            GLint               MipLevel;
        };

	public:
                            CFrameBuffer        ( GLenum ColorFormat, GLenum DepthStencilFormat, GLuint NumSamples, GLuint NumAuxBuffers, ELayerType LayerType, GLsizei Width, GLsizei Height );
                            ~CFrameBuffer       ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CFrameBuffer"; }

        //
        // Interface
        //

    #ifdef _WIN32    
        bool                IsLost              () const;
    #endif
        void                GetCaps             ( TCaps *Caps ) const;

        virtual void        Present             () const;
        virtual void        SwapBuffers         () const;

        //
        // Color attachments
        //

		virtual void        SetTexture1D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture1D> Texture );
        virtual void        SetTexture2D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture2D> Texture ); 
        virtual void        SetTextureRectangle ( GLenum Attachment, Ptr<CTextureRectangle> Texture );
        virtual void        SetTexture3D        ( GLenum Attachment, GLint MipLevel, GLint zOffset, Ptr<CTexture3D> Texture );
        virtual void        SetTextureCubeMap   ( GLenum Attachment, GLenum Face, GLint MipLevel, Ptr<CTextureCubeMap> Texture );

        virtual void        CheckStatus         () const;
        
    private:
        void                ChoosePixelFormat   ( GLenum ColorFormat, GLenum DepthStencilFormat, TPixelFormatDesc *Desc ) const;

        virtual void        Set                 () const;

        //
        // Class members
        //

    #ifdef _WIN32
        HDC                 m_DC;
        HGLRC               m_Context;
        int                 m_PixelFormat;

        HPBUFFERARB         m_Pbuffer;
    #elif defined (__linux__)
        Display*            m_Display; // Specifies the connection to the X server.      
        GLXContext          m_Context;
        GLXFBConfig*        m_Config;
        
        GLXDrawable         m_Drawable;
    #elif defined (MACOS_X) || defined (__APPLE__)
        // ...
    #endif // _WIN32

        map<GLenum, TAttachmentState> m_Attachments;
	};

    //  Объект буфера кадра, расширения GL_EXT_framebuffer_object, GL_EXT_framebuffer_multisample, 
    //  GL_EXT_framebuffer_blit и др.

    class DLLAPI CFrameBufferObject : public IFrameBuffer
    {     
        enum
        {
            MAX_ATTACHMENTS = 18
        };

                            // For ::Blit() method.
        friend              CRenderDeviceDebug; 
        friend              CRenderDeviceRelease; 

    public:
                            CFrameBufferObject  ( GLenum Target, GLsizei Width, GLsizei Height );
                            ~CFrameBufferObject ();
                                    
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CFrameBufferObject"; }

        //
        // Interface
        //

        static void         EnumColorBufferFormats  ( vector<CInternalFormat> *Formats );

        virtual void        Present             () const;
        virtual void        SwapBuffers         () const;

        //
        // Color/Depth/Stencil attachments
        //

        virtual void        SetTexture1D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture1D> Texture );
        virtual void        SetTexture2D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture2D> Texture ); 
        virtual void        SetTextureRectangle ( GLenum Attachment, Ptr<CTextureRectangle> Texture );
        virtual void        SetTexture3D        ( GLenum Attachment, GLint MipLevel, GLint zOffset, Ptr<CTexture3D> Texture );
        virtual void        SetTextureCubeMap   ( GLenum Attachment, GLenum Face, GLint MipLevel, Ptr<CTextureCubeMap> Texture );
        void                SetRenderBuffer     ( GLenum Attachment, Ptr<class CRenderBuffer> Buffer );

		virtual void        CheckStatus         () const;
		
    private:
        void                SetTextureAttachment( GLenum Attachment, Ptr<CTexture> Texture );
        
        virtual void        Set                 () const;

        //
        // Class members
        //

        GLuint              m_Framebuffer;
        GLenum              m_Target;
        GLsizei             m_Width;
        GLsizei             m_Height;

        Ptr<CTexture>       m_Textures[ MAX_ATTACHMENTS ];
        Ptr<CRenderBuffer>  m_Buffers[ MAX_ATTACHMENTS ]; 
    };

    //  Буфер вывода, расширение GL_EXT_framebuffer_object.

    class DLLAPI CRenderBuffer : public CObject
    {
    public:
        enum EEnumFormatType
        {
            EFT_FORMATS = 0,
            EFT_MULTISAMPLE_FORMATS
        };

        struct DLLAPI TDesc
        {
                                TDesc           ();

            GLsizei             RedSize;
            GLsizei             GreenSize;
            GLsizei             BlueSize;
            GLsizei             AlphaSize;
            GLsizei             DepthSize;
            GLsizei             StencilSize;
        };

        friend              CFrameBufferObject;

    public:
                            CRenderBuffer       ( GLenum InternalFormat, GLubyte NumSamples, GLsizei Width, GLsizei Height );
                            ~CRenderBuffer      ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CRenderBuffer"; }

        //
        // Interface
        //

        static void         EnumInternalFormats ( EEnumFormatType EnumType, vector<CInternalFormat> *Formats );
        static void         EnumSampleCounts    ( GLenum InternalFormat, vector<GLsizei> *SampleCounts );

        GLsizei             GetWidth            () const;
        GLsizei             GetHeight           () const;
        GLenum              GetInternalFormat   () const;
		GLsizei             GetSampleCount      () const;
        void                GetDesc             ( TDesc *Desc ) const;

    private:

		//
		// Class members
		//

        GLuint              m_Renderbuffer;
    };
}

#endif // __GL_FRAME_BUFFER_H__