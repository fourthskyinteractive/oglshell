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

// Файл: /GL/Uniform.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_UNIFORM_H__
#define __GL_UNIFORM_H__

#include "Texture.h"

namespace GL
{
    //  Юниформ, OpenGL Shading Language (GLSL).

    class DLLAPI CUniform : public IUniform
    {
        friend              CShadingProgram;

    private:
    #ifdef _DEBUG
                            CUniform            ( const string& Name, GLint Location, GLenum Type );
    #else
                            CUniform            ( const string& Name, GLint Location );
    #endif // _DEBUG
    
    public:
                            
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CUniform"; }

        //
        // Interface
        //

        virtual void        SetBool             ( bool x );
        virtual void        SetFloat            ( GLfloat x );
        virtual void        SetInt              ( GLint x );
        virtual void        SetFloat2           ( GLfloat x, GLfloat y );
        virtual void        SetInt2             ( GLint x, GLint y );
        virtual void        SetFloat3           ( GLfloat x, GLfloat y, GLfloat z );
        virtual void        SetInt3             ( GLint x, GLint y, GLint z );
        virtual void        SetFloat4           ( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
        virtual void        SetInt4             ( GLint x, GLint y, GLint z, GLint w );
        virtual void        SetFloatArray       ( GLsizei Dimension, GLsizei Count, const GLfloat *Array );
        virtual void        SetIntArray         ( GLsizei Dimension, GLsizei Count, const GLint *Array );

    #ifdef MATH_LIB_INCLUDED
        virtual void        SetFloatVec2        ( const Vec2<GLfloat>& v );
        virtual void        SetIntVec2          ( const Vec2<GLint>& v );
        virtual void        SetFloatVec3        ( const Vec3<GLfloat>& v );
        virtual void        SetIntVec3          ( const Vec3<GLint>& v );
        virtual void        SetFloatVec4        ( const Vec4<GLfloat>& v );
        virtual void        SetIntVec4          ( const Vec4<GLint>& v );
        virtual void        SetFloatMat2        ( EMatrixOrder Order, const Mat2& m );
        virtual void        SetFloatMat3        ( EMatrixOrder Order, const Mat3& m );
        virtual void        SetFloatMat4        ( EMatrixOrder Order, const Mat4& m );
    #endif // MATH_LIB_INCLUDED

    private:
    #ifdef _DEBUG
        void                Throw               ( const char *Method ) const;
    #endif

        //
        // Class members
        //

        GLint               m_Location;
    #ifdef _DEBUG
        GLenum              m_Type;
    #endif
    };

    //  Юниформ, способный делать выборку из текстуры, OpenGL Shading Language (GLSL).

    class DLLAPI CSamplerUniform : public ISamplerUniform
    {
        friend              CShadingProgram;

    private:
                            CSamplerUniform     ( const string& Name, GLint Location, GLenum Unit );

    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CSamplerUniform"; }

        //
        // Interface
        //

        virtual void        SetSampler          ( Ptr<const CTexture> Texture );

        virtual void        EnableSampler       () const;
        virtual void        DisableSampler      () const;

    private:
        //
        // Class members
        //

        GLint               m_Location;
        GLenum              m_Unit;

        Ptr<const CTexture> m_Texture;
    };

    //  Юниформ, привязываемый к буферу данных, OpenGL Shading Language (GLSL).
    //  http://www.opengl.org/registry/specs/EXT/bindable_uniform.txt

    class DLLAPI CBindableUniform : public IBindableUniform
    {
        friend              CShadingProgram;

    private:
                            CBindableUniform    ( const string& Name, GLuint Program, GLuint Location );
                                
    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CBindableUniform"; }

        //
        // Interface
        //

        virtual GLsizei     GetBufferSize       () const;
        virtual GLintptr    GetElementOffset    ( GLuint Index );
        
        virtual void        AttachBuffer        ( Ptr<const CBuffer> Buffer );

    private:
    
        //
        // Class members
        //

        GLuint              m_Program;
        GLuint              m_Location;
    };

    #ifdef CG_SDK

    //  Юниформ, NVIDIA Cg.

    class DLLAPI CCgUniform : public IUniform
    {
        friend              CCgShadingProgram;

    private:
                            CCgUniform          ( const string& Name, CGparameter Parameter );
    
    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CCgUniform"; }

        //
        // Interface
        //

        virtual void        SetBool             ( bool x );
        virtual void        SetFloat            ( GLfloat x );
        virtual void        SetInt              ( GLint x );
        virtual void        SetFloat2           ( GLfloat x, GLfloat y );
        virtual void        SetInt2             ( GLint x, GLint y );
        virtual void        SetFloat3           ( GLfloat x, GLfloat y, GLfloat z );
        virtual void        SetInt3             ( GLint x, GLint y, GLint z );
        virtual void        SetFloat4           ( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
        virtual void        SetInt4             ( GLint x, GLint y, GLint z, GLint w );
        virtual void        SetFloatArray       ( GLsizei Dimension, GLsizei Count, const GLfloat *Array );
        virtual void        SetIntArray         ( GLsizei Dimension, GLsizei Count, const GLint *Array );

    #ifdef MATH_LIB_INCLUDED
        virtual void        SetFloatVec2        ( const Vec2<GLfloat>& v );
        virtual void        SetIntVec2          ( const Vec2<GLint>& v );
        virtual void        SetFloatVec3        ( const Vec3<GLfloat>& v );
        virtual void        SetIntVec3          ( const Vec3<GLint>& v );
        virtual void        SetFloatVec4        ( const Vec4<GLfloat>& v );
        virtual void        SetIntVec4          ( const Vec4<GLint>& v );
        virtual void        SetFloatMat2        ( EMatrixOrder Order, const Mat2& m );
        virtual void        SetFloatMat3        ( EMatrixOrder Order, const Mat3& m );
        virtual void        SetFloatMat4        ( EMatrixOrder Order, const Mat4& m );
    #endif // MATH_LIB_INCLUDED

    private:

        //
        // Class members
        //

        CGparameter         m_Parameter;
    };

    //  Юниформ, способный делать выборку из текстуры, NVIDIA Cg.

    class DLLAPI CCgSamplerUniform : public ISamplerUniform
    {
        friend              CCgShadingProgram;

    private:
                            CCgSamplerUniform   ( const string& Name, CGparameter Parameter );

    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CCgSamplerUniform"; }

        //
        // Interface
        //

        virtual void        SetSampler          ( Ptr<const CTexture> Texture );

        virtual void        EnableSampler       () const;
        virtual void        DisableSampler      () const;

    private:
        //
        // Class members
        //

        CGparameter         m_Parameter;
    };

    //  Юниформ, привязываемый к буферу данных, NVIDIA Cg

    class DLLAPI CCgBindableUniform : public IBindableUniform
    {
        friend              CCgShadingProgram;

    private:
                            CCgBindableUniform  ( const string& Name, CGprogram Program, CGparameter Parameter );
                            
    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CCgBindableUniform"; }

        //
        // Interface
        //

        virtual GLsizei     GetBufferSize       () const;
        virtual GLintptr    GetElementOffset    ( GLuint Index );
        
        virtual void        AttachBuffer        ( Ptr<const CBuffer> Buffer );

    private:
    
        //
        // Class members
        //

        CGprogram           m_Program;
        CGparameter         m_Parameter;
    };

    #endif // CG_SDK
}

#endif // __GL_UNIFORM_H__ 