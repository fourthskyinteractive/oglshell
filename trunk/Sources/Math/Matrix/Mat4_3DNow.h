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

// Файл: /Math/Matrix/Mat4_3DNow.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_MAT4_3DNOW_H__
#define __MATH_SIMD_MAT4_3DNOW_H__

namespace MathSIMD
{
    //  Матрица четвёртого порядка, использует SIMD-инструкции 3DNow!
    //  В целях оптимизации под инструкции матрица записана по строкам.
    
    class Mat4_3DNow : public Mat4
    {
    public:
                            SIMD_ALLOCATOR();

    public:
                            Mat4_3DNow();

                            Mat4_3DNow( const __m64& m0, const __m64& m1, const __m64& m2, const __m64& m3,
                                const __m64& m4, const __m64& m5, const __m64& m6, const __m64& m7 );

                            Mat4_3DNow( const float& s );
                            Mat4_3DNow( float m00, float m01, float m02, float m03,
                                float m10, float m11, float m12, float m13,
                                float m20, float m21, float m22, float m23,
                                float m30, float m31, float m32, float m33 );

                            Mat4_3DNow( const Math::Mat3& m );
                            Mat4_3DNow( const Math::Mat3& m, const Math::Vec3<float>& v );
                            Mat4_3DNow( const Math::Mat4& m );

                            Mat4_3DNow( const float m[] );
                            Mat4_3DNow( const vector<float>& m );

        //
        // Interface
        //
                                
        bool                Compare( const Mat4_3DNow& m ) const;

        void                Transpose();
        Mat4_3DNow          GetTransposed() const;

        //
        // Operators
        //

        Mat4_3DNow&         operator *= (const float& s);
        Mat4_3DNow&         operator *= (const Mat4_3DNow& m);
        Mat4_3DNow&         operator /= (const float& s);
        Mat4_3DNow&         operator += (const float& s);
        Mat4_3DNow&         operator += (const Mat4_3DNow &m);
        Mat4_3DNow&         operator -= (const float& s);
        Mat4_3DNow&         operator -= (const Mat4_3DNow &m);

        Mat4_3DNow          operator * (const float& s) const;
        friend Mat4_3DNow   operator * (const float& s, const Mat4_3DNow& m) { return m * s; }
        Vec4_3DNow          operator * (const Vec4_3DNow& v) const;
        friend Vec4_3DNow   operator * (const Vec4_3DNow& v, const Mat4_3DNow& m) { return m * v; } 
        Mat4_3DNow          operator * (const Mat4_3DNow& m) const;
        Mat4_3DNow          operator / (const float& s) const;
        Mat4_3DNow          operator + (const float& s) const;
        Mat4_3DNow          operator + (const Mat4_3DNow& m) const;
        Mat4_3DNow          operator - (const float& s) const;
        Mat4_3DNow          operator - (const Mat4_3DNow& m) const;

        bool                operator == (const Mat4_3DNow& m) const; 
        bool                operator != (const Mat4_3DNow& m) const;
    };

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow()
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const __m64& m0, const __m64& m1, const __m64& m2, const __m64& m3,
        const __m64& m4, const __m64& m5, const __m64& m6, const __m64& m7 ):

        Mat4( m0, m1, m2, m3, m4, m5, m6, m7 )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const float& s ):
        Mat4( s )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, 
        float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 ):

        Mat4( m00, m10, m20, m30, 
            m01, m11, m21, m31, 
            m02, m12, m22, m32,
            m03, m13, m23, m33 )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const Math::Mat3& m ):
        Mat4( m, true )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const Math::Mat3& m, const Math::Vec3<float>& v ):
        Mat4( m, v, true )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const Math::Mat4& m ):
        Mat4( m, true )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const float m[] ):
        Mat4( m, true )
    {
    }

    //
    // Constructor
    //
    inline Mat4_3DNow::Mat4_3DNow( const vector<float>& m ):
        Mat4( m, true )
    {
    }

    //
    // Compare
    //
    inline bool Mat4_3DNow::Compare( const Mat4_3DNow& n ) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;

        r0 = _m_pfcmpeq( m0q0, n.m0q0 );
        r1 = _m_pfcmpeq( m0q1, n.m0q1 );
        r2 = _m_pfcmpeq( m1q0, n.m1q0 );
        r3 = _m_pfcmpeq( m1q1, n.m1q1 );
        r4 = _m_pfcmpeq( m2q0, n.m2q0 );
        r5 = _m_pfcmpeq( m2q1, n.m2q1 );
        r6 = _m_pfcmpeq( m3q0, n.m3q0 );
        r7 = _m_pfcmpeq( m3q1, n.m3q1 );
        r0 = _m_pfmax( r0, r1 );
        r2 = _m_pfmax( r2, r3 );
        r4 = _m_pfmax( r4, r5 );
        r6 = _m_pfmax( r6, r7 );
        r0 = _m_pfmax( r0, r2 );
        r4 = _m_pfmax( r4, r6 );
        r0 = _m_pfmax( r0, r4 );

        bool eq = (r0.m64_u64 == 0xFFFFFFFFFFFFFFFF);

        _m_femms();
    
        return eq;
    }

    //
    // Transpose
    //
    inline void Mat4_3DNow::Transpose()
    {
        using namespace std;

        // Возможно создание множества переменных Temp. Заменить на хэнд-код!

        swap( m[ 0 ].y, m[ 1 ].x );
        swap( m[ 0 ].z, m[ 2 ].x );
        swap( m[ 0 ].w, m[ 3 ].x );
        swap( m[ 1 ].z, m[ 2 ].y );
        swap( m[ 1 ].w, m[ 3 ].y );
        swap( m[ 2 ].w, m[ 3 ].z );
    }

    //
    // GetTransposed
    //
    inline Mat4_3DNow Mat4_3DNow::GetTransposed() const
    {
        Mat4_3DNow k = *this;

        k.Transpose();
        return k;
    }

    //
    // operator *=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator *= (const float& s)
    {
        __m64 r0;

        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        m0q0 = _m_pfmul( m0q0, r0 );
        m0q1 = _m_pfmul( m0q1, r0 );
        m1q0 = _m_pfmul( m1q0, r0 );
        m1q1 = _m_pfmul( m1q1, r0 );
        m2q0 = _m_pfmul( m2q0, r0 );
        m2q1 = _m_pfmul( m2q1, r0 );
        m3q0 = _m_pfmul( m3q0, r0 );
        m3q1 = _m_pfmul( m3q1, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator *=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator *= (const Mat4_3DNow& n)
    {
        Mat4_3DNow k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z + m[ 3 ].x * n[ 0 ].w;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z + m[ 3 ].x * n[ 1 ].w;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z + m[ 3 ].x * n[ 2 ].w;
        k[ 3 ].x = m[ 0 ].x * n[ 3 ].x + m[ 1 ].x * n[ 3 ].y + m[ 2 ].x * n[ 3 ].z + m[ 3 ].x * n[ 3 ].w;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z + m[ 3 ].y * n[ 0 ].w;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z + m[ 3 ].y * n[ 1 ].w;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z + m[ 3 ].y * n[ 2 ].w;
        k[ 3 ].y = m[ 0 ].y * n[ 3 ].x + m[ 1 ].y * n[ 3 ].y + m[ 2 ].y * n[ 3 ].z + m[ 3 ].y * n[ 3 ].w;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z + m[ 3 ].z * n[ 0 ].w;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z + m[ 3 ].z * n[ 1 ].w;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z + m[ 3 ].z * n[ 2 ].w;
        k[ 3 ].z = m[ 0 ].z * n[ 3 ].x + m[ 1 ].z * n[ 3 ].y + m[ 2 ].z * n[ 3 ].z + m[ 3 ].z * n[ 3 ].w;

        k[ 0 ].w = m[ 0 ].w * n[ 0 ].x + m[ 1 ].w * n[ 0 ].y + m[ 2 ].w * n[ 0 ].z + m[ 3 ].w * n[ 0 ].w;
        k[ 1 ].w = m[ 0 ].w * n[ 1 ].x + m[ 1 ].w * n[ 1 ].y + m[ 2 ].w * n[ 1 ].z + m[ 3 ].w * n[ 1 ].w;
        k[ 2 ].w = m[ 0 ].w * n[ 2 ].x + m[ 1 ].w * n[ 2 ].y + m[ 2 ].w * n[ 2 ].z + m[ 3 ].w * n[ 2 ].w;
        k[ 3 ].w = m[ 0 ].w * n[ 3 ].x + m[ 1 ].w * n[ 3 ].y + m[ 2 ].w * n[ 3 ].z + m[ 3 ].w * n[ 3 ].w;

        m[ 0 ] = k[ 0 ];
        m[ 1 ] = k[ 1 ];
        m[ 2 ] = k[ 2 ];
        m[ 3 ] = k[ 3 ];

        return *this;
    }

    //
    // operator /=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator /= (const float& s)
    {
        __m64 r0;

        r0 = _m_from_float( s );
        r0 = _m_pfrcp( r0 );

        m0q0 = _m_pfmul( m0q0, r0 );
        m0q1 = _m_pfmul( m0q1, r0 );
        m1q0 = _m_pfmul( m1q0, r0 );
        m1q1 = _m_pfmul( m1q1, r0 );
        m2q0 = _m_pfmul( m2q0, r0 );
        m2q1 = _m_pfmul( m2q1, r0 );
        m3q0 = _m_pfmul( m3q0, r0 );
        m3q1 = _m_pfmul( m3q1, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator +=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator += (const float& s)
    {
        __m64 r0;

        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        m0q0 = _m_pfadd( m0q0, r0 );
        m0q1 = _m_pfadd( m0q1, r0 );
        m1q0 = _m_pfadd( m1q0, r0 );
        m1q1 = _m_pfadd( m1q1, r0 );
        m2q0 = _m_pfadd( m2q0, r0 );
        m2q1 = _m_pfadd( m2q1, r0 );
        m3q0 = _m_pfadd( m3q0, r0 );
        m3q1 = _m_pfadd( m3q1, r0 );
    
        _m_femms();

        return *this;
    }

    //
    // operator +=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator += (const Mat4_3DNow& n)
    {
        m0q0 = _m_pfadd( m0q0, n.m0q0 );
        m0q1 = _m_pfadd( m0q1, n.m0q1 );
        m1q0 = _m_pfadd( m1q0, n.m1q0 );
        m1q1 = _m_pfadd( m1q1, n.m1q1 );
        m2q0 = _m_pfadd( m2q0, n.m2q0 );
        m2q1 = _m_pfadd( m2q1, n.m2q1 );
        m3q0 = _m_pfadd( m3q0, n.m3q0 );
        m3q1 = _m_pfadd( m3q1, n.m3q1 );

        _m_femms();

        return *this;
    }

    //
    // operator -=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator -= (const float& s)
    {
        __m64 r0;

        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        m0q0 = _m_pfsub( m0q0, r0 );
        m0q1 = _m_pfsub( m0q1, r0 );
        m1q0 = _m_pfsub( m1q0, r0 );
        m1q1 = _m_pfsub( m1q1, r0 );
        m2q0 = _m_pfsub( m2q0, r0 );
        m2q1 = _m_pfsub( m2q1, r0 );
        m3q0 = _m_pfsub( m3q0, r0 );
        m3q1 = _m_pfsub( m3q1, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator -=
    //
    inline Mat4_3DNow& Mat4_3DNow::operator -= (const Mat4_3DNow& n)
    {
        m0q0 = _m_pfsub( m0q0, n.m0q0 );
        m0q1 = _m_pfsub( m0q1, n.m0q1 );
        m1q0 = _m_pfsub( m1q0, n.m1q0 );
        m1q1 = _m_pfsub( m1q1, n.m1q1 );
        m2q0 = _m_pfsub( m2q0, n.m2q0 );
        m2q1 = _m_pfsub( m2q1, n.m2q1 );
        m3q0 = _m_pfsub( m3q0, n.m3q0 );
        m3q1 = _m_pfsub( m3q1, n.m3q1 );

        _m_femms();

        return *this;
    }

    //
    // operator *
    //
    inline Mat4_3DNow Mat4_3DNow::operator * (const float& s) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;
    
        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        r7 = _m_pfmul( m3q1, r0 );
        r6 = _m_pfmul( m3q0, r0 );
        r5 = _m_pfmul( m2q1, r0 );
        r4 = _m_pfmul( m2q0, r0 );
        r3 = _m_pfmul( m1q1, r0 );
        r2 = _m_pfmul( m1q0, r0 );
        r1 = _m_pfmul( m0q1, r0 );
        r0 = _m_pfmul( m0q0, r0 );

        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator *
    //
    inline Vec4_3DNow Mat4_3DNow::operator * (const Vec4_3DNow& v) const
    {
        __m64 r0, r1, r2, r3;
        __m64 q0, q1;
    
        r0 = _m_pfmul( m0q0, v.m1 ); 
        r1 = _m_pfmul( m0q1, v.m2 );
        r2 = _m_pfmul( m1q0, v.m1 );
        r3 = _m_pfmul( m1q1, v.m2 );
        r0 = _m_pfacc( r0, r1 );
        r2 = _m_pfacc( r2, r3 );
        r0 = _m_pfacc( r0, r0 );
        r2 = _m_pfacc( r2, r2 );

        q0 = _m_punpckldq( r0, r2 ); // x, y

        r0 = _m_pfmul( m2q0, v.m1 ); 
        r1 = _m_pfmul( m2q1, v.m2 );
        r2 = _m_pfmul( m3q0, v.m1 );
        r3 = _m_pfmul( m3q1, v.m2 );
        r0 = _m_pfacc( r0, r1 );
        r2 = _m_pfacc( r2, r3 );
        r0 = _m_pfacc( r0, r0 );
        r2 = _m_pfacc( r2, r2 );

        q1 = _m_punpckldq( r0, r2 ); // z, w

        Vec4_3DNow u( q0, q1 );

        _m_femms();

        return u;
    }

    //
    // operator *
    //
    inline Mat4_3DNow Mat4_3DNow::operator * (const Mat4_3DNow& n) const
    {
        Mat4_3DNow k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z + m[ 3 ].x * n[ 0 ].w;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z + m[ 3 ].x * n[ 1 ].w;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z + m[ 3 ].x * n[ 2 ].w;
        k[ 3 ].x = m[ 0 ].x * n[ 3 ].x + m[ 1 ].x * n[ 3 ].y + m[ 2 ].x * n[ 3 ].z + m[ 3 ].x * n[ 3 ].w;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z + m[ 3 ].y * n[ 0 ].w;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z + m[ 3 ].y * n[ 1 ].w;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z + m[ 3 ].y * n[ 2 ].w;
        k[ 3 ].y = m[ 0 ].y * n[ 3 ].x + m[ 1 ].y * n[ 3 ].y + m[ 2 ].y * n[ 3 ].z + m[ 3 ].y * n[ 3 ].w;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z + m[ 3 ].z * n[ 0 ].w;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z + m[ 3 ].z * n[ 1 ].w;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z + m[ 3 ].z * n[ 2 ].w;
        k[ 3 ].z = m[ 0 ].z * n[ 3 ].x + m[ 1 ].z * n[ 3 ].y + m[ 2 ].z * n[ 3 ].z + m[ 3 ].z * n[ 3 ].w;

        k[ 0 ].w = m[ 0 ].w * n[ 0 ].x + m[ 1 ].w * n[ 0 ].y + m[ 2 ].w * n[ 0 ].z + m[ 3 ].w * n[ 0 ].w;
        k[ 1 ].w = m[ 0 ].w * n[ 1 ].x + m[ 1 ].w * n[ 1 ].y + m[ 2 ].w * n[ 1 ].z + m[ 3 ].w * n[ 1 ].w;
        k[ 2 ].w = m[ 0 ].w * n[ 2 ].x + m[ 1 ].w * n[ 2 ].y + m[ 2 ].w * n[ 2 ].z + m[ 3 ].w * n[ 2 ].w;
        k[ 3 ].w = m[ 0 ].w * n[ 3 ].x + m[ 1 ].w * n[ 3 ].y + m[ 2 ].w * n[ 3 ].z + m[ 3 ].w * n[ 3 ].w;

        return k;
    }

    //
    // operator /
    //
    inline Mat4_3DNow Mat4_3DNow::operator / (const float& s) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;
    
        r0 = _m_from_float( s );
        r0 = _m_pfrcp( r0 );

        r7 = _m_pfmul( m3q1, r0 );
        r6 = _m_pfmul( m3q0, r0 );
        r5 = _m_pfmul( m2q1, r0 );
        r4 = _m_pfmul( m2q0, r0 );
        r3 = _m_pfmul( m1q1, r0 );
        r2 = _m_pfmul( m1q0, r0 );
        r1 = _m_pfmul( m0q1, r0 );
        r0 = _m_pfmul( m0q0, r0 );

        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator +
    //
    inline Mat4_3DNow Mat4_3DNow::operator + (const float& s) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;
    
        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        r7 = _m_pfadd( m3q1, r0 );
        r6 = _m_pfadd( m3q0, r0 );
        r5 = _m_pfadd( m2q1, r0 );
        r4 = _m_pfadd( m2q0, r0 );
        r3 = _m_pfadd( m1q1, r0 );
        r2 = _m_pfadd( m1q0, r0 );
        r1 = _m_pfadd( m0q1, r0 );
        r0 = _m_pfadd( m0q0, r0 );
        
        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator +
    //
    inline Mat4_3DNow Mat4_3DNow::operator + (const Mat4_3DNow& n) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;
    
        r0 = _m_pfadd( m0q0, n.m0q0 );
        r1 = _m_pfadd( m0q1, n.m0q1 );
        r2 = _m_pfadd( m1q0, n.m1q0 );
        r3 = _m_pfadd( m1q1, n.m1q1 );
        r4 = _m_pfadd( m2q0, n.m2q0 );
        r5 = _m_pfadd( m2q1, n.m2q1 );
        r6 = _m_pfadd( m3q0, n.m3q0 );
        r7 = _m_pfadd( m3q1, n.m3q1 );

        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator -
    //
    inline Mat4_3DNow Mat4_3DNow::operator - (const float& s) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;

        r0 = _m_from_float( s );
        r0 = _m_punpckldq( r0, r0 );

        r7 = _m_pfsub( m3q1, r0 );
        r6 = _m_pfsub( m3q0, r0 );
        r5 = _m_pfsub( m2q1, r0 );
        r4 = _m_pfsub( m2q0, r0 );
        r3 = _m_pfsub( m1q1, r0 );
        r2 = _m_pfsub( m1q0, r0 );
        r1 = _m_pfsub( m0q1, r0 );
        r0 = _m_pfsub( m0q0, r0 );

        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator -
    //
    inline Mat4_3DNow Mat4_3DNow::operator - (const Mat4_3DNow& n) const
    {
        __m64 r0, r1, r2, r3, r4, r5, r6, r7;

        r0 = _m_pfsub( m0q0, n.m0q0 );
        r1 = _m_pfsub( m0q1, n.m0q1 );
        r2 = _m_pfsub( m1q0, n.m1q0 );
        r3 = _m_pfsub( m1q1, n.m1q1 );
        r4 = _m_pfsub( m2q0, n.m2q0 );
        r5 = _m_pfsub( m2q1, n.m2q1 );
        r6 = _m_pfsub( m3q0, n.m3q0 );
        r7 = _m_pfsub( m3q1, n.m3q1 );

        Mat4_3DNow k( r0, r1, r2, r3, r4, r5, r6, r7 );

        _m_femms();

        return k;
    }

    //
    // operator ==
    //
    inline bool Mat4_3DNow::operator == (const Mat4_3DNow& n) const
    {
        return Compare( n );
    }

    //
    // operator !=
    //
    inline bool Mat4_3DNow::operator != (const Mat4_3DNow& n) const
    {
        return !Compare( n );
    }
}

#endif // __MATH_SIMD_MAT4_3DNOW_H__