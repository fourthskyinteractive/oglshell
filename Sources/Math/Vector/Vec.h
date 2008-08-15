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

// Файл: /Math/Vector/Vec.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_VEC_H__
#define __MATH_VEC_H__

namespace Math
{
    //  Шаблон вектора.
    
    template <int N, typename T>
    class Vec
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
       
                            Vec();
                                            
                            Vec( const T& s );

        TEMPLATE_Y          Vec( const Y v[] );
        TEMPLATE_Y          Vec( const vector<Y>& v );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;
                                                                
        bool                Compare( const Vec<N, T>& v, const T& Eps = EPSILON ) const;
                                    
        T*                  ToPtr();
        const T*            ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const Vec<N, T>& v) const; 
        bool                operator != (const Vec<N, T>& v) const;

        T&                  operator [] (const int& n);
        const T&            operator [] (const int& n) const;
    };

    //
    // Constructor
    //
    template <int N, typename T>
    inline Vec<N, T>::Vec() 
    {
    }

    //
    // Constructor
    //
    template <int N, typename T>
    inline Vec<N, T>::Vec( const T& s ): 
        x( s ) 
    {
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Vec<N, T>::Vec( const Y v[] )
    {
        for (int i = 0; i < N; ++i)
            vec[ i ] = v[ i ];
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Vec<N, T>::Vec( const vector<Y>& v )
    {
        assert( v.size() >= N );

        for (int i = 0; i < N; ++i)
            vec[ i ] = v[ i ];
    }

    //
    // Zero
    //
    template <int N, typename T>
    inline void Vec<N, T>::Zero()
    {
        for (int i = 0; i < N; ++i)
            vec[ i ] = static_cast<T>( 0.0 );
    }

    //
    // IsZero
    //
    template <int N, typename T>
    inline bool Vec<N, T>::IsZero() const
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
    inline bool Vec<N, T>::Compare( const Vec<N, T>& v, const T& Eps ) const
    {
	    for (int i = 0; i < N; ++i) 
        {
		    if (Abs( vec[ i ] - v.vec[ i ] ) > Eps)
			    return false;
        }

        return true;
    }

    //
    // ToPtr
    //
    template <int N, typename T>    
    inline T *Vec<N, T>::ToPtr()
    {
        return &x;
    }

    //
    // ToPtr
    //
    template <int N, typename T>
    inline const T *Vec<N, T>::ToPtr() const
    {
        return &x;
    }

    //
    // operator ==
    //
    template <int N, typename T>
    inline bool Vec<N, T>::operator == (const Vec<N, T>& v) const
    {
        return Compare( v, static_cast<T>( 0.0 ) );
    }

    //
    // operator !=
    //
    template <int N, typename T>
    inline bool Vec<N, T>::operator != (const Vec<N, T>& v) const
    {
        return !Compare( v, static_cast<T>( 0.0 ) );
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline T& Vec<N, T>::operator [] (const int& n)                 
    {
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < N );
    #endif
        return vec[ n ]; 
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline const T& Vec<N, T>::operator [] (const int& n) const
    {
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < N );
    #endif
        return vec[ n ]; 
    }
}

#endif // __MATH_VEC_H__