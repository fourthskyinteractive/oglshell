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

// Файл: /GL/GL/RenderDevice.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_RENDER_DEVICE_H__
#define __GL_RENDER_DEVICE_H__

namespace GL
{
    //  Базовый класс RenderDevice.

    class DLLAPI CRenderDevice : public IRenderDevice
    {
    protected:
                            CRenderDevice               ();

    public:

        //
        // Interface
        //

        void                GetFrameBuffer              ( Ptr<IFrameBuffer> *FrameBuffer ) const;

        void                GetTexture                  ( GLenum Unit, Ptr<const CTexture> *Texture ) const;
        void                GetShadingProgram           ( Ptr<const IShadingProgram> *Program ) const;
        
        void                GetVertexStructure          ( Ptr<const CVertexStructure> *Struct ) const;
        void                GetVertexBuffer             ( GLuint StreamIndex, Ptr<const CBuffer> *Buffer ) const;
        void                GetIndexBuffer              ( Ptr<const CBuffer> *Buffer ) const;
        void                GetPackPixelBuffer          ( Ptr<CBuffer> *Buffer ) const;
        void                GetUnpackPixelBuffer        ( Ptr<const CBuffer> *Buffer ) const;
        void                GetTransformFeedbackBuffer  ( Ptr<CBuffer> *Buffer ) const;

    protected:
        GLsizei             GetIndexSize                ( GLenum IndexType ) const;

        bool                IsDeprecatedTopology        ( GLenum Mode ) const;
        bool                IsSupportedTopology         ( GLenum Mode ) const;
        const char*         ToString                    ( GLenum Mode ) const;
        bool                IsVertexBufferBound         () const;

        //
        // Class members
        //

    __M(
        m_FrameBuffer,      Ptr<IFrameBuffer>,
        m_Program,          Ptr<const IShadingProgram>,
        m_VertexStruct,     Ptr<const CVertexStructure>,        
		m_IndexBuffer,      Ptr<const CBuffer>,          
		m_IndexType,        GLenum,  
        m_IndexSize,        GLsizei,                     
        m_PackBuffer,       Ptr<CBuffer>,
		m_UnpackBuffer,     Ptr<const CBuffer>,          	
        m_FeedbackBuffer,   Ptr<CBuffer>                
        );

    #ifdef CG_SDK
    __M(
        m_APIType,          IShadingProgram::EShaderAPI
        );
    #endif 

        Ptr<const CTexture> m_Textures[ MAX_TEXTURES ];
        Ptr<const CBuffer>  m_VertexBuffers[ MAX_VERTEX_STREAMS ];
    };

    //  Debug-версия класса.
    //  Проверяются доступные расширения OpenGL, входные параметры, топология примитивов, ошибки OpenGL.

    class CRenderDeviceDebug : public CRenderDevice
    {
    public:

        //
        // RTTI
        //

        virtual string      GetClassName                () const { return "GL::CRenderDeviceDebug"; }

        //
        // Interface
        //

        virtual void        SetFrameBuffer              ( Ptr<IFrameBuffer> FrameBuffer );
        virtual void        Blit                        ( Ptr<CFrameBufferObject> DestFrameBuffer, Ptr<const CFrameBufferObject> SrcFrameBuffer, 
                                                            GLbitfield Mask, GLenum Filter ) const;
        virtual void        CopyDepthStencilToColor     ( GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum Type ) const;
        virtual void        CopyPixels                  ( GLint x, GLint y, GLsizei Width, GLsizei Height, 
                                                            GLenum InputFormat, GLenum OutputFormat, GLenum Type, Ptr<CBuffer> Buffer ) const;

                            // Данный метод предназначен только для FFP. Вместо него используйте методы класса ISamplerUniform.
        virtual void        SetTexture                  ( GLenum Unit, Ptr<const CTexture> Texture );
        virtual void        SetShadingProgram           ( Ptr<const IShadingProgram> Program );

        virtual void        SetVertexStructure          ( Ptr<const CVertexStructure> Struct );
        virtual void        SetVertexBuffer             ( GLuint StreamIndex, Ptr<const CBuffer> Buffer, GLintptr Offset, GLsizei Stride );
        virtual void        SetIndexBuffer              ( Ptr<const CIndexBuffer> Buffer );
        virtual void        SetIndexBuffer              ( Ptr<const CBuffer> Buffer, GLenum IndexType ); 
        virtual void        SetPackPixelBuffer          ( Ptr<CBuffer> Buffer );
		virtual void        SetUnpackPixelBuffer        ( Ptr<const CBuffer> Buffer );
        virtual void        SetTransformFeedbackBuffer  ( GLuint Index, Ptr<CBuffer> Buffer, GLintptr Offset, GLsizeiptr Size );

                            // В случае, если доступно только расширение GL_NVX_conditional_render, параметр Mode не используется.
        virtual void        BeginConditionalRender      ( Ptr<const CQuery> Query, GLenum Mode );
        virtual void        EndConditionalRender        ();
        virtual void        BeginTransformFeedback      ( GLenum Mode );
        virtual void        EndTransformFeedback        ();

        virtual void        DrawArrays                  ( GLenum Mode, GLint First, GLsizei Count ) const;
        virtual void        DrawArraysInstanced         ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const;
        virtual void        DrawElements                ( GLenum Mode, GLint First, GLsizei Count ) const;
        virtual void        DrawElementsInstanced       ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const;
        virtual void        DrawRangeElements           ( GLenum Mode, GLint First, GLuint Start, GLuint End, 
                                                            GLsizei Count ) const;
    };

    //  Release-версия класса.
    //  Проверяются расширения OpenGL для исключения вызова функции по несуществующему адресу.

    class DLLAPI CRenderDeviceRelease : public CRenderDevice
    {
    public:

        //
        // RTTI
        //

        virtual string      GetClassName                () const { return "GL::CRenderDeviceRelease"; }

        //
        // Interface
        //

        virtual void        SetFrameBuffer              ( Ptr<IFrameBuffer> FrameBuffer );
        virtual void        Blit                        ( Ptr<CFrameBufferObject> DestFrameBuffer, Ptr<const CFrameBufferObject> SrcFrameBuffer, 
                                                            GLbitfield Mask, GLenum Filter ) const;
        virtual void        CopyDepthStencilToColor     ( GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum Type ) const;
        virtual void        CopyPixels                  ( GLint x, GLint y, GLsizei Width, GLsizei Height, 
                                                            GLenum InputFormat, GLenum OutputFormat, GLenum Type, Ptr<CBuffer> Buffer ) const;

                            // Данный метод предназначен только для FFP. Вместо него используйте методы класса ISamplerUniform.
        virtual void        SetTexture                  ( GLenum Unit, Ptr<const CTexture> Texture );
        virtual void        SetShadingProgram           ( Ptr<const IShadingProgram> Program );

        virtual void        SetVertexStructure          ( Ptr<const CVertexStructure> Struct );
        virtual void        SetVertexBuffer             ( GLuint StreamIndex, Ptr<const CBuffer> Buffer, GLintptr Offset, GLsizei Stride );
        virtual void        SetIndexBuffer              ( Ptr<const CIndexBuffer> Buffer );
        virtual void        SetIndexBuffer              ( Ptr<const CBuffer> Buffer, GLenum IndexType ); 
        virtual void        SetPackPixelBuffer          ( Ptr<CBuffer> Buffer );
		virtual void        SetUnpackPixelBuffer        ( Ptr<const CBuffer> Buffer );
        virtual void        SetTransformFeedbackBuffer  ( GLuint Index, Ptr<CBuffer> Buffer, GLintptr Offset, GLsizeiptr Size );

                            // В случае, если доступно только расширение GL_NVX_conditional_render, параметр Mode не используется.
        virtual void        BeginConditionalRender      ( Ptr<const CQuery> Query, GLenum Mode );
        virtual void        EndConditionalRender        ();
        virtual void        BeginTransformFeedback      ( GLenum Mode );
        virtual void        EndTransformFeedback        ();

        virtual void        DrawArrays                  ( GLenum Mode, GLint First, GLsizei Count ) const;
        virtual void        DrawArraysInstanced         ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const;
        virtual void        DrawElements                ( GLenum Mode, GLint First, GLsizei Count ) const;
        virtual void        DrawElementsInstanced       ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const;
        virtual void        DrawRangeElements           ( GLenum Mode, GLint First, GLuint Start, GLuint End, 
                                                            GLsizei Count ) const;
    };
}

#endif // __GL_RENDER_DEVICE_H__