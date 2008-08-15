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

// Τΰιλ: /Math/Math.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_H__
#define __MATH_H__

#ifndef _INC_MATH
#define _USE_MATH_DEFINES                
#include <math.h>
#endif

#define MATH_LIB_INCLUDED

#ifdef _MSC_VER
#ifndef _DEBUG
#define inline __forceinline
#endif // _DEBUG
#endif // _MSC_VER

namespace Math
{
    #ifdef _DEBUG
    #define MATH_ASSERT_RANGES
    #endif

    #define TEMPLATE_Y template <typename Y>

    const float PI = static_cast<float>( 3.14159265358979323846 );
    const float PI2 = 2.0f * PI;

    const float EPSILON = 1e-6f;
    const float SLERP_EPSILON = 1e-3f;

    const float INFINITY = 9999999.9f;

    //
    // ACos
    //
    template <typename T> 
    inline T ACos( const T& s )
    {
        return static_cast<T>( acos( static_cast<double>( s ) ) );
    }

    //
    // ASin
    //
    template <typename T> 
    inline T ASin( const T& s )
    {
        return static_cast<T>( asin( static_cast<double>( s ) ) );
    }

    //
    // ATan
    //
    template <typename T> 
    inline T ATan( const T& s )
    {
        return static_cast<T>( atan( static_cast<double>( s ) ) );
    }

    //
    // ATan2
    //
    template <typename T> 
    inline T ATan2( const T& y, const T& x )
    {
        return static_cast<T>( atan2( static_cast<double>( y ), static_cast<double>( x ) ) );
    }

    //
    // CbRt
    //
    template <typename T>
    inline T CbRt( const T& s )
    {
        return static_cast<T>( sqrt( sqrt( static_cast<double>( s ) ) ) );
    }
  
    //
    // Ceil
    //
    template <typename T>
    inline T Ceil( const T& s )
    {
        return static_cast<T>( ceil( static_cast<double>( s ) ) );
    }

    //
    // Cos
    //
    template <typename T> 
    inline T Cos( const T& s )
    {
        return static_cast<T>( cos( static_cast<double>( s ) ) );
    }

    //
    // CosH
    //
    template <typename T> 
    inline T CosH( const T& s )
    {
        return static_cast<T>( cosh( static_cast<double>( s ) ) );
    }

    //
    // Exp
    //
    template <typename T>
    inline T Exp( const T& s )
    {
        return static_cast<T>( exp( static_cast<double>( s ) ) );
    }

    //
    // Floor
    //
    template <typename T>
    inline T Floor( const T& s )
    {
        return static_cast<T>( floor( static_cast<double>( s ) ) );
    }

    //
    // FMod
    //
    template <typename T>
    inline T FMod( const T& a, const T& b )
    {
        return static_cast<T>( fmod( static_cast<double>( a ), static_cast<double>( b ) ) ); 
    }

    //
    // Hypot
    //
    template <typename T>
    inline T Hypot( const T& Side1, const T& Side2 )
    {
        return static_cast<T>( _hypot( static_cast<double>( Side1 ), static_cast<double>( Side2 ) ) );
    }

    //
    // Log
    //
    template <typename T>
    inline T Log( const T& s )
    {
        return static_cast<T>( log( static_cast<double>( s ) ) );
    }

    //
    // Log10
    //
    template <typename T>
    inline T Log10( const T& s )
    {
        return static_cast<T>( log10( static_cast<double>( s ) ) );
    }

    //
    // Mod
    //
    template <typename T>
    inline T Mod( const T& s, double *i )
    {
        return static_cast<T>( modf( static_cast<double>( s ), i ) ); // Double version!
    }

    //
    // Pow
    //
    template <typename T>
    inline T Pow( const T& Base, const T& Exp )
    {
        return static_cast<T>( pow( static_cast<double>( Base ), static_cast<double>( Exp ) ) );
    }

    //
    // Round
    //
    template <typename T>
    inline T Round( const T& s ) 
    {
        return static_cast<T>( floor( static_cast<double>( s ) + 0.5 ) );
    }

    //
    // Sin
    //
    template <typename T> 
    inline T Sin( const T& s )
    {
        return static_cast<T>( sin( static_cast<double>( s ) ) );
    }

    //
    // SinH
    //
    template <typename T> 
    inline T SinH( const T& s )
    {
        return static_cast<T>( sinh( static_cast<double>( s ) ) );
    }

    //
    //
    //
    template <typename T> 
    inline T SqRt( const T& s )
    {
        return static_cast<T>( sqrt( static_cast<double>( s ) ) );
    }

    //
    // Tan
    //
    template <typename T> 
    inline T Tan( const T& s )
    {
        return static_cast<T>( tan( static_cast<double>( s ) ) );
    }

    //
    // TanH
    //
    template <typename T> 
    inline T TanH( const T& s )
    {
        return static_cast<T>( tanh( static_cast<double>( s ) ) );
    }

    //
    // Abs
    //
    template <typename T>
    inline T Abs( const T& s )
    {
        return (s < static_cast<T>( 0.0 )) ? -s : s;
    }

    //
    // Clamp
    //
    template <typename T> 
    inline T Clamp( const T& s, const T& min, const T& max ) 
    { 
        return Min( max, Max( min, s ) ); 
    }

    //
    // ClampPeriod
    //
    template <typename T>
    inline T ClampPeriod( const T& s, const T& min, const T& max )
    {
        T c;
    
        if (min == max)
            return min;
        else if (s < min)
            c = max - (min - s);
        else if (s > max)
            c = min + (s - max);
        else
            c = s;

        while (c < min || c > max)
            c = ClampPeriod( c, min, max );

        return c;
    }

    //
    // Cube
    //
    template <typename T> 
    inline T Cube( const T& s ) 
    { 
        return s * s * s; 
    }

    //
    // Degrees
    //
    template <typename T>
    inline T Degrees( const T& s )
    {
        return s * (static_cast<T>( 180.0 ) / static_cast<T>( PI ));
    }

    //
    // Max
    //
    template <typename T> 
    inline T Max( const T& x, const T& y ) 
    { 
        return (x > y) ? x : y; 
    }

    //
    // Max
    //
    template <typename T> 
    inline T Max( const T& x, const T& y, const T& z ) 
    { 
        return (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z); 
    }

    //
    // Max
    //
    template <typename T> 
    inline T Max( const vector<T>& v, int Dim )
    {
        assert( v.size() > 0 && Dim > 0 );
        T Max = v[0];
        
        for (vector<T>::const_iterator i = v.begin() + 1, end = v.end(); i != end; ++i) 
        {
            for (int j = 0; j < Dim; ++j) 
            {
                if ((*i)[j] > Max[j])
                    Max[j] = (*i)[j];
            }
        }

        return Max;
    }

    //
    // MaxIndex
    //
    template <typename T> 
    inline int MaxIndex( const T& x, const T& y ) 
    { 
        return (x > y) ? 0 : 1; 
    }

    //
    // MaxIndex
    //
    template <typename T> 
    inline int MaxIndex( const T& x, const T& y, const T& z ) 
    { 
        return (x > y) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2); 
    }

    //
    // MaxIndex
    //
    template <typename T> 
    inline int MaxIndex( const vector<T>& v )
    {
        assert( v.size() > 0 );
        vector<T>::const_iterator j = v.begin();

        for (vector<T>::const_iterator i = v.begin() + 1, end = v.end(); i != end; ++i) 
        {
            if (*i > *j)
                j = i;
        }

        return j - v.begin();
    }

    //
    // Min
    //
    template<class T> 
    inline T Min( const T& x, const T& y ) 
    { 
        return (x < y) ? x : y; 
    }

    //
    // Min
    //
    template<class T> 
    inline T Min( const T& x, const T& y, const T& z ) 
    { 
        return (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z); 
    }

    //
    // Min
    //
    template <typename T> 
    inline T Min( const vector<T>& v, int Dim )
    {
        assert( v.size() > 0 && Dim > 0 );
        T Min = v[0];
        
        for (vector<T>::const_iterator i = v.begin() + 1, end = v.end(); i != end; ++i) 
        {
            for (int j = 0; j < Dim; ++j) 
            {
                if ((*i)[j] < Min[j])
                    Min[j] = (*i)[j];
            }
        }

        return Min;
    }

    //
    // MinIndex
    //
    template <typename T> 
    inline int MinIndex( const T& x, const T& y ) 
    { 
        return (x < y) ? 0 : 1; 
    }

    //
    // MinIndex
    //
    template <typename T> 
    inline int MinIndex( const T& x, const T& y, const T& z ) 
    { 
        return (x < y) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2); 
    }

    //
    // MinIndex
    //
    template <typename T> 
    inline int MinIndex( const vector<T>& v )
    {
        assert( v.size() > 0 );
        vector<T>::const_iterator j = v.begin();

        for (vector<T>::const_iterator i = v.begin() + 1, end = v.end(); i != end; ++i) 
        {
            if (*i < *j)
                j = i;
        }

        return j - v.begin();
    }

    //
    // Sign
    //
    template <typename T> 
    inline T Sign( const T& s ) 
    { 
        return (s > static_cast<T>( 0 )) ? static_cast<T>( 1 ) : (s < static_cast<T>( 0 )) ? static_cast<T>( -1 ) : static_cast<T>( 0 ); 
    }

    //
    // SinCos
    //
    inline void SinCos( float s, float& Sin, float& Cos ) 
    {
    #ifdef _WIN32
	    _asm 
        {
		    fld             s
		    fsincos
		    mov             ecx, Cos
		    mov             edx, Sin
		    fstp            dword ptr [ecx]
		    fstp            dword ptr [edx]
	    }
    #else
	    Sin = sinf( s );
	    Cos = cosf( s );
    #endif
    }

    //
    // Square
    //
    template <typename T> 
    inline T Square( const T& s ) 
    { 
        return s * s; 
    }

    //
    // Radians
    //
    template <typename T>
    inline T Radians( const T& s )
    {
        return s * (static_cast<T>( PI ) / static_cast<T>( 180.0 ));
    }

    //
    // Rand
    //
    template <typename T> 
    inline T Rand( const T& min, const T& max )
    {
        assert( min < max );
        return static_cast<T>( rand() ) / static_cast<T>( RAND_MAX ) * (max - min) + min;
    }

    //
    // Reciprocal
    //
    inline float Reciprocal( const float &s ) 
    {
        const int i = 0x7F000000 - *reinterpret_cast<const int *>( &s ); 
        const float r = *reinterpret_cast<const float *>( &i ); 
        
        return r * (2.0f - s * r);
    }

    //
    // Reciprocal
    //
    inline double Reciprocal( const double &s )
    {
        return 1.0 / s;
    }

    //
    // InvSqRt
    //
    inline float InvSqRt( float x ) 
    {
        long i;
        float y, r;

	    y = x * 0.5f;
	    i = *reinterpret_cast<long *>( &x );
	    i = 0x5f3759df - ( i >> 1 );
	    r = *reinterpret_cast<float *>( &i );
	    r = r * ( 1.5f - r * r * y );
	    return r;
    }

    //
    // Trunc
    //
    template <typename T>
    inline T Trunc( const T& s )
    {
        return static_cast<T>( static_cast<int>( s ) );
    }
}

#endif // __MATH_H__