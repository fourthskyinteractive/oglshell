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

// Файл: /Math/Matrix/Mat4.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_MAT4_H__
#define __MATH_MAT4_H__

namespace Math
{
    //  Матрица четвёртого порядка, запись по столбцам.

    class Mat4 : public Mat<4, Vec4<float> >
    {
    public:
                            Mat4();

                            Mat4( float s );
                            Mat4( float _00, float _01, float _02, float _03, 
                                float _10, float _11, float _12, float _13,
                                float _20, float _21, float _22, float _23, 
                                float _30, float _31, float _32, float _33 );

                            Mat4( const Vec3<float>& v );
                            Mat4( const Mat3& m );
                            Mat4( const Mat3& m, const Vec3<float>& v );
                            Mat4( const Vec4<float>& _0, const Vec4<float>& _1, const Vec4<float>& _2,
                                const Vec4<float>& _3 = Vec4<float>( 0.0f, 0.0f, 0.0f, 1.0f ) );
                            
                            Mat4( const float m[ 16 ] );
                            Mat4( const vector<float>& m );

        //
        // Interface
        //

        float               GetDeterminant() const;
                                                          
        Mat4                GetTransposed() const;
        bool                Inverse();
        Mat4                GetInverted() const;
        void                OrthoNormalize();
        Mat4                GetOrthoNormalized() const;

        void                Translation( float x, float y, float z );
        void                Translation( const Vec3<float>& v );
        void                RotationX( float Angle );
        void                RotationY( float Angle );
        void                RotationZ( float Angle );
        void                RotationXYZ( float x, float y, float z );
        void                Scaling( float x, float y, float z );
        void                ReflectionXY();
        void                ReflectionYZ();
        void                ReflectionZX();

        bool                Ortho( float Left, float Right, float Bottom, float Top, float ZNear, float ZFar );
        bool                Ortho2D( float Left, float Right, float Bottom, float Top );
        bool                PerspectiveRHS( float Fovy, float Aspect, float ZNear, float ZFar );
        bool                InfinitePerspectiveRHS( float Fovy, float Aspect, float ZNear, float ZFar );
        bool                PerspectiveLHS( float Fovy, float Aspect, float ZNear, float ZFar );
        bool                InfinitePerspectiveLHS( float Fovy, float Aspect, float ZNear, float ZFar );
    
        void                LookAt( const Vec3<float>& Eye, const Vec3<float>& Dir, const Vec3<float>& Up );
        void                LookAtGL( const Vec3<float>& Eye, const Vec3<float>& Center, const Vec3<float>& Up );

        void                SetRotation( const Mat3& m );
        Mat3                GetRotation() const;
        void                SetTranslation( const Vec3<float>& v );
        Vec3<float>         GetTranslation() const; 

        Mat3                ToMat3() const;
        Mat43               ToMat43() const;

        //
        // Operators
        //

        Mat4&               operator *= (const float& s);
        Mat4&               operator *= (const Mat4& m);
        Mat4&               operator /= (const float& s);
        Mat4&               operator += (const float& s);
        Mat4&               operator += (const Mat4& m);
        Mat4&               operator -= (const float& s);
        Mat4&               operator -= (const Mat4& m);

        Mat4                operator * (const float& s) const;
        friend Mat4         operator * (const float& s, const Mat4& m) { return m * s; }
        Vec3<float>         operator * (const Vec3<float>& v) const;
        friend Vec3<float>  operator * (const Vec3<float>& v, const Mat4& m) { return m * v; } 
        Vec4<float>         operator * (const Vec4<float>& v) const;
        friend Vec4<float>  operator * (const Vec4<float>& v, const Mat4& m) { return m * v; }
        Mat4                operator * (const Mat4& m) const;
        Mat4                operator / (const float& s) const;
        Mat4                operator + (const float& s) const;
        Mat4                operator + (const Mat4& m) const;
        Mat4                operator - (const float& s) const;
        Mat4                operator - (const Mat4& m) const;
    };

    //
    // operator *=
    //
    inline Mat4& Mat4::operator *= (const float& s)
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
    inline Mat4& Mat4::operator *= (const Mat4& n)
    {
        Mat4 k;

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
    inline Mat4& Mat4::operator /= (const float& s)
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
    inline Mat4& Mat4::operator += (const float& s)
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
    inline Mat4& Mat4::operator += (const Mat4& n)
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
    inline Mat4& Mat4::operator -= (const float& s)
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
    inline Mat4& Mat4::operator -= (const Mat4& n)
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
    inline Mat4 Mat4::operator * (const float& s) const
    {
        return Mat4( m[ 0 ] * s, m[ 1 ] * s, m[ 2 ] * s, m[ 3 ] * s );
    }

    //
    // operator *
    //
    inline Vec3<float> Mat4::operator * (const Vec3<float>& v) const
    {
        Vec3<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z + m[ 3 ].x;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z + m[ 3 ].y;
        u.z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z + m[ 3 ].z;
    
        // Проективное преобразование.
        float w = m[ 0 ].w * v.x + m[ 1 ].w * v.y + m[ 2 ].w * v.z + m[ 3 ].w; 
        if (w != 1.0f)
            u /= w;

       return u;
    }

    //
    // operator *
    //
    inline Vec4<float> Mat4::operator * (const Vec4<float>& v) const
    {
        Vec4<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z + m[ 3 ].x * v.w;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z + m[ 3 ].y * v.w;
        u.z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z + m[ 3 ].z * v.w;
        u.w = m[ 0 ].w * v.x + m[ 1 ].w * v.y + m[ 2 ].w * v.z + m[ 3 ].w * v.w;

        return u;
    }

    //
    // operator *
    //
    inline Mat4 Mat4::operator * (const Mat4& n) const
    {
        Mat4 k;
    
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
    inline Mat4 Mat4::operator / (const float& s) const
    {
        assert( s != 0.0f );

        float r = 1.0f / s;

        return Mat4( m[ 0 ] * r, m[ 1 ] * r, m[ 2 ] * r, m[ 3 ] * r );
    }

    //
    // operator +
    //
    inline Mat4 Mat4::operator + (const float& s) const
    {
        return Mat4( m[ 0 ] + s, m[ 1 ] + s, m[ 2 ] + s, m[ 3 ] + s );
    }

    //
    // operator +
    //
    inline Mat4 Mat4::operator + (const Mat4& n) const
    {
        return Mat4( m[ 0 ] + n[ 0 ], m[ 1 ] + n[ 1 ], m[ 2 ] + n[ 2 ], m[ 3 ] + n[ 3 ] );
    }

    //
    // operator -
    //
    inline Mat4 Mat4::operator - (const float& s) const
    {
        return Mat4( m[ 0 ] - s, m[ 1 ] - s, m[ 2 ] - s, m[ 3 ] - s );
    }

    //
    // operator -
    //
    inline Mat4 Mat4::operator - (const Mat4& n) const
    {
        return Mat4( m[ 0 ] - n[ 0 ], m[ 1 ] - n[ 1 ], m[ 2 ] - n[ 2 ], m[ 3 ] - n[ 3 ] );
    }
}

#endif // __MATH_MAT4_H__