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

// Файл: /Math/Quaternion/Quat.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_QUAT_H__
#define __MATH_QUAT_H__

namespace Math
{
    //  Шаблон кватерниона.

    template <int N, typename T>
    class Quat
    {
    public:
        union 
        {
            struct 
            {
                T           x;  
            };
		
            T               vec[ 1 ]; // C++ hack.    
        };

                            Quat();

                            Quat( const T& s );

        TEMPLATE_Y          Quat( const Y q[] );
        TEMPLATE_Y          Quat( const vector<Y>& q );
                                    
        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        bool                Compare( const Quat<N, T>& q, const T& Eps = EPSILON ) const;

        T*                  ToPtr();
        const T*            ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const Quat<N, T>& q) const;    
        bool                operator != (const Quat<N, T>& q) const;

        T&                  operator [] (const int& n);
        const T&            operator [] (const int& n) const;
    };

    //
    // Constructor
    //
    template <int N, typename T>
    inline Quat<N, T>::Quat()
    {
    }

    //
    // Constructor
    //
    template <int N, typename T> 
    inline Quat<N, T>::Quat( const T& s ):
        x( s )
    {
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Quat<N, T>::Quat( const Y q[] )
    {
        for (int i = 0; i < N; ++i)
           vec[ i ] = q[ i ];
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Quat<N, T>::Quat( const vector<Y>& q )
    {
        assert( q.size() >= N );

        for (int i = 0; i < N; ++i)
            vec[ i ] = q[ i ];
    }

    //
    // Zero
    //
    template <int N, typename T>
    inline void Quat<N, T>::Zero()
    {
        for (int i = 0; i < N; ++i)
            vec[ i ] = static_cast<T>( 0.0 );
    }

    //
    // IsZero
    //
    template <int N, typename T>
    inline bool Quat<N, T>::IsZero() const
    {
        for (int i = 0; i < N; ++i) 
        {
            if (vec[ i ] != static_cast<T>( 0.0 ))
                return false;
        }

        return true;
    }

    //
    // Compare
    //
    template <int N, typename T>
    inline bool Quat<N, T>::Compare( const Quat<N, T>& q, const T& Eps ) const
    {
        for (int i = 0; i < N; ++i)
        {
            if (Abs( vec[ i ] - q.vec[ i ] ) > Eps)
                return false;
        }

        return true;
    }

    //
    // ToPtr
    //
    template <int N, typename T>
    inline T *Quat<N, T>::ToPtr()
    {
        return vec;
    }

    //
    // ToPtr
    //
    template <int N, typename T>
    inline const T *Quat<N, T>::ToPtr() const
    {
        return vec;
    }

    //
    // operator ==
    //
    template <int N, typename T>
    inline bool Quat<N, T>::operator == (const Quat<N, T>& q) const
    {
        return Compare( q, static_cast<T>( 0.0 ) );
    }

    //
    // operator !=
    //
    template <int N, typename T>
    inline bool Quat<N, T>::operator != (const Quat<N, T>& q) const
    {
        return !Compare( q, static_cast<T>( 0.0 ) );
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline T& Quat<N, T>::operator [] (const int& n)
    {
        ASSERT_RANGE( n, 0, N );
        return vec[ n ];  
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline const T& Quat<N, T>::operator [] (const int& n) const
    {
        ASSERT_RANGE( n, 0, N );
        return vec[ n ];  
    }
}

#endif // __MATH_QUAT_H__