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

// Файл: /Math/Vector/Vec4_3DNow.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_SIMD_VEC4_3DNOW_H__
#define __MATH_SIMD_VEC4_3DNOW_H__

namespace MathSIMD
{
    class Mat4_3DNow;

    //  Вектор, ипользующий SIMD-инструкции 3DNow!
    //  Fast-методы и оператор деления на скаляр имеют точность 15 бит.

    class Vec4_3DNow : public Vec4
    {
    public:
                            SIMD_ALLOCATOR();

    public:
                            Vec4_3DNow();

                            Vec4_3DNow( const __m64& m1, const __m64& m2 );
                            Vec4_3DNow( const __m128& vec );

                            Vec4_3DNow( const float& s );
                            Vec4_3DNow( const float& x, const float& y, const float& z, const float& w = 0.0f );
                             
                            Vec4_3DNow( const Math::Vec2<float>& v );
                            Vec4_3DNow( const Math::Vec3<float>& v );
                            Vec4_3DNow( const Math::Vec3<float>& v, const float& w );
                            Vec4_3DNow( const Math::Vec4<float>& v );

                            Vec4_3DNow( const float v[] );
                            Vec4_3DNow( const vector<float>& v );

        //
        // Interface
        //

        bool                Compare( const Vec4_3DNow& v ) const;

        float               GetLength() const;
        float               GetLengthFast() const;
        float               GetSquareLength() const;

        void                Normalize(); 
        Vec4_3DNow          GetNormalized() const;
        void                NormalizeFast();
        Vec4_3DNow          GetNormalizedFast() const;

        void                Truncate( const float& Length );
        Vec4_3DNow          GetTruncated( const float& Length ) const;
        void                TruncateFast( const float& Length );
        Vec4_3DNow          GetTruncatedFast( const float& Length ) const;

        //
        // Operators
        //

        const Vec4_3DNow&   operator + () const { return *this; }
        Vec4_3DNow          operator - () const { return Vec4_3DNow( -x, -y, -z, -w ); }

        Vec4_3DNow&         operator *= (const float& s);                  
        Vec4_3DNow&         operator *= (const Mat4_3DNow& m); // См. Postpone.h
        Vec4_3DNow&         operator /= (const float& s);
        Vec4_3DNow&         operator += (const float& s);
        Vec4_3DNow&         operator += (const Vec4_3DNow& v);
        Vec4_3DNow&         operator -= (const float& s);
        Vec4_3DNow&         operator -= (const Vec4_3DNow& v);

        Vec4_3DNow          operator * (const float& s) const;  
        friend Vec4_3DNow   operator * (const float& s, const Vec4_3DNow& v) { return v * s; }
        Vec4_3DNow          operator / (const float& s) const;          
        Vec4_3DNow          operator + (const float& s) const; 
        Vec4_3DNow          operator + (const Vec4_3DNow& v) const; 
        Vec4_3DNow          operator - (const float& s) const;
        Vec4_3DNow          operator - (const Vec4_3DNow& v) const;
    };

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow()
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const __m64& m1, const __m64& m2 ):
        Vec4( m1, m2 )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const __m128& vec ):
        Vec4( vec )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const float& s ):
        Vec4( s )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const float& x, const float& y, const float& z, const float& w ):
        Vec4( x, y, z, w )
    {
    }
      
    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const Math::Vec2<float>& v ):
        Vec4( v )
    {
    }
     
    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const Math::Vec3<float>& v ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const Math::Vec3<float>& v, const float& w ):
        Vec4( v, w )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const Math::Vec4<float>& v ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const float v[] ):
        Vec4( v )
    {
    }

    //
    // Constructor
    //
    inline Vec4_3DNow::Vec4_3DNow( const vector<float>& v ):
        Vec4( v )
    {
    }

    //
    // Compare
    //
    inline bool Vec4_3DNow::Compare( const Vec4_3DNow& v ) const
    {
        __m64 r0, r1;
        
        r0 = _m_pfcmpeq( m1, v.m1 );
        r1 = _m_pfcmpeq( m2, v.m2 );

        if (r0.m64_u32[ 0 ] != 0xFFFFFFFF)
            return false;
        if (r0.m64_u32[ 1 ] != 0xFFFFFFFF)
            return false;
        if (r1.m64_u32[ 0 ] != 0xFFFFFFFF)
            return false;
        if (r1.m64_u32[ 1 ] != 0xFFFFFFFF)
            return false;

        return true;
    }

    //
    // GetLength
    //
    inline float Vec4_3DNow::GetLength() const
    {
        __m64 r0, r1;
    
        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r1 = _m_pfrsqrt( r0 );

        __m64 r2 = r1;

        // Newton-Raphson recurrence.
        r1 = _m_pfrsqit1( _m_pfmul( r1, r1 ), r0 );
        r1 = _m_pfrcpit2( r1, r2 );

        r0 = _m_pfmul( r0, r1 );

        return _m_to_float( r0 );
    }

    //
    // GetLengthFast
    //
    inline float Vec4_3DNow::GetLengthFast() const
    {
        __m64 r0, r1;

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r1 = _m_pfrsqrt( r0 );

        r0 = _m_pfmul( r0, r1 );

        return _m_to_float( r0 );
    }

    //
    // GetSquareLength
    //
    inline float Vec4_3DNow::GetSquareLength() const
    {
        __m64 r0, r1;

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );

        return _m_to_float( r0 );
    }

    //
    // Normalize
    //
    inline void Vec4_3DNow::Normalize()
    {
        __m64 r0, r1;

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r1 = _m_pfrsqrt( r0 );
        
        __m64 r2 = r1;

        // Newton-Raphson recurrence.
        r1 = _m_pfrsqit1( _m_pfmul( r1, r1 ), r0 );
        r0 = _m_pfrcpit2( r1, r2 );

        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );

        _m_femms();
    }

    //
    // GetNormalized
    //
    inline Vec4_3DNow Vec4_3DNow::GetNormalized() const
    {
        Vec4_3DNow v = *this;

        v.Normalize();

        return v;
    }

    //
    // NormalizeFast
    //
    inline void Vec4_3DNow::NormalizeFast()
    {
        __m64 r0, r1;

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r0 = _m_pfrsqrt( r0 );

        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );

        _m_femms();
    }

    //
    // GetNormalizedFast
    //
    inline Vec4_3DNow Vec4_3DNow::GetNormalizedFast() const
    {
        Vec4_3DNow v = *this;

        v.NormalizeFast();

        return v;
    }

    //
    // Truncate
    //
    inline void Vec4_3DNow::Truncate( const float& Length )
    {
        __m64 r0, r1;
        __m64 r3 = _m_from_float( Length );

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r1 = _m_pfrsqrt( r0 );

        __m64 r2 = r1;

        // Newton-Raphson recurrence.
        r1 = _m_pfrsqit1( _m_pfmul( r1, r1 ), r0 );
        r1 = _m_pfrcpit2( r1, r2 );

        r3 = _m_punpckldq( r3, r3 );
        r0 = _m_pfmul( r1, r3 );

        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );
    
        _m_femms();
    }

    //
    // GetTruncated
    //
    inline Vec4_3DNow Vec4_3DNow::GetTruncated( const float& Length ) const
    {
        Vec4_3DNow v = *this;

        v.Truncate( Length );

        return v;
    }

    //
    // TruncateFast
    //
    inline void Vec4_3DNow::TruncateFast( const float& Length )
    {
        __m64 r0, r1;
        __m64 r3 = _m_from_float( Length );

        r0 = _m_pfmul( m1, m1 );
        r1 = _m_pfmul( m2, m2 );
        r0 = _m_pfacc( r0, r1 );
        r0 = _m_pfacc( r0, r0 );
        r0 = _m_pfrsqrt( r0 );
        r3 = _m_punpckldq( r3, r3 );
        r0 = _m_pfmul( r0, r3 );

        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );
    
        _m_femms();
    }

    //
    // GetTruncatedFast
    //
    inline Vec4_3DNow Vec4_3DNow::GetTruncatedFast( const float& Length ) const
    {
        Vec4_3DNow v = *this;

        v.TruncateFast( Length );

        return v;
    }

    //
    // operator *=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator *= (const float& s)
    {
        __m64 r0 = _m_from_float( s );

        r0 = _m_punpckldq( r0, r0 );
        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator /=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator /= (const float& s)
    {
        assert( s != 0.0f );

        __m64 r0 = _m_from_float( s );

        r0 = _m_pfrcp( r0 );
        m1 = _m_pfmul( m1, r0 );
        m2 = _m_pfmul( m2, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator +=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator += (const float& s)
    {
        __m64 r0 = _m_from_float( s );

        r0 = _m_punpckldq( r0, r0 );
        m1 = _m_pfadd( m1, r0 );
        m2 = _m_pfadd( m2, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator +=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator += (const Vec4_3DNow& v)
    {
        m1 = _m_pfadd( m1, v.m1 );
        m2 = _m_pfadd( m2, v.m2 );

        _m_femms();

        return *this;
    }

    //
    // operator -=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator -= (const float& s)
    {
        __m64 r0 = _m_from_float( s );

        r0 = _m_punpckldq( r0, r0 );
        m1 = _m_pfsub( m1, r0 );
        m2 = _m_pfsub( m2, r0 );

        _m_femms();

        return *this;
    }

    //
    // operator -=
    //
    inline Vec4_3DNow& Vec4_3DNow::operator -= (const Vec4_3DNow& v)
    {
        m1 = _m_pfsub( m1, v.m1 );
        m2 = _m_pfsub( m2, v.m2 );

        _m_femms();

        return *this;
    }

    //
    // operator *
    //
    inline Vec4_3DNow Vec4_3DNow::operator * (const float& s) const
    {
        Vec4_3DNow v;

        __m64 r0 = _m_from_float( s );
       
        r0 = _m_punpckldq( r0, r0 );
        v.m1 = _m_pfmul( m1, r0 );
        v.m2 = _m_pfmul( m2, r0 );

        _m_femms();

        return v;
    }

    //
    // operator /
    //
    inline Vec4_3DNow Vec4_3DNow::operator / (const float& s) const
    {
        assert( s != 0.0f );

        Vec4_3DNow v;

        __m64 r0 = _m_from_float( s );

        r0 = _m_pfrcp( r0 );
        v.m1 = _m_pfmul( m1, r0 );
        v.m2 = _m_pfmul( m2, r0 );

        _m_femms();

        return v;
    }

    //
    // operator +
    //
    inline Vec4_3DNow Vec4_3DNow::operator + (const float& s) const
    {
        Vec4_3DNow v;

        __m64 r0 = _m_from_float( s );

        r0 = _m_punpckldq( r0, r0 );
        v.m1 = _m_pfadd( m1, r0 );
        v.m2 = _m_pfadd( m2, r0 );

        _m_femms();

        return v;
    }

    //
    // operator +
    //
    inline Vec4_3DNow Vec4_3DNow::operator + (const Vec4_3DNow& u) const
    {
        Vec4_3DNow v;

        v.m1 = _m_pfadd( m1, u.m1 );
        v.m2 = _m_pfadd( m2, u.m2 );

        _m_femms();

        return v;
    }

    //
    // operator -
    //
    inline Vec4_3DNow Vec4_3DNow::operator - (const float& s) const
    {
        Vec4_3DNow v;

        __m64 r0 = _m_from_float( s );

        r0 = _m_punpckldq( r0, r0 );
        v.m1 = _m_pfsub( m1, r0 );
        v.m2 = _m_pfsub( m2, r0 );

        _m_femms();

        return v;
    }

    //
    // operator -
    //
    inline Vec4_3DNow Vec4_3DNow::operator - (const Vec4_3DNow& u) const
    {
        Vec4_3DNow v;

        v.m1 = _m_pfsub( m1, u.m1 );
        v.m2 = _m_pfsub( m2, u.m2 );

        _m_femms();

        return v;
    }
}

namespace MathSIMD
{
    //  Инструкции 3DNow! на процессорах AMD в следующих фукциях работают 
    //  медленнее x87 FPU, поэтому были заменены на стандартный код.

    //
    // DotProduct
    //
    inline float DotProduct( const Vec4_3DNow& a, const Vec4_3DNow& b )
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    //
    // CrossProduct
    //
    inline Vec4_3DNow CrossProduct( const Vec4_3DNow& p, const Vec4_3DNow& q )
    {
        Vec4_3DNow v;

        v.x = (p.y * q.z) - (p.z * q.y);
        v.y = (p.z * q.x) - (p.x * q.z);
        v.z = (p.x * q.y) - (p.y * q.x);
        v.w = 0.0f;
        
        return v;
    }

    //
    // Normal
    //
    inline Vec4_3DNow Normal( const Vec4_3DNow& a, const Vec4_3DNow& b, const Vec4_3DNow& c )
    {
         Vec4_3DNow v = CrossProduct( b - a, c - a );
	
         v.NormalizeFast();

         return v;
    }

    //
    // LErp
    //
    inline Vec4_3DNow LErp( const Vec4_3DNow& a, const Vec4_3DNow& b, const float& t )
    {
        assert( t >= 0.0f && t <= 1.0f );
    
        return a + t * (b - a);
    }
}

#endif // __MATH_SIMD_VEC4_3DNOW_H__