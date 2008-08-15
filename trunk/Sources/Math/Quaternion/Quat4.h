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

// Файл: /Math/Quaternion/Quat4.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_QUAT4_H__
#define __MATH_QUAT4_H__

namespace Math
{
    template <typename T> 
    class Quat3;

    class Euler;

    //  Четырёхкомпонентный кватернион У. Гамильтона.
    //  Кватернион, представляющий вращение, должен быть единичным.

    template <typename T> 
    class Quat4: public Quat<4, T>
    {
    public:
        T                   y, z, w;

                            Quat4();

                            Quat4( const T& x, const T& y, const T& z, const T& w = static_cast<T>( 0.0 ) );
                                
                            Quat4( const Vec3<T>& v, const T& w = 0.0 );
        TEMPLATE_Y          Quat4( const Quat4<Y>& q );

        TEMPLATE_Y          Quat4( const Y q[ 4 ] );
        TEMPLATE_Y          Quat4( const vector<Y>& q );
        
        //
        // Interface
        //

        void                Assume( const T& Eps = EPSILON ) const;
 
        void                Identity(); 
        bool                IsIdentity( const T& Eps = EPSILON ) const;

        T                   GetNorm() const;   
        T                   GetMagnitude() const;
        T                   GetMagnitudeFast() const;
        T                   GetAngle() const;

        T                   Normalize();
        void                Conjugate();
        Quat4<T>            GetConjugated() const;
        void                Inverse();
        Quat4<T>            GetInverted() const;

        Vec3<T>             ToVec3() const;
        Quat3<T>            ToQuat3() const; // См. Postpone.h
        Mat3                ToMat3() const;
        Mat3                ToMat3FromUnit() const; 
        //Euler               ToEuler() const; // Postpone.h ?
        //AxisAngle         ToAxisAngle() const;
        Vec3<T>             ToAngularVelocity() const;                            

        //
        // Operators
        //

        const Quat4<T>&     operator + () const { return *this; }
        Quat4<T>            operator - () const { return Quat4<T>( -x, -y, -z, -w ); }

        Quat4<T>&           operator *= (const T& s);
        Quat4<T>&           operator *= (const Quat4<T>& q);
        Quat4<T>&           operator /= (const T& s);
        Quat4<T>&           operator += (const Quat4<T>& q);
        Quat4<T>&           operator -= (const Quat4<T>& q);
                                
        Quat4<T>            operator * (const T& s) const;
        friend Quat4<T>     operator * (const T& s, const Quat4<T>& q) { return q * s; }
        Vec3<T>             operator * (const Vec3<T>& v) const;
        friend Vec3<T>      operator * (const Vec3<T>& v, const Quat4<T>& q) { return q * v; }
        Quat4<T>            operator * (const Quat4<T>& q) const;
        Quat4<T>            operator / (const T &s) const;
        Quat4<T>            operator + (const Quat4<T>& q) const;
        Quat4<T>            operator - (const Quat4<T>& q) const;
    };

    //
    // Constructor
    //
    template <typename T>
    inline Quat4<T>::Quat4() 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Quat4<T>::Quat4( const T& x, const T& y, const T& z, const T& w ): 
        Quat<4, T>( x ), y( y ), z( z ), w( w ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Quat4<T>::Quat4( const Vec3<T>& v, const T& w ):
        Quat<4, T>( v.x ), y( v.y ), z( v.z ), w( w )
    {
        v.Assume( EPSILON );
    }
       
    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Quat4<T>::Quat4( const Quat4<Y>& q ):
        Quat<4, T>( q.x ), y( q.y ), z( q.z ), w( q.w )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Quat4<T>::Quat4( const Y q[ 4 ] ): 
        Quat<4, T>( q )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Quat4<T>::Quat4( const vector<Y>& q ): 
        Quat<4, T>( q )
    {
    }

    //
    // Assume
    //
    template <typename T>
    inline void Quat4<T>::Assume( const T& Eps ) const
    {
        //assert( Abs( 1.0 - Norm() ) <= eps );
    }

    //
    // Identity
    //
    template <typename T> 
    inline void Quat4<T>::Identity()
    {
        x = static_cast<T>( 0.0 );
        y = static_cast<T>( 0.0 );
        z = static_cast<T>( 0.0 );
        w = static_cast<T>( 1.0 );
    }

    //
    // IsIdentity
    //
    template <typename T>
    inline bool Quat4<T>::IsIdentity( const T& Eps ) const
    {
        return Compare( Quat4<T>( 0.0, 0.0, 0.0, 1.0 ), Eps );
    }

    //
    // GetNorm
    //
    template <typename T> 
    inline T Quat4<T>::GetNorm() const
    {
        return x * x + y * y + z * z + w * w;
    }

    //
    // GetMagnitude
    //
    template <typename T> 
    inline T Quat4<T>::GetMagnitude() const
    {
        return SqRt( x * x + y * y + z * z + w * w );
    }

    //
    // GetMagnitudeFast
    //
    template <typename T> 
    inline T Quat4<T>::GetMagnitudeFast() const
    {
        return SqrtFast( x * x + y * y + z * z + w * w );
    }

    //
    // GetAngle
    //
    template <typename T> 
    inline T Quat4<T>::GetAngle() const
    {
        T Length = Vec3<T>( x, y, z ).Length();

        if (w < static_cast<T>( 0.0 ))
            return Degrees( static_cast<T>( 2.0 ) * ATan2( -Length, -w ) );

        return Degrees( static_cast<T>( 2.0 ) * ATan2( Length, w ) );
    }

    //
    // Normalize
    //
    template <typename T> 
    inline T Quat4<T>::Normalize()
    {
        T Mag = GetMagnitude();

        if (Mag < EPSILON) 
        {
            T cs = Abs( x ) + Abs( y ) + Abs( z ) + Abs( w );

            if (cs > static_cast<T>( 0.0 )) 
            {
                *this /= cs;
                Mag = GetMagnitude();
            }
            else 
            {
                Identity();
                Mag = static_cast<T>( 1.0 );
            }
        }
  
        *this /= Mag;
        return Mag;
    }

    //
    // Conjugate
    //
    template <typename T> 
    inline void Quat4<T>::Conjugate()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    //
    // GetConjugated
    //
    template <typename T>
    inline Quat4<T> Quat4<T>::GetConjugated() const
    {
        return Quat4<T>( -x, -y, -z, w );
    }

    //
    // Inverse
    //
    template <typename T>
    inline void Quat4<T>::Inverse()
    {
        Conjugate();
        *this /= Norm();
    }

    //
    // GetInverted
    //
    template <typename T>
    inline Quat4<T> Quat4<T>::GetInverted() const
    {
        return GetConjugated() / Norm();
    }

    //
    // ToVec3
    // 
    template <typename T>
    inline Vec3<T> Quat4<T>::ToVec3() const
    {
        return Vec3<T>( x, y, z );
    }

    //
    // ToMat3
    //
    template <typename T>
    inline Mat3 Quat4<T>::ToMat3() const
    {
        T s = static_cast<T>( 2.0 ) / GetNorm();

        T x2 = x * s;
        T y2 = y * s;
        T z2 = z * s;

        T xx = x * x2; 
        T xy = x * y2; 
        T xz = x * z2;

        T yy = y * y2; 
        T yz = y * z2; 
        T zz = z * z2;

        T wx = w * x2; 
        T wy = w * y2; 
        T wz = w * z2;

        Mat3 m;

        m[ 0 ][ 0 ] = static_cast<T>( 1.0 ) - (yy + zz);
        m[ 0 ][ 1 ] = xy + wz;
        m[ 0 ][ 2 ] = xz - wy;

        m[ 1 ][ 0 ] = xy - wz;
        m[ 1 ][ 1 ] = static_cast<T>( 1.0 ) - (xx + zz);
        m[ 1 ][ 2 ] = yz + wx;

        m[ 2 ][ 0 ] = xz + wy;
        m[ 2 ][ 1 ] = yz - wx;
        m[ 2 ][ 2 ] = static_cast<T>( 1.0 ) - (xx + yy);

        return m;
    }

    //
    // ToMat3FromUnit
    //
    template <typename T>
    inline Mat3 Quat4<T>::ToMat3FromUnit() const
    {
    #ifdef _DEBUG
        Assume();
    #endif

        T x2 = x + x;
        T y2 = y + y;
        T z2 = z + z;

        T xx = x * x2; 
        T xy = x * y2; 
        T xz = x * z2;

        T yy = y * y2; 
        T yz = y * z2; 
        T zz = z * z2;

        T wx = w * x2; 
        T wy = w * y2; 
        T wz = w * z2;

        Mat3 m;

        m[ 0 ][ 0 ] = static_cast<T>( 1.0 ) - (yy + zz);
        m[ 0 ][ 1 ] = xy + wz;
        m[ 0 ][ 2 ] = xz - wy;

        m[ 1 ][ 0 ] = xy - wz;
        m[ 1 ][ 1 ] = static_cast<T>( 1.0 ) - (xx + zz);
        m[ 1 ][ 2 ] = yz + wx;

        m[ 2 ][ 0 ] = xz + wy;
        m[ 2 ][ 1 ] = yz - wx;
        m[ 2 ][ 2 ] = static_cast<T>( 1.0 ) - (xx + yy);

        return m;
    }

/*
template <typename T> 
inline Euler Quat4<T>::ToEuler() const
{
    // FIXME: implement
    assert( 0 );
    return Euler( 0.0, 0.0, 0.0 );
}
*/

/*
template <typename T> 
inline AxisAngle Quat4<T>::ToAxisAngle() const
{
    Vec3<T> axis = ToVec3();
    T length = axis.Length();

    if (length < EPSILON)
        return AxisAngle( Vec3<float>( 0.0f ), 0.0f );

    T angle;

    if (w < 0.0)
        angle = Degrees( 2.0 * ATan2( -length, -w ) ); 
    else
        angle = Degrees( 2.0 * ATan2( length, w ) ); 
    
    return AxisAngle( axis, angle );
}
*/

    //
    // ToAngularVelocity
    //
    template <typename T> 
    inline Vec3<T> Quat4<T>::ToAngularVelocity() const
    {
        Vec3<T> Axis( x, y, z );

        Axis.Normalize();

        return Axis * static_cast<T>( 2.0 ) * ACos( w );
    }

    //
    // operator *=
    //
    template <typename T> 
    inline Quat4<T>& Quat4<T>::operator *= (const T& s) 
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
    inline Quat4<T>& Quat4<T>::operator *= (const Quat4<T>& q)
    {
        Quat4<T> r;
    
        r.x = w * q.x + x * q.w + y * q.z - z * q.y;
        r.y = w * q.y + y * q.w + z * q.x - x * q.z;
        r.z = w * q.z + z * q.w + x * q.y - y * q.x;
        r.w = w * q.w - x * q.x - y * q.y - z * q.z;
    
        x = r.x;
        y = r.y;
        z = r.z;
        w = r.w;

        return *this;
    }

    //
    // operator /=
    //
    template <typename T> 
    inline Quat4<T>& Quat4<T>::operator /= (const T& s)
    {
        assert( s != 0.0 );
        T r = static_cast<T>( 1.0 ) / s;

        x *= r;
        y *= r;
        z *= r;
        w *= r;

        return *this;
    }

    //
    // operator +=
    //
    template <typename T> 
    inline Quat4<T>& Quat4<T>::operator += (const Quat4<T>& q) 
    {
        x += q.x;
        y += q.y;
        z += q.z;
        w += q.w;

        return *this;
    }

    //
    // operator -=
    //
    template <typename T> 
    inline Quat4<T>& Quat4<T>::operator -= (const Quat4<T>& q) 
    {
        x -= q.x;
        y -= q.y;
        z -= q.z;
        w -= q.w;

        return *this;
    }

    //
    // operator *
    //
    template <typename T> 
    inline Quat4<T> Quat4<T>::operator * (const T& s) const
    {   
        return Quat4<T>( x * s, y * s, z * s, w * s );
    }

    //
    // operator *
    //
    template <typename T> 
    inline Vec3<T> Quat4<T>::operator * (const Vec3<T>& v) const
    {
    #ifdef _DEBUG
        Assume();
    #endif

        // Основная реализация:
        // 24 умножения, 11 сложений, 6 вычитаний.
   
        Quat4<T> q;

        q.x = v.x * w + v.z * y - v.y * z;
        q.y = v.y * w + v.x * z - v.z * x;
        q.z = v.z * w + v.y * x - v.x * y;
        q.w = v.x * x + v.y * y + v.z * z;

        Vec3<T> u;

        u.x = w * q.x + x * q.w + y * q.z - z * q.y;
        u.y = w * q.y + y * q.w + z * q.x - x * q.z;
        u.z = w * q.z + z * q.w + x * q.y - y * q.x;
    
        // Альтернативная реализация:
        // 18 умножений, 15 сложений, 6 вычитаний.

        /*
        T x2 = x + x;
        T y2 = y + y;
        T z2 = z + z;

        T xx = x * x2; 
        T xy = x * y2; 
        T xz = x * z2;

        T yy = y * y2; 
        T yz = y * z2; 
        T zz = z * z2;

        T wx = w * x2; 
        T wy = w * y2; 
        T wz = w * z2;

        Vec3<T> u;

        u.x = v.x - v.x * (yy + zz) + v.y * (xy - wz) + v.z * (xz + wy);
        u.y = v.y + v.x * (xy + wz) - v.y * (xx + zz) + v.z * (yz - wx);
        u.z = v.z + v.x * (xz - wy) + v.y * (yz + wx) - v.z * (xx + yy);
        */

        return u;
    }

    //
    // operator *
    //
    template <typename T> 
    inline Quat4<T> Quat4<T>::operator * (const Quat4<T>& q) const
    {
        Quat4<T> r;

        r.x = w * q.x + x * q.w + y * q.z - z * q.y;
        r.y = w * q.y + y * q.w + z * q.x - x * q.z;
        r.z = w * q.z + z * q.w + x * q.y - y * q.x;
        r.w = w * q.w - x * q.x - y * q.y - z * q.z;

        return r;
    }

    //
    // operator /
    //
    template <typename T> 
    inline Quat4<T> Quat4<T>::operator / (const T& s) const
    {
        assert( s != 0.0 );
        T r = static_cast<T>( 1.0 ) / s;

        return Quat4<T>( x * r, y * r, z * r, w * r );
    }

    //
    // operator +
    //
    template <typename T> 
    inline Quat4<T> Quat4<T>::operator + (const Quat4<T>& q) const
    {
        return Quat4<T>( x + q.x, y + q.y, z + q.z, w + q.w );
    }

    //
    // operator -
    //
    template <typename T> 
    inline Quat4<T> Quat4<T>::operator - (const Quat4<T>& q) const
    {
        return Quat4<T>( x - q.x, y - q.y, z - q.z, w - q.w );
    }
}

namespace Math
{
    //
    // DotProduct
    //
    template <typename T> 
    inline T DotProduct( const Quat4<T>& a, const Quat4<T>& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    //
    // LErp 
    //
    template <typename T, typename Y> 
    inline Quat4<T> LErp( const Quat4<T>& a, const Quat4<T>& b, const Y& t )
    {       
        assert( t >= 0.0 && t <= 1.0 );

#ifdef _DEBUG
        a.Assume();
        b.Assume();
#endif
 
        Quat4<T> c;

        if (DotProduct( a, b ) < static_cast<T>( 0.0 ))
            c = a - (b + a) * t;
        else
            c = a + (b - a) * t;

        c.Normalize();

        return c;
    }

    //
    // SLErp
    //
    template <typename T, typename Y> 
    inline Quat4<T> SLErp( const Quat4<T>& a, const Quat4<T>& b, const Y& t ) 
    {
        assert( t >= static_cast<T>( 0.0 ) && t <= static_cast<T>( 1.0 ) );

#ifdef _DEBUG
        a.Assume();
        b.Assume();
#endif

        T Cosom = DotProduct( a, b );
        Quat4<T> q;

        if (Cosom < static_cast<T>( 0.0 )) 
        {
            q = -b;
            Cosom = -Cosom;
        } 
        else 
        {
            q = b;
        }

        if (static_cast<T>( 1.0 ) - Cosom > SLERP_EPSILON) 
        {
            T Omega = ACos( Cosom );
            T Sinom = Sin( Omega );        
            T s0 = Sin( static_cast<T>( 1.0 ) - t) * Omega ) / Sinom;
            T s1 = Sin( t * Omega ) / Sinom;
       
            return a * s0 + q * s1;
        }

        q = a + t * (q - a);
        q.Normalize();

        return q;
    }

    //
    // ShortestArc
    //
    template <typename T> 
    inline Quat4<T> ShortestArc( const Vec3<T>& a, const Vec3<T>& b )
    {
        Vec3<T> c = CrossProduct( a, b );
        Quat4<T> q;

        q.x = c.x;
        q.y = c.y;
        q.z = c.z;
        q.w = DotProduct( a, b );

        q.Normalize();
        q.w += static_cast<T>( 1.0 ); // Halfangle

        if (q.w < EPSILON) 
        {
            if (a.z * a.z > a.x * a.x) 
            {
                q.x = static_cast<T>( 0.0 );
                q.x = a.z;
                q.z = -a.y;
            }
            else 
            {
                q.x = a.y;
                q.y = -a.x;
                q.z = static_cast<T>( 0.0 );
            }
        }

        q.Normalize();

        return q;
    }

    //
    // OrthoProjectOnSphere
    //
    template <typename T> 
    inline Vec3<T> OrthoProjectOnSphere( const T& x, const T& y )
    {
        Vec3<T> v( x, y, static_cast<T>( 0.0 ) );
        T SquareLength = v.GetSquareLength();

        if (SquareLength > static_cast<T>( 1.0 ))
            v.Normalize();
        else
            v.z = SqRt( static_cast<T>( 1.0 ) - SquareLength );

        return v;
    }

    //
    // SwingTwistDecomposition
    // http://www.euclideanspace.com/Maths/geometry/elements/plane/planeOnPlane/
    //
    template <typename T> 
    inline void SwingTwistDecomposition( const Quat4<T>& Rot, const Vec3<T>& Dir, Quat4<T> *Swing, Quat4<T> *Twist )
    {   
        T SquareLength = Dir.GetSquareLength();
        Vec3<T> p, r = Rot.ToVec3();
       
        if (SqureLength > EPSILON)
            p = Dir * (DotProduct( r, Dir ) / SquareLength);
        else
            p.Zero();

        Twist->x = p.x; 
        Twist->y = p.y; 
        Twist->z = p.z; 
        Twist->w = Rot.w;
        Twist->Normalize();

        *Swing = Rot * Twist->GetConjugated();
    }
}

#endif // __MATH_QUAT4_H__