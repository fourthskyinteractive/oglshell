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

// Файл: /Math/Vector/Vec2.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_VEC2_H__
#define __MATH_VEC2_H__

namespace Math
{
    //  Двукомпонентный вектор.

    template <typename T> 
    class Vec2 : public Vec<2, T>
    {
    public:
        T                   y;
                                        
                            Vec2();

                            Vec2( const T& s );
                            Vec2( const T& x, const T& y );

        TEMPLATE_Y          Vec2( const Vec2<Y>& v );

        TEMPLATE_Y          Vec2( const Y v[ 2 ] );
        TEMPLATE_Y          Vec2( const vector<Y>& v );

        //
        // Interface
        //
                                
        void                Assume( const T& Eps = EPSILON ) const;

        T                   GetLength() const;
        T                   GetSquareLength() const;

        T                   Normalize();
        Vec2<T>             GetNormalized() const;
        void                NormalizeFast();
        Vec2<T>             GetNormalizedFast() const;
        void                Truncate( const T& Length );
        Vec2<T>             GetTruncated( const T& Length ) const;

        //
        // Swizzling
        //

        Vec2<T>             xx() const;
        Vec2<T>             yx() const;
        const Vec2<T>&      xy() const;
        Vec2<T>             yy() const;

        //
        // Operators
        //

        const Vec2<T>&      operator + () const { return *this; }
        Vec2<T>             operator - () const { return Vec2<T>( -x, -y ); }

        Vec2<T>&            operator *= (const T& s);
        Vec2<T>&            operator *= (const Vec2<T>& v); 
        Vec2<T>&            operator /= (const T& s);
        Vec2<T>&            operator /= (const Vec2<T>& v); 
        Vec2<T>&            operator += (const T& s);
        Vec2<T>&            operator += (const Vec2<T>& v);
        Vec2<T>&            operator -= (const T& s);
        Vec2<T>&            operator -= (const Vec2<T>& v);

        Vec2<T>             operator * (const T& s) const;
        friend Vec2<T>      operator * (const T& s, const Vec2<T>& v) { return v * s; }
        Vec2<T>             operator * (const Vec2<T>& v) const;
        Vec2<T>             operator / (const T &s) const;  
        Vec2<T>             operator / (const Vec2<T>& v) const;
        Vec2<T>             operator + (const T &s) const;  
        Vec2<T>             operator + (const Vec2<T>& v) const; 
        Vec2<T>             operator - (const T &s) const;
        Vec2<T>             operator - (const Vec2<T>& v) const;
    };

    //
    // Constructor
    //
    template <typename T>
    inline Vec2<T>::Vec2() 
    {
    }  

    //
    // Constructor
    //
    template <typename T>
    inline Vec2<T>::Vec2( const T& s ): 
        Vec<2, T>( s ), y( s ) 
    {
    }
        
    //
    // Constructor
    //
    template <typename T>
    inline Vec2<T>::Vec2( const T& x, const T& y ): 
        Vec<2, T>( x ), y( y ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec2<T>::Vec2( const Vec2<Y>& v ):
        Vec<2, T>( x ), y( y )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec2<T>::Vec2( const Y v[ 2 ] ): 
        Vec<2, T>( v ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec2<T>::Vec2( const vector<Y>& v ): 
        Vec<2, T>( v ) 
    {
    }

    //
    // Assume
    //
    template <typename T> 
    inline void Vec2<T>::Assume( const T& Eps ) const
    {
        assert( Abs( static_cast<T>( 1.0 ) - Length() ) <= Eps );
    }

    //
    // GetLength
    //
    template <typename T> 
    inline T Vec2<T>::GetLength() const
    {
        return SqRt( x * x + y * y );
    }

    //
    // GetSquareLength
    //
    template <typename T> 
    inline T Vec2<T>::GetSquareLength() const
    {
        return x * x + y * y;
    }

    //
    // Normalize
    //
    template <typename T> 
    inline T Vec2<T>::Normalize()
    {
        T Length = GetLength();

        if (Length > EPSILON && Abs( static_cast<T>( 1.0 ) - Length ) > EPSILON) 
        {
            T r = static_cast<T>( 1.0 ) / Length;
            x *= r;
            y *= r;
        }

        return Length;
    }

    //
    // GetNormalized
    // 
    template <typename T> 
    inline Vec2<T> Vec2<T>::GetNormalized() const
    {
        Vec2<T> v = *this;

        v.Normalize();

        return v;
    }

    //
    // NormalizeFast
    //
    template <typename T> 
    inline void Vec2<T>::NormalizeFast()
    {
        T r = InvSqRt( GetSquareLength() );

        x *= r;
        y *= r;
    }

    //
    // GetNormalizedFast
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::GetNormalizedFast() const
    {
        Vec2<T> v = *this;

        v.NormalizeFast();

        return v;
    }

    //
    // Truncate
    //
    template <typename T> 
    inline void Vec2<T>::Truncate( const T& Length ) 
    {
        if (Length < EPSILON)
            Zero();
        else 
        {
            T SquareLength = GetSquareLength();

            if (SquareLength > Length * Length) 
            {
                T r = Length / SqRt( SquareLength );
                x *= r;
                y *= r;
            }
        }
    }

    //
    // GetTruncated
    //
    template <typename T>
    inline Vec2<T> Vec2<T>::GetTruncated( const T& Length ) const
    {
        Vec2<T> v = *this;

        v.Truncate( Length );

        return v;
    }

    //
    // xx
    //
    template <typename T>
    inline Vec2<T> Vec2<T>::xx() const
    {
        return Vec2<T>( x, x );
    }
        
    //
    // yx
    //
    template <typename T>
    inline Vec2<T> Vec2<T>::yx() const
    {
        return Vec2<T>( y, x );
    }

    //
    // xy
    //
    template <typename T>
    inline const Vec2<T>& Vec2<T>::xy() const
    {
        return *this;
    }
      
    //
    // yy
    //
    template <typename T>
    inline Vec2<T> Vec2<T>::yy() const
    {
        return Vec2<T>( y, y );
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator *= (const T& s) 
    {
        x *= s;
        y *= s;

        return *this;
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator *= (const Vec2<T>& v) 
    {
        x *= v.x;
        y *= v.y;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator /= (const T& s) 
    {
        assert( s != static_cast<T>( 0.0 ) );

        x /= s;
        y /= s;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator /= (const Vec2<T>& v) 
    {
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) );

        x /= v.x;
        y /= v.y;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator += (const T& s) 
    {
        x += s;
        y += s;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator += (const Vec2<T>& v) 
    {
        x += v.x;
        y += v.y;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator -= (const T& s) 
    {
        x -= s;
        y -= s;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec2<T>& Vec2<T>::operator -= (const Vec2<T>& v) 
    {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    //
    // operator *
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator * (const T& s) const 
    { 
        return Vec2<T>( x * s, y * s ); 
    }

    //
    // operator *
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator * (const Vec2<T>& v) const 
    { 
        return Vec2<T>( x * v.x, y * v.y ); 
    }

    //
    // operator /
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator / (const T& s) const 
    { 
        assert( s != static_cast<T>( 0.0 ) );

        return Vec2<T>( x / s, y / s ); 
    }

    //
    // operator /
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator / (const Vec2<T>& v) const 
    { 
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) );

        return Vec2<T>( x / v.x, y / v.y ); 
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator + (const T& s) const 
    { 
        return Vec2<T>( x + s, y + s ); 
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator + (const Vec2<T>& v) const       
    { 
        return Vec2<T>( x + v.x, y + v.y ); 
    } 

    //
    // operator -
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator - (const T& s) const 
    { 
        return Vec2<T>( x - s, y - s ); 
    }

    //
    // operator -
    //
    template <typename T> 
    inline Vec2<T> Vec2<T>::operator - (const Vec2<T>& v) const       
    { 
        return Vec2<T>( x - v.x, y - v.y ); 
    }
} 

namespace Math
{
    //
    // DotProduct
    //
    template <typename T> 
    inline T DotProduct( const Vec2<T>& a, const Vec2<T>& b )
    {
        return a.x * b.x + a.y * b.y;
    }

    //
    // CrossProduct
    //
    template <typename T> 
    inline T CrossProduct( const Vec2<T>& p, const Vec2<T>& q )
    {
        return p.x * q.y - p.y * q.x;
    }

    //
    // LErp
    //
    template <typename T, typename Y>
    inline Vec2<T> LErp( const Vec2<T>& a, const Vec2<T>& b, const Y& t )
    {
        assert( t >= static_cast<T>( 0.0 ) && t <= static_cast<T>( 1.0 ) );

        Vec2<T> c;

        c.x = a.x + t * (b.x - a.x);
        c.y = a.y + t * (b.y - a.y);

        return c;
    }

    //
    // SLErp
    //
    template <typename T, typename Y>
    inline Vec2<T> SLErp( const Vec2<T>& a, const Vec2<T>& b, const Y& t )
    {
        assert( t >= static_cast<T>( 0.0 ) && t <= static_cast<T>( 1.0 ) );

    #ifdef _DEBUG
        a.Assume();
        b.Assume();
    #endif

        T Cosom = DotProduct( a, b );
	    
        if (static_cast<T>( 1.0 ) - Cosom > SLERP_EPSILON) 
        {
            T Omega = ACos( Cosom );
            T Sinom = Sin( Omega );	    
            T s0 = Sin( static_cast<T>( 1.0 ) - t ) * Omega ) / Sinom;
            T s1 = Sin( t * Omega ) / Sinom;
	   
            return a * s0 + b * s1;
        }
            
        return a + t * (b - a);
    }

    //
    // Max
    //
    template <typename T> 
    inline Vec2<T> Max( const Vec2<T>& a, const Vec2<T>& b )
    {
        return Vec2<T>( Max( a.x, b.x ), Max( a.y, b.y ) );
    }

    //
    // Min
    //
    template <typename T> 
    inline Vec2<T> Min( const Vec2<T>& a, const Vec2<T>& b )
    {
        return Vec2<T>( Min( a.x, b.x ), Min( a.y, b.y ) );
    }

    //
    // Reflect
    //
    template <typename T>
    inline Vec2<T> Reflect( const Vec2<T>& I, const Vec2<T>& N )
    {
        return I - static_cast<T>( 2.0 ) * DotProduct( N, I ) * N;
    }
} 

#endif // __MATH_VEC2_H__