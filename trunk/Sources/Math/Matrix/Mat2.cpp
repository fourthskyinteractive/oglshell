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

// Τΰιλ: /Math/Matrix/Mat2.cpp
//

#include "Precompiled.h"
#pragma hdrstop

namespace Math
{
    //
    // Constructor
    //
    Mat2::Mat2():
        Mat<2, Vec2<float> >( 1.0f )
    {
    }

    //
    // Constructor
    //
    Mat2::Mat2( float s ):
        Mat<2, Vec2<float> >( s )
    {
    }

    //
    // Constructor
    //
    Mat2::Mat2( 
               float _00, float _01,
               float _10, float _11 
               )
    {
        m[ 0 ][ 0 ] = _00;
        m[ 0 ][ 1 ] = _01;

        m[ 1 ][ 0 ] = _10;
        m[ 1 ][ 1 ] = _11;
    }

    //
    // Constructor
    //
    Mat2::Mat2( const Vec2<float>& _0, const Vec2<float>& _1 )
    {
        m[ 0 ] = _0;
        m[ 1 ] = _1;
    }

    //
    // Constructor
    //
    Mat2::Mat2( const float m[ 4 ] ):
        Mat<2, Vec2<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat2::Mat2( const vector<float>& m ):
        Mat<2, Vec2<float> >( m )
    {
    }

    //
    // Constructor
    //
    Mat2::Mat2( const float m[ 2 ][ 2 ] ):
        Mat<2, Vec2<float> >( m )
    {
    }

    //
    // GetDeterminant
    //
    float Mat2::GetDeterminant() const
    {
        return m[ 0 ][ 0 ] * m[ 1 ][ 1 ] - m[ 0 ][ 1 ] * m[ 1 ][ 0 ];
    }

    //
    // GetTransposed
    //
    Mat2 Mat2::GetTransposed() const
    {
        Mat2 n( *this );

        n.Transpose();

        return n;
    }

    //
    // Inverse
    //
    bool Mat2::Inverse()
    {
        float Det = GetDeterminant();
        
        if (Abs( Det ) < EPSILON)
            return false;

        std::swap( m[ 0 ][ 0 ], m[ 1 ][ 1 ] );
        m[ 0 ][ 1 ] = -m[ 0 ][ 1 ];
        m[ 1 ][ 0 ] = -m[ 1 ][ 0 ];

        if (Abs( 1.0f - Det ) > EPSILON) 
        {
            m[ 0 ] /= Det;
            m[ 1 ] /= Det;
        }

        return true;
    }

    //
    // GetInverted
    //
    Mat2 Mat2::GetInverted() const
    {
        Mat2 n( *this );

        n.Inverse();

        return n;
    }

    //
    // Rotation
    //
    void Mat2::Rotation( float Angle )
    {
        float Rad = Radians( Angle );
        float s = Sin( Rad );
        float c = Cos( Rad );

        m[ 0 ][ 0 ] = c;
        m[ 0 ][ 1 ] = s;

        m[ 1 ][ 0 ] = -s;
        m[ 1 ][ 1 ] = c;
    }

    //
    // Scaling
    //
    void Mat2::Scaling( float x, float y )
    {
        m[ 0 ][ 0 ] = x;
        m[ 0 ][ 1 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = y;
    }

    //
    // ReflectionX
    //
    void Mat2::ReflectionX()
    {
        m[ 0 ][ 0 ] = 1.0f;
        m[ 0 ][ 1 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = -1.0f;
    }

    //
    // ReflectionY
    //
    void Mat2::ReflectionY()
    {
        m[ 0 ][ 0 ] = -1.0f;
        m[ 0 ][ 1 ] = 0.0f;

        m[ 1 ][ 0 ] = 0.0f;
        m[ 1 ][ 1 ] = 1.0f;
    }
}