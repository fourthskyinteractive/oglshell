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

// Файл: /Math/Quaternion/Quat4_SSE.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_QUAT4_SSE_H__
#define __MATH_SIMD_QUAT4_SSE_H__

namespace MathSIMD
{
    //  Кватернион, использующий SIMD-инструкции SSE. 

    class SIMD_ALIGN Quat4_SSE
    {
    public:
                            SIMD_ALLOCATOR();

    public:
        union 
        {
            struct {
                float       x, y, z, w;  
            };

            __m128          vec;
        };
        
                            Quat4_SSE();

                            Quat4_SSE( const __m128& vec );

                            Quat4_SSE( const float& x, const float& y, const float& z, const float& w = 0.0f );
                                                                                                           
                            Quat4_SSE( const Math::Vec3<float>& v, const float& w = 0.0f );
                            Quat4_SSE( const Math::Quat4<float>& q );

                            Quat4_SSE( const float q[ 4 ] );
                            Quat4_SSE( const vector<float>& q );

        //
        // Interface
        //

        void                Assume( const float& Eps = EPSILON ) const;

        void                Zero();
        void                Identity(); 
        bool                IsIdentity() const;

        bool                Compare( const Quat4_SSE& q )const;

        float               GetNorm() const;   
        float               GetMagnitude() const;
        float               GetMagnitudeFast() const;

        void                Normalize();
        void                NormalizeFast();
    
        Math::Quat4<float>  ToQuat4() const;

        //
        // Operators
        //

        const Quat4_SSE&    operator + () const { return *this; }
        Quat4_SSE           operator - () const { return Quat4_SSE( -x, -y, -z, -w ); }

        Quat4_SSE&          operator *= (const float& s);
        Quat4_SSE&          operator *= (const Quat4_SSE& q);
        Quat4_SSE&          operator /= (const float& s);
        Quat4_SSE&          operator += (const Quat4_SSE& q);
        Quat4_SSE&          operator -= (const Quat4_SSE& q);

        Quat4_SSE           operator * (const float& s) const;
        friend Quat4_SSE    operator * (const float& s, const Quat4_SSE& q) { return q * s; }
        Quat4_SSE           operator * (const Quat4_SSE& q) const;
        Quat4_SSE           operator / (const float& s) const;
        Quat4_SSE           operator + (const Quat4_SSE& q) const;
        Quat4_SSE           operator - (const Quat4_SSE& q) const;

        bool                operator == (const Quat4_SSE& m) const; 
        bool                operator != (const Quat4_SSE& m) const;

        const float&        operator [] (const int& n) const;
        float&              operator [] (const int& n);
    };

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE()
    {
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const __m128& vec ):
        vec( vec )
    {
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const float& x, const float& y, const float& z, const float& w )
    {
        vec = _mm_set_ps( w, z, y, x );
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const Math::Vec3<float>& v, const float& w )
    {
        vec = _mm_set_ps( w, v.z, v.y, v.x );
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const Math::Quat4<float>& q )
    {
        vec = _mm_set_ps( q.w, q.z, q.y, q.x );
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const float q[ 4 ] )
    {                                            
        vec = _mm_loadu_ps( q );
    }

    //
    // Constructor
    //
    inline Quat4_SSE::Quat4_SSE( const vector<float>& q )
    {
        assert( q.size() >= 4 );
        vec = _mm_loadu_ps( &q[ 0 ] );
    }

    //
    // Assume
    //
    inline void Quat4_SSE::Assume( const float& Eps ) const
    {
        assert( Math::Abs( 1.0f - GetNorm() ) <= Eps );
    }

    //
    // Zero
    //
    inline void Quat4_SSE::Zero()
    {
        vec = _mm_setzero_ps();
    }

    //
    // Identity
    //
    inline void Quat4_SSE::Identity()
    {
        vec = _mm_set_ps( 1.0f, 0.0f, 0.0f, 0.0f );
    }

    //
    // IsIdentity
    //
    inline bool Quat4_SSE::IsIdentity() const
    {
        return Compare( Quat4_SSE( 0.0f, 0.0f, 0.0f, 1.0f ) );
    }

    //
    // Compare
    //
    inline bool Quat4_SSE::Compare( const Quat4_SSE& q )const
    {
        __m128 r0 = _mm_cmpeq_ps( vec, q.vec );

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
    // GetNorm
    //
    inline float Quat4_SSE::GetNorm() const
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
  
        float norm;

        _mm_store_ss( &norm, r0 );

        return norm;
    }

    //
    // GetMagnitude
    //
    inline float Quat4_SSE::GetMagnitude() const
    {
        __m128 r0, r1;
   
        r0 = _mm_mul_ps( vec, vec );
        r1 = _mm_movehl_ps( r0, r0 );
        r1 = _mm_add_ps( r0, r1 );
        r0 = _mm_move_ss( r0, r1 );
        r1 = _mm_shuffle_ps( r1, r1, _MM_SHUFFLE( 0, 0, 0, 1 ) );   
        r0 = _mm_add_ss( r0, r1 );
        r0 = _mm_sqrt_ss( r0 );

        float mag;

        _mm_store_ss( &mag, r0 );

        return mag;
    }

    //
    // GetMagnitudeFast
    //
    inline float Quat4_SSE::GetMagnitudeFast() const
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

        float mag;

        _mm_store_ss( &mag, r0 );

        return mag;
    }

    //
    // Normalize
    //
    inline void Quat4_SSE::Normalize()
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
    // NormalizeFast
    //
    inline void Quat4_SSE::NormalizeFast()
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
    // ToQuat4
    //
    inline Math::Quat4<float> Quat4_SSE::ToQuat4() const
    {
        return Math::Quat4<float>( x, y, z, w );
    }

    //
    // operator *=
    //
    inline Quat4_SSE& Quat4_SSE::operator *= (const float& s)
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );

        return *this;
    }

    //
    // opearator *=
    //
    inline Quat4_SSE& Quat4_SSE::operator *= (const Quat4_SSE& q)
    {
        __m128 r0, r1, r2, r3, r4, r5, r6;

        r0 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 3, 3, 3, 3 ) ); 
        r1 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 0, 2, 1, 0 ) ); 
        r2 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 1, 0, 2, 1 ) ); 
        r3 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 2, 1, 0, 2 ) ); 

        r4 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 0, 3, 3, 3 ) ); 
        r5 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 1, 1, 0, 2 ) ); 
        r6 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 2, 0, 2, 1 ) );

        r0 = _mm_mul_ps( r0, q.vec );
        r1 = _mm_mul_ps( r1, r4 );
        r2 = _mm_mul_ps( r2, r5 );
        r3 = _mm_mul_ps( r3, r6 );

        SIMD_ALIGN static const float c0[ 4 ] = {1.0f, 1.0f, 1.0f, -1.0f};

        r4 = _mm_load_ps( c0 );
        r1 = _mm_mul_ps( r1, r4 );
        r2 = _mm_mul_ps( r2, r4 );

        r0 = _mm_add_ps( r0, r1 );
        r0 = _mm_add_ps( r0, r2 );
        vec = _mm_sub_ps( r0, r3 );

        return *this;
    }

    //
    // operator /=
    //
    inline Quat4_SSE& Quat4_SSE::operator /= (const float& s)
    {
        __m128 r0;

        r0 = _mm_rcp_ss( _mm_load_ss( &s ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        vec = _mm_mul_ps( vec, r0 );

        return *this;
    }

    //
    // operator +=
    //
    inline Quat4_SSE& Quat4_SSE::operator += (const Quat4_SSE& q)
    {
        vec = _mm_add_ps( vec, q.vec );

        return *this;
    }

    //
    // operator -=
    //
    inline Quat4_SSE& Quat4_SSE::operator -= (const Quat4_SSE& q)
    {
        vec = _mm_sub_ps( vec, q.vec );

        return *this;
    }

    //
    // operator *
    //
    inline Quat4_SSE Quat4_SSE::operator * (const float& s) const
    {
        __m128 r0;

        r0 = _mm_load_ss( &s );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        r0 = _mm_mul_ps( r0, vec );

        return Quat4_SSE( r0 );
    }

    //
    // operator *
    //
    inline Quat4_SSE Quat4_SSE::operator * (const Quat4_SSE& q) const
    {    
        __m128 r0, r1, r2, r3, r4, r5, r6;

        r0 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 3, 3, 3, 3 ) ); 
        r1 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 0, 2, 1, 0 ) ); 
        r2 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 1, 0, 2, 1 ) ); 
        r3 = _mm_shuffle_ps( vec, vec, _MM_SHUFFLE( 2, 1, 0, 2 ) ); 

        r4 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 0, 3, 3, 3 ) ); 
        r5 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 1, 1, 0, 2 ) ); 
        r6 = _mm_shuffle_ps( q.vec, q.vec, _MM_SHUFFLE( 2, 0, 2, 1 ) );

        r0 = _mm_mul_ps( r0, q.vec );
        r1 = _mm_mul_ps( r1, r4 );
        r2 = _mm_mul_ps( r2, r5 );
        r3 = _mm_mul_ps( r3, r6 );

        SIMD_ALIGN static const float c0[ 4 ] = {1.0f, 1.0f, 1.0f, -1.0f};

        r4 = _mm_load_ps( c0 );
        r1 = _mm_mul_ps( r1, r4 );
        r2 = _mm_mul_ps( r2, r4 );

        r0 = _mm_add_ps( r0, r1 );
        r0 = _mm_add_ps( r0, r2 );
        r0 = _mm_sub_ps( r0, r3 );

        return Quat4_SSE( r0 );
    }

    //
    // operator /
    //
    inline Quat4_SSE Quat4_SSE::operator / (const float& s) const
    {
        __m128 r0;

        r0 = _mm_rcp_ss( _mm_load_ss( &s ) );
        r0 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 0, 0, 0 ) ); 
        r0 = _mm_mul_ps( r0, vec );

        return Quat4_SSE( r0 );
    }   

    //
    // operator +
    //
    inline Quat4_SSE Quat4_SSE::operator + (const Quat4_SSE& q) const
    {
        return Quat4_SSE( _mm_add_ps( vec, q.vec ) );
    }

    //
    // operator -
    //
    inline Quat4_SSE Quat4_SSE::operator - (const Quat4_SSE& q) const
    {
        return Quat4_SSE( _mm_sub_ps( vec, q.vec ) );
    }

    //
    // operator ==
    //
    inline bool Quat4_SSE::operator == (const Quat4_SSE& q) const
    {
        return Compare( q );
    }

    //
    // operator !=
    //
    inline bool Quat4_SSE::operator != (const Quat4_SSE& q) const
    {
        return !Compare( q );
    }

    //
    // operator []
    //
    inline const float& Quat4_SSE::operator [] (const int& n) const
    {
        ASSERT_RANGE( n, 0, 4 );
        return vec.m128_f32[ n ]; 
    }

    //
    // operator []
    //
    inline float& Quat4_SSE::operator [] (const int& n)
    {
        ASSERT_RANGE( n, 0, 4 );
        return vec.m128_f32[ n ]; 
    }
}

#endif // __MATH_SIMD_QUAT4_SSE_H__