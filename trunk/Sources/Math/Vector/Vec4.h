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

// Файл: /Math/Vector/Vec4.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_VEC4_H__
#define __MATH_VEC4_H__

namespace Math
{
    //  Четырёхкомпонентный вектор.

    template <typename T> 
    class Vec4 : public Vec<4, T>
    {
    public:
        T                   y, z, w;

                            Vec4();
                
                            Vec4( const T& s );
                            Vec4( const T& x, const T& y, const T& z, const T& w = static_cast<T>( 1.0 ) );
    
        TEMPLATE_Y          Vec4( const Vec2<Y>& v );
        TEMPLATE_Y          Vec4( const Vec3<Y>& v );
        TEMPLATE_Y          Vec4( const Vec3<Y>& v, const Y& w );
        TEMPLATE_Y          Vec4( const Vec4<Y>& v );

        TEMPLATE_Y          Vec4( const Y v[ 4 ] );
        TEMPLATE_Y          Vec4( const vector<Y>& v );

        //
        // Interface
        //
                                                                
        T                   GetLength() const;
        T                   GetSquareLength() const;

        T                   Normalize();
        Vec4<T>             GetNormalized() const;
        void                NormalizeFast(); 
        Vec4<T>             GetNormalizedFast() const;

        TEMPLATE_Y Vec2<Y>  ToVec2() const;
        TEMPLATE_Y Vec3<Y>  ToVec3() const;

        //
        // Swizzling
        //

        // TODO: Implement?

        //
        // Operators
        //

        const Vec4<T>&      operator + () const { return *this; }
        Vec4<T>             operator - () const { return Vec4<T>( -x, -y, -z, -w ); }

        Vec4<T>&            operator = (const Vec3<T>& v); // Компонент w не изменяется.

        Vec4<T>&            operator *= (const T& s);   
        Vec4<T>&            operator *= (const Vec4<T>& v); 
        Vec4<T>&            operator *= (const Mat4& m); // Cм. Postponed.h
        Vec4<T>&            operator /= (const T& s);
        Vec4<T>&            operator /= (const Vec4<T>& v); 
        Vec4<T>&            operator += (const T& s);
        Vec4<T>&            operator += (const Vec3<T>& v); // !
        Vec4<T>&            operator += (const Vec4<T>& v);
        Vec4<T>&            operator -= (const T& s);
        Vec4<T>&            operator -= (const Vec3<T>& v); // !
        Vec4<T>&            operator -= (const Vec4<T>& v);

        Vec4<T>             operator * (const T& s) const;  
        friend Vec4<T>      operator * (const T& s, const Vec4<T>& v) { return v * s; }
        Vec4<T>             operator * (const Vec4<T>& v) const; 
        Vec4<T>             operator / (const T& s) const; 
        Vec4<T>             operator / (const Vec4<T>& v) const; 
        Vec4<T>             operator + (const T& s) const; 
        Vec4<T>             operator + (const Vec4<T>& v) const; 
        Vec4<T>             operator - (const T& s) const;
        Vec4<T>             operator - (const Vec4<T>& v) const;
    };

    //
    // Constructor
    //
    template <typename T> 
    inline Vec4<T>::Vec4() 
    {
    }

    //
    // Constructor
    //
    template <typename T> 
    inline Vec4<T>::Vec4( const T& s ):
        Vec<4, T>( s ), y( s ), z( s ), w( s ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> 
    inline Vec4<T>::Vec4( const T& x, const T& y, const T& z, const T& w ): 
        Vec<4, T>( x ), y( y ), z( z ), w( w ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const Vec2<Y>& v ):
        Vec<4, T>( v.x ), y( v.y ), z( 0.0 ), w( 1.0 )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const Vec3<Y>& v ):
        Vec<4, T>( v.x ), y( v.y ), z( v.z ), w( 1.0 )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const Vec3<Y>& v, const Y& w ):
        Vec<4, T>( v.x ), y( v.y ), z( v.z ), w( w )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const Vec4<Y>& v ):
        Vec<4, T>( v.x ), y( v.y ), z( v.z ), w( v.w )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const Y v[ 4 ] ): 
        Vec<4, T>( v )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Vec4<T>::Vec4( const vector<Y>& v ): 
        Vec<4, T>( v )
    {
    }

    //
    // GetLength
    //
    template <typename T> 
    inline T Vec4<T>::GetLength() const
    {
        return SqRt( x * x + y * y + z * z + w * w );
    }

    //
    // GetSquareLength
    //
    template <typename T> 
    inline T Vec4<T>::GetSquareLength() const
    {
        return x * x + y * y + z * z + w * w;
    }

    //
    // Normalize
    //
    template <typename T> 
    inline T Vec4<T>::Normalize()
    {
        T Length = GetLength();

        if (Length > EPSILON && Abs( static_cast<T>( 1.0 ) - Length ) > EPSILON) 
        {
            T r = static_cast<T>( 1.0 ) / Length;

            x *= r;
            y *= r;
            z *= r;
            w *= r;
        }

        return Length;
    }

    //
    // GetNormalized
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::GetNormalized() const
    {
        Vec4<T> v = *this;

        v.Normalize();

        return v;
    }

    //
    // NormalizeFast
    //
    template <typename T> 
    inline void Vec4<T>::NormalizeFast()
    {
        T r = InvSqRt( GetSquareLength() );

        x *= r;
        y *= r;
        z *= r;
        w *= r;
    }

    //
    // GetNormalizedFast
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::GetNormalizedFast() const
    {
        Vec4<T> v = *this;

        v.NormalizeFast();

        return v;
    }

    //
    // ToVec2
    //
    template <typename T> template <typename Y>
    inline Vec2<Y> Vec4<T>::ToVec2() const
    {
        return Vec2<Y>( x, y );
    }

    //
    // ToVec3
    //
    template <typename T> template <typename Y>
    inline Vec3<Y> Vec4<T>::ToVec3() const
    {
        return Vec3<Y>( x, y, z );
    }

    //
    // operator =
    //
    template <typename T>
    inline Vec4<T>& Vec4<T>::operator = (const Vec3<T>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator *= (const T& s) 
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;

        return *this;
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator *= (const Vec4<T>& v) 
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator /= (const T& s) 
    {
        assert( s != static_cast<T>( 0.0 ) );

        T r = static_cast<T>( 1.0 ) / s;

        x *= r;
        y *= r;
        z *= r;
        w *= r;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator /= (const Vec4<T>& v) 
    {
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) && v.z != static_cast<T>( 0.0 ) && v.w != static_cast<T>( 0.0 ) );

        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator += (const T& s) 
    {
        x += s;
        y += s;
        z += s;
        w += s;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator += (const Vec3<T>& v) 
    {
        x += v.x; 
        y += v.y; 
        z += v.z;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator += (const Vec4<T>& v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator -= (const T& s) 
    {
        x -= s;
        y -= s;
        z -= s;
        w -= s;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator -= (const Vec3<T>& v) 
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Vec4<T>& Vec4<T>::operator -= (const Vec4<T>& v) 
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
 
        return *this;
    }

    //
    // operator *
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator * (const T& s) const 
    { 
        return Vec4<T>( x * s, y * s, z * s, w * s ); 
    }

    //
    // operator *
    //
    template <typename T>
    inline Vec4<T> Vec4<T>::operator * (const Vec4<T>& v) const
    {
        return Vec4<T>( x * v.x, y * v.y, z * v.z, w * v.w );
    }

    //
    // operator /
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator / (const T& s) const 
    { 
        assert( s != static_cast<T>( 0.0 ) );

        T r = static_cast<T>( 1.0 ) / s;

        return Vec4<T>( x * r, y * r, z * r, w * r ); 
    }

    //
    // operator /
    //
    template <typename T>
    inline Vec4<T> Vec4<T>::operator / (const Vec4<T>& v) const
    {
        assert( v.x != static_cast<T>( 0.0 ) && v.y != static_cast<T>( 0.0 ) && v.z != static_cast<T>( 0.0 ) && v.w != static_cast<T>( 0.0 ) );

        return Vec4<T>( x / v.x, y / v.y, z / v.z, w / v.w );
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator + (const T& s) const 
    { 
        return Vec4<T>( x + s, y + s, z + s, w + s ); 
    }

    //
    // operator +
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator + (const Vec4<T>& v) const       
    {  
        return Vec4<T>( x + v.x, y + v.y, z + v.z, w + v.w ); 
    } 

    //
    // operator -
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator - (const T& s) const 
    { 
        return Vec4<T>( x - s, y - s, z - s, w - s ); 
    }

    //
    // operator -
    //
    template <typename T> 
    inline Vec4<T> Vec4<T>::operator - (const Vec4<T>& v) const       
    { 
        return Vec4<T>( x - v.x, y - v.y, z - v.z, w - v.w ); 
    }
}

namespace Math
{
    //
    // DotProduct
    //
    template <typename T> 
    inline T DotProduct( const Vec4<T>& a, const Vec4<T>& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    //
    // CrossProduct
    //
    template <typename T> 
    inline Vec3<T> CrossProduct( const Vec4<T>& p, const Vec4<T>& q )
    {
        Vec3<T> v;

        v.x = p.y * q.z - p.z * q.y;
        v.y = p.z * q.x - p.x * q.z;
        v.z = p.x * q.y - p.y * q.x;
     
        return v;
    }
}

#endif // __MATH_VEC4_H__