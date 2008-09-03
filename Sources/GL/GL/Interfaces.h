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

// Файл: /GL/GL/Interfaces.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_INTERFACES_H__												
#define __GL_INTERFACES_H__

namespace GL
{
    //  Буфер кадра.
    //  Из-за наследия старого OpenGL, проблем совместимости и реализации OpenGL-драйверов ATI/AMD 
    //  буфер кадра может быть P-buffer'ом или объектом буфера кадра.
                                                                                            
    class DLLAPI IFrameBuffer : public CObject
    {
    public:
        enum EFrameBufferType
        {
            FBT_FRAMEBUFFER_OBJECT = 0,
            FBT_PBUFFER
        };

        enum ELayerType
        {
            LT_SINGLE_BUFFER = 0,
            LT_DOUBLE_BUFFER
        };

        friend              CRenderDeviceDebug; 
        friend              CRenderDeviceRelease;

    protected:
                            IFrameBuffer        ( EFrameBufferType Type, GLsizei Width, GLsizei Height );

    public:

        //
        // Interface
        //

        GLsizei             GetFrameWidth       () const;
        GLsizei             GetFrameHeight      () const;

        bool                IsCurrent           () const;

        virtual void        Present             () const = 0;
        virtual void        SwapBuffers         () const = 0; // Для Early-Z/Stencil на видеокартах NVIDIA.

        //
        // Color attachments
        //

        virtual void        SetTexture1D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture1D> Texture ) = 0;
        virtual void        SetTexture2D        ( GLenum Attachment, GLint MipLevel, Ptr<CTexture2D> Texture ) = 0; 
        virtual void        SetTextureRectangle ( GLenum Attachment, Ptr<CTextureRectangle> Texture ) = 0;
        virtual void        SetTexture3D        ( GLenum Attachment, GLint MipLevel, GLint zOffset, Ptr<CTexture3D> Texture ) = 0;
        virtual void        SetTextureCubeMap   ( GLenum Attachment, GLenum Face, GLint MipLevel, Ptr<CTextureCubeMap> Texture ) = 0;

        virtual void        CheckStatus         () const = 0;
        
    protected:
        virtual void        Set                 () const = 0;

        //
		// Class members
		//

        EFrameBufferType    m_Type;

        GLsizei             m_Width;
        GLsizei             m_Height;
        set<GLenum>         m_DrawBuffers;

        bool                m_Current;        
    };

    //  Базовый класс для всех типов юниформов (GLSL, Cg).

    class DLLAPI CBaseUniform : public CObject
    {
    public:

        //
        // Interface
        //

        const string&       GetName             () const;

    protected:
                            CBaseUniform        ( const string& Name );

        //
        // Class members
        //

        string              m_Name;
    };

    //  Юниформ.

    class DLLAPI IUniform : public CBaseUniform
    {
    public:
        enum EMatrixOrder
        {
            MO_COLUMN_MAJOR = 0,
            MO_ROW_MAJOR
        };

    public:

        //
        // Interface
        //

        const string&       GetName             () const;

        virtual void        SetBool             ( bool x ) = 0;
        virtual void        SetFloat            ( GLfloat x ) = 0;
        virtual void        SetInt              ( GLint x ) = 0;
        virtual void        SetUnsignedInt      ( GLuint x ) = 0;                                               // GL_EXT_gpu_shader4
        virtual void        SetFloat2           ( GLfloat x, GLfloat y ) = 0;
        virtual void        SetInt2             ( GLint x, GLint y ) = 0;
        virtual void        SetUnsignedInt2     ( GLuint x, GLuint y ) = 0;                                     // GL_EXT_gpu_shader4
        virtual void        SetFloat3           ( GLfloat x, GLfloat y, GLfloat z ) = 0;
        virtual void        SetInt3             ( GLint x, GLint y, GLint z ) = 0;
        virtual void        SetUnsignedInt3     ( GLuint x, GLuint y, GLuint z ) = 0;                           // GL_EXT_gpu_shader4
        virtual void        SetFloat4           ( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) = 0;
        virtual void        SetInt4             ( GLint x, GLint y, GLint z, GLint w ) = 0;
        virtual void        SetUnsignedInt4     ( GLuint x, GLuint y, GLuint z, GLuint w ) = 0;                 // GL_EXT_gpu_shader4
        
        virtual void        SetFloatArray       ( GLsizei Dimension, GLsizei Count, const GLfloat *Array ) = 0;
        virtual void        SetIntArray         ( GLsizei Dimension, GLsizei Count, const GLint *Array ) = 0;
        virtual void        SetUnsignedIntArray ( GLsizei Dimension, GLsizei Count, const GLuint *Array ) = 0;  // GL_EXT_gpu_shader4

    #ifdef MATH_LIB_INCLUDED
        virtual void        SetFloatVec2        ( const Vec2<GLfloat>& v ) = 0;
        virtual void        SetIntVec2          ( const Vec2<GLint>& v ) = 0;
        virtual void        SetUnsignedIntVec2  ( const Vec2<GLuint>& v ) = 0;                                  // GL_EXT_gpu_shader4
        virtual void        SetFloatVec3        ( const Vec3<GLfloat>& v ) = 0;
        virtual void        SetIntVec3          ( const Vec3<GLint>& v ) = 0;
        virtual void        SetUnsignedIntVec3  ( const Vec3<GLuint>& v ) = 0;                                  // GL_EXT_gpu_shader4
        virtual void        SetFloatVec4        ( const Vec4<GLfloat>& v ) = 0;
        virtual void        SetIntVec4          ( const Vec4<GLint>& v ) = 0;
        virtual void        SetUnsignedIntVec4  ( const Vec4<GLuint>& v ) = 0;                                  // GL_EXT_gpu_shader4

        virtual void        SetFloatMat2        ( const Mat2& m, EMatrixOrder Order ) = 0;
        virtual void        SetFloatMat3        ( const Mat3& m, EMatrixOrder Order ) = 0;
        virtual void        SetFloatMat4        ( const Mat4& m, EMatrixOrder Order ) = 0;
    #endif // MATH_LIB_INCLUDED

    protected:
                            IUniform            ( const string& Name );
    };

    //  Юниформ, способный делать выборку (семплинг) из текстуры.

    class DLLAPI ISamplerUniform : public CBaseUniform
    {
    public:

        //
        // Interface
        //

        virtual void        SetSampler          ( Ptr<const CTexture> Texture ) = 0;

        virtual void        EnableSampler       () const = 0;
        virtual void        DisableSampler      () const = 0;

    protected:
                            ISamplerUniform     ( const string& Name );
    };

    //  Юниформ, привязываемый к буферу данных.
    //  В настоящее время обновлять буфер юниформов можно только через VBO API, glUniform*() не используется.

    class DLLAPI IBindableUniform : public CBaseUniform
    {
    public:

        //
        // Interface
        //

        virtual GLsizei     GetBufferSize       () const = 0;
        virtual GLintptr    GetElementOffset    ( GLuint Index ) = 0;
        
        virtual void        AttachBuffer        ( Ptr<const CBuffer> Buffer ) = 0;

    protected:
                            IBindableUniform    ( const string& Name );
    };

    //  Программа GPU на языке высокого уровня Cg или GLSL.

    class DLLAPI IShadingProgram : public CObject
    {
        friend              CRenderDeviceDebug; 
        friend              CRenderDeviceRelease;

    public:
    #ifdef CG_SDK
        enum EShaderAPI 
        {
            SA_GLSL = 0,
            SA_CG,
            SA_UNKNOWN
        };
    #endif // CG_SDK

    public:

        //
        // Interface
        //

        static CSTRING&     GetLastInfoLog      ();

        virtual void        Link                () = 0;
        virtual string      GetInfoLog          () const = 0;

        virtual void        GetUniform          ( const string& Name, Ptr<IUniform> *Uniform ) const = 0;
        virtual void        GetSamplerUniform   ( const string& Name, Ptr<ISamplerUniform> *Uniform ) const = 0;
        virtual void        GetBindableUniform  ( const string& Name, Ptr<IBindableUniform> *Uniform ) const = 0;

        virtual bool        Validate            () const = 0;

    protected:

        //
        // Called by CRenderDevice
        //
        
        virtual void        Set                 () const = 0;
    #ifdef CG_SDK
        virtual EShaderAPI  GetAPIType          () const = 0;
    #endif
        
        //
		// Class members
		//

        static string       m_LastInfoLog;
    #ifdef CG_SDK
        vector<CGprofile>   m_Profiles;
    #endif // CG_SDK
        mutable map<string, Ptr<IUniform> > m_UniformCache;
        mutable map<string, Ptr<ISamplerUniform> > m_SamplerUniformCache;
        mutable map<string, Ptr<IBindableUniform> > m_BindableUniformCache;
    };

    //  Класс абстрактного графического устройства - операции с буфером кадра, установка OpenGL states.

    class DLLAPI IRenderDevice : public CObject
    {
    protected:
        enum 
        {
            MAX_TEXTURES = 32,
            MAX_VERTEX_STREAMS = 4 // Произвольная константа, 4 вполне достаточно.
        };

    public:

        //
        // Interface
        //

        virtual void        SetFrameBuffer              ( Ptr<IFrameBuffer> FrameBuffer ) = 0;
        virtual void        Blit                        ( Ptr<CFrameBufferObject> DestFrameBuffer, Ptr<const CFrameBufferObject> SrcFrameBuffer, 
                                                            GLbitfield Mask, GLenum Filter ) const = 0;
        virtual void        CopyDepthStencilToColor     ( GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum Type ) const = 0;
        virtual void        CopyPixels                  ( GLint x, GLint y, GLsizei Width, GLsizei Height, 
                                                            GLenum InputFormat, GLenum OutputFormat, GLenum Type, Ptr<CBuffer> Buffer ) const = 0;

        virtual void        SetTexture                  ( GLenum Unit, Ptr<const CTexture> Texture ) = 0;
        virtual void        SetShadingProgram           ( Ptr<const IShadingProgram> Program ) = 0;

        virtual void        SetVertexStructure          ( Ptr<const CVertexStructure> Struct ) = 0;
        virtual void        SetVertexBuffer             ( GLuint StreamIndex, Ptr<const CBuffer> Buffer, GLintptr Offset = 0, GLsizei Stride = -1 ) = 0;
        virtual void        SetIndexBuffer              ( Ptr<const CIndexBuffer> Buffer ) = 0;
        virtual void        SetIndexBuffer              ( Ptr<const CBuffer> Buffer, GLenum IndexType ) = 0; 
        virtual void        SetPackPixelBuffer          ( Ptr<CBuffer> Buffer ) = 0;
		virtual void        SetUnpackPixelBuffer        ( Ptr<const CBuffer> Buffer ) = 0;
        virtual void        SetTransformFeedbackBuffer  ( GLuint Index, Ptr<CBuffer> Buffer, GLintptr Offset = 0, GLsizeiptr Size = -1 ) = 0;

        virtual void        BeginConditionalRender      ( Ptr<const CQuery> Query, GLenum Mode ) = 0;
        virtual void        EndConditionalRender        () = 0;
        virtual void        BeginTransformFeedback      ( GLenum Mode ) = 0;
        virtual void        EndTransformFeedback        () = 0;

        virtual void        DrawArrays                  ( GLenum Mode, GLint First, GLsizei Count ) const = 0;
        virtual void        DrawArraysInstanced         ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const = 0;
        virtual void        DrawElements                ( GLenum Mode, GLint First, GLsizei Count ) const = 0;
        virtual void        DrawElementsInstanced       ( GLenum Mode, GLint First, GLsizei Count, 
                                                            GLsizei PrimCount ) const = 0;
        virtual void        DrawRangeElements           ( GLenum Mode, GLint First, GLuint Start, GLuint End, 
                                                            GLsizei Count ) const = 0;
    };
}

#endif // __GL_INTERFACES_H__