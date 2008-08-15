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

// Файл: /Math/Plane/Plane.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__

namespace Math
{
    template <typename T>
    class Poly3;

    //  Плоскость, описываемая уравнением вида Ax + By + Cz + D = 0.

    template <typename T>
    class Plane
    {
    public:
        union 
        {
            struct 
            {
                Vec3<T>     n;
                T           d;
            };
        
            T               eq[ 4 ];  
        };

                            Plane();

                            Plane( const T& x, const T& y, const T& z, const T& d );
                            Plane( const Vec3<T>& n, const T&d );

                            Plane( const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c );
                            Plane( const Vec4<T>& a, const Vec4<T>& b, const Vec4<T>& c );
                            Plane( const Vec3<T> p[ 3 ] );
                            Plane( const Vec4<T> p[ 3 ] );

                            Plane( const T Eq[ 4 ] );
                            Plane( const vector<T>& Eq );

        //
        // Interface
        //

        void                Zero();
        bool                IsZero() const;

        bool                Compare( const Plane<T>& p, const T& Eps = EPSILON ) const;

        T                   GetDistance( const Vec3<T>& Pt ) const;
                                                                                                                            
        void                Rotate( const Mat3& m );
        Plane<T>            GetRotated( const Mat3& m ) const;
        void                Rotate( const Mat4& m );
        Plane<T>            GetRotated( const Mat4& m ) const;
        void                Rotate( const Quat4<T>& q );
        Plane<T>            GetRotated( const Quat4<T>& q ) const;

        bool                IntersectLine( const Vec3<T>& Start, const Vec3<T>& End, Vec3<T> *Pt = NULL ) const;
        bool                IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, float *Scale = NULL ) const;
        bool                IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, Vec3<T> *Pt = NULL ) const;
        
        void                ClipPoly( const Poly3<T>& Poly, Poly3<T> *ClippedPoly ) const;
        void                ClipPoly( Poly3<T> *Poly ) const;

        TEMPLATE_Y Vec4<Y>  ToVec4() const;
        T*                  ToPtr();
        const T*            ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const Plane<T>& p) const; 
        bool                operator != (const Plane<T>& p) const;

        const T&            operator [] (const int& n) const;
        T&                  operator [] (const int& n);
    };

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane() 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const T& x, const T& y, const T& z, const T& d ): 
        n( x, y, z ), d( d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const Vec3<T>& n, const T& d ): 
        n( n ), d( d ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c ):
        n( CrossProduct( b - a, c - a ) ), d( static_cast<T>( 0.0 ) )
    {
        n.Normalize();
        d = -DotProduct( n, a );
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const Vec4<T>& a, const Vec4<T>& b, const Vec4<T>& c ):
        n( CrossProduct( b - a, c - a ) ), d( static_cast<T>( 0.0 ) )
    {
        n.Normalize();
        d = -DotProduct( n, a );
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const Vec3<T> p[ 3 ] ):
        n( CrossProduct( p[ 1 ] - p[ 0 ], p[ 2 ] - p[ 0 ] ) ), d( static_cast<T>( 0.0 ) )
    {
        n.Normalize();
        d = -DotProduct( n, p[0] );
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const Vec4<T> p[ 3 ] ):
        n( CrossProduct( p[ 1 ] - p[ 0 ], p[ 2 ] - p[ 0 ] ) ), d( static_cast<T>( 0.0 ) )
    {
        n.Normalize();
        d = -DotProduct( n, p[0] );
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const T Eq[ 4 ] ): 
        n( Eq[ 0 ], Eq[ 1 ], Eq[ 2 ] ), d( Eq[ 3 ] ) 
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Plane<T>::Plane( const vector<T>& Eq ): 
        n( Eq[0], Eq[1], Eq[2] ), d( eEq[3] ) 
    {
        assert( Eq.size() >= 4 );
    }

    //
    // Zero
    //
    template <typename T>
    inline void Plane<T>::Zero()
    {
        n.Zero();
        d = static_cast<T>( 0.0 );
    }

    //
    // IsZero
    //
    template <typename T>
    inline bool Plane<T>::IsZero() const
    {
        return n.IsZero() && d == static_cast<T>( 0.0 );
    }

    //
    // Compare
    //
    template <typename T> 
    inline bool Plane<T>::Compare( const Plane<T>& p, const T& Eps ) const 
    {
        if (!n.Compare( p.n, Eps ))
            return false;
        if (Abs( d - p.d ) > Eps)
            return false;
    
        return true;
    }

    //
    // GetDistance
    //
    template <typename T>
    inline T Plane<T>::GetDistance( const Vec3<T>& Pt ) const
    {
        return DotProduct( n, Pt ) + d;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Mat3& m )
    {
        Vec3<T> Pt = n * -d;

        n *= m;
        n.Normalize();

        Pt *= m;

        d = -DotProduct( n, Pt );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Mat3& m ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( m );

        return Plane;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Mat4& m )
    {
        Vec4<T> n( this->n, static_cast<T>( 0.0 ) );

        n *= m;
        n.Normalize();

        Vec4<T> Pt( this->n * -d, static_cast<T>( 1.0 ) );

        Pt *= m;
    
        this->n = n.ToVec3<T>();
        d = -DotProduct( n, Pt );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Mat4& m ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( m );

        return Plane;
    }

    //
    // Rotate
    //
    template <typename T>
    inline void Plane<T>::Rotate( const Quat4<T>& q )
    {
        Vec3<T> Pt = n * -d;

        n *= q;
        n.Normalize();

        Pt *= q;

        d = -DotProduct( n, Pt );
    }

    //
    // GetRotated
    //
    template <typename T>
    inline Plane<T> Plane<T>::GetRotated( const Quat4<T>& q ) const
    {
        Plane<T> Plane( *this );

        Plane.Rotate( q );

        return Plane;
    }

    //
    // IntersectLine
    //
    template <typename T> 
    inline bool Plane<T>::IntersectLine( const Vec3<T>& Start, const Vec3<T>& End, Vec3<T> *Pt ) const
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
        if (Pt)
            *Pt = (End * Dist[ 0 ] - Start * Dist[ 1 ]) / Dist[ 2 ]; 
    
        return true;
    }

    //
    // IntersectRay
    //
    template <typename T> 
    inline bool Plane<T>::IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, float *Scale ) const
    {
        T Dist[ 2 ];

        Dist[ 1 ] = DotProduct( n, Dir );
        if (Abs( Dist[ 1 ] ) < EPSILON)
            return false;

        Dist[ 0 ] = GetDistance( Start );
        if (Scale)
            *Scale = -(Dist[ 0 ] / Dist[ 1 ]);

        return true;
    }

    //
    // IntersectRay
    //
    template <typename T> 
    inline bool Plane<T>::IntersectRay( const Vec3<T>& Start, const Vec3<T>& Dir, Vec3<T> *Pt ) const
    {
        T Scale;

        if (!IntersectRay( Start, Dir, &Scale ))
            return false;
        if (Pt)
            *Pt = Start + Dir * Scale;

        return true;
    }

    //
    // ClipPoly
    //
    template <typename T>
    inline void Plane<T>::ClipPoly( const Poly3<T>& Poly, Poly3<T> *ClippedPoly ) const
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
    inline void Plane<T>::ClipPoly( Poly3<T> *Poly ) const
    {
        if (Poly->GetNumPoints() < 3)
            return;

        Poly3<T> ClippedPoly;

        ClipPoly( *Poly, &ClippedPoly );
        *Poly = ClippedPoly;
    }

    //
    // ToVec4
    //
    template <typename T> template <typename Y>
    inline Vec4<Y> Plane<T>::ToVec4() const
    {
        return Vec4<Y>( n.x, n.y, n.z, d ); 
    }
    
    //
    // ToPtr
    //
    template <typename T>
    inline T *Plane<T>::ToPtr()
    {
        return &n.x;
    }

    //
    // ToPtr
    //
    template <typename T>
    inline const T *Plane<T>::ToPtr() const
    {
        return &n.x;
    }

    //
    // operator ==
    //
    template <typename T>
    inline bool Plane<T>::operator == (const Plane<T>& p) const
    {
        return Compare( p, static_cast<T>( 0.0 ) );
    }
      
    //
    // operator !=
    //
    template <typename T>
    inline bool Plane<T>::operator != (const Plane<T>& p) const
    {
        return !Compare( p, static_cast<T>( 0.0 ) );
    }

    //
    // operator []
    //
    template <typename T> 
    inline const T &Plane<T>::operator [] (const int& n) const               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }

    //
    // operator []
    //
    template <typename T> 
    inline T &Plane<T>::operator [] (const int& n)               
    { 
    #ifdef MATH_ASSERT_RANGES
        assert( n >= 0 && n < 4 );
    #endif
        return eq[ n ];
    }
}

#endif // __MATH_PLANE_H__