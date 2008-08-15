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

// Файл: /Math/Quaternion/Quat3.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_QUAT3_H__
#define __MATH_QUAT3_H__

namespace Math
{
    //  Трёхкомпонентный (сжатый) кватернион.
    //  x^2 + y^2 + z^2 + w^2 = 1.0; w = sqrt( x^2 + y^2 + z^2 ).

    template <typename T> 
    class Quat3: public Quat<3, T>
    {
    public:
        T                   y, z;
        
                            Quat3();
                           
                            Quat3( const T& x, const T& y, const T& z );                  

        TEMPLATE_Y          Quat3( const Quat3<Y>& q ); 

        TEMPLATE_Y          Quat3( const Y q[ 3 ] );
        TEMPLATE_Y          Quat3( const vector<Y>& q ); 

        //
        // Interface
        // 

        TEMPLATE_Y Vec3<Y>  ToVec3() const;
        TEMPLATE_Y Quat4<Y> ToQuat4() const;
    };

    //
    // Constructor
    //
    template <typename T>
    inline Quat3<T>::Quat3() 
    {
    }
           
    //
    // Constructor
    //
    template <typename T>
    inline Quat3<T>::Quat3( const T& x, const T& y, const T& z ): 
        Quat<3, T>( x ), y( y ), z( z ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>       
    inline Quat3<T>::Quat3( const Quat3<Y>& q ): 
        Quat<3, T>( q.x ), y( q.y ), z( q.z ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Quat3<T>::Quat3( const Y q[ 3 ] ): 
        Quat<3, T>( q )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Quat3<T>::Quat3( const vector<Y>& q ): 
        Quat<3, T>( q )
    {
    }

    //
    // ToVec3
    //
    template <typename T> template <typename Y>
    inline Vec3<Y> Quat3<T>::ToVec3() const
    {
        return Vec3<Y>( x, y, z );
    }

    //
    // ToQuat4
    //
    template <typename T> template <typename Y>
    inline Quat4<Y> Quat3<T>::ToQuat4() const
    {
        Quat4<Y> q;
    
        q.x = x;
        q.y = y;
        q.z = z;

        T w2 = static_cast<T>( 1.0 ) - (x * x + y * y + z * z);
        if (w2 < EPSILON)
            q.w = static_cast<T>( 0.0 );
        else
            q.w = -SqRt( w2 );
     
        return q;
    }
}

#endif // __MATH_QUAT3_H__