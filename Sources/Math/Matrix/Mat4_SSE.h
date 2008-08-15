/*
This file is a part of Z-Trek 3D engine math library. 
You can use it freely in your proprietary applications.

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
*/

// Файл: /Math/Matrix/Mat4_SSE.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_MAT4_SSE_H__
#define __MATH_SIMD_MAT4_SSE_H__

namespace MathSIMD
{
    //  Матрица четвёртого порядка, использует SIMD-инструкции SSE.
    //  Запись по столбцам.
    
    class Mat4_SSE : public Mat4
    {
    public:
                            SIMD_ALLOCATOR();

    public:
                            Mat4_SSE();
                            
                            Mat4_SSE( const __m128& m1, const __m128& m2, const __m128& m3, const __m128& m4 );

                            Mat4_SSE( const float& s );
                            Mat4_SSE( float m00, float m01, float m02, float m03,
                                float m10, float m11, float m12, float m13,
                                float m20, float m21, float m22, float m23,
                                float m30, float m31, float m32, float m33 );

                            Mat4_SSE( const Math::Mat3& m );
                            Mat4_SSE( const Math::Mat3& m, const Math::Vec3<float>& v );
                            Mat4_SSE( const Math::Mat4& m );

                            Mat4_SSE( const float m[] );
                            Mat4_SSE( const vector<float>& m );

        //
        // Interface
        //

        bool                Compare( const Mat4_SSE& m ) const;

        float               GetDeterminant3() const;

        void                Transpose();
        Mat4_SSE            GetTransposed() const;

        //
        // Operators
        //

        Mat4_SSE&           operator *= (const float& s);
        Mat4_SSE&           operator *= (const Mat4_SSE& m);
        Mat4_SSE&           operator /= (const float& s);
        Mat4_SSE&           operator += (const float& s);
        Mat4_SSE&           operator += (const Mat4_SSE& m);
        Mat4_SSE&           operator -= (const float& s);
        Mat4_SSE&           operator -= (const Mat4_SSE& m);

        Mat4_SSE            operator * (const float& s) const;
        friend Mat4_SSE     operator * (const float& s, const Mat4_SSE& m) { return m * s; }
        Vec4_SSE            operator * (const Vec4_SSE& v) const;
        friend Vec4_SSE     operator * (const Vec4_SSE& v, const Mat4_SSE& m) { return m * v; } 
        Mat4_SSE            operator * (const Mat4_SSE &m) const;
        Mat4_SSE            operator / (const float& s) const;
        Mat4_SSE            operator + (const float& s) const;
        Mat4_SSE            operator + (const Mat4_SSE& m) const;
        Mat4_SSE            operator - (const float& s) const;
        Mat4_SSE            operator - (const Mat4_SSE& m) const;

        bool                operator == (const Mat4_SSE& m) const; 
        bool                operator != (const Mat4_SSE& m) const;
    };

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE()
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const __m128& m1, const __m128& m2, const __m128& m3, const __m128& m4 ):
        Mat4( m1, m2, m3, m4 )
    {                                
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const float& s ):
        Mat4( s )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, 
        float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 ):
    
        Mat4( m00, m01, m02, m03, 
            m10, m11, m12, m13, 
            m20, m21, m22, m23,
            m30, m31, m32, m33 )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const Math::Mat3& m ):
        Mat4( m, false )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const Math::Mat3& m, const Math::Vec3<float>& v ):
        Mat4( m, v, false )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const Math::Mat4& m ):
        Mat4( m, false )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const float m[] ):
        Mat4( m, false )
    {
    }

    //
    // Constructor
    //
    inline Mat4_SSE::Mat4_SSE( const vector<float>& m ):
        Mat4( m, false )
    {
    }

    //
    // Compare
    //
    inline bool Mat4_SSE::Compare( const Mat4_SSE& n ) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_cmpeq_ps( m1, n.m1 );
        r1 = _mm_cmpeq_ps( m2, n.m2 );
        r2 = _mm_cmpeq_ps( m3, n.m3 );
        r3 = _mm_cmpeq_ps( m4, n.m4 );
        r0 = _mm_and_ps( r0, r1 );
        r2 = _mm_and_ps( r2, r3 );
        r0 = _mm_and_ps( r0, r2 );

        if (r0.m128_u32[ 0 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 1 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 2 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 3 ] != 0xFFFFFFFF)
            return false;

        return true;
    }

    //
    // GetDeterminant3
    //
    inline float Mat4_SSE::GetDeterminant3() const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_shuffle_ps( m2, m2, _MM_SHUFFLE( 3, 0, 2, 1 ) );
        r1 = _mm_shuffle_ps( m3, m3, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r2 = _mm_shuffle_ps( m2, m2, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r3 = _mm_shuffle_ps( m3, m3, _MM_SHUFFLE( 3, 0, 2, 1 ) );

        r0 = _mm_mul_ps( r0, r1 );
        r2 = _mm_mul_ps( r2, r3 );
        r0 = _mm_sub_ps( r0, r2 );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r1, r0 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );
        r0 = _mm_add_ss( r0, r1 );
        
        float det;

        _mm_store_ss( &det, r0 );

        return det;
    }
    
    //
    // Transpose
    //
    inline void Mat4_SSE::Transpose()
    {
        _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
    }

    //
    // GetTransposed
    //
    inline Mat4_SSE Mat4_SSE::GetTransposed() const
    {
        Mat4_SSE k = *this;

        k.Transpose();
        return k;
    }               

    //
    // operator *=
    //
    inline Mat4_SSE& Mat4_SSE::operator *= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        
        m1 = _mm_mul_ps( m1, r0 );
        m2 = _mm_mul_ps( m2, r0 );
        m3 = _mm_mul_ps( m3, r0 );
        m4 = _mm_mul_ps( m4, r0 );

        return *this;
    }

    //
    // operator *=
    //
    inline Mat4_SSE& Mat4_SSE::operator *= (const Mat4_SSE& n)
    {
        __m128 r0, r1, r2, r3;
        __m128 k0, k1, k2;
 
        r0 = _mm_load_ss( &n[ 0 ].x );
        r1 = _mm_load_ss( &n[ 0 ].y );
        r2 = _mm_load_ss( &n[ 0 ].z );
        r3 = _mm_load_ss( &n[ 0 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k0 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 1 ].x );
        r1 = _mm_load_ss( &n[ 1 ].y );
        r2 = _mm_load_ss( &n[ 1 ].z );
        r3 = _mm_load_ss( &n[ 1 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k1 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 2 ].x );
        r1 = _mm_load_ss( &n[ 2 ].y );
        r2 = _mm_load_ss( &n[ 2 ].z );
        r3 = _mm_load_ss( &n[ 2 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k2 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 3 ].x );
        r1 = _mm_load_ss( &n[ 3 ].y );
        r2 = _mm_load_ss( &n[ 3 ].z );
        r3 = _mm_load_ss( &n[ 3 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        r0 = _mm_add_ps( r0, r2 );

        m1 = k0;
        m2 = k1;
        m3 = k2;
        m4 = r0;

        return *this;
    }

    //
    // operator /=
    //
    inline Mat4_SSE& Mat4_SSE::operator /= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_rcp_ss( r0 );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        m1 = _mm_mul_ps( m1, r0 );
        m2 = _mm_mul_ps( m2, r0 );
        m3 = _mm_mul_ps( m3, r0 );
        m4 = _mm_mul_ps( m4, r0 );

        return *this;
    }

    //
    // operator +=
    //
    inline Mat4_SSE& Mat4_SSE::operator += (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        m1 = _mm_add_ps( m1, r0 );
        m2 = _mm_add_ps( m2, r0 );
        m3 = _mm_add_ps( m3, r0 );
        m4 = _mm_add_ps( m4, r0 );

        return *this;
    }

    //
    // operator +=
    //
    inline Mat4_SSE& Mat4_SSE::operator += (const Mat4_SSE& n)
    {
        m1 = _mm_add_ps( m1, n.m1 );
        m2 = _mm_add_ps( m2, n.m2 );
        m3 = _mm_add_ps( m3, n.m3 );
        m4 = _mm_add_ps( m4, n.m4 );

        return *this;
    }

    //
    // operator -=
    //
    inline Mat4_SSE& Mat4_SSE::operator -= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        m1 = _mm_sub_ps( m1, r0 );
        m2 = _mm_sub_ps( m2, r0 );
        m3 = _mm_sub_ps( m3, r0 );
        m4 = _mm_sub_ps( m4, r0 );

        return *this;
    }

    //
    // operator -=
    //
    inline Mat4_SSE& Mat4_SSE::operator -= (const Mat4_SSE& n)
    {
        m1 = _mm_sub_ps( m1, n.m1 );
        m2 = _mm_sub_ps( m2, n.m2 );
        m3 = _mm_sub_ps( m3, n.m3 );
        m4 = _mm_sub_ps( m4, n.m4 );

        return *this;
    }

    //
    // operator *
    //
    inline Mat4_SSE Mat4_SSE::operator * (const float& s) const
    {
        __m128 r0;
        Mat4_SSE k;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        k.m1 = _mm_mul_ps( m1, r0 );
        k.m2 = _mm_mul_ps( m2, r0 );
        k.m3 = _mm_mul_ps( m3, r0 );
        k.m4 = _mm_mul_ps( m4, r0 );

        return k;
    }

    //
    // operator *
    //
    inline Vec4_SSE Mat4_SSE::operator * (const Vec4_SSE& v) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_load_ss( &v.x );
        r1 = _mm_load_ss( &v.y );
        r2 = _mm_load_ss( &v.z );
        r3 = _mm_load_ss( &v.w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        r0 = _mm_add_ps( r0, r2 );

        return Vec4_SSE( r0 );
    }

    //
    // operator *
    //
    inline Mat4_SSE Mat4_SSE::operator * (const Mat4_SSE& n) const
    {
        __m128 r0, r1, r2, r3;
        __m128 k0, k1, k2;
 
        r0 = _mm_load_ss( &n[ 0 ].x );
        r1 = _mm_load_ss( &n[ 0 ].y );
        r2 = _mm_load_ss( &n[ 0 ].z );
        r3 = _mm_load_ss( &n[ 0 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k0 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 1 ].x );
        r1 = _mm_load_ss( &n[ 1 ].y );
        r2 = _mm_load_ss( &n[ 1 ].z );
        r3 = _mm_load_ss( &n[ 1 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k1 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 2 ].x );
        r1 = _mm_load_ss( &n[ 2 ].y );
        r2 = _mm_load_ss( &n[ 2 ].z );
        r3 = _mm_load_ss( &n[ 2 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        k2 = _mm_add_ps( r0, r2 );

        r0 = _mm_load_ss( &n[ 3 ].x );
        r1 = _mm_load_ss( &n[ 3 ].y );
        r2 = _mm_load_ss( &n[ 3 ].z );
        r3 = _mm_load_ss( &n[ 3 ].w );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r2 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        r3 = _mm_shuffle_ps( r3, r3, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r0 = _mm_mul_ps( r0, m1 );
        r1 = _mm_mul_ps( r1, m2 );
        r2 = _mm_mul_ps( r2, m3 );
        r3 = _mm_mul_ps( r3, m4 );
        r0 = _mm_add_ps( r0, r1 );
        r2 = _mm_add_ps( r2, r3 );
        r0 = _mm_add_ps( r0, r2 );

        return Mat4_SSE( k0, k1, k2, r0 );
    }

    //
    // operator /
    //
    inline Mat4_SSE Mat4_SSE::operator / (const float& s) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_load_ss( &s );
        r0 = _mm_rcp_ss( r0 );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r3 = _mm_mul_ps( m4, r0 );
        r2 = _mm_mul_ps( m3, r0 );
        r1 = _mm_mul_ps( m2, r0 );
        r0 = _mm_mul_ps( m1, r0 );

        return Mat4_SSE( r0, r1, r2, r3 );
    }

    //
    // operator +
    //
    inline Mat4_SSE Mat4_SSE::operator + (const float& s) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r3 = _mm_add_ps( m4, r0 );
        r2 = _mm_add_ps( m3, r0 );
        r1 = _mm_add_ps( m2, r0 );
        r0 = _mm_add_ps( m1, r0 );

        return Mat4_SSE( r0, r1, r2, r3 );
    }

    //
    // operator +
    //
    inline Mat4_SSE Mat4_SSE::operator + (const Mat4_SSE& n) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_add_ps( m1, n.m1 );
        r1 = _mm_add_ps( m2, n.m2 );
        r2 = _mm_add_ps( m3, n.m3 );
        r3 = _mm_add_ps( m4, n.m4 );

        return Mat4_SSE( r0, r1, r2, r3 );
    }

    //
    // operator -
    //
    inline Mat4_SSE Mat4_SSE::operator - (const float& s) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );

        r3 = _mm_sub_ps( m4, r0 );
        r2 = _mm_sub_ps( m3, r0 );
        r1 = _mm_sub_ps( m2, r0 );
        r0 = _mm_sub_ps( m1, r0 );

        return Mat4_SSE( r0, r1, r2, r3 );
    }

    //
    // operator -
    //
    inline Mat4_SSE Mat4_SSE::operator - (const Mat4_SSE& n) const
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_sub_ps( m1, n.m1 );
        r1 = _mm_sub_ps( m2, n.m2 );
        r2 = _mm_sub_ps( m3, n.m3 );
        r3 = _mm_sub_ps( m4, n.m4 );
        
        return Mat4_SSE( r0, r1, r2, r3 );
    }

    //
    // operator ==
    //
    inline bool Mat4_SSE::operator == (const Mat4_SSE& n) const
    {
        return Compare( n );
    }

    //
    // operator !=
    //
    inline bool Mat4_SSE::operator != (const Mat4_SSE& n) const
    {
        return !Compare( n );
    }
}

#endif // __MATH_SIMD_MAT4_SSE_H__