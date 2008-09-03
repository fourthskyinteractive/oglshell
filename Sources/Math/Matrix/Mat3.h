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

// Файл: /Math/Matrix/Mat3.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_MAT3_H__
#define __MATH_MAT3_H__

namespace Math
{
    class Euler;
    class AxisAngle;

    template <typename T>
    class Quat4;
    template <typename T>
    class Quat3;

    //  Матрица третьего порядка, запись по столбцам.

    class Mat3 : public Mat<3, Vec3<float> >
    {
    public:
                            Mat3();
                            
                            Mat3( float s );
                            Mat3( float _00, float _01, float _02,
                                float _10, float _11, float _12, 
                                float _20, float _21, float _22 );

                            Mat3( const Vec2<float>& v );
                            Mat3( const Mat2& m );
                            Mat3( const Mat2& m, const Vec2<float>& v );
                            Mat3( const Vec3<float>& _0, const Vec3<float>& _1,
                                const Vec3<float>& _2 = Vec3<float>( 0.0f, 0.0f, 1.0f ) );
                         
                            Mat3( const float m[ 9 ] );
                            Mat3( const vector<float>& m );

        //
        // Interface
        //

        float               GetDeterminant() const;

        Mat3                GetTransposed() const;
        bool                Invert();
        Mat3                GetInverted() const;
        void                OrthoNormalize();
        Mat3                GetOrthoNormalized() const;

        void                Translation( float x, float y );
        void                Translation( const Vec2<float>& v );
        void                RotationX( float Angle ); 
        void                RotationY( float Angle );
        void                RotationZ( float Angle );
        void                RotationXYZ( float x, float y, float z );
        void                RotationAroundAxis( const Vec3<float>& Axis, float Angle );
        void                Scaling( float x, float y );
        void                ReflectionX();
        void                ReflectionY();

        void                SetTranslation( const Vec2<float>& v );
        Vec2<float>         GetTranslation() const;

        Mat2                ToMat2() const;
        //Euler               ToEuler() const;
        //AxisAngle           ToAxisAngle() const;
        Quat3<float>        ToQuat3() const;
        Quat4<float>        ToQuat4() const;
        Vec3<float>         ToAngularVelocity() const;

        //
        // Operators
        //

        Mat3&               operator *= (const float& s);
        Mat3&               operator *= (const Mat3& m);
        Mat3&               operator /= (const float& s);
        Mat3&               operator += (const Mat3& m);
        Mat3&               operator -= (const Mat3& m);

        Mat3                operator * (const float& s) const;
        friend Mat3         operator * (const float& s, const Mat3& m) { return m * s; } 
        Vec2<float>         operator * (const Vec2<float>& v) const;
        friend Vec2<float>  operator * (const Vec2<float>& v, const Mat3& m) { return m * v; }
        Vec3<float>         operator * (const Vec3<float>& v) const;
        friend Vec3<float>  operator * (const Vec3<float>& v, const Mat3& m) { return m * v; }
        Mat3                operator * (const Mat3& m) const;
        Mat3                operator / (const float& s) const;
        Mat3                operator + (const Mat3& m) const;
        Mat3                operator - (const Mat3& m) const;
    };

    //
    // operator *=
    //
    inline Mat3& Mat3::operator *= (const float& s)
    {
        m[ 0 ] *= s;
        m[ 1 ] *= s;
        m[ 2 ] *= s;

        return *this;
    }

    //
    // operator *=
    //
    inline Mat3& Mat3::operator *= (const Mat3& n)
    {
        Mat3 k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z;
    
        m[ 0 ] = k[ 0 ];
        m[ 1 ] = k[ 1 ];
        m[ 2 ] = k[ 2 ];

        return *this;
    }

    //
    // operator /=
    //
    inline Mat3& Mat3::operator /= (const float& s)
    {
        assert( s != 0.0f );  

        float r = 1.0f / s;

        m[ 0 ] *= r;
        m[ 1 ] *= r;
        m[ 2 ] *= r;

        return *this;
    }

    //
    // operator +=
    //
    inline Mat3& Mat3::operator += (const Mat3& n)
    {
        m[ 0 ] += n[ 0 ];
        m[ 1 ] += n[ 1 ];
        m[ 2 ] += n[ 2 ];

        return *this;
    }

    //
    // operator -=
    //
    inline Mat3& Mat3::operator -= (const Mat3& n)
    {
        m[ 0 ] -= n[ 0 ];
        m[ 1 ] -= n[ 1 ];
        m[ 2 ] -= n[ 2 ];

        return *this;
    }

    //
    // operator *
    //
    inline Mat3 Mat3::operator * (const float& s) const
    {
        return Mat3( m[ 0 ] * s, m[ 1 ] * s, m[ 2 ] * s );
    }

    //
    // operator *
    //
    inline Vec2<float> Mat3::operator * (const Vec2<float>& v) const
    {
        Vec2<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y;

        return u;
    }

    //
    // operator *
    //
    inline Vec3<float> Mat3::operator * (const Vec3<float>& v) const
    {
        Vec3<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z;
        u.z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z;

        return u;
    }

    //
    // operator *
    //
    inline Mat3 Mat3::operator * (const Mat3& n) const
    {
        Mat3 k;

        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y + m[ 2 ].x * n[ 0 ].z;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y + m[ 2 ].x * n[ 1 ].z;
        k[ 2 ].x = m[ 0 ].x * n[ 2 ].x + m[ 1 ].x * n[ 2 ].y + m[ 2 ].x * n[ 2 ].z;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y + m[ 2 ].y * n[ 0 ].z;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y + m[ 2 ].y * n[ 1 ].z;
        k[ 2 ].y = m[ 0 ].y * n[ 2 ].x + m[ 1 ].y * n[ 2 ].y + m[ 2 ].y * n[ 2 ].z;

        k[ 0 ].z = m[ 0 ].z * n[ 0 ].x + m[ 1 ].z * n[ 0 ].y + m[ 2 ].z * n[ 0 ].z;
        k[ 1 ].z = m[ 0 ].z * n[ 1 ].x + m[ 1 ].z * n[ 1 ].y + m[ 2 ].z * n[ 1 ].z;
        k[ 2 ].z = m[ 0 ].z * n[ 2 ].x + m[ 1 ].z * n[ 2 ].y + m[ 2 ].z * n[ 2 ].z;

        return k;
    }

    //
    // operator /
    //
    inline Mat3 Mat3::operator / (const float& s) const
    {
       assert( s != 0.0f );

       float r = 1.0f / s;
       
       return Mat3( m[ 0 ] * r, m[ 1 ] * r, m[ 2 ] * r );
    }

    //
    // operator +
    //
    inline Mat3 Mat3::operator + (const Mat3& n) const
    {
        return Mat3( m[ 0 ] + n[ 0 ], m[ 1 ] + n[ 1 ], m[ 2 ] + n[ 2 ] );
    }

    //
    // operator -
    //
    inline Mat3 Mat3::operator - (const Mat3& n) const
    {
        return Mat3( m[ 0 ] - n[ 0 ], m[ 1 ] - n[ 1 ], m[ 2 ] - n[ 2 ] );
    }
}

#endif // __MATH_MAT3_H__