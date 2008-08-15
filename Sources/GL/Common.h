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

e-mail: bob.vilson@gmail.com
*/

// Файл: /GL/Common.h
//                                                                

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_COMMON_H__
#define __GL_COMMON_H__

#include "InternalFormat.h"

namespace GL
{
    //
    //  Опережающие описания классов.
    //

                        // Описание для CClass и CObject.
    class DLLAPI        CExtensionRegistry;
    class DLLAPI        CInternalFormat;

                        // Описание для RenderDevice и Texture.
    class DLLAPI        CWindowSwapChain;
    class DLLAPI        IFrameBuffer;
    class DLLAPI        CFrameBuffer;
    class DLLAPI        CFrameBufferObject;

                        // Описание для FrameBuffer и SamplerUniform.
    class DLLAPI        CTexture;
    class DLLAPI        CTexture1D;
    class DLLAPI        CTexture2D;
    class DLLAPI        CTextureRectangle;
    class DLLAPI        CTexture3D;
    class DLLAPI        CTextureCubeMap;

                        // Описание для RenderDevice и Uniform.
    class DLLAPI        CBuffer;
    class DLLAPI        CIndexBuffer;

                        // Описание для Program.
    class DLLAPI        CShader;
    class DLLAPI        CCgShader;
    class DLLAPI        IUniform;
    class DLLAPI        ISamplerUniform;
    class DLLAPI        IBindableUniform;
                        // Описание для Texture. 
    class DLLAPI        CSamplerUniform;
    class DLLAPI        CCgSamplerUniform;
                        // Описание для Buffer.
    class DLLAPI        CBindableUniform;
    class DLLAPI        CCgBindableUniform;

                        // Описание для RenderDevice, Shader и CgShader.
    class DLLAPI        IShadingProgram;
    class DLLAPI        CShadingProgram; 
    class DLLAPI        CCgShadingProgram;

                        // Описание для RenderDevice.
    class DLLAPI        CQuery;
    class DLLAPI        CVertexStructure;
    
                        // Описание для Main.
    class DLLAPI        CDriverDesc;
    class DLLAPI        CCapsDesc;
    class DLLAPI        IRenderDevice;
    class DLLAPI        IDummyRenderDevice;

                        // Описание для различных классов.
	class DLLAPI        CRenderDeviceDebug;
    class DLLAPI        CRenderDeviceRelease;

    //
    //  С++ обёртки процедур OpenGL для более удобной работы с ними.
    //

    DLLAPI void         glClearErrors();

    #ifdef MATH_LIB_INCLUDED

    DLLAPI void         glVertex2fv( const Vec2<GLfloat>& v );
    DLLAPI void         glVertex2iv( const Vec2<GLint>& v );
    DLLAPI void         glVertex3fv( const Vec3<GLfloat>& v );
    DLLAPI void         glVertex3fv( const Vec4_SSE& v );
    DLLAPI void         glVertex3iv( const Vec3<GLint>& v );
    DLLAPI void         glVertex4fv( const Vec4<GLfloat>& v );
    DLLAPI void         glVertex4fv( const Vec4_SSE& v );
    DLLAPI void         glVertex4iv( const Vec4<GLint>& v );

    DLLAPI void         glTranslatefv( const Vec2<GLfloat>& v );
    DLLAPI void         glTranslatefv( const Vec3<GLfloat>& v );

    DLLAPI void         glLoadMatrixf( const Mat4& m );
    DLLAPI void         glMultMatrixf( const Mat3& m );
    DLLAPI void         glMultMatrixf( const Mat4& m );

    #endif // MATH_LIB_INCLUDED

    //  Базовый класс для всех классов OpenGL Shell.

    class DLLAPI CObject : 
                            public Sys::IRTTIObject,
                            public Sys::CNonCopyable
                            
    {
        friend DLLAPI void  CreateShellAPI      ( UINT Flags, Ptr<GL::IRenderDevice> *RenderDevice, Ptr<const GL::CExtensionRegistry> *Extensions );

    protected:
        struct TCaps
        {
            GLint               MaxDrawBuffers;
            GLint               MaxTextureImageUnits;
            GLint               MaxVertexAttribs;
        };

    public:
                            ~CObject            ();

    protected:
                            CObject             ();
                            CObject             ( int Dummy );

        //
        // Interface
        //

        static void         Init                ( Ptr<const CExtensionRegistry> Extensions, bool CgShaders );
        static void         Release             ();

    protected:

        //
        // Class members
        //

        static Ptr<const CExtensionRegistry> m_Extensions;
        static const CInternalFormat m_InternalFormats[];
        static TCaps        m_Caps;

        static bool         m_CgShaders;

    private:
        static int          m_Count;
    };

    //  Исключение, бросаемое при возникновении ошибки OpenGL.
    
    class DLLAPI CException : public Sys::CException
    {
    public:
                            CException          ( const Sys::IRTTIObject *Obj, GLenum Code, const char *FormatStr, ... );
                            CException          ( const char *ClsName, GLenum Code, const char *FormatStr, ... );

        //
        // Interface
        //

    private:
        const char*         ToString            ( GLenum Code ) const;
    };

    #ifdef _WIN32
    
    //  Исключение, бросаемое при возникновении ошибки Windows OpenGL.

    class DLLAPI CWGLException : public Sys::CException
    {
    public:
                                                
                            CWGLException       ( const Sys::IRTTIObject *Obj, const char *FormatStr, ... );
                            CWGLException       ( const char *ClsName, const char *FormatStr, ... );

        //
        // Interface
        //

    private:                
        const char*         ToString            ( DWORD dwLastError ) const;
    };

    #elif defined (__linux__)
    
    //  Исключение, бросаемое при возникновении ошибки GLX.

    class DLLAPI CGLXException : public Sys::CException
    {
    public:
                            CGLXException       ( const Sys::IRTTIObject *Obj, const char *FormatStr, ... );
                            CGLXException       ( const char *ClsName, const char *FormatStr, ... );

        //
        // Interface
        //

    private:
        const char*         ToStringX           ( int Code ) const;
        const char*         ToStringGLX         ( int Code ) const;
    };

    #endif // _WIN32

    #ifdef CG_SDK

    //  Исключение, бросаемое при возникновении ошибки Cg.

    class DLLAPI CCgException : public Sys::CException
    {
    public:
                            CCgException        ( const Sys::IRTTIObject *Obj, CGerror Code, const char *FormatStr, ... );
                            CCgException        ( const char *ClsName, CGerror Code, const char *FormatStr, ... );

        //
        // Interface
        //

    private:
        const char*         ToString            ( CGerror Code ) const;
    };
    
    #endif // CG_SDK
    
    //  Исключение, бросаемое при отсутствии требуемого расширения или версии OpenGL.
    
    class DLLAPI CExtensionException : public Sys::CException
    {
    public:
                            CExtensionException ( const Sys::IRTTIObject *Obj, const char *Method, const char *Extension );
                            CExtensionException ( const char *ClsName, const char *Method, const char *Extension );
                            CExtensionException ( const Sys::IRTTIObject *Obj, const char *Method, int MajorNumber, int MinorNumber );
                            CExtensionException ( const char *ClsName, const char *Method, int MajorNumber, int MinorNumber );
                            
        //
        // Interface
        //
    };
} 

#endif // __GL_COMMON_H__