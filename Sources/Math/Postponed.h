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

// Τΰιλ: /Math/Postponed.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_POSTPONED_H__
#define __MATH_POSTPONED_H__

namespace Math
{
    //
    // ToMat3
    //
    template <typename T>
    inline Mat3 Vec3<T>::ToMat3() const
    {
    #ifdef _DEBUG
        Assume();
    #endif

        Mat3 m;
    
        m[ 0 ].x = x;
        m[ 0 ].y = y;
        m[ 0 ].z = z;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;

        m[ 2 ] = CrossProduct( m[ 0 ], m[ 1 ] );
        m[ 2 ].Normalize();

        m[ 1 ] = CrossProduct( m[ 2 ], m[ 0 ] );
        m[ 2 ].Normalize();

        return m;
    }

    //
    // ToMat4
    //
    template <typename T>
    inline Mat4 Vec3<T>::ToMat4() const
    {
    #ifdef _DEBUG
        Assume();
    #endif

        Mat4 m;

        m[ 0 ].x = x;
        m[ 0 ].y = y;
        m[ 0 ].z = z;
        m[ 0 ].w = 0.0f;

        m[ 1 ].x = 0.0f;
        m[ 1 ].y = 1.0f;
        m[ 1 ].z = 0.0f;
        m[ 1 ].w = 0.0f;

        Vec3<float> v = CrossProduct( m[ 0 ], m[ 1 ] );
        v.Normalize();

        m[ 2 ].x = v.x;
        m[ 2 ].y = v.y;
        m[ 2 ].z = v.z;
        m[ 2 ].w = 0.0f;
        
        v = CrossProduct( m[ 2 ], m[ 0 ] );
        v.Normalize();

        m[ 1 ].x = v.x;
        m[ 1 ].y = v.y;
        m[ 1 ].z = v.z;
        m[ 1 ].w = 0.0f;

        m[ 3 ].x = 0.0f;
        m[ 3 ].y = 0.0f;
        m[ 3 ].z = 0.0f;
        m[ 3 ].w = 1.0f;

        return m;
    }

    //
    // operator *=
    //
    template <typename T>
    inline Vec3<T>& Vec3<T>::operator *= (const Mat3& m)
    {
        *this = *this * m;
        return *this;
    }

    //
    // operator *=
    //
    template <typename T>
    inline Vec3<T>& Vec3<T>::operator *= (const Mat4& m)
    {
        *this = *this * m;
        return *this;
    }

    //
    // operator *=
    //
    template <typename T>
    inline Vec3<T>& Vec3<T>::operator *= (const Quat4<T>& q)
    {
        *this = *this * q;
        return *this;
    }

    //
    // operator *=
    //
    template <typename T>
    inline Vec4<T>& Vec4<T>::operator *= (const Mat4& m)
    {
        *this = *this * m;
        return *this;
    }

    #ifdef __MATH_QUAT4_H__

    //
    // ToQuat3
    //
    template <typename T>
    inline Quat3<T> Quat4<T>::ToQuat3() const
    {
    #ifdef _DEBUG
        Assume();
    #endif
        Quat3<T> q;

        if (w < static_cast<T>( 0.0 )) 
        {
            q.x = -x;
            q.y = -y;
            q.z = -z;
        }
        else 
        {
            q.x = x;
            q.y = y;
            q.z = z;
        }

        return q;
    }

    #endif // __MATH_QUAT4_H__
}

namespace MathSIMD
{
    #if defined (__MATH_SIMD_VEC4_SSE_H__) && defined (__MATH_SIMD_MAT4_SSE_H__)

    //
    // *=
    //
    inline Vec4_SSE& Vec4_SSE::operator *= (const Mat4_SSE& m)
    {
        *this = *this * m;
        return *this;
    }

    #endif // __MATH_SIMD_VEC4_SSE_H__

    #if defined (__MATH_SIMD_VEC4_3DNOW_H__) && defined (__MATH_SIMD_MAT4_3DNOW_H__)

    //
    // *=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator *= (const Mat4_3DNow& m)
    {
        *this = *this * m;
        return *this;
    }

    #endif // __MATH_SIMD_VEC4_3DNOW_H__
}

#endif // __MATH_POSTPONED_H__