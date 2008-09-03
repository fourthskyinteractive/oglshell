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

// Файл: /Math/Vector/Vec4_SSE.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_VEC4_SSE_H__
#define __MATH_SIMD_VEC4_SSE_H__

namespace MathSIMD
{
    class Mat4_SSE;

    //  Вектор, ипользующий SIMD-инструкции SSE.
    //  Fast-методы и оператор деления на скаляр имеют точность ~12 бит.

    class Vec4_SSE : public Vec4
    {
    public:
                            SIMD_ALLOCATOR();

    public:
                            Vec4_SSE();

                            Vec4_SSE( const __m128& vec );

                            Vec4_SSE( const float& s );
                            Vec4_SSE( const float& x, const float& y, const float& z, const float& w = 0.0f );

                            Vec4_SSE( const Math::Vec2<float>& v );
                            Vec4_SSE( const Math::Vec3<float>& v );
                            Vec4_SSE( const Math::Vec3<float>& v, const float& w );
                            Vec4_SSE( const Math::Vec4<float>& v );

                            Vec4_SSE( const float v[] );
                            Vec4_SSE( const vector<float>& v );

        //
        // Interface
        //

        bool                Compare( const Vec4_SSE& v ) const;

        float               GetLength() const;
        float               GetLengthFast() const;
        float               GetSquareLength() const;

        void                Normalize();  
        Vec4_SSE            GetNormalized() const;
        void                NormalizeFast();
        Vec4_SSE            GetNormalizedFast() const;

        void                Truncate( const float& Length );
        Vec4_SSE            GetTruncated( const float& Length ) const;
        void                TruncateFast( const float& Length );
        Vec4_SSE            GetTruncatedFast( const float& Length ) const;

        //
        // Operators
        //

        const Vec4_SSE&     operator + () const { return *this; }
        Vec4_SSE            operator - () const { return Vec4_SSE( -x, -y, -z, -w ); }

        Vec4_SSE&           operator *= (const float& s);                  
        Vec4_SSE&           operator *= (const Mat4_SSE& m); // Cм. Postponed.h
        Vec4_SSE&           operator /= (const float& s);
        Vec4_SSE&           operator += (const float& s);
        Vec4_SSE&           operator += (const Vec4_SSE& v);
        Vec4_SSE&           operator -= (const float& s);
        Vec4_SSE&           operator -= (const Vec4_SSE& v);

        Vec4_SSE            operator * (const float& s) const;  
        friend Vec4_SSE     operator * (const float& s, const Vec4_SSE& v) { return v * s; }
        Vec4_SSE            operator / (const float& s) const;          
        Vec4_SSE            operator + (const float& s) const; 
        Vec4_SSE            operator + (const Vec4_SSE& v) const; 
        Vec4_SSE            operator - (const float& s) const;
        Vec4_SSE            operator - (const Vec4_SSE& v) const;
    };

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE()
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const __m128& vec ):
        Vec4( vec )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const float& s ):
        Vec4( s )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const float& x, const float& y, const float& z, const float& w ):
        Vec4( x, y, z, w )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const Math::Vec2<float>& v ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const Math::Vec3<float>& v ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const Math::Vec3<float>& v, const float& w ):
        Vec4( v, w )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const Math::Vec4<float>& v ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const float v[] ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_SSE::Vec4_SSE( const vector<float>& v ):
        Vec4( v )
    {
    }

    //
    // Compare
    //
    inline bool Vec4_SSE::Compare( const Vec4_SSE& v ) const
    {
        __m128 r0 = _mm_cmpeq_ps( vec, v.vec );

        if (r0.m128_u32[ 0 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 1 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 2 ] != 0xFFFFFFFF)
            return false;
        if (r0.m128_u32[ 3 ] != 0xFFFFFFFF)
            return false;

        return true;
    }

    //
    // GetLength
    //
    inline float Vec4_SSE::GetLength() const
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r0 = _mm_sqrt_ss( r0 );

        float l;

        _mm_store_ss( &l, r0 );

        return l;
    }

    //
    // GetLengthFast
    //
    inline float Vec4_SSE::GetLengthFast() const
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r1 = _mm_rsqrt_ss( r0 );
        r0 = _mm_mul_ss( r0, r1 );

        float l;

        _mm_store_ss( &l, r0 );

        return l;
    }

    //
    // GetSquareLength
    //
    inline float Vec4_SSE::GetSquareLength() const
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
  
        float sl;

        _mm_store_ss( &sl, r0 );

        return sl;
    }

    //
    // Normalize
    //
    inline void Vec4_SSE::Normalize()
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r1 = _mm_rsqrt_ss( r0 );

        static const float c0 = 3.0f, c1 = -0.5f;

        // The general Newton-Raphson reciprocal square root recurrence:
        // (3 - b * X * X) * (X / 2)
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_sub_ps( r0, _mm_load_ss( &c0 ) );
        r1 = _mm_mul_ss( r1, _mm_load_ss( &c1 ) );
        r0 = _mm_mul_ss( r0, r1 );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );
    }

    //
    // GetNormalized
    //
    inline Vec4_SSE Vec4_SSE::GetNormalized() const
    {
        Vec4_SSE v = *this;

        v.Normalize();

        return v;
    }

    //
    // NormalizeFast
    //
    inline void Vec4_SSE::NormalizeFast()
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r0 = _mm_rsqrt_ss( r0 );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );
    }

    //
    // GetNormalizedFast
    //
    inline Vec4_SSE Vec4_SSE::GetNormalizedFast() const
    {
        Vec4_SSE v = *this;

        v.NormalizeFast();

        return v;
    }

    //
    // Truncate
    //
    inline void Vec4_SSE::Truncate( const float& Length )
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r1 = _mm_rsqrt_ss( r0 );

        static const float c0 = 3.0f, c1 = -0.5f;

        // The general Newton-Raphson reciprocal square root recurrence:
        // (3 - b * X * X) * (X / 2)
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_sub_ps( r0, _mm_load_ss( &c0 ) );
        r1 = _mm_mul_ss( r1, _mm_load_ss( &c1 ) );
        r0 = _mm_mul_ss( r0, r1 );

        // TODO: Может быть, загрузку значения следует делать в начале функции, 
        // чтобы снизить латентность доступа к памяти?
        r0 = _mm_mul_ss( r0, _mm_load_ss( &Length ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );
    }

    //
    // GetTruncated
    //
    inline Vec4_SSE Vec4_SSE::GetTruncated( const float& Length ) const
    {
        Vec4_SSE v = *this;

        v.Truncate( Length );

        return v;
    }

    //
    // TruncateFast
    //
    inline void Vec4_SSE::TruncateFast( const float& Length )
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r0 = _mm_rsqrt_ss( r0 );

        r0 = _mm_mul_ss( r0, _mm_load_ss( &Length ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );
    }

    //
    // GetTruncatedFast
    //
    inline Vec4_SSE Vec4_SSE::GetTruncatedFast( const float& Length ) const
    {
        Vec4_SSE v = *this;

        v.TruncateFast( Length );

        return v;
    }

    //
    // operator *= 
    //
    inline Vec4_SSE& Vec4_SSE::operator *= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );

        return *this;
    }

    //
    // operator /=
    //
    inline Vec4_SSE& Vec4_SSE::operator /= (const float& s)
    {
        assert( s != 0.0f );

        __m128 r0;

        r0 = _mm_rcp_ss( _mm_load_ss( &s ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        vec = _mm_mul_ps( vec, r0 );

        return *this;
    }

    //
    // operator +=
    //
    inline Vec4_SSE& Vec4_SSE::operator += (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );  
        vec = _mm_add_ps( vec, r0 );

        return *this;
    }

    //
    // operator +=
    //
    inline Vec4_SSE& Vec4_SSE::operator += (const Vec4_SSE& v)
    {
        vec = _mm_add_ps( vec, v.vec );

        return *this;
    }

    //
    // operator -=
    //
    inline Vec4_SSE& Vec4_SSE::operator -= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );  
        vec = _mm_sub_ps( vec, r0 );

        return *this;
    }

    //
    // operator -=
    //
    inline Vec4_SSE& Vec4_SSE::operator -= (const Vec4_SSE& v)
    {
        vec = _mm_sub_ps( vec, v.vec );

        return *this;
    }

    //
    // operator *
    //
    inline Vec4_SSE Vec4_SSE::operator * (const float& s) const
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );   
        r0 = _mm_mul_ps( r0, vec );

        return Vec4_SSE( r0 );
    }

    //
    // operator /
    //
    inline Vec4_SSE Vec4_SSE::operator / (const float& s) const
    {
        assert( s != 0.0f );

        __m128 r0;

        r0 = _mm_rcp_ss( _mm_load_ss( &s ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );   
        r0 = _mm_mul_ps( r0, vec );

        return Vec4_SSE( r0 );
    }

    //
    // operator +
    //
    inline Vec4_SSE Vec4_SSE::operator + (const float &s) const
    {
        __m128 r0;
   
        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );  
        r0 = _mm_add_ps( r0, vec );

        return Vec4_SSE( r0 );
    }

    //
    // operator +
    //
    inline Vec4_SSE Vec4_SSE::operator + (const Vec4_SSE& v) const
    {
        return Vec4_SSE( _mm_add_ps( vec, v.vec ) );
    }

    //
    // operator -
    //
    inline Vec4_SSE Vec4_SSE::operator - (const float& s) const
    {
        __m128 r0;
   
        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) );  
        r0 = _mm_sub_ps( r0, vec );

        return Vec4_SSE( r0 );
    }

    //
    // operator -
    //
    inline Vec4_SSE Vec4_SSE::operator - (const Vec4_SSE& v) const
    {
        return Vec4_SSE( _mm_sub_ps( vec, v.vec ) );
    }
}

namespace MathSIMD
{
    //
    // DotProduct
    //
    inline float DotProduct( const Vec4_SSE& a, const Vec4_SSE& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    //
    // CrossProduct
    //
    inline Vec4_SSE CrossProduct( const Vec4_SSE& p, const Vec4_SSE& q )
    {
        __m128 r0, r1, r2, r3;

        r0 = _mm_shuffle_ps( p.vec, p.vec, _MM_SHUFFLE( 3, 0, 2, 1 ) );
        r1 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r2 = _mm_shuffle_ps( p.vec, p.vec, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r3 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 3, 0, 2, 1 ) );

        r0 = _mm_mul_ps( r0, r1 );
        r2 = _mm_mul_ps( r2, r3 );
        r0 = _mm_sub_ps( r0, r2 );

        return Vec4_SSE( r0 );
    }

    //
    // Normal
    //
    inline Vec4_SSE Normal( const Vec4_SSE& a, const Vec4_SSE& b, const Vec4_SSE& c )
    {
        __m128 r0, r1, r2, r3, r4, r5;

        r0 = _mm_sub_ps( b.vec, a.vec );
        r1 = _mm_sub_ps( c.vec, a.vec );

        r2 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 3, 0, 2, 1 ) );
        r3 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r4 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 3, 1, 0, 2 ) );
        r5 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 3, 0, 2, 1 ) );

        r2 = _mm_mul_ps( r2, r3 );
        r4 = _mm_mul_ps( r4, r5 );
        
        __m128 vec = _mm_sub_ps( r2, r4 );
	
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r0 = _mm_rsqrt_ss( r0 );

        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );

        return Vec4_SSE( vec );
    }
                                                                                                
    //
    // LErp
    //
    inline Vec4_SSE LErp( const Vec4_SSE& a, const Vec4_SSE& b, const float& t )
    {
        assert( t >= 0.0f && t <= 1.0f );

        __m128 r0, r1;

        r0 = _mm_load_ss( &t );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        r1 = _mm_sub_ps( b.vec, a.vec );
        r0 = _mm_mul_ps( r0, r1 );
        r0 = _mm_add_ps( a.vec, r0 );

        return Vec4_SSE( r0 );
    }
}

#endif // __MATH_SIMD_VEC4_SSE_H__