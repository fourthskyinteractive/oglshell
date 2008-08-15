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

// Файл: /Math/Math_SIMD.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_H__
#define __MATH_SIMD_H__

#include <mmintrin.h>
#include <xmmintrin.h>
#include <mm3dnow.h>

namespace MathSIMD
{
    #define SIMD_ALIGNMENT 16

    const float EPSILON = 1e-6f;

    //  Макрос для перегрузки операторов new, new[], delete, delete[], выравнивающих память по границе, кратной 16 байтам.
    //  Используется для классов SIMD-векторов и матриц.

    #define SIMD_ALLOCATOR() \
        void* operator new ( size_t Size ) \
        { \
            return _mm_malloc( Size, SIMD_ALIGNMENT ); \
        } \
        \
        void *operator new[] ( size_t Size ) \
        { \
            return _mm_malloc( Size, SIMD_ALIGNMENT ); \
        } \
        \
        void operator delete ( void *Memory, size_t Size ) \
        { \
            _mm_free( Memory ); \
        } \
        \
        void operator delete[] ( void *Memory, size_t Size ) \
        { \
            _mm_free( Memory ); \
        }

    #ifdef _MSC_VER
    #define SIMD_ALIGN __declspec( align( SIMD_ALIGNMENT ) )
    #else 
    #define SIMD_ALIGN // TODO
    #endif // _MSC_VER

    //  Математические функции, использующие SIMD-инструкции SSE.
    //  Fast-методы имеют точность ~12 бит.

    //
    // SqRt_SSE
    //
    inline float SqRt_SSE( const float& x )
    {
        __m128 r0; 

        r0 = _mm_load_ss( &x );
        r0 = _mm_sqrt_ss( r0 );

        float y;

        _mm_store_ss( &y, r0 );

        return y;
    }

    //
    // SqRt_SSE
    //
    inline void SqRt_SSE( float x[ 4 ] )
    {
        __m128 r0;

        r0 = _mm_load_ps( x );
        r0 = _mm_sqrt_ps( r0 );

        _mm_store_ps( x, r0 );
    }

    //
    // InvSqRt_SSE
    //
    inline float InvSqRt_SSE( const float& x ) 
    {
        static const float c0 = 3.0f, c1 = -0.5f;

        __m128 r0, r1;

        r0 = _mm_load_ss( &x );
        r1 = _mm_rsqrt_ss( r0 );

        // The general Newton-Raphson reciprocal square root recurrence:
        // (3 - b * X * X) * (X / 2)
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_mul_ss( r0, r1 );
        r0 = _mm_sub_ss( r0, _mm_load_ss( &c0 ) );
        r1 = _mm_mul_ss( r1, _mm_load_ss( &c1 ) );
        r0 = _mm_mul_ss( r0, r1 );

        float y;

        _mm_store_ss( &y, r0 );

        return y;
    }

    //
    // InvSqRt_SSE
    //
    inline void InvSqRt_SSE( float x[ 4 ] ) 
    {
        SIMD_ALIGN static const float c0[ 4 ] = {3.0f, 3.0f, 3.0f, 3.0f};
        SIMD_ALIGN static const float c1[ 4 ] = {-0.5f, -0.5f, -0.5f, -0.5f};

        __m128 r0, r1;

        r0 = _mm_load_ps( x ); 
        r1 = _mm_rsqrt_ps( r0 );

        // The general Newton-Raphson reciprocal square root recurrence:
        // (3 - b * X * X) * (X / 2)
        r0 = _mm_mul_ps( r0, r1 );
        r0 = _mm_mul_ps( r0, r1 );
        r0 = _mm_sub_ps( r0, _mm_load_ps( c0 ) );
        r1 = _mm_mul_ps( r1, _mm_load_ps( c1 ) );
        r0 = _mm_mul_ps( r0, r1 );

        _mm_store_ps( x, r0 );
    }

    //
    // InvSqRtFast_SSE
    //
    inline float InvSqRtFast_SSE( const float& x ) 
    {
        __m128 r0; 

        r0 = _mm_load_ss( &x );
        r0 = _mm_rsqrt_ss( r0 );

        float y;

        _mm_store_ss( &y, r0 );

        return y;
    }

    //
    // InvSqRtFast_SSE
    //
    inline void InvSqRtFast_SSE( float x[ 4 ] ) 
    {
        __m128 r0; 

        r0 = _mm_load_ps( x );
        r0 = _mm_rsqrt_ps( r0 );

        _mm_store_ps( x, r0 );
    }

    //  Математические функции, использующие SIMD-инструкции 3DNow!
    //  Fast-методы имеют точность 15 бит.
    
    //
    // SqRt_3DNow
    //
    inline float SqRt_3DNow( const float& x ) 
    {
        __m64 r1, r2, r0 = _m_from_float( x );

        r1 = _m_pfrsqrt( r0 );

        // Newton-Raphson recurrence.
        r2 = r1;
        r1 = _m_pfrsqit1( _m_pfmul( r1, r1 ), r0 );
        r1 = _m_pfrcpit2( r1, r2 );

        r0 = _m_pfmul( r0, r1 );

        return _m_to_float( r0 );
    }

    //
    // SqRtFast_3DNow
    //
    inline float SqRtFast_3DNow( const float& x ) 
    {
        __m64 r1, r0 = _m_from_float( x );

        r1 = _m_pfrsqrt( r0 );
        r0 = _m_pfmul( r0, r1 );

        return _m_to_float( r0 );
    }

    //
    // InvSqRt_3DNow
    //
    inline float InvSqRt_3DNow( const float& x ) 
    {
        __m64 r1, r2, r0 = _m_from_float( x );

        r1 = _m_pfrsqrt( r0 );

        // Newton-Raphson recurrence.
        r2 = r1;
        r1 = _m_pfrsqit1( _m_pfmul( r1, r1 ), r0 );
        r0 = _m_pfrcpit2( r1, r2 );

        return _m_to_float( r0 );
    }

    //
    // InvSqRtFast_3DNow
    //
    inline float InvSqRtFast_3DNow( const float& x ) 
    {
        __m64 r0 = _m_from_float( x );

        r0 = _m_pfrsqrt( r0 );

        return _m_to_float( r0 );
    }
}

#endif // __MATH_SIMD_H__