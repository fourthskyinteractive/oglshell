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

// Файл: /Math/Plane/PlaneEx.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_PLANE_EX_H__
#define __MATH_PLANE_EX_H__

namespace Math
{
    template <typename T>
    class Poly3;

    //  Вся расширенная функциональность при работе с уравнением плоскости
    //  располагается в этом классе.

    template <typename T>
    class PlaneEx : public Plane<T>
    {
    public:
                            PlaneEx();

                            PlaneEx( const T& x, const T& y, const T& z, const T& d );
        TEMPLATE_Y          PlaneEx( const Vec3<Y>& n, const Y& d );

        TEMPLATE_Y          PlaneEx( const Vec3<Y>& a, const Vec3<Y>& b, const Vec3<Y>& c );

        TEMPLATE_Y          PlaneEx( const Plane<Y>& p );
        TEMPLATE_Y          PlaneEx( const PlaneEx<Y>& p );

        TEMPLATE_Y          PlaneEx( const Y eq[ 4 ] );
        TEMPLATE_Y          PlaneEx( const vector<Y>& eq );

        //
        // Interface
        //

        bool                IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, Vec3<T> *Pt ) const;
        bool                IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, float *Scale ) const;

        bool                IntersectLine( const Vec3<T>& Start, const Vec3<T>& End, Vec3<T> *Pt ) const;

        void                ClipPoly( const Poly3<T>& Poly, Poly3<T> *ClippedPoly ) const;
        void                ClipPoly( Poly3<T> *Poly ) const;
    };

    //
    // Constructor
    //
    template <typename T>
    inline PlaneEx<T>::PlaneEx() 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline PlaneEx<T>::PlaneEx( const T& x, const T& y, const T& z, const T& d ): 
        Plane( x, y, z, d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const Vec3<Y>& n, const Y& d ):
        Plane( n, d )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const Vec3<Y>& a, const Vec3<Y>& b, const Vec3<Y>& c ):
        Plane( a, b, c )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const Plane<Y>& p ):
        Plane( p )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const PlaneEx<Y>& p ):
        Plane( p.n, p.d ),
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const Y eq[ 4 ] ): 
        Plane( eq )
    {
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline PlaneEx<T>::PlaneEx( const vector<Y>& eq ): 
        Plane( eq )
    {
    }

    //
    // IntersectRay
    //
    template <typename T> 
    inline bool PlaneEx<T>::IntersectRay( 
                                         const Vec3<T>& Start, const Vec3<T>& Dir, 
                                         Vec3<T> *Pt 
                                         ) const
    {
        T Dist[ 2 ];

        Dist[ 1 ] = DotProduct( n, Dir );
        if (Dist[ 1 ] >= 0.0 || Abs( Dist[ 1 ] ) < EPSILON)
            return false;

        Dist[ 0 ] = GetDistance( Start );
        
        assert( Pt != NULL );
        *Pt = Start + Dir * -(Dist[ 0 ] / Dist[ 1 ]);

        return true;
    }

    //
    // IntersectRay
    //
    template <typename T> 
    inline bool PlaneEx<T>::IntersectRay( 
                                         const Vec3<T>& Start, const Vec3<T>& Dir, 
                                         float *Scale 
                                         ) const
    {
        T Dist[ 2 ];

        Dist[ 1 ] = DotProduct( n, Dir );
        if (Dist[ 1 ] >= 0.0 || Abs( Dist[ 1 ] ) < EPSILON)
            return false;

        Dist[ 0 ] = GetDistance( Start );
        
        assert( Scale != NULL );
        *Scale = -(Dist[ 0 ] / Dist[ 1 ]);

        return true;
    }

    //
    // IntersectLine
    //
    template <typename T> 
    inline bool PlaneEx<T>::IntersectLine(      
                                          const Vec3<T>& Start, const Vec3<T>& End, 
                                          Vec3<T> *Pt 
                                          ) const
    {
        T Dist[ 3 ];

        Dist[ 0 ] = GetDistance( Start );
        Dist[ 1 ] = GetDistance( End );
        Dist[ 2 ] = Dist[ 0 ] - Dist[ 1 ];

        if (Abs( Dist[ 2 ] ) < EPSILON)
            return false;
        if ((Dist[ 0 ] > 0.0 && Dist[ 1 ] > 0.0) || (Dist[ 0 ] < 0.0 && Dist[ 1 ] < 0.0))
            return false;

        T s = Dist[ 0 ] / Dist[ 2 ];
        if (s < static_cast<T>( 0.0 ) || s > static_cast<T>( 1.0 ))
            return false;

        assert( Pt != NULL );
        *Pt = (End * Dist[ 0 ] - Start * Dist[ 1 ]) / Dist[ 2 ]; 
    
        return true;
    }

    //
    // ClipPoly
    //
    template <typename T>
    inline void PlaneEx<T>::ClipPoly( 
                                     const Poly3<T>& Poly, Poly3<T> *ClippedPoly 
                                     ) const
    {
        int N = Poly.GetNumPoints();
        if (N < 3)
            return;

        ClippedPoly->Clear();

        for (int i = 0; i < N; ++i) 
        {
            Vec3<T> Pt[ 2 ];

            Pt[ 0 ] = Poly[ i ];
            Pt[ 1 ] = Poly[ (i + 1) % N ];

            T Dist[ 2 ];

            Dist[ 0 ] = GetDistance( Pt[ 0 ] );
            Dist[ 1 ] = GetDistance( Pt[ 1 ] );

            if (Dist[ 0 ] >= static_cast<T>( 0.0 ))
                ClippedPoly->AddPoint( Pt[0] );
            if (Dist[ 0 ] * Dist[ 1 ] < static_cast<T>( 0.0 )) 
            {
                float t[ 2 ];

                t[ 0 ] = Dist[ 1 ] / (Dist[ 1 ] - Dist[ 0 ]);
                t[ 1 ] = -Dist[ 0 ] / (Dist[ 1 ] - Dist[ 0 ]);
                ClippedPoly->AddPoint( Pt[0] * t[0] + Pt[1] * t[1] );
            }
        }

        if (ClippedPoly->GetNumPoints() < 3)
            ClippedPoly->Clear();
    }

    //
    // ClipPoly
    //
    template <typename T>
    inline void PlaneEx<T>::ClipPoly( 
                                     Poly3<T> *Poly 
                                     ) const
    {
        if (Poly->GetNumPoints() < 3)
            return;

        Poly3<T> ClippedPoly;

        ClipPoly( *Poly, &ClippedPoly );
        *Poly = ClippedPoly;
    }
}

#endif // __MATH_PLANE_EX_H__ 