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

// Файл: /Math/Matrix/Mat4_SIMD.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_MAT4_H__
#define __MATH_SIMD_MAT4_H__

namespace MathSIMD
{
    //  Базовый класс матрицы четвёртого порядка, использующей SIMD-инструкции.
    //  Инструкции SSE применены, т. к. поддерживаются всеми современными CPU.

    class SIMD_ALIGN Mat4
    {
    public:
        struct Vec
        {
            // TODO : Union + оператор [] ?
            float           x, y, z, w;
        };

    protected:

        //
        // Class members
        //

        union 
        {
            Vec             m[ 4 ];

            struct {
                __m64       m0q0, m0q1, m1q0, m1q1, m2q0, m2q1, m3q0, m3q1;
            };

            struct {
                __m128      m1, m2, m3, m4;
            };
        };

    public:
                            Mat4();

                            Mat4( const __m64& m0, const __m64& m1, const __m64& m2, const __m64& m3, 
                                const __m64& m4, const __m64& m5, const __m64& m6, const __m64& m7 );
                            Mat4( const __m128& m1, const __m128& m2, const __m128& m3, const __m128& m4 );

                            Mat4( const float& s );
                            Mat4( float m00, float m01, float m02, float m03,
                                float m10, float m11, float m12, float m13,
                                float m20, float m21, float m22, float m23,
                                float m30, float m31, float m32, float m33 );
                            
                            Mat4( const Math::Mat3& m, bool Transpose );
                            Mat4( const Math::Mat3& m, const Math::Vec3<float>& v, bool Transpose );
                            Mat4( const Math::Mat4& m, bool Transpose );
                            
                            Mat4( const float m[], bool Transpose );
                            Mat4( const vector<float>& m, bool Transpose );

        //
        // Interface
        //

        void                Zero();
        void                Identity();
        bool                IsIdentity() const;

        float               Trace() const;

        //
        // Операторы
        //

        const Vec&          operator [] (const int& n) const;
        Vec&                operator [] (const int& n);
    };

    //
    // Constructor
    //
    inline Mat4::Mat4()
    {
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const __m64& m0, const __m64& m1, const __m64& m2, const __m64& m3,
        const __m64& m4, const __m64& m5, const __m64& m6, const __m64& m7 ):

        m0q0( m0 ), m0q1( m1 ), m1q0( m2 ), m1q1( m3 ), 
        m2q0( m4 ), m2q1( m5 ), m3q0( m6 ), m3q1( m7 )
    {
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const __m128& m1, const __m128& m2, const __m128& m3, const __m128& m4 ):
        m1( m1 ), m2( m2 ), m3( m3 ), m4( m4 )
    {                                
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const float& s )
    {
        m1 = _mm_set_ps( 0.0f, 0.0f, 0.0f, s );
        m2 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 1, 1, 0, 1 ) );
        m3 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 1, 0, 1, 1 ) );
        m4 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 0, 1, 1, 1 ) );
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, 
        float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 )
    {
        m1 = _mm_set_ps( m03, m02, m01, m00 );
        m2 = _mm_set_ps( m13, m12, m11, m10 );
        m3 = _mm_set_ps( m23, m22, m21, m20 );
        m4 = _mm_set_ps( m33, m32, m31, m30 );
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const Math::Mat3& n, bool Transpose )
    {
        m1 = _mm_set_ps( 0.0f, n[ 0 ].z, n[ 0 ].y, n[ 0 ].x );
        m2 = _mm_set_ps( 0.0f, n[ 1 ].z, n[ 1 ].y, n[ 1 ].x );
        m3 = _mm_set_ps( 0.0f, n[ 2 ].z, n[ 2 ].y, n[ 2 ].x );
        m4 = _mm_set_ps( 1.0f, 0.0f, 0.0f, 0.0f );

        if (Transpose) 
        {
            _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
        }
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const Math::Mat3& n, const Math::Vec3<float>& v, bool Transpose )
    {
        m1 = _mm_set_ps( 0.0f, n[ 0 ].z, n[ 0 ].y, n[ 0 ].x );
        m2 = _mm_set_ps( 0.0f, n[ 1 ].z, n[ 1 ].y, n[ 1 ].x );
        m3 = _mm_set_ps( 0.0f, n[ 2 ].z, n[ 2 ].y, n[ 2 ].x );
        m4 = _mm_set_ps( 1.0f, v.x, v.y, v.x );

        if (Transpose) 
        {
            _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
        }
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const Math::Mat4& n, bool Transpose )
    {
        m1 = _mm_loadu_ps( &n[ 0 ].x );
        m2 = _mm_loadu_ps( &n[ 4 ].x );
        m3 = _mm_loadu_ps( &n[ 8 ].x );
        m4 = _mm_loadu_ps( &n[ 12 ].x );

        if (Transpose) 
        {
            _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
        }
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const float n[], bool Transpose )
    {
        m1 = _mm_loadu_ps( &n[ 0 ] );
        m2 = _mm_loadu_ps( &n[ 4 ] );
        m3 = _mm_loadu_ps( &n[ 8 ] );
        m4 = _mm_loadu_ps( &n[ 12 ] );

        if (Transpose) 
        {
            _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
        }
    }

    //
    // Constructor
    //
    inline Mat4::Mat4( const vector<float>& n, bool Transpose )
    {
        assert( n.size() >= 16 );

        m1 = _mm_loadu_ps( &n[ 0 ] );
        m2 = _mm_loadu_ps( &n[ 4 ] );
        m3 = _mm_loadu_ps( &n[ 8 ] );
        m4 = _mm_loadu_ps( &n[ 12 ] );

        if (Transpose) 
        {
            _MM_TRANSPOSE4_PS( m1, m2, m3, m4 );
        }
    }

    //
    // Zero
    //
    inline void Mat4::Zero()
    {
        m1 = _mm_setzero_ps();
        m2 = _mm_setzero_ps();
        m3 = _mm_setzero_ps();
        m4 = _mm_setzero_ps();
    }

    //
    // Identity
    //
    inline void Mat4::Identity()
    {
        m1 = _mm_set_ps( 0.0f, 0.0f, 0.0f, 1.0f );
        m2 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 1, 1, 0, 1 ) );
        m3 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 1, 0, 1, 1 ) );
        m4 = _mm_shuffle_ps( m1, m1, _MM_SHUFFLE( 0, 1, 1, 1 ) );
    }

    //
    // IsIdentity
    //
    inline bool Mat4::IsIdentity() const
    {
        __m128 n1, n2, n3, n4;

        n1 = _mm_set_ps( 0.0f, 0.0f, 0.0f, 1.0f );
        n2 = _mm_shuffle_ps( n1, n1, _MM_SHUFFLE( 1, 1, 0, 1 ) );
        n3 = _mm_shuffle_ps( n1, n1, _MM_SHUFFLE( 1, 0, 1, 1 ) );
        n4 = _mm_shuffle_ps( n1, n1, _MM_SHUFFLE( 0, 1, 1, 1 ) );

        __m128 r0, r1, r2, r3;

        r0 = _mm_cmpeq_ps( m1, n1 );
        r1 = _mm_cmpeq_ps( m2, n2 );
        r2 = _mm_cmpeq_ps( m3, n3 );
        r3 = _mm_cmpeq_ps( m4, n4 );
        r0 = _mm_and_ps( r0, r1 );
        r2 = _mm_and_ps( r2, r3 );
        r0 = _mm_and_ps( r0, r2 );

        for (int i = 0; i < 4; ++i) 
        {
            if (r0.m128_u32[i] != 0xFFFFFFFF)
                return false;
        }

        return true;
    }

    //
    // Trace
    //
    inline float Mat4::Trace() const
    {
        __m128 r0, r1, r2;

        r0 = _mm_shuffle_ps( m1, m2, _MM_SHUFFLE( 0, 1, 0, 0 ) ); 
        r1 = _mm_shuffle_ps( m3, m4, _MM_SHUFFLE( 0, 3, 0, 2 ) ); 
        r2 = _mm_add_ps( r0, r1 );
        r1 = _mm_shuffle_ps( r2, r2, _MM_SHUFFLE( 0, 0, 0, 2 ) );
        r0 = _mm_add_ss( r1, r2 );

        float tr;

        _mm_store_ss( &tr, r0 );

        return tr;
    }

    //
    // operator []
    //
    inline const Mat4::Vec& Mat4::operator [] (const int& n) const
    {
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return m[ n ];
    }

    //
    // operator []
    //
    inline Mat4::Vec& Mat4::operator [] (const int& n)
    {
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return m[ n ];
    }
}

#endif // __MATH_SIMD_MAT4_H__