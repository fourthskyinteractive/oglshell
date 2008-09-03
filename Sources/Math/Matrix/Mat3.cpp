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

// Файл: /Math/Matrix/Mat3.cpp
//

#include "Pch.h"
#pragma hdrstop

namespace Math
{
    //
    // Constructor
    //
    Mat3::Mat3():
        Mat<3, Vec3<float> >( 1.0f )
    {
    }

    //
    // Constructor
    //
    Mat3::Mat3( float s ):
        Mat<3, Vec3<float> >( s )
    {
    }

    //
    // Constructor
    //
    Mat3::Mat3( 
               float _00, float _01, float _02, 
               float _10, float _11, float _12, 
               float _20, float _21, float _22 
               )
    {
        m[ 0 ][ 0 ] = _00;
        m[ 0 ][ 1 ] = _01;
        m[ 0 ][ 2 ] = _02;

        m[ 1 ][ 0 ] = _10;
        m[ 1 ][ 1 ] = _11;
        m[ 1 ][ 2 ] = _12;

        m[ 2 ][ 0 ] = _20;
        m[ 2 ][ 1 ] = _21;
        m[ 2 ][ 2 ] = _22;
    }

    //
    // Constructor
    //
    Mat3::Mat3( const Vec2<float>& v )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = v.x;
        m[ 2 ].y = v.y;
        m[ 2 ].z = 1.0f;
    }

    //
    // Constructor
    //
    Mat3::Mat3( const Mat2& m ):
        Mat<3, Vec3<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat3::Mat3( const Mat2& m, const Vec2<float>& v ):
        Mat<3, Vec3<float> >( m, v )
    {
    }

    //
    // Constructor
    //
    Mat3::Mat3( const Vec3<float>& _0, const Vec3<float>& _1, const Vec3<float>& _2 )
    {
       m[ 0 ] = _0;
       m[ 1 ] = _1;
       m[ 2 ] = _2;
    }

    //
    // Constructor
    //
    Mat3::Mat3( const float m[ 9 ] ):
        Mat<3, Vec3<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat3::Mat3( const vector<float>& m ):
        Mat<3, Vec3<float> >( m )
    {
    }

    //
    // GetDeterminant
    //
    float Mat3::GetDeterminant() const
    {
        return m[ 0 ][ 0 ] * (m[ 1 ][ 1 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 1 ]) + m[ 0 ][ 1 ] * -(m[ 1 ][ 0 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 0 ]) + m[ 0 ][ 2 ] * (m[ 1 ][ 0 ] * m[ 2 ][ 1 ] - m[ 1 ][ 1 ] * m[ 2 ][ 0 ]);
    }

    //
    // GetTransposed
    //
    Mat3 Mat3::GetTransposed() const
    {
        Mat3 n( *this );

        n.Transpose();

        return n;
    }

    //
    // Invert
    //
    bool Mat3::Invert()
    {
        Mat3 k;

        k[ 0 ][ 0 ] = m[ 1 ][ 1 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 1 ];
        k[ 1 ][ 0 ] = -(m[ 1 ][ 0 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 0 ]);
        k[ 2 ][ 0 ] = m[ 1 ][ 0 ] * m[ 2 ][ 1 ] - m[ 1 ][ 1 ] * m[ 2 ][ 0 ];

        float Det = m[ 0 ][ 0 ] * k[ 0 ][ 0 ] + m[ 0 ][ 1 ] * k[ 1 ][ 0 ] + m[ 0 ][ 2 ] * k[ 2 ][ 0 ];
        if (Abs( Det ) < EPSILON)
            return false;

        k[ 0 ][ 1 ] = -(m[ 0 ][ 1 ] * m[ 2 ][ 2 ] - m[ 0 ][ 2 ] * m[ 2 ][ 1 ]);
        k[ 1 ][ 1 ] = m[ 0 ][ 0 ] * m[ 2 ][ 2 ] - m[ 0 ][ 2 ] * m[ 2 ][ 0 ];
        k[ 2 ][ 1 ] = -(m[ 0 ][ 0 ] * m[ 2 ][ 1 ] - m[ 0 ][ 1 ] * m[ 2 ][ 0 ]);

        k[ 0 ][ 2 ] = m[ 0 ][ 1 ] * m[ 1 ][ 2 ] - m[ 0 ][ 2 ] * m[ 1 ][ 1 ];
        k[ 1 ][ 2 ] = -(m[ 0 ][ 0 ] * m[ 1 ][ 2 ] - m[ 0 ][ 2 ] * m[ 1 ][ 0 ]);
        k[ 2 ][ 2 ] = m[ 0 ][ 0 ] * m[ 1 ][ 1 ] - m[ 0 ][ 1 ] * m[ 1 ][ 0 ];

        m[ 0 ] = k[ 0 ];
        m[ 1 ] = k[ 1 ];
        m[ 2 ] = k[ 2 ];

        if (Abs( 1.0f - Det ) > EPSILON) 
        {
            float r = 1.0f / Det;

            m[ 0 ] *= r;
            m[ 1 ] *= r;
            m[ 2 ] *= r;
        }

        return true;
    }

    //
    // GetInverted
    //
    Mat3 Mat3::GetInverted() const
    {
        Mat3 n( *this );

        n.Invert();

        return n;
    }

    //
    // OrthoNormalize
    //
    void Mat3::OrthoNormalize()
    {
        m[ 0 ].Normalize();

        m[ 2 ] = CrossProduct( m[ 0 ], m[ 1 ] );
        m[ 2 ].Normalize();

        m[ 1 ] = CrossProduct( m[ 2 ], m[ 0 ] );
        m[ 1 ].Normalize();
    }

    //
    // GetOrtoNormalized
    //
    Mat3 Mat3::GetOrthoNormalized() const
    {
        Mat3 n( *this );

        n.OrthoNormalize();

        return n;
    }

    //
    // Translation
    //
    void Mat3::Translation( float x, float y )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = x;
        m[ 2 ].y = y;
        m[ 2 ].z = 1.0f;
    }

    //
    // Translation
    //
    void Mat3::Translation( const Vec2<float>& v )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = v.x;
        m[ 2 ].y = v.y;
        m[ 2 ].z = 1.0f;
    }

    //
    // RotationX
    //
    void Mat3::RotationX( float Angle )
    {
        float Rad = Radians( Angle );
    
        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = c;
        m[ 1 ].z = s;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = -s;
        m[ 2 ].z = c;
    }

    //
    // RotationY
    //
    void Mat3::RotationY( float Angle )
    {
        float Rad = Radians( Angle );

        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = c;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = -s;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = s;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = c;
    }

    //
    // RotationZ
    //
    void Mat3::RotationZ( float Angle )
    {
        float Rad = Radians( Angle );

        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = c;
        m[ 0 ].y = s;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = -s;
        m[ 1 ].y = c;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
    }

    //
    // RotationXYZ
    //
    void Mat3::RotationXYZ( float x, float y, float z )
    {
        x = Radians( x );
        y = Radians( y );
        z = Radians( z );

        float sx = Sin( x ); 
        float cx = Cos( x );
        float sy = Sin( y ); 
        float cy = Cos( y );
        float sz = Sin( z ); 
        float cz = Cos( z );

	    float sxsy = -sx * -sy;
	    float cxsy = cx * -sy;

	    m[ 0 ].x = cy * cz;
	    m[ 0 ].y = sxsy * cz + cx * sz;
	    m[ 0 ].z = cxsy * cz + sx * sz;

	    m[ 1 ].x = cy * -sz;
	    m[ 1 ].y = sxsy * -sz + cx * cz;
	    m[ 1 ].z = cxsy * -sz + sx * cz;

	    m[ 2 ].x = sy;	  
	    m[ 2 ].y = -sx * cy; 
	    m[ 2 ].z = cx * cy;
    }

    //
    // RotationAroundAxis
    //
    void Mat3::RotationAroundAxis( const Vec3<float>& Axis, float Angle )
    {
	    // x^2 + (1 - x^2) * cos(a) => x^2 + cos(a) - x^2 * cos(a) => 
        // x^2 * (1 - cos(a)) + cos(a)

    #ifdef _DEBUG
	    Axis.Assume();
    #endif

        float Rad = Radians( Angle );

        float s = Sin( Rad );
        float c = Cos( Rad );
	    float d = 1.0f - c;

	    float xs = Axis.x * s;
	    float ys = Axis.y * s;
	    float zs = Axis.z * s;

	    float xyd = Axis.x * Axis.y * d;
	    float xzd = Axis.x * Axis.z * d;
	    float yzd = Axis.y * Axis.z * d;

	    m[ 0 ].x = Axis.x * Axis.x * d + c; 
	    m[ 0 ].y = xyd + zs;
	    m[ 0 ].z = xzd - ys;

	    m[ 1 ].x = xyd - zs;
	    m[ 1 ].y = Axis.y * Axis.y * d + c; 
	    m[ 1 ].z = yzd + xs;

	    m[ 2 ].x = xzd + ys;
	    m[ 2 ].y = yzd - xs;
	    m[ 2 ].z = Axis.z * Axis.z * d + c;
    }

    //
    // Scaling
    //
    void Mat3::Scaling( float x, float y )
    {
        m[ 0 ].x = x;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = y;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
    }

    //
    // ReflectionX
    //
    void Mat3::ReflectionX()
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = -1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
    }

    //
    // ReflectionY
    //
    void Mat3::ReflectionY()
    {
        m[ 0 ].x = -1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
    }

    //
    // SetTranslation
    //
    void Mat3::SetTranslation( const Vec2<float>& v )
    {
        m[ 2 ].x = v.x;
        m[ 2 ].y = v.y;
    }

    //
    // GetTranslation
    //
    Vec2<float> Mat3::GetTranslation() const
    {
        return m[ 2 ].ToVec2<float>();
    }

    //
    // ToMat2
    //
    Mat2 Mat3::ToMat2() const
    {
        Mat2 n;

        n[ 0 ].x = m[ 0 ].x;
        n[ 0 ].y = m[ 0 ].y;

        n[ 1 ].x = m[ 1 ].x;
        n[ 1 ].y = m[ 1 ].y;

        return n;
    }

/*
// FIXME: матрица перводится в углы Эйлера так, как будто была получена 
// из комбинации roll * yaw * pitch. Найти другой метод и переделать на pitch * yaw * roll.
Euler Mat3::ToEuler() const
{
    Euler angles;

    float s = Clamp( m[ 0 ][ 2 ], -1.0f, 1.0f );
    float theta = -ASin( s );
    float c = Cos( theta );

    angles.yaw = theta;
    if (c > EPSILON) {
        angles.pitch = atan2( m[ 1 ][ 2 ], m[ 2 ][ 2 ] );
        angles.roll = atan2( m[ 0 ][ 1 ], m[ 0 ][ 0 ] );
        
    } else {
        angles.pitch = 0;
        angles.roll = -atan2( m[ 1 ][ 0 ], m[ 1 ][ 1 ] );
    }

    return angles.ToDegrees();
}

AxisAngle Mat3::ToAxisAngle() const
{
    return ToQuat4().ToAxisAngle();
}
*/

    //
    // ToQuat3
    //
    Quat3<float> Mat3::ToQuat3() const
    {
        return ToQuat4().ToQuat3();
    }

    //
    // ToQuat4
    //
    Quat4<float> Mat3::ToQuat4() const
    {
        Quat4<float> q;
        float s, tr = Trace();

        if (tr > 0.0) 
        {                         
            q.x = m[ 1 ][ 2 ] - m[ 2 ][ 1 ];
            q.y = m[ 2 ][ 0 ] - m[ 0 ][ 2 ];
            q.z = m[ 0 ][ 1 ] - m[ 1 ][ 0 ];
            q.w = tr + 1.0f;
            s = q.w;
        }
        else if ((m[ 0 ][ 0 ] > m[ 1 ][ 1 ]) && (m[ 0 ][ 0 ] > m[ 2 ][ 2 ])) 
        {
            q.x = 1.0f + m[ 0 ][ 0 ] - m[ 1 ][ 1 ] - m[ 2 ][ 2 ];
            q.y = m[ 1 ][ 0 ] + m[ 0 ][ 1 ];
            q.z = m[ 2 ][ 0 ] + m[ 0 ][ 2 ];
            q.w = m[ 1 ][ 2 ] - m[ 2 ][ 1 ];
            s = q.x;
        }
        else if (m[ 1 ][ 1 ] > m[ 2 ][ 2 ]) 
        {
            q.x = m[ 1 ][ 0 ] + m[ 0 ][ 1 ];
            q.y = 1.0f + m[ 1 ][ 1 ] - m[ 0 ][ 0 ] - m[ 2 ][ 2 ];
            q.z = m[ 2 ][ 1 ] + m[ 1 ][ 2 ];
            q.w = m[ 2 ][ 0 ] - m[ 0 ][ 2 ];
            s = q.y;
        }
        else 
        {
            q.x = m[ 2 ][ 0 ] + m[ 0 ][ 2 ];
            q.y = m[ 2 ][ 1 ] + m[ 1 ][ 2 ];
            q.z = 1.0f + m[ 2 ][ 2 ] - m[ 0 ][ 0 ] - m[ 1 ][ 1 ];
            q.w = m[ 0 ][ 1 ] - m[ 1 ][ 0 ];
            s = q.z;
        }

        float Scale = 0.5f / SqRt( s );

        return q *= Scale;
    }

    //
    // ToAngularVelocity
    //
    Vec3<float> Mat3::ToAngularVelocity() const
    {
        return ToQuat4().ToAngularVelocity();
    }
}