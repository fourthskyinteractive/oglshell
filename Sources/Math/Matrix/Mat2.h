// Файл: /Math/Matrix/Mat2.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_MAT2_H__
#define __MATH_MAT2_H__

namespace Math
{
    //  Матрица второго порядка, запись по столбцам.

    class Mat2 : public Mat<2, Vec2<float> >
    {
    public:
                            Mat2();

                            Mat2( float s );
                            Mat2( float _00, float _01, 
                                float _10, float _11 );
                                
                            Mat2( const Vec2<float>& _0, const Vec2<float>& _1 );
                                
                            Mat2( const float m[ 4 ] );
                            Mat2( const vector<float>& m );
                            Mat2( const float m[ 2 ][ 2 ] );

        //
        // Interface
        //

        float               GetDeterminant() const;
    
        Mat2                GetTransposed() const;
        bool                Inverse();
        Mat2                GetInverted() const;

        void                Rotation( float Angle );
        void                Scaling( float x, float y );
        void                ReflectionX();
        void                ReflectionY();

        //
        // Operators
        //

        Mat2&               operator *= (const float& s);
        Mat2&               operator *= (const Mat2& m);
        Mat2&               operator /= (const float& s);
        Mat2&               operator += (const Mat2& m);
        Mat2&               operator -= (const Mat2& m);

        Mat2                operator * (const float& s) const;
        friend Mat2         operator * (const float& s, const Mat2& m) { return m * s; } 
        Vec2<float>         operator * (const Vec2<float>& v) const;
        friend Vec2<float>  operator * (const Vec2<float>& v, const Mat2& m) { return m * v; } 
        Mat2                operator * (const Mat2& m) const;
        Mat2                operator / (const float& s) const;
        Mat2                operator + (const Mat2& m) const;
        Mat2                operator - (const Mat2& m) const;
    };

    //
    // operator *=
    //
    inline Mat2& Mat2::operator *= (const float& s)
    {
        m[ 0 ] *= s;
        m[ 1 ] *= s;

        return *this;
    }

    //
    // operator *=
    //
    inline Mat2& Mat2::operator *= (const Mat2& n)
    {
        Mat2 k;
    
        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y;

        m[ 0 ] = k[ 0 ];
        m[ 1 ] = k[ 1 ];
    
        return *this;
    }

    //
    // operator /=
    //
    inline Mat2& Mat2::operator /= (const float& s)
    {
        assert( s != 0.0f );

        float r = 1.0f / s;

        m[ 0 ] *= r;
        m[ 1 ] *= r;
    
        return *this;
    }

    //
    // operator +=
    //
    inline Mat2& Mat2::operator += (const Mat2& n)
    {
        m[ 0 ] += n[ 0 ];
        m[ 1 ] += n[ 1 ];
    
        return *this;
    }

    //
    // operator -=
    //
    inline Mat2& Mat2::operator -= (const Mat2& n)
    {
        m[ 0 ] -= n[ 0 ];
        m[ 1 ] -= n[ 1 ];
    
        return *this;
    }

    //
    // operator *
    //
    inline Mat2 Mat2::operator * (const float& s) const
    {
        return Mat2( m[ 0 ] * s, m[ 1 ] * s );
    }

    //
    // operator *
    //
    inline Vec2<float> Mat2::operator * (const Vec2<float>& v) const
    {
        Vec2<float> u;

        u.x = m[ 0 ].x * v.x + m[ 1 ].x * v.y;
        u.y = m[ 0 ].y * v.x + m[ 1 ].y * v.y;

        return u;
    }

    //
    // operator *
    //
    inline Mat2 Mat2::operator * (const Mat2& n) const
    {
        Mat2 k;
    
        k[ 0 ].x = m[ 0 ].x * n[ 0 ].x + m[ 1 ].x * n[ 0 ].y;
        k[ 1 ].x = m[ 0 ].x * n[ 1 ].x + m[ 1 ].x * n[ 1 ].y;

        k[ 0 ].y = m[ 0 ].y * n[ 0 ].x + m[ 1 ].y * n[ 0 ].y;
        k[ 1 ].y = m[ 0 ].y * n[ 1 ].x + m[ 1 ].y * n[ 1 ].y;

        return k;
    }

    //
    // operator /
    //
    inline Mat2 Mat2::operator / (const float& s) const
    {
        assert( s != 0.0f );  

        float r = 1.0f / s;

        return Mat2( m[ 0 ] * r, m[ 1 ] * r );
    }

    //
    // operator +
    //
    inline Mat2 Mat2::operator + (const Mat2& n) const
    {
        return Mat2( m[ 0 ] + n[ 0 ], m[ 1 ] + n[ 1 ] );
    }

    //
    // operator -
    //
    inline Mat2 Mat2::operator - (const Mat2& n) const
    {
        return Mat2( m[ 0 ] - n[ 0 ], m[ 1 ] - n[ 1 ] );
    }
}

#endif // __MATH_MAT2_H__ 