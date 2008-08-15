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

// Файл: /Math/Plane/Plane_SSE.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_PLANE_SSE_H__
#define __MATH_SIMD_PLANE_SSE_H__

namespace MathSIMD
{
    //  Плоскость, ипользующая SIMD-инструкции SSE.

    class SIMD_ALIGN Plane_SSE
    {
    public:
                            SIMD_ALLOCATOR();

    public:
        union 
        {
            struct 
            {
                Vec4_SSE    n;
                float       d; // ?
            };
        
            float           eq[ 4 ];  
        };

                            Plane_SSE();

                            Plane_SSE( const float& x, const float& y, const float& z, const float& d );
                            Plane_SSE( const Vec4_SSE& n, const float& d );
                            Plane_SSE( const Vec4_SSE& a, const Vec4_SSE& b, const Vec4_SSE& c );
                            Plane_SSE( const Vec4_SSE& a, const Vec4_SSE& b, const Vec4_SSE& c, bool Normalize );

        TEMPLATE_Y          Plane_SSE( const Math::Plane<Y>& p );
                                
                            Plane_SSE( const float eq[ 4 ] );
                            Plane_SSE( const vector<float>& eq );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        bool                Compare( const Plane_SSE& p) const;

        float               GetDistance( const Vec4_SSE& Pt ) const;
        bool                IntersectLine( const Vec4_SSE& Start, const Vec4_SSE& End, Vec4_SSE *Pt = NULL ) const;

        //
        // Operators
        //

        const float&        operator [] (const int& n) const;
        float&              operator [] (const int& n);
    };

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE() 
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const float& x, const float& y, const float& z, const float& d ): 
        n( x, y, z ), d( d ) 
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const Vec4_SSE& n, const float& d ): 
        n( n ), d( d ) 
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const Vec4_SSE& a, const Vec4_SSE& b, const Vec4_SSE& c ):
        n( CrossProduct( b - a, c - a ) ), d( -DotProduct( n, a ) )
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const Vec4_SSE& a, const Vec4_SSE& b, const Vec4_SSE& c, bool Normalize ):
        n( CrossProduct( b - a, c - a ) ), d( 0.0f )
    {
        if (Normalize)
            n.Normalize();
        d = -DotProduct( n, a );
    }

    //
    // Constructor
    //
    template <typename Y>
    inline Plane_SSE::Plane_SSE( const Math::Plane<Y>& p ):
        n( p.n ), d( p.d )
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const float eq[ 4 ] ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] ) 
    {
    }

    //
    // Constructor
    //
    inline Plane_SSE::Plane_SSE( const vector<float>& eq ): 
        n( eq[ 0 ], eq[ 1 ], eq[ 2 ] ), d( eq[ 3 ] ) 
    {
        assert( eq.size() >= 4 );
    }

    //
    // Zero
    //
    inline void Plane_SSE::Zero()
    {
        n.Zero();
        d = 0.0f;
    }

    //
    // IsZero
    //
    inline bool Plane_SSE::IsZero() const
    {
        return n.IsZero() && d == 0.0f;
    }

    //
    // Compare
    //
    inline bool Plane_SSE::Compare( const Plane_SSE& p ) const 
    {
        if (!n.Compare( p.n ))
            return false;
        if (d != p.d)
            return false;
    
        return true;
    }

    //
    // GetDistance
    //
    inline float Plane_SSE::GetDistance( const Vec4_SSE& Pt ) const
    {
        return DotProduct( n, Pt ) + d;
    }

    //
    // IntersectLine
    //
    inline bool Plane_SSE::IntersectLine( const Vec4_SSE& Start, const Vec4_SSE& End, Vec4_SSE *Pt ) const
    {
        float d[ 3 ];

        d[ 0 ] = GetDistance( Start );
        d[ 1 ] = GetDistance( End );
        d[ 2 ] = d[ 0 ] - d[ 1 ];

        if (Math::Abs( d[ 2 ] ) < Math::EPSILON)
            return false;
        if ((d[ 0 ] > 0.0f && d[ 1 ] > 0.0f) || (d[ 0 ] < 0.0f && d[ 1 ] < 0.0f))
            return false;

        float s = d[ 0 ] / d[ 2 ];
        if (s < 0.0f || s > 1.0f)
            return false;
        if (Pt)
            *Pt = (End * d[ 0 ] - Start * d[ 1 ]) / d[ 2 ];

        return true;
    }

    //
    // operator []
    //
    inline const float& Plane_SSE::operator [] (const int& n) const               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }

    //
    // operator []
    //
    inline float& Plane_SSE::operator [] (const int& n)               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }
}

#endif // __MATH_SIMD_PLANE_SSE_H__