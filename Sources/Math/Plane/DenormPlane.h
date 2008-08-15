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

// Файл: /Math/Plane/DenormPlane.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_DENORM_PLANE_H__
#define __MATH_DENORM_PLANE_H__

namespace Math
{
    //  Ненормализованная плоскость.

    template <typename T>
    class DenormPlane
    {
    public:
        union 
        {
            struct 
            {
                Vec3<T>     n;
                T           d;
            };
        
            T               eq[ 4 ];  
        };

                            DenormPlane();
                                                                
                            DenormPlane( const T& x, const T& y, const T& z, const T& d );
                            DenormPlane( const Vec3<T>& n, const T& d );

                            DenormPlane( const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c );
                            DenormPlane( const Vec4<T>& a, const Vec4<T>& b, const Vec4<T>& c );
                            DenormPlane( const Vec3<T> p[ 3 ] );
                            DenormPlane( const Vec4<T> p[ 3 ] );

                            DenormPlane( const T eq[ 4 ] );
                            DenormPlane( const vector<T>& eq );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        bool                Compare( const DenormPlane<T>& p, const T& Eps = EPSILON ) const;

        bool                IsFrontFaced( const Vec3<T>& Pt ) const;
        bool                IsBackFaced( const Vec3<T>& Pt ) const;

        T*                  ToPtr();
        const T*            ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const DenormPlane<T>& p) const; 
        bool                operator != (const DenormPlane<T>& p) const;

        const T&            operator [] (const int& n) const;
        T&                  operator [] (const int& n);
    };

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane() 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const T& x, const T& y, const T& z, const T& d ): 
        n( x, y, z ), d( d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const Vec3<T>& n, const T& d ): 
        n( n ), d( d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c ):
        n( CrossProduct( b - a, c - a ) ), d( -DotProduct( n, a ) )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const Vec4<T> &a, const Vec4<T> &b, const Vec4<T> &c ):
        n( CrossProduct( b - a, c - a ) ), d( -DotProduct( n, a ) )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const Vec3<T> p[ 3 ] ):
        n( CrossProduct( p[ 1 ] - p[ 0 ], p[ 2 ] - p[ 0 ] ) ), d( -DotProduct( n, p[ 0 ] ) )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const Vec4<T> p[ 3 ] ):
        n( CrossProduct( p[ 1 ] - p[ 0 ], p[ 2 ] - p[ 0 ] ) ), d( -DotProduct( n, p[ 0 ] ) )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const T eq[ 4 ] ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline DenormPlane<T>::DenormPlane( const vector<T>& eq ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] ) 
    {
       assert( eq.size() >= 4 );
    }

    //
    // Zero
    //
    template <typename T>
    inline void DenormPlane<T>::Zero()
    {
        n.Zero();
        d = static_cast<T>( 0.0 );
    }

    //
    // IsZero
    //
    template <typename T>
    inline bool DenormPlane<T>::IsZero() const
    {
        return n.IsZero() && d == static_cast<T>( 0.0 );
    }

    //
    // Compare
    //
    template <typename T> 
    inline bool DenormPlane<T>::Compare( const DenormPlane<T>& p, const T& Eps ) const 
    {
        if (!n.Compare( p.n, Eps ))
            return false;
        if (Abs( d - p.d ) > Eps)
            return false;
    
        return true;
    }

    //
    // IsFrontFaced
    //
    template <typename T>
    inline bool DenormPlane<T>::IsFrontFaced( const Vec3<T>& Pt ) const
    {
        return DotProduct( n, Pt ) + d >= 0.0f;
    }

    //
    // IsBackFaced
    //
    template <typename T>
    inline bool DenormPlane<T>::IsBackFaced( const Vec3<T>& Pt ) const
    {
       return DotProduct( n, Pt ) + d < 0.0f;
    }

    //
    // ToPtr
    //
    template <typename T>
    inline T *DenormPlane<T>::ToPtr()
    {
       return &n.x;
    }

    //
    // ToPtr
    //
    template <typename T>
    inline const T *DenormPlane<T>::ToPtr() const
    {
        return &n.x;
    }

    //
    // operator ==
    //
    template <typename T>
    inline bool DenormPlane<T>::operator == (const DenormPlane<T>& p) const
    {
        return Compare( p, static_cast<T>( 0.0 ) );
    }
      
    //
    // opearator !=
    //
    template <typename T>
    inline bool DenormPlane<T>::operator != (const DenormPlane<T>& p) const
    {
        return !Compare( p, static_cast<T>( 0.0 ) );
    }

    //
    // operator []
    //
    template <typename T> 
    inline const T& DenormPlane<T>::operator [] (const int& n) const               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }

    //
    // operator []
    //
    template <typename T> 
    inline T& DenormPlane<T>::operator [] (const int& n)               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }
} 

using Math::DenormPlane;

#endif // __MATH_DENORM_PLANE_H__