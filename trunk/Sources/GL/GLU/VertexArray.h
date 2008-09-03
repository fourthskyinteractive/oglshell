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

// ‘айл: /GL/GLU/VertexArray.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GLU_VERTEX_ARRAY_H__
#define __GLU_VERTEX_ARRAY_H__

namespace GLU
{
    //  ћассив вершинных данных, заполн€емых пользователем в immediate режиме.
    //  ћежду парой команд Begin()/End() может быть задано множество батчей, каждый с отдельной 
    //  топологией примитива, вывод откладываетс€ до вызова метода класса Draw().
    //   ласс создан дл€ удобства использовани€ в некритичных дл€ скорости местах.

    //  ѕараметр MaxVertexAttribs конструктора предпочтительно задавать наименьшим возможным числом,
    //  это существенно сэкономит пам€ть. ≈сли оставить значение по умолчанию, используетс€
    //  завис€щее от реализации значение GL_MAX_VERTEX_ATTRIBS.

    //  ѕравила использовани€:
    //  1) ¬се массивы вершин в батче должны использовать одинаковое кол-во вершин.
    //  2) ¬се батчи должны между собой использовать одни и те же массивы вершинных данных.

    class CVertexArray : public GL::CObject
    {
        struct TVec4
        {
            GLfloat         x, y, z, w;
        };
        
        struct TDrawBatch
        {
            GLenum          Mode;
            GLint           First;
            GLsizei         Count;

                            // »спользуетс€ дл€ слежени€ за используемыми вершинными массивами
                            // и когерентностью используемых массивов между батчами.
            vector<GLsizei> Counts;
        };

    public:
                            CVertexArray        ( GLsizeiptr MaxVertices, GLuint MaxVertexAttribs = 0 );
                            ~CVertexArray       ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CVertexArray"; }

        //
        // Interface
        //

        void                Begin               ( GLenum Topology );
        void                End                 ();

        void                PushVertexAttrib1   ( GLuint Index, GLfloat x );
        void                PushVertexAttrib2   ( GLuint Index, GLfloat x, GLfloat y );
        void                PushVertexAttrib3   ( GLuint Index, GLfloat x, GLfloat y, GLfloat z );    
        void                PushVertexAttrib4   ( GLuint Index, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
    #ifdef MATH_LIB_INCLUDED
        void                PushVertexAttrib2   ( GLuint Index, const Vec2<GLfloat>& v );
        void                PushVertexAttrib3   ( GLuint Index, const Vec3<GLfloat>& v );
        void                PushVertexAttrib4   ( GLuint Index, const Vec4<GLfloat>& v );
        void                PushVertexAttrib4   ( GLuint Index, const Vec4_SSE& v );
        void                PushVertexAttrib4   ( GLuint Index, const Vec4_3DNow& v );
    #endif // MATH_LIB_INCLUDED

        void                Draw                () const;

    private:

        //
        // Class members
        //

    __M(
        m_MaxVertices,      GLsizeiptr,
        m_MaxVertexAttribs, GLuint,

        m_VB[ 2 ],          vector<GLuint>,
        m_VBMapped[ 2 ],    mutable vector<bool>,
        m_VBSetIndex,       mutable GLubyte,
        m_Data,             mutable vector<TVec4 *>,

        m_Batches,          mutable vector<TDrawBatch>,
        m_Batch,            TDrawBatch *,
        m_Enclosed,         bool,
        );

    #ifdef _DEBUG
    __M(
        m_NumVertices,      mutable GLsizeiptr,
        );
    #endif
    };

    #ifdef _DEBUG
        #define ASSERT_GLU_VA_PUSHVERTEX( Name ) \
            if (!m_Enclosed) \
            { \
                throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL, \
                "%s: Invalid usage, call ::Begin() first.", Name ); \
            } \
            if (Index >= m_MaxVertexAttribs) \
                throw Sys::CDeveloperException( this, "%s: Invalid <Index> parameter.", Name ); \
            if (m_NumVertices++ == m_MaxVertices) \
                throw Sys::CException( this, "%s: Out of memory.", Name );  
    #else
        #define ASSERT_GLU_VA_PUSHVERTEX( Name )
    #endif // _DEBUG

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib1( 
                                                GLuint Index, GLfloat x 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib1()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = x;
        Data->y = 0.0f;
        Data->z = 0.0f;
        Data->w = 1.0f;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib2( 
                                                GLuint Index, 
                                                GLfloat x, GLfloat y 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib2()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = x;
        Data->y = y;
        Data->z = 0.0f;
        Data->w = 1.0f;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib3( 
                                                GLuint Index, 
                                                GLfloat x, GLfloat y, GLfloat z 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib3()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = x;
        Data->y = y;
        Data->z = z;
        Data->w = 1.0f;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib4( 
                                                GLuint Index, 
                                                GLfloat x, GLfloat y, GLfloat z, GLfloat w 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib4()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = x;
        Data->y = y;
        Data->z = z;
        Data->w = w;

        ++m_Batch->Counts[ Index ];
    }

    #ifdef MATH_LIB_INCLUDED

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib2( 
                                                GLuint Index, 
                                                const Vec2<GLfloat>& v 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib2()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = v.x;
        Data->y = v.y;
        Data->z = 0.0f;
        Data->w = 1.0f;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib3( 
                                                GLuint Index, 
                                                const Vec3<GLfloat>& v 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib3()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = v.x;
        Data->y = v.y;
        Data->z = v.z;
        Data->w = 1.0f;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib4( 
                                                GLuint Index, 
                                                const Vec4<GLfloat>& v 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib4()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = v.x;
        Data->y = v.y;
        Data->z = v.z;
        Data->w = v.w;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib4( 
                                                GLuint Index, 
                                                const Vec4_SSE& v 
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib4()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = v.x;
        Data->y = v.y;
        Data->z = v.z;
        Data->w = v.w;

        ++m_Batch->Counts[ Index ];
    }

    //
    // PushVertexAttrib
    //
    inline void CVertexArray::PushVertexAttrib4( 
                                                GLuint Index, 
                                                const Vec4_3DNow& v
                                                )
    {
        ASSERT_GLU_VA_PUSHVERTEX( "::PushVertexAttrib4()" );
        TVec4 *Data = m_Data[ Index ]++;

        Data->x = v.x;
        Data->y = v.y;
        Data->z = v.z;
        Data->w = v.w;

        ++m_Batch->Counts[ Index ];
    }

    #endif // MATH_LIB_INCLUDED
}

#endif // __GLU_VERTEX_ARRAY_H__