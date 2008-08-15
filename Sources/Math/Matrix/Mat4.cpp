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

// Τΰιλ: /Math/Matrix/Mat4.cpp
//

#include "Precompiled.h"
#pragma hdrstop

namespace Math
{
    //
    // Constructor
    //
    Mat4::Mat4():
        Mat<4, Vec4<float> >( 1.0f )
    {
    }

    //
    // Constructor
    //
    Mat4::Mat4( float s ):
        Mat<4, Vec4<float> >( s )
    {
    }

    //
    // Constructor
    //
    Mat4::Mat4( 
               float _00, float _01, float _02, float _03,
               float _10, float _11, float _12, float _13,
               float _20, float _21, float _22, float _23,
               float _30, float _31, float _32, float _33 
               )
    {
        m[ 0 ][ 0 ] = _00;
        m[ 0 ][ 1 ] = _01;
        m[ 0 ][ 2 ] = _02;
        m[ 0 ][ 3 ] = _03;

        m[ 1 ][ 0 ] = _10;
        m[ 1 ][ 1 ] = _11;
        m[ 1 ][ 2 ] = _12;
        m[ 1 ][ 3 ] = _13;

        m[ 2 ][ 0 ] = _20;
        m[ 2 ][ 1 ] = _21;
        m[ 2 ][ 2 ] = _22;
        m[ 2 ][ 3 ] = _23;

        m[ 3 ][ 0 ] = _30;
        m[ 3 ][ 1 ] = _31;
        m[ 3 ][ 2 ] = _32;
        m[ 3 ][ 3 ] = _33;
    }

    //
    // Constructor
    //
    Mat4::Mat4( const Vec3<float>& v )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = v.x;
        m[ 3 ].y = v.y;
        m[ 3 ].z = v.z;
        m[ 3 ].w = 1.0f;
    }

    //
    // Constructor
    //
    Mat4::Mat4( const Mat3& m ):
        Mat<4, Vec4<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat4::Mat4( const Mat3& m, const Vec3<float>& v ):
        Mat<4, Vec4<float> >( m, v )
    {
    }

    //
    // Constructor
    //
    Mat4::Mat4( const Vec4<float>& _0, const Vec4<float>& _1, const Vec4<float>& _2, const Vec4<float>& _3 )
    {
        m[ 0 ] = _0;
        m[ 1 ] = _1;
        m[ 2 ] = _2;
        m[ 3 ] = _3;
    }

    //
    // Constructor
    //
    Mat4::Mat4( const float m[ 16 ] ):
        Mat<4, Vec4<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat4::Mat4( const vector<float>& m ):
        Mat<4, Vec4<float> >( m )
    {
    }

    //
    // GetDeterminant
    //
    float Mat4::GetDeterminant() const
    {
        float d22_33_23_32 = m[ 2 ][ 2 ] * m[ 3 ][ 3 ] - m[ 2 ][ 3 ] * m[ 3 ][ 2 ];
        float d21_33_23_31 = m[ 2 ][ 1 ] * m[ 3 ][ 3 ] - m[ 2 ][ 3 ] * m[ 3 ][ 1 ];
        float d21_32_22_31 = m[ 2 ][ 1 ] * m[ 3 ][ 2 ] - m[ 2 ][ 2 ] * m[ 3 ][ 1 ];
        float d20_33_23_30 = m[ 2 ][ 0 ] * m[ 3 ][ 3 ] - m[ 2 ][ 3 ] * m[ 3 ][ 0 ];
        float d20_32_22_30 = m[ 2 ][ 0 ] * m[ 3 ][ 2 ] - m[ 2 ][ 2 ] * m[ 3 ][ 0 ];
        float d20_31_21_30 = m[ 2 ][ 0 ] * m[ 3 ][ 1 ] - m[ 2 ][ 1 ] * m[ 3 ][ 0 ];

        return m[ 0 ][ 0 ] *  (m[ 1 ][ 1 ] * d22_33_23_32 - m[ 1 ][ 2 ] * d21_33_23_31 + m[ 1 ][ 3 ] * d21_32_22_31) +
            m[ 0 ][ 1 ] * -(m[ 1 ][ 0 ] * d22_33_23_32 - m[ 1 ][ 2 ] * d20_33_23_30 + m[ 1 ][ 3 ] * d20_32_22_30) +
            m[ 0 ][ 2 ] *  (m[ 1 ][ 0 ] * d21_33_23_31 - m[ 1 ][ 1 ] * d20_33_23_30 + m[ 1 ][ 3 ] * d20_31_21_30) +
            m[ 0 ][ 3 ] * -(m[ 1 ][ 0 ] * d21_32_22_31 - m[ 1 ][ 1 ] * d20_32_22_30 + m[ 1 ][ 2 ] * d20_31_21_30);
    }       

    //
    // GetTransposed
    //
    Mat4 Mat4::GetTransposed() const
    {
        Mat4 n( *this );

        n.Transpose();

        return n;
    }

    //
    // Inverse
    //
    bool Mat4::Inverse()
    {    
        float *m = this->ToPtr();

        float Det = m[ 0 * 4 + 0 ] * m[ 1 * 4 + 1 ] - m[ 0 * 4 + 1 ] * m[ 1 * 4 + 0 ];
        if (Abs( Det ) < EPSILON)
            return false;

        Mat2 r0, r1, r2, r3;

        r0[ 0 ][ 0 ] = m[ 1 * 4 + 1 ];
        r0[ 0 ][ 1 ] = -m[ 0 * 4 + 1 ];
        r0[ 1 ][ 0 ] = -m[ 1 * 4 + 0 ];
        r0[ 1 ][ 1 ] = m[ 0 * 4 + 0 ];

        if (Abs( 1.0f - Det ) > EPSILON) 
        {
            float r = 1.0f / Det;

            r0[ 0 ][ 0 ] *= r;
            r0[ 0 ][ 1 ] *= r;
            r0[ 1 ][ 0 ] *= r;
            r0[ 1 ][ 1 ] *= r;
        }

        r1[ 0 ][ 0 ] = r0[ 0 ][ 0 ] *  m[ 0 * 4 + 2 ] +  r0[ 0 ][ 1 ] * m[ 1 * 4 + 2 ];
        r1[ 0 ][ 1 ] = r0[ 0 ][ 0 ] *  m[ 0 * 4 + 3 ] +  r0[ 0 ][ 1 ] * m[ 1 * 4 + 3 ];
        r1[ 1 ][ 0 ] = r0[ 1 ][ 0 ] *  m[ 0 * 4 + 2 ] +  r0[ 1 ][ 1 ] * m[ 1 * 4 + 2 ];
        r1[ 1 ][ 1 ] = r0[ 1 ][ 0 ] *  m[ 0 * 4 + 3 ] +  r0[ 1 ][ 1 ] * m[ 1 * 4 + 3 ];

        r2[ 0 ][ 0 ] = m[ 2 * 4 + 0 ] * r1[ 0 ][ 0 ] + m[ 2 * 4 + 1 ] * r1[ 1 ][ 0 ];
        r2[ 0 ][ 1 ] = m[ 2 * 4 + 0 ] * r1[ 0 ][ 1 ] + m[ 2 * 4 + 1 ] * r1[ 1 ][ 1 ];
        r2[ 1 ][ 0 ] = m[ 3 * 4 + 0 ] * r1[ 0 ][ 0 ] + m[ 3 * 4 + 1 ] * r1[ 1 ][ 0 ];
        r2[ 1 ][ 1 ] = m[ 3 * 4 + 0 ] * r1[ 0 ][ 1 ] + m[ 3 * 4 + 1 ] * r1[ 1 ][ 1 ];

        r3[ 0 ][ 0 ] = r2[ 0 ][ 0 ] - m[ 2 * 4 + 2 ];
        r3[ 0 ][ 1 ] = r2[ 0 ][ 1 ] - m[ 2 * 4 + 3 ];
        r3[ 1 ][ 0 ] = r2[ 1 ][ 0 ] - m[ 3 * 4 + 2 ];
        r3[ 1 ][ 1 ] = r2[ 1 ][ 1 ] - m[ 3 * 4 + 3 ];

        Det = r3[ 0 ][ 0 ] * r3[ 1 ][ 1 ] - r3[ 0 ][ 1 ] * r3[ 1 ][ 0 ];
        if (Abs( Det ) < EPSILON)
            return false;

        std::swap( r3[ 0 ][ 0 ], r3[ 1 ][ 1 ] );
        r3[ 0 ][ 1 ] = -r3[ 0 ][ 1 ];
        r3[ 1 ][ 0 ] = -r3[ 1 ][ 0 ];

        if (Abs( 1.0f - Det ) > EPSILON) 
        {
            float r = 1.0f / Det;

            r3[ 0 ][ 0 ] *= r;
            r3[ 0 ][ 1 ] *= r;
            r3[ 1 ][ 0 ] *= r;
            r3[ 1 ][ 1 ] *= r;
        }

        r2[ 0 ][ 0 ] = m[ 2 * 4 + 0 ] * r0[ 0 ][ 0 ] + m[ 2 * 4 + 1 ] * r0[ 1 ][ 0 ];
        r2[ 0 ][ 1 ] = m[ 2 * 4 + 0 ] * r0[ 0 ][ 1 ] + m[ 2 * 4 + 1 ] * r0[ 1 ][ 1 ];
        r2[ 1 ][ 0 ] = m[ 3 * 4 + 0 ] * r0[ 0 ][ 0 ] + m[ 3 * 4 + 1 ] * r0[ 1 ][ 0 ];
        r2[ 1 ][ 1 ] = m[ 3 * 4 + 0 ] * r0[ 0 ][ 1 ] + m[ 3 * 4 + 1 ] * r0[ 1 ][ 1 ];

        m[ 2 * 4 + 0 ] = r3[ 0 ][ 0 ] * r2[ 0 ][ 0 ] + r3[ 0 ][ 1 ] * r2[ 1 ][ 0 ];
        m[ 2 * 4 + 1 ] = r3[ 0 ][ 0 ] * r2[ 0 ][ 1 ] + r3[ 0 ][ 1 ] * r2[ 1 ][ 1 ];
        m[ 3 * 4 + 0 ] = r3[ 1 ][ 0 ] * r2[ 0 ][ 0 ] + r3[ 1 ][ 1 ] * r2[ 1 ][ 0 ];
        m[ 3 * 4 + 1 ] = r3[ 1 ][ 0 ] * r2[ 0 ][ 1 ] + r3[ 1 ][ 1 ] * r2[ 1 ][ 1 ];

        m[ 0 * 4 + 0 ] = r0[ 0 ][ 0 ] - r1[ 0 ][ 0 ] * m[ 2 * 4 + 0 ] - r1[ 0 ][ 1 ] * m[ 3 * 4 + 0 ];
        m[ 0 * 4 + 1 ] = r0[ 0 ][ 1 ] - r1[ 0 ][ 0 ] * m[ 2 * 4 + 1 ] - r1[ 0 ][ 1 ] * m[ 3 * 4 + 1 ];
        m[ 1 * 4 + 0 ] = r0[ 1 ][ 0 ] - r1[ 1 ][ 0 ] * m[ 2 * 4 + 0 ] - r1[ 1 ][ 1 ] * m[ 3 * 4 + 0 ];
        m[ 1 * 4 + 1 ] = r0[ 1 ][ 1 ] - r1[ 1 ][ 0 ] * m[ 2 * 4 + 1 ] - r1[ 1 ][ 1 ] * m[ 3 * 4 + 1 ];

        m[ 0 * 4 + 2 ] = r1[ 0 ][ 0 ] * r3[ 0 ][ 0 ] + r1[ 0 ][ 1 ] * r3[ 1 ][ 0 ];
        m[ 0 * 4 + 3 ] = r1[ 0 ][ 0 ] * r3[ 0 ][ 1 ] + r1[ 0 ][ 1 ] * r3[ 1 ][ 1 ];
        m[ 1 * 4 + 2 ] = r1[ 1 ][ 0 ] * r3[ 0 ][ 0 ] + r1[ 1 ][ 1 ] * r3[ 1 ][ 0 ];
        m[ 1 * 4 + 3 ] = r1[ 1 ][ 0 ] * r3[ 0 ][ 1 ] + r1[ 1 ][ 1 ] * r3[ 1 ][ 1 ];

        m[ 2 * 4 + 2 ] = -r3[ 0 ][ 0 ];
        m[ 2 * 4 + 3 ] = -r3[ 0 ][ 1 ];
        m[ 3 * 4 + 2 ] = -r3[ 1 ][ 0 ];
        m[ 3 * 4 + 3 ] = -r3[ 1 ][ 1 ];
    
        return true;
    }

    //
    // GetInverted
    //
    Mat4 Mat4::GetInverted() const
    {
        Mat4 n( *this );

        n.Inverse();

        return n;
    }

    //
    // OrthoNormalize
    //
    void Mat4::OrthoNormalize()
    {
        Vec3<float> v = m[ 0 ].ToVec3<float>();
        v.Normalize();
        
        m[ 0 ].x = v.x;
        m[ 0 ].y = v.y;
        m[ 0 ].z = v.z;
        
        v = CrossProduct( m[ 0 ], m[ 1 ] );
        v.Normalize();

        m[ 2 ].x = v.x;
        m[ 2 ].y = v.y;
        m[ 2 ].z = v.z;

        v = CrossProduct( m[ 2 ], m[ 0 ] );
        v.Normalize();

        m[ 1 ].x = v.x;
        m[ 1 ].y = v.y;
        m[ 1 ].z = v.z;
    }

    //
    // GetOrthoNormalized
    //
    Mat4 Mat4::GetOrthoNormalized() const
    {
        Mat4 n( *this );

        n.OrthoNormalize();

        return n;
    }

    //
    // Translation
    //
    void Mat4::Translation( float x, float y, float z )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = x;
        m[ 3 ].y = y;
        m[ 3 ].z = z;
        m[ 3 ].w = 1.0f;
    }

    //
    // Translation
    //
    void Mat4::Translation( const Vec3<float>& v )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = v.x;
        m[ 3 ].y = v.y;
        m[ 3 ].z = v.z;
        m[ 3 ].w = 1.0f;
    }

    //
    // RotationX
    //
    void Mat4::RotationX( float Angle )
    {
        float Rad = Radians( Angle );
    
        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = c;
        m[ 1 ].z = s;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = -s;
        m[ 2 ].z = c;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // RotationY
    //
    void Mat4::RotationY( float Angle )
    {
        float Rad = Radians( Angle );

        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = c;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = -s;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = s;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = c;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // RotationZ
    //
    void Mat4::RotationZ( float Angle )
    {
        float Rad = Radians( Angle );

        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ].x = c;
        m[ 0 ].y = s;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = -s;
        m[ 1 ].y = c;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // RotationXYZ
    //
    void Mat4::RotationXYZ( float x, float y, float z )
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
        m[ 0 ].w = 0.0f;

	    m[ 1 ].x = cy * -sz;
	    m[ 1 ].y = sxsy * -sz + cx * cz;
	    m[ 1 ].z = cxsy * -sz + sx * cz;
        m[ 1 ].w = 0.0f;

	    m[ 2 ].x = sy;	  
	    m[ 2 ].y = -sx * cy; 
	    m[ 2 ].z = cx * cy;
	    m[ 2 ].w = 0.0f;

	    m[ 3 ].x = 0.0f;
	    m[ 3 ].y = 0.0f;
	    m[ 3 ].z = 0.0f;
	    m[ 3 ].w = 1.0f;
    }

    //
    // Scaling
    //
    void Mat4::Scaling( float x, float y, float z )
    {
        m[ 0 ].x = x;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = y;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = z;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // ReflectionXY
    //
    void Mat4::ReflectionXY()
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = -1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // ReflectionYZ
    //
    void Mat4::ReflectionYZ()
    {
        m[ 0 ].x = -1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // ReflectionZX
    //
    void Mat4::ReflectionZX()
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = -1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;
        m[ 2 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // Ortho
    //
    bool Mat4::Ortho( float Left, float Right, float Bottom, float Top, float ZNear, float ZFar )
    {
        if ((Right - Left < EPSILON) || (Top - Bottom < EPSILON) || (ZFar - ZNear < EPSILON))
            return false;

        m[ 0 ][ 0 ] = 2.0f / (Right - Left);
        m[ 0 ][ 1 ] = 0.0f;
        m[ 0 ][ 2 ] = 0.0f;
        m[ 0 ][ 3 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = 2.0f / (Top - Bottom);
        m[ 1 ][ 2 ] = 0.0f;
        m[ 1 ][ 3 ] = 0.0f;

        m[ 2 ][ 0 ] = 0.0f; 
        m[ 2 ][ 1 ] = 0.0f;
        m[ 2 ][ 2 ] = -2.0f / (ZFar - ZNear);
        m[ 2 ][ 3 ] = 0.0f;

        m[ 3 ][ 0 ] = -(Right + Left) / (Right - Left);
        m[ 3 ][ 1 ] = -(Top + Bottom) / (Top - Bottom);
        m[ 3 ][ 2 ] = -(ZFar + ZNear) / (ZFar - ZNear);
        m[ 3 ][ 3 ] = 1.0f;
        
        return true;
    }

    //
    // Ortho2D
    //
    bool Mat4::Ortho2D( float Left, float Right, float Bottom, float Top )
    {
        return Ortho( Left, Right, Bottom, Top, -1.0f, 1.0f );
    }

    //
    // PerspectiveRHS
    //
    bool Mat4::PerspectiveRHS( float Fovy, float Aspect, float ZNear, float ZFar )
    {
        //     [ 2n/(r-l),        0,  (r+l)/(r-l),          0 ]
        // M = [        0, 2n/(t-b),  (t+b)/(t-b),          0 ]
        //     [        0,        0, -(f+n)/(f-n), -2fn/(f-n) ]
        //     [        0,        0,           -1,          0 ]

        if (ZFar - ZNear < EPSILON)
            return false;
    
        float Top = ZNear * Tan( Fovy * PI / 360.0f );
        float Bottom = -Top;
        float Left = Bottom * Aspect;
        float Right = Top * Aspect;

        if ((Right - Left < EPSILON) || (Top - Bottom < EPSILON))
            return false;

        m[ 0 ][ 0 ] = 2.0f * ZNear / (Right - Left);
        m[ 0 ][ 1 ] = 0.0f;
        m[ 0 ][ 2 ] = 0.0f;
        m[ 0 ][ 3 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = 2.0f * ZNear / (Top - Bottom);
        m[ 1 ][ 2 ] = 0.0f;
        m[ 1 ][ 3 ] = 0.0f;

        m[ 2 ][ 0 ] = (Right + Left) / (Right - Left);
        m[ 2 ][ 1 ] = (Top + Bottom) / (Top - Bottom);
        m[ 2 ][ 2 ] = -(ZFar + ZNear) / (ZFar - ZNear);
        m[ 2 ][ 3 ] = -1.0f;

        m[ 3 ][ 0 ] = 0.0f; 
        m[ 3 ][ 1 ] = 0.0f;
        m[ 3 ][ 2 ] = -2.0f * ZFar * ZNear / (ZFar - ZNear);
        m[ 3 ][ 3 ] = 0.0f;

        return true;
    }

    //
    // InfinitePerspectiveRHS
    //
    bool Mat4::InfinitePerspectiveRHS( float Fovy, float Aspect, float ZNear, float ZFar )
    {
        //     [ 2n/(r-l),        0,  (r+l)/(r-l),      0 ]
        // M = [        0, 2n/(t-b),  (t+b)/(t-b),      0 ]
        //     [        0,        0,          e-1, n(e-2) ]
        //     [        0,        0,           -1,      0 ]

        if (ZFar - ZNear < EPSILON)
            return false;

        float Top = ZNear * Tan( Fovy * PI / 360.0f );
        float Bottom = -Top;
        float Left = Bottom * Aspect;
        float Right = Top * Aspect;

        if ((Right - Left < EPSILON) || (Top - Bottom < EPSILON))
            return false;

        m[ 0 ][ 0 ] = 2.0f * ZNear / (Right - Left);
        m[ 0 ][ 1 ] = 0.0f;
        m[ 0 ][ 2 ] = 0.0f;
        m[ 0 ][ 3 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = 2.0f * ZNear / (Top - Bottom);
        m[ 1 ][ 2 ] = 0.0f;
        m[ 1 ][ 3 ] = 0.0f;

        m[ 2 ][ 0 ] = (Right + Left) / (Right - Left);
        m[ 2 ][ 1 ] = (Top + Bottom) / (Top - Bottom);
        m[ 2 ][ 2 ] = EPSILON - 1.0f;
        m[ 2 ][ 3 ] = -1.0f;               

        m[ 3 ][ 0 ] = 0.0f; 
        m[ 3 ][ 1 ] = 0.0f;
        m[ 3 ][ 2 ] = ZNear * (EPSILON - 2.0f);
        m[ 3 ][ 3 ] = 0.0f;

        return true;
    }

    //
    // TODO:
    //
    bool Mat4::PerspectiveLHS( float Fovy, float Aspect, float ZNear, float ZFar )
    {
        return false;
    }

    //
    // TODO:
    //
    bool Mat4::InfinitePerspectiveLHS( float Fovy, float Aspect, float ZNear, float ZFar )
    {
        return false;
    }

    //
    // LookAt
    //
    void Mat4::LookAt( const Vec3<float>& Eye, const Vec3<float>& Dir, const Vec3<float>& Up )
    {
    #ifdef _DEBUG
        Up.Assume();
    #endif
        Vec3<float> d = Dir.GetNormalized();
        Vec3<float> s; 

        s = CrossProduct( d, Up );
	    s.Normalize();

        Vec3<float> u = CrossProduct( s, d );

	    m[ 0 ].x = s.x;    
        m[ 1 ].x = s.y;    
        m[ 2 ].x = s.z;     
        m[ 3 ].x = m[ 0 ].x * -Eye.x + m[ 1 ].x * -Eye.y + m[ 2 ].x * -Eye.z;  

	    m[ 0 ].y = u.x;    
        m[ 1 ].y = u.y;    
        m[ 2 ].y = u.z;     
        m[ 3 ].y = m[ 0 ].y * -Eye.x + m[ 1 ].y * -Eye.y + m[ 2 ].y * -Eye.z;

	    m[ 0 ].z = -d.x;  
        m[ 1 ].z = -d.y;   
        m[ 2 ].z = -d.z;    
        m[ 3 ].z = m[ 0 ].z * -Eye.x + m[ 1 ].z * -Eye.y + m[ 2 ].z * -Eye.z;

	    m[ 0 ].w = 0.0f;   
        m[ 1 ].w = 0.0f;   
        m[ 2 ].w = 0.0f;
        m[ 3 ].w = 1.0f;
    }

    //
    // LookAtGL
    //
    void Mat4::LookAtGL( const Vec3<float>& Eye, const Vec3<float>& Center, const Vec3<float>& Up )
    {
        LookAt( Eye, Center - Eye, Up );
    }

    //
    // SetRotation
    //
    void Mat4::SetRotation( const Mat3& n )
    {
        m[ 0 ].x = n[ 0 ].x;
        m[ 0 ].y = n[ 0 ].y;
        m[ 0 ].z = n[ 0 ].z;

        m[ 1 ].x = n[ 1 ].x;
        m[ 1 ].y = n[ 1 ].y;
        m[ 1 ].z = n[ 1 ].z;

        m[ 2 ].x = n[ 2 ].x;
        m[ 2 ].y = n[ 2 ].y;
        m[ 2 ].z = n[ 2 ].z;
    }

    //
    // GetRotation
    //
    Mat3 Mat4::GetRotation() const
    {
        return ToMat3();
    }

    //
    // SetTranslation
    //
    void Mat4::SetTranslation( const Vec3<float>& v )
    {
        m[ 3 ].x = v.x;
        m[ 3 ].y = v.y;
        m[ 3 ].z = v.z;
    }

    //
    // GetTranslation
    //
    Vec3<float> Mat4::GetTranslation() const
    {
        return m[ 3 ].ToVec3<float>();
    }

    //
    // ToMat3
    //
    Mat3 Mat4::ToMat3() const
    {
        Mat3 n;

        n[ 0 ].x = m[ 0 ].x;
        n[ 0 ].y = m[ 0 ].y;
        n[ 0 ].z = m[ 0 ].z;

        n[ 1 ].x = m[ 1 ].x;
        n[ 1 ].y = m[ 1 ].y;
        n[ 1 ].z = m[ 1 ].z;

        n[ 2 ].x = m[ 2 ].x;
        n[ 2 ].y = m[ 2 ].y;
        n[ 2 ].z = m[ 2 ].z;

        return n;
    }

    //
    // ToMat43
    //
    Mat43 Mat4::ToMat43() const
    {
        Mat43 n;

        n[ 0 ].x = m[ 0 ].x;
        n[ 0 ].y = m[ 0 ].y;
        n[ 0 ].z = m[ 0 ].z;

        n[ 1 ].x = m[ 1 ].x;
        n[ 1 ].y = m[ 1 ].y;
        n[ 1 ].z = m[ 1 ].z;

        n[ 2 ].x = m[ 2 ].x;
        n[ 2 ].y = m[ 2 ].y;
        n[ 2 ].z = m[ 2 ].z;

        n[ 3 ].x = m[ 3 ].x;
        n[ 3 ].y = m[ 3 ].y;
        n[ 3 ].z = m[ 3 ].z;

        return n;
    }
}