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

// Τΰιλ: /Math/Matrix/Mat43.cpp
//

#include "Precompiled.h"
#pragma hdrstop

namespace Math
{
    //
    // Constructor
    //
    Mat43::Mat43()
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
    }

    //
    // Constructor
    //
    Mat43::Mat43( float s )
    {
        m[ 0 ].x = s;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = s;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].x = s;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
    }

    //
    // Constructor
    //
    Mat43::Mat43( 
                 float _00, float _01, float _02, 
                 float _10, float _11, float _12, 
                 float _20, float _21, float _22, 
                 float _30, float _31, float _32 
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

        m[ 3 ][ 0 ] = _30;
        m[ 3 ][ 1 ] = _31;
        m[ 3 ][ 2 ] = _32;
    }

    //
    // Constructor
    //
    Mat43::Mat43( const Vec3<float>& v )
    {
        m[ 0 ].x = 1.0f;
        m[ 0 ].y = 0.0f;
        m[ 0 ].z = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ].x = 0.0f;
        m[ 2 ].y = 0.0f;
        m[ 2 ].z = 1.0f;

        m[ 3 ].x = v.x;
        m[ 3 ].y = v.y;
        m[ 3 ].z = v.z;
    }

    //
    // Constructor
    //
    Mat43::Mat43( const Mat3& n, const Vec3<float>& v )
    {
        m[ 0 ].x = n[ 0 ].x;
        m[ 0 ].y = n[ 0 ].y;
        m[ 0 ].z = n[ 0 ].x;

        m[ 1 ].x = n[ 1 ].x;
        m[ 1 ].y = n[ 1 ].y;
        m[ 1 ].z = n[ 1 ].z;

        m[ 2 ].x = n[ 2 ].x;
        m[ 2 ].y = n[ 2 ].y;
        m[ 2 ].z = n[ 2 ].z;

        m[ 3 ].x = v.x;
        m[ 3 ].y = v.y;
        m[ 3 ].z = v.z;
    }

    //
    // Constructor
    //
    Mat43::Mat43( const Vec3<float>& _0, const Vec3<float>& _1, const Vec3<float>& _2, const Vec3<float>& _3 )
    {
        m[ 0 ] = _0;
        m[ 1 ] = _1;
        m[ 2 ] = _2;
        m[ 3 ] = _3;
    }

    //
    // Constructor
    //
    Mat43::Mat43( const float n[ 12 ] )
    {
        m[ 0 ].x = n[ 0 ];
        m[ 0 ].y = n[ 1 ];
        m[ 0 ].x = n[ 2 ];

        m[ 1 ].x = n[ 3 ];
        m[ 1 ].y = n[ 4 ];
        m[ 1 ].x = n[ 5 ];

        m[ 2 ].x = n[ 6 ];
        m[ 2 ].y = n[ 7 ];
        m[ 2 ].z = n[ 8 ];

        m[ 3 ].x = n[ 9 ];
        m[ 3 ].y = n[ 10 ];
        m[ 3 ].z = n[ 11 ];
    }

    //
    // Constructor
    //
    Mat43::Mat43( const vector<float>& n )
    {
        assert( n.size() >= 12 );

        m[ 0 ].x = n[ 0 ];
        m[ 0 ].y = n[ 1 ];
        m[ 0 ].x = n[ 2 ];

        m[ 1 ].x = n[ 3 ];
        m[ 1 ].y = n[ 4 ];
        m[ 1 ].x = n[ 5 ];

        m[ 2 ].x = n[ 6 ];
        m[ 2 ].y = n[ 7 ];
        m[ 2 ].z = n[ 8 ];

        m[ 3 ].x = n[ 9 ];
        m[ 3 ].y = n[ 10 ];
        m[ 3 ].z = n[ 11 ];
    }

    //
    // SetRotation
    //
    void Mat43::SetRotation( const Mat3& n )
    {
        m[ 0 ].x = n[ 0 ].x;
        m[ 0 ].y = n[ 0 ].y;
        m[ 0 ].z = n[ 0 ].x;

        m[ 1 ].x = n[ 1 ].x;
        m[ 1 ].y = n[ 1 ].y;
        m[ 1 ].z = n[ 1 ].z;

        m[ 2 ].x = n[ 2 ].x;
        m[ 2 ].y = n[ 2 ].y;
        m[ 2 ].z = n[ 2 ].z;
    }

    //
    // SetTranslation
    //
    void Mat43::SetTranslation( const Vec3<float>& v )
    {
        m[ 3 ] = v;
    }

    //
    // GetTranslation
    //
    const Vec3<float>& Mat43::GetTranslation() const
    {
        return m[ 3 ];
    }

    //
    // ToMat3
    //
    Mat3 Mat43::ToMat3() const
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
}