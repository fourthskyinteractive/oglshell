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

// Файл: /Math/Plane/Plane.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__

namespace Math
{
    //  Плоскость, описываемая уравнением вида Ax + By + Cz + D = 0.

    template <typename T>
    class Plane
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

                            Plane();

                            Plane( const T& x, const T& y, const T& z, const T& d );
        TEMPLATE_Y          Plane( const Vec3<Y>& n, const Y& d );

        TEMPLATE_Y          Plane( const Vec3<Y>& a, const Vec3<Y>& b, const Vec3<Y>& c );
        TEMPLATE_Y          Plane( const Plane<Y>& p );

        TEMPLATE_Y          Plane( const Y eq[ 4 ] );
        TEMPLATE_Y          Plane( const vector<Y>& eq );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        bool                Compare( const Plane<T>& p, const T& Eps = EPSILON ) const;

        T                   GetDistance( const Vec3<T>& Pt ) const;

        void                Rotate( const Mat3& m );
        Plane<T>            GetRotated( const Mat3& m ) const;
        void                Rotate( const Mat4& m );
        Plane<T>            GetRotated( const Mat4& m ) const;
        void                Rotate( const Quat4<T>& q );
        Plane<T>            GetRotated( const Quat4<T>& q ) const;

        void                CalcDenormEquation( const Vec3<T> &a, const Vec3<T>& b, const Vec3<T>& c );

        TEMPLATE_Y Vec4<Y>  ToVec4() const;
        T*                  ToPtr();
        const T*            ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const Plane<T>& p) const; 
        bool                operator != (const Plane<T>& p) const;

        const T&            operator [] (const int& n) const;
        T&                  operator [] (const int& n);
    };

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane() 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const T& x, const T& y, const T& z, const T& d ): 
        n( x, y, z ), d( d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Plane<T>::Plane( const Vec3<Y>& n, const Y& d ): 
        n( n ), d( d ) 
    {
    #ifdef _DEBUG
        n.Assume();
    #endif
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Plane<T>::Plane( const Vec3<Y>& a, const Vec3<Y>& b, const Vec3<Y>& c ):
        n( CrossProduct( b - a, c - a ) ), d( static_cast<T>( 0.0 ) )
    {
        n.Normalize();
        d = -DotProduct( n, a );
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Plane<T>::Plane( const Plane<Y>& p ):
        n( p.n ), d( p.d )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Plane<T>::Plane( const Y eq[ 4 ] ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Plane<T>::Plane( const vector<Y>& eq ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] ) 
    {
        assert( eq.size() >= 4 );
    }

    //
    // Zero
    //
    template <typename T>
    inline void Plane<T>::Zero()
    {
        n.Zero();
        d = static_cast<T>( 0.0 );
    }

    //
    // IsZero
    //
    template <typename T>
    inline bool Plane<T>::IsZero() const
    {
        return n.IsZero() && (d == static_cast<T>( 0.0 ));
    }

    //
    // Compare
    //
    template <typename T> 
    inline bool Plane<T>::Compare( const Plane<T>& p, const T& Eps ) const 
    {
        if (!n.Compare( p.n, Eps ))
            return false;
        if (Abs( d - p.d ) > Eps)
            return false;
    
        return true;
    }

    //
    // GetDistance
    //
    template <typename T>
    inline T Plane<T>::GetDistance( const Vec3<T>& Pt ) const
    {
        return DotProduct( n, Pt ) + d;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Mat3& m )
    {
        Vec3<T> Pt = (n * -d) * m;

        n *= m;
        n.Normalize();

        d = -DotProduct( n, Pt );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Mat3& m ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( m );

        return Plane;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Mat4& m )
    {
        Vec4<T> Pt = Vec4<T>( n * -d, static_cast<T>( 1.0 ) ) * m;
        Vec4<T> n4 = Vec4<T>( n, static_cast<T>( 0.0 ) ) * m;

        n = n4.ToVec3<T>();
        n.Normalize();

        d = -DotProduct( n, Pt.ToVec3<T>() );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Mat4& m ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( m );

        return Plane;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Quat4<T>& q )
    {
        Vec3<T> Pt = (n * -d) * q;

        n *= q;
        n.Normalize();

        d = -DotProduct( n, Pt );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Quat4<T>& q ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( q );

        return Plane;
    }

    //
    // CalcDenormEquation
    //
    template <typename T>
    inline void Plane<T>::CalcDenormEquation( const Vec3<T> &a, const Vec3<T>& b, const Vec3<T>& c )
    {
        n = CrossProduct( b - a, c - a );
        d = -DotProduct( n, a ); 
    }

    //
    // ToVec4
    //
    template <typename T> template <typename Y>
    inline Vec4<Y> Plane<T>::ToVec4() const
    {
        return Vec4<Y>( n.x, n.y, n.z, d ); 
    }
    
    //
    // ToPtr
    //
    template <typename T>
    inline T *Plane<T>::ToPtr()
    {
        return vec;
    }

    //
    // ToPtr
    //
    template <typename T>
    inline const T *Plane<T>::ToPtr() const
    {
        return vec;
    }

    //
    // operator ==
    //
    template <typename T>
    inline bool Plane<T>::operator == (const Plane<T>& p) const
    {
        return Compare( p, static_cast<T>( 0.0 ) );
    }
      
    //
    // operator !=
    //
    template <typename T>
    inline bool Plane<T>::operator != (const Plane<T>& p) const
    {
        return !Compare( p, static_cast<T>( 0.0 ) );
    }

    //
    // operator []
    //
    template <typename T> 
    inline const T &Plane<T>::operator [] (const int& n) const               
    { 
        ASSERT_RANGE( n, 0, 4 );
        return eq[ n ];
    }

    //
    // operator []
    //
    template <typename T> 
    inline T &Plane<T>::operator [] (const int& n)               
    { 
        ASSERT_RANGE( n, 0, 4 );
        return eq[ n ];
    }
}

#endif // __MATH_PLANE_H__