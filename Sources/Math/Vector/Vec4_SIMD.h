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

// Файл: /Math/Vector/Vec4_SIMD.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_VEC4_H__
#define __MATH_SIMD_VEC4_H__

namespace MathSIMD
{
    //  Четырёхкомпонентный вектор, использующий SIMD-инструкции.

    class SIMD_ALIGN Vec4
    {
    public:
        union 
        {
            struct {
                float       x, y, z, w;  
            };

            struct {
                __m64       m1, m2;
            };

            __m128          vec; 
        };      

                            Vec4();

                            Vec4( const __m64& m1, const __m64& m2 );
                            Vec4( const __m128& vec );

                            Vec4( const float& s );
                            Vec4( const float& x, const float &y, const float& z, const float& w = 0.0f );
                                
                            Vec4( const Math::Vec2<float>& v );
                            Vec4( const Math::Vec3<float>& v );
                            Vec4( const Math::Vec3<float>& v, const float& w );
                            Vec4( const Math::Vec4<float>& v );
    
                            Vec4( const float v[] );
                            Vec4( const vector<float>& v );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        Math::Vec3<float>   ToVec3() const;
        Math::Vec4<float>   ToVec4() const;

        //
        // Operators
        //

        const float&        operator [] (const int& n) const;
        float&              operator [] (const int& n);
    };

    //
    // Constructor
    //
    inline Vec4::Vec4()
    {
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const __m64& m1, const __m64& m2 ):
        m1( m1 ), m2( m2 )
    {
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const __m128& vec ):
        vec( vec )                         
    {
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const float& s )
    {
        vec = _mm_set1_ps( s );
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const float& x, const float& y, const float& z, const float& w )
    {
        vec = _mm_set_ps( w, z, y, x );
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const Math::Vec2<float>& v )
    {
        vec = _mm_set_ps( 0.0f, 0.0f, v.y, v.x );
    }
     
    //
    // Constructor
    //
    inline Vec4::Vec4( const Math::Vec3<float>& v )
    {
        vec = _mm_set_ps( 0.0f, v.z, v.y, v.x );
    }
     
    //
    // Constructor
    //
    inline Vec4::Vec4( const Math::Vec3<float>& v, const float& w )
    {
        vec = _mm_set_ps( w, v.z, v.y, v.x );
    }
    
    //
    // Constructor
    //
    inline Vec4::Vec4( const Math::Vec4<float>& v )
    {
        vec = _mm_set_ps( v.w, v.z, v.y, v.x );
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const float v[] )
    {
        vec = _mm_loadu_ps( v );
    }

    //
    // Constructor
    //
    inline Vec4::Vec4( const vector<float>& v )
    {
        assert( v.size() >= 4 );
        vec = _mm_loadu_ps( &v[ 0 ] );
    }

    //
    // Zero
    //
    inline void Vec4::Zero()
    {
        vec = _mm_setzero_ps();
    }

    //
    // IsZero 
    //
    inline bool Vec4::IsZero() const
    {
        return (x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f);
    }

    //
    // ToVec3 
    //
    inline Math::Vec3<float> Vec4::ToVec3() const
    {
        return Math::Vec3<float>( x, y, z );
    }

    //
    // ToVec4 
    //
    inline Math::Vec4<float> Vec4::ToVec4() const
    {
        return Math::Vec4<float>( x, y, z, w );
    }

    //
    // operator [] 
    //
    inline const float& Vec4::operator [] (const int& n) const
    {
        ASSERT_RANGE( n, 0, 4 );
        return vec.m128_f32[ n ]; 
    }

    //
    // operator [] 
    //
    inline float& Vec4::operator [] (const int& n)                 
    {
        ASSERT_RANGE( n, 0, 4 );
        return vec.m128_f32[ n ]; 
    }
}

#endif // __MATH_SIMD_VEC4_H__