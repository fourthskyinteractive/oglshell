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

// Файл: /Math/Vector/Vec3.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_VEC3_H__
#define __MATH_VEC3_H__

namespace Math
{
    class Mat3;
    class Mat4;

    template <typename T> 
    class Quat4;

    //  Трёхкомпонентный вектор.

    template <typename T> 
    class Vec3 : public Vec<3, T>
    {          
    public:
        T                   y, z;
            
                            Vec3();

                            Vec3( const T& s );
                            Vec3( const T& x, const T& y, const T& z = static_cast<T>( 0.0 ) );

        TEMPLATE_Y          Vec3( const Vec2<Y>& v ); // Компонент z = 0.0.
        TEMPLATE_Y          Vec3( const Vec3<Y>& v );

        TEMPLATE_Y          Vec3( const Y v[ 3 ] );
        TEMPLATE_Y          Vec3( const vector<Y>& v );

        //
        // Interface
        //

        void                Assume( const T& Eps = EPSILON ) const;

        T                   GetLength() const;
        T                   GetSquareLength() const;
    
        T                   Normalize(); 
        Vec3<T>             GetNormalized() const;
        void                NormalizeFast(); 
        Vec3<T>             GetNormalizedFast() const;                           
        void                Truncate( const T& Length );
        Vec3<T>             GetTruncated( const T& Length ) const;

        TEMPLATE_Y Vec2<Y>  ToVec2() const;
        Mat3                ToMat3() const; // Cм. Postpone.h
        Mat4                ToMat4() const; // Cм. Postpone.h

        //
        // Swizzling
        //

        Vec2<T>             xx() const;
        Vec2<T>             yx() const;
        Vec2<T>             xy() const;
        Vec2<T>             yy() const;

        Vec3<T>             xxx() const;
        Vec3<T>             yxx() const;
        Vec3<T>             zxx() const;
        Vec3<T>             xyx() const;
        Vec3<T>             yyx() const;
        Vec3<T>             zyx() const;
        Vec3<T>             xzx() const;
        Vec3<T>             yzx() const;
        Vec3<T>             zzx() const;
        Vec3<T>             xxy() const;
        Vec3<T>             yxy() const;
        Vec3<T>             zxy() const;
        Vec3<T>             xyy() const;
        Vec3<T>             yyy() const;
        Vec3<T>             zyy() const;
        Vec3<T>             xzy() const;
        Vec3<T>             yzy() const;
        Vec3<T>             zzy() const;
        Vec3<T>             xxz() const;
        Vec3<T>             yxz() const;
        Vec3<T>             zxz() const;
        const Vec3<T>&      xyz() const;
        Vec3<T>             yyz() const;
        Vec3<T>             zyz() const;
        Vec3<T>             xzz() const;
        Vec3<T>             yzz() const;
        Vec3<T>             zzz() const;

        //
        // Operators
        //
									
        const Vec3<T>&      operator + () const { return *this; }
        Vec3<T>             operator - () const { return Vec3<T>( -x, -y, -z ); }

        Vec3<T>&            operator *= (const T& s);   
        Vec3<T>&            operator *= (const Vec3<T>& v); 
        Vec3<T>&            operator *= (const Mat3& m); // См. Postpone.h  
        Vec3<T>&            operator *= (const Mat4& m); // См. Postpone.h  
        Vec3<T>&            operator *= (const Quat4<T>& q); // См. Postpone.h
        Vec3<T>&            operator /= (const T& s);
        Vec3<T>&            operator /= (const Vec3<T>& v);
        Vec3<T>&            operator += (const T& s);
        Vec3<T>&            operator += (const Vec3<T>& v);
        Vec3<T>&            operator -= (const T& s);
        Vec3<T>&            operator -= (const Vec3<T>& v);

        Vec3<T>             operator * (const T& s) const;
        friend Vec3<T>      operator * (const T& s, const Vec3<T>& v) { return v * s; }		  
        Vec3<T>             operator * (const Vec3<T>& v) const;
        Vec3<T>             operator / (const T& s) const;  
        Vec3<T>             operator / (const Vec3<T>& v) const; 
        Vec3<T>             operator + (const T& s) const;  
        Vec3<T>             operator + (const Vec3<T>& v) const; 
        Vec3<T>             operator - (const T& s) const;
        Vec3<T>             operator - (const Vec3<T>& v) const;
    };

    //
    // Constructor
    //
    template <typename T>
    inline Vec3<T>::Vec3()
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Vec3<T>::Vec3( const T& s ): 
        Vec<3, T>( s ), y( s ), z( s ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Vec3<T>::Vec3( const T& x, const T& y, const T& z ): 
        Vec<3, T>( x ), y( y ), z( z ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec3<T>::Vec3( const Vec2<Y>& v ):
        Vec<3, T>( v.x ), y( v.y ), z( 0.0 )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec3<T>::Vec3( const Vec3<Y>& v ):
        Vec<3, T>( v.x ), y( v.y ), z( v.z )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec3<T>::Vec3( const Y v[ 3 ] ): 
        Vec<3, T>( v )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec3<T>::Vec3( const vector<Y>& v ): 
        Vec<3, T>( v )
    {
    }

    //
    // Assume
    //
    template <typename T> 
    inline void Vec3<T>::Assume( const T& Eps ) const
    {
        assert( Abs( static_cast<T>( 1.0 ) - GetLength() ) <= Eps );
    }

    //
    // GetLength
    //
    template <typename T> 
    inline T Vec3<T>::GetLength() const
    {
        return SqRt( x * x + y * y + z * z );
    }

    //
    // GetSquareLength
    //
    template <typename T> 
    inline T Vec3<T>::GetSquareLength() const
    {
        return x * x + y * y + z * z;
    }

    //
    // Normalize
    //
    template <typename T> 
    inline T Vec3<T>::Normalize()
    {
        T Length = GetLength();

        if (Length > EPSILON && Abs( static_cast<T>( 1.0 ) - Length ) > EPSILON) 
        {
            T r = static_cast<T>( 1.0 ) / Length;
            x *= r;
            y *= r;
            z *= r;
        }

        return Length;
    }

    //
    // GetNormalized
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::GetNormalized() const
    {
        Vec3<T> v = *this;

        v.Normalize();

        return v;
    }

    //
    // NormalizeFast
    //
    template <typename T> 
    inline void Vec3<T>::NormalizeFast()
    {
        T r = InvSqRt( GetSquareLength() );

        x *= r;
        y *= r;
        z *= r;
    }

    //
    // GetNormalizedFast
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::GetNormalizedFast() const
    {
        Vec3<T> v = *this;

        v.NormalizeFast();

        return v;
    }

    //
    // Truncate
    //
    template <typename T> 
    inline void Vec3<T>::Truncate( const T& Length ) 
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
                z *= r;
            }
        }
    }

    //
    // GetTruncated
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::GetTruncated( const T& Length ) const
    {
        Vec3<T> v = *this;

        v.Truncate( Length );

        return v;
    }

    //
    // ToVec2
    //
    template <typename T> template <typename Y>
    inline Vec2<Y> Vec3<T>::ToVec2() const
    {
        return Vec2<Y>( x, y );
    }

    //
    // xx
    //
    template <typename T>
    inline Vec2<T> Vec3<T>::xx() const
    {
        return Vec2<T>( x, x );
    }
        
    //
    // yx
    //
    template <typename T>
    inline Vec2<T> Vec3<T>::yx() const
    {
        return Vec2<T>( y, x );
    }

    //
    // xy
    //
    template <typename T>
    inline Vec2<T> Vec3<T>::xy() const
    {
        return Vec2<T>( x, y );
    }
      
    //
    // yy
    //
    template <typename T>
    inline Vec2<T> Vec3<T>::yy() const
    {
        return Vec2<T>( y, y );
    }

    //
    // xxx
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::xxx() const
    {
        return Vec3<T>( x, x, x );
    }
      
    //
    // yxx
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::yxx() const
    {
        return Vec3<T>( y, x, x );
    }
      
    //
    // zxx
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::zxx() const
    {
        return Vec3<T>( z, x, x );
    }
      
    //
    // xyx  
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::xyx() const
    {
        return Vec3<T>( x, y, x );
    }

    //
    // yyx
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yyx() const
    {
        return Vec3<T>( y, y, x );
    }

    //
    // zyx
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zyx() const
    {
        return Vec3<T>( z, y, x );
    }

    //
    // xzx
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::xzx() const
    {
        return Vec3<T>( x, z, x );
    }

    //
    // yzx
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yzx() const
    {
        return Vec3<T>( y, z, x );
    }

    //
    // zzx
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zzx() const
    {
        return Vec3<T>( z, z, x );
    }

    //
    // xxy
    //
    template <typename T>   
    inline Vec3<T> Vec3<T>::xxy() const
    {
        return Vec3<T>( x, x, y );
    }

    //
    // yxy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yxy() const
    {
        return Vec3<T>( y, x, y );
    }

    //
    // zxy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zxy() const
    {
        return Vec3<T>( z, x, y );
    }

    //
    // xyy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::xyy() const
    {
        return Vec3<T>( x, y, y );
    }

    //
    // yyy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yyy() const
    {
        return Vec3<T>( y, y, y );
    }

    //
    // zyy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zyy() const
    {
        return Vec3<T>( z, y, y );
    }

    //
    // xzy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::xzy() const
    {
        return Vec3<T>( x, z, y );
    }

    //
    // yzy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yzy() const
    {
        return Vec3<T>( y, z, y );
    }

    //
    // zzy
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zzy() const
    {
        return Vec3<T>( z, z, y );
    }

    //
    // xxz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::xxz() const
    {
        return Vec3<T>( x, x, z );
    }

    //
    // yxz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yxz() const
    {
        return Vec3<T>( y, x, z );
    }

    //
    //  zxz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zxz() const
    {
        return Vec3<T>( z, x, z );
    }

    //
    // xyz
    //
    template <typename T>    
    inline const Vec3<T>& Vec3<T>::xyz() const
    {
        return *this;
    }

    //
    // yyz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yyz() const
    {
        return Vec3<T>( y, y, z );
    }

    //
    // zyz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zyz() const
    {
        return Vec3<T>( z, y, z );
    }

    //
    // xzz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::xzz() const
    {
        return Vec3<T>( x, z, z );
    }

    //
    // yzz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::yzz() const
    {
        return Vec3<T>( y, z, z );
    }

    //
    // zzz
    //
    template <typename T>    
    inline Vec3<T> Vec3<T>::zzz() const
    {
        return Vec3<T>( z, z, z );
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator *= (const T& s) 
    {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator *= (const Vec3<T>& v) 
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator /= (const T& s) 
    {
        assert( s != static_cast<T>( 0.0 ) );

        T r = static_cast<T>( 1.0 ) / s;
        x *= r;
        y *= r;
        z *= r;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator /= (const Vec3<T>& v) 
    {
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) && v.z != static_cast<T>( 0.0 ) );

        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator += (const T& s) 
    {
        x += s;
        y += s;
        z += s;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator += (const Vec3<T>& v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator -= (const T& s) 
    {
        x -= s;
        y -= s;
        z -= s;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec3<T>& Vec3<T>::operator -= (const Vec3<T>& v) 
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    //
    // operator *
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator * (const T& s) const 
    { 
        return Vec3<T>( x * s, y * s, z * s ); 
    }

    //
    // operator *
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::operator * (const Vec3<T>& v) const
    {
        return Vec3<T>( x * v.x, y * v.y, z * v.z );
    }

    //
    // operator /
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator / (const T& s) const 
    { 
        assert( s != static_cast<T>( 0.0 ) );

        T r = static_cast<T>( 1.0 ) / s;
        return Vec3<T>( x * r, y * r, z * r ); 
    }

    //
    // operator /
    //
    template <typename T>
    inline Vec3<T> Vec3<T>::operator / (const Vec3<T>& v) const
    {
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) && v.z != static_cast<T>( 0.0 ) );

        return Vec3<T>( x / v.x, y / v.y, z / v.z );
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator + (const T& s) const 
    { 
        return Vec3<T>( x + s, y + s, z + s ); 
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator + (const Vec3<T>& v) const       
    { 
        return Vec3<T>( x + v.x, y + v.y, z + v.z ); 
    } 

    //
    // operator -
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator - (const T& s) const 
    { 
        return Vec3<T>( x - s, y - s, z - s ); 
    }

    //
    // operator -
    //
    template <typename T> 
    inline Vec3<T> Vec3<T>::operator - (const Vec3<T>& v) const       
    { 
        return Vec3<T>( x - v.x, y - v.y, z - v.z ); 
    }
}

namespace Math 
{
    //
    // DotProduct
    //
    template <typename T> 
    inline T DotProduct( const Vec3<T>& a, const Vec3<T>& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    //
    // CrossProduct
    //
    template <typename T> 
    inline Vec3<T> CrossProduct( const Vec3<T>& p, const Vec3<T>& q )
    {
        Vec3<T> v;

        v.x = p.y * q.z - p.z * q.y;
        v.y = p.z * q.x - p.x * q.z;
        v.z = p.x * q.y - p.y * q.x;

        return v;
    }

    //
    // Normal
    //
    template <typename T> 
    inline Vec3<T> Normal( const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c )
    {
        Vec3<T> v = CrossProduct( b - a, c - a );
	
        v.Normalize();

        return v;
    }

    //
    // LErp
    //
    template <typename T, typename Y>
    inline Vec3<T> LErp( const Vec3<T>& a, const Vec3<T>& b, const Y& t )
    {
        assert( t >= static_cast<T>( 0.0 ) && t <= static_cast<T>( 1.0 ) );
    
        Vec3<T> c;

        c.x = a.x + t * (b.x - a.x);
        c.y = a.y + t * (b.y - a.y);
        c.z = a.z + t * (b.z - a.z);
    
        return c;
    }

    //
    // SLErp
    //
    template <typename T, typename Y>
    inline Vec3<T> SLErp( const Vec3<T>& a, const Vec3<T>& b, const Y& t )
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
    // Reflect
    //
    template <typename T>
    inline Vec3<T> Reflect( const Vec3<T>& I, const Vec3<T>& N )
    {
        return I - static_cast<T>( 2.0 ) * DotProduct( N, I ) * N;
    }
}

#endif // __MATH_VEC3_H__