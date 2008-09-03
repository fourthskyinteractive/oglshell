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

// Τΰιλ: /GL/GLU/MatrixStack.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GLU_MATRIX_STACK_H__
#define __GLU_MATRIX_STACK_H__

#ifdef MATH_LIB_INCLUDED

namespace GLU
{
    //

    class CMatrixStack : public Sys::IRTTIObject
    {
    public:
        enum EMatrix
        {
            MAT_WORLD = 0, // DEFAULT
            MAT_VIEW,
            MAT_PROJECTION,
            MAT_WORLDVIEW,
            MAT_WORLDVIEW_PROJECTION
        };

    public:
                            CMatrixStack        ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GLU::CMatrixStack"; }

        //
        // Interface
        //

        void                Select              ( EMatrix Type );

        void                Push                ();
        void                Pop                 ();
        Mat4                GetTop              ( EMatrix Type ) const;

        void                SetIdentity         ();
        void                Set                 ( const Mat4& m );

        void                Multiply            ( const Mat4& m );
        void                Translate           ( float x, float y, float z );
        void                Translate           ( const Vec3<float>& v );
        void                Rotate              ( float x, float y, float z, float Angle );
        void                Rotate              ( const Vec3<float>& Axis, float Angle );
        void                Scale               ( float x, float y, float z );

    private:

        //
        // Class members
        //

        stack<Mat4>         m_World;
        stack<Mat4>         m_View;
        stack<Mat4>         m_Projection;
        stack<Mat4>*        m_Curr;
    };
}

#endif // MATH_LIB_INCLUDED

#endif // __GLU_MATRIX_STACK_H__