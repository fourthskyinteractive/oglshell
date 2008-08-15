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

// Файл: /Math/Matrix/Mat43.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_MAT43_H__
#define __MATH_MAT43_H__

namespace Math
{
    //  Матрица из четырёх столбцов по три элемента в каждом, запись по столбцам.
    //  Строка проективного преобразования всегда равна (0, 0, 0, 1).

    class Mat43 : public Mat<4, Vec3<float> >
    {
    public:
                            Mat43();
                                
                            Mat43( float s );
                            Mat43( float _00, float _01, float _02,
                                float _10, float _11, float _12,
                                float _20, float _21, float _22, 
                                float _30, float _31, float _32 );

                            Mat43( const Vec3<float>& v );
                            Mat43( const Mat3& m, const Vec3<float>& v = Vec3<float>( 0.0f ) );
                            Mat43( const Vec3<float>& _0, const Vec3<float>& _1, const Vec3<float>& _2, 
                                const Vec3<float>& _3 = Vec3<float>( 0.0f, 0.0f, 1.0f ) );

                            Mat43( const float m[ 12 ] );
                            Mat43( const vector<float>& m );

        //
        // Interface
        //

        void                SetRotation( const Mat3& m );
        void                SetTranslation( const Vec3<float>& v );
        const Vec3<float>&  GetTranslation() const;

        Mat3                ToMat3() const;

        //
        // Operators
        //

        Mat43&              operator *= (const float& s);
        Mat43&              operator *= (const Mat43& n);
        Mat43&              operator /= (const float& s);
        Mat43&              operator += (const float& s);
        Mat43&              operator += (const Mat43& m);
        Mat43&              operator -= (const float& s);
        Mat43&              operator -= (const Mat43& m);

        Mat43               operator * (const float& s) const;
        friend Mat43        operator * (const float& s, const Mat43& m) { return m * s; }
        Vec3<float>         operator * (const Vec3<float>& v) const;
        friend Vec3<float>  operator * (const Vec3<float>& v, const Mat43& m) { return m * v; } 
        Vec4<float>         operator * (const Vec4<float>& v) const;
        friend Vec4<float>  operator * (const Vec4<float>& v, const Mat43& m) { return m * v; }
        Mat43               operator * (const Mat43& m) const;             
        Mat43               operator / (const float& s) const;
        Mat43               operator + (const float& s) const;
        Mat43               operator + (const Mat43& m) const;
        Mat43               operator - (const float& s) const;
        Mat43               operator - (const Mat43& m) const;
    };

    //
    // operator *=
    //
    inline Mat43& Mat43::operator *= (const float& s)
    {
        m[ 0 ] *= s;
        m[ 1 ] *= s;
        m[ 2 ] *= s;
        m[ 3 ] *= s;

        return *this;
    }

    //
    // operator *=
    //
    inline Mat43& Mat43::operator *= (const Mat43& n)
    {
        Mat43 k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z;
        k[ 3 ].x = m[ 0 ].x * n[ 3 ].x + m[ 1 ].x * n[ 3 ].y + m[ 2 ].x * n[ 3 ].z + m[ 3 ].x;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z;
        k[ 3 ].y = m[ 0 ].y * n[ 3 ].x + m[ 1 ].y * n[ 3 ].y + m[ 2 ].y * n[ 3 ].z + m[ 3 ].y;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z;
        k[ 3 ].z = m[ 0 ].z * n[ 3 ].x + m[ 1 ].z * n[ 3 ].y + m[ 2 ].z * n[ 3 ].z + m[ 3 ].z;

        m[ 0 ] = k[ 0 ];
        m[ 1 ] = k[ 1 ];
        m[ 2 ] = k[ 2 ];
        m[ 3 ] = k[ 3 ];

        return *this;
    }

    //
    // operator /=
    //
    inline Mat43& Mat43::operator /= (const float& s)
    {
        assert( s != 0.0f );
        
        float r = 1.0f / s;

        m[ 0 ] *= r;
        m[ 1 ] *= r;
        m[ 2 ] *= r;
        m[ 3 ] *= r;

        return *this;
    }

    //
    // operator +=
    //
    inline Mat43& Mat43::operator += (const float& s)
    {
        m[ 0 ] += s;
        m[ 1 ] += s;
        m[ 2 ] += s;
        m[ 3 ] += s;

        return *this;
    }

    //
    // operator +=
    //
    inline Mat43& Mat43::operator += (const Mat43& n)
    {
        m[ 0 ] += n[ 0 ];
        m[ 1 ] += n[ 1 ];
        m[ 2 ] += n[ 2 ];
        m[ 3 ] += n[ 3 ];

        return *this;
    }

    //
    // operator -=
    //
    inline Mat43& Mat43::operator -= (const float& s)
    {
        m[ 0 ] -= s;
        m[ 1 ] -= s;
        m[ 2 ] -= s;
        m[ 3 ] -= s;

        return *this;
    }

    //
    // operator -=
    //
    inline Mat43& Mat43::operator -= (const Mat43& n)
    {
        m[ 0 ] -= n[ 0 ];
        m[ 1 ] -= n[ 1 ];
        m[ 2 ] -= n[ 2 ];
        m[ 3 ] -= n[ 3 ];

        return *this;
    }

    //
    // operator *
    //
    inline Mat43 Mat43::operator * (const float& s) const
    {
        return Mat43( m[ 0 ] * s, m[ 1 ] * s, m[ 2 ] * s, m[ 3 ] * s );
    }

    //
    // operator *
    //
    inline Vec3<float> Mat43::operator * (const Vec3<float>& v) const
    {
        Vec3<float> u;
                                                        // + t
        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z + m[ 3 ].x;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z + m[ 3 ].y;
        u.z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z + m[ 3 ].z;

        return u;
    }
 
    //
    // operator *
    //
    inline Vec4<float> Mat43::operator * (const Vec4<float>& v) const
    {
        Vec4<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z + m[ 3 ].x * v.w;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z + m[ 3 ].y * v.w;
        u.z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z + m[ 3 ].z * v.w;
        u.w = v.w;

        return u;
    }

    //
    // operator *
    //
    inline Mat43 Mat43::operator * (const Mat43& n) const
    {
        Mat43 k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z;
        k[ 3 ].x = m[ 0 ].x * n[ 3 ].x + m[ 1 ].x * n[ 3 ].y + m[ 2 ].x * n[ 3 ].z + m[ 3 ].x;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z;
        k[ 3 ].y = m[ 0 ].y * n[ 3 ].x + m[ 1 ].y * n[ 3 ].y + m[ 2 ].y * n[ 3 ].z + m[ 3 ].y;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z;
        k[ 3 ].z = m[ 0 ].z * n[ 3 ].x + m[ 1 ].z * n[ 3 ].y + m[ 2 ].z * n[ 3 ].z + m[ 3 ].z;

        return k;
    }

    //
    // operator /
    //
    inline Mat43 Mat43::operator / (const float& s) const
    {
        assert( s != 0.0f );
        
        float r = 1.0f / s;

        return Mat43( m[ 0 ] * r, m[ 1 ] * r, m[ 2 ] * r, m[ 3 ] * r );
    }

    //
    // operator +
    //
    inline Mat43 Mat43::operator + (const float& s) const
    {
        return Mat43( m[ 0 ] + s, m[ 1 ] + s, m[ 2 ] + s, m[ 3 ] + s );
    }

    //
    // operator +
    //
    inline Mat43 Mat43::operator + (const Mat43& n) const
    {
        return Mat43( m[ 0 ] + n[ 0 ], m[ 1 ] + n[ 1 ], m[ 2 ] + n[ 2 ], m[ 3 ] + n[ 3 ] );
    }

    //
    // operator -
    //
    inline Mat43 Mat43::operator - (const float& s) const
    {
        return Mat43( m[ 0 ] - s, m[ 1 ] - s, m[ 2 ] - s, m[ 3 ] - s );
    }

    //
    // operator -
    //
    inline Mat43 Mat43::operator - (const Mat43& n) const
    {
        return Mat43( m[ 0 ] - n[ 0 ], m[ 1 ] - n[ 1 ], m[ 2 ] - n[ 2 ], m[ 3 ] - n[ 3 ] );
    }
}

#endif // __MATH_MAT43_H__