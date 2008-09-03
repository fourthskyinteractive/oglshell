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

// Файл: /Math/Matrix/Mat.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_MAT_H__
#define __MATH_MAT_H__

namespace Math
{
    //  Шаблон квадратной матрицы.

    template <int N, typename T>
    class Mat
    {
    public:
                                    
                            Mat();

                            Mat( const float& s ); // Только для квадратных матриц.

        TEMPLATE_Y          Mat( const Mat<N - 1, Y>& m );
        TEMPLATE_Y          Mat( const Mat<N - 1, Y>& m, const Y& v );
        
                            Mat( const float m[] );
                            Mat( const vector<float>& m );
                            Mat( const float m[ N ][ N ] ); // Инициализация строка-в-строку.

        //
        // Interface
        //

        void                Zero();
        void                Identity();
        bool                IsIdentity( const float& Eps = EPSILON ) const;

        bool                Compare( const Mat<N, T>& m, const float& Eps = EPSILON ) const;
    
        float               Trace() const;
        void                Transpose();

        float*              ToPtr();
        const float*        ToPtr() const;

        //
        // Operators
        //

        bool                operator == (const Mat<N, T>& m) const; 
        bool                operator != (const Mat<N, T>& m) const;

        T&                  operator [] (const int& n);
        const T&            operator [] (const int& n) const;
    
    protected:

        //
        // Class members
        //

        T                   m[ N ];
    };

    //
    // Constructor
    //
    template <int N, typename T>
    inline Mat<N, T>::Mat()
    {
    }

    //
    // Constructor
    //
    template <int N, typename T>
    inline Mat<N, T>::Mat( const float& s )
    {
        for (int i = 0; i < N; ++i) 
        {
            for (int j = 0; j < N; ++j)
                m[ i ][ j ] = (i == j) ? s : 0.0f;
        }
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Mat<N, T>::Mat( const Mat<N - 1, Y>& n )
    {
        for (int i = 0; i < N; ++i) 
        {
            if (i < N - 1) 
            {
                for (int j = 0; j < N; ++j)
                    m[ i ][ j ] = (j < N - 1) ? n[ i ][ j ] : 0.0f;
            }
            else 
            {
                for (int j = 0; j < N; ++j)
                    m[ i ][ j ] = (j < N - 1) ? 0.0f : 1.0f;
            }
        }
    }

    //
    // Constructor
    //
    template <int N, typename T> template <typename Y>
    inline Mat<N, T>::Mat( const Mat<N - 1, Y>& n, const Y& v )
    {
        for (int i = 0; i < N; ++i) 
        {
            if (i < N - 1) 
            {
                for (int j = 0; j < N; ++j)
                    m[ i ][ j ] = (j < N - 1) ? n[ i ][ j ] : 0.0f;
            }
            else 
            {
                for (int j = 0; j < N; ++j)
                    m[ i ][ j ] = (j < N - 1) ? v[ j ] : 1.0f;
            }
        }
    }

    //
    // Constructor
    //
    template <int N, typename T>
    inline Mat<N, T>::Mat( const float n[] )
    {
        int k = 0;

        for (int i = 0; i < N; ++i) 
        {
            for (int j = 0; j < N; ++j)
                m[ i ][ j ] = n[ k++ ];
        }
    }

    //
    // Constructor
    //
    template <int N, typename T>
    inline Mat<N, T>::Mat( const vector<float>& n )
    {
        assert( n.size() >= N * N );

        int k = 0;

        for (int i = 0; i < N; ++i) 
        {
            for (int j = 0; j < N; ++j)
                m[ i ][ j ] = n[ k++ ];
        }
    }

    //
    // Constructor
    //
    template <int N, typename T>
    inline Mat<N, T>::Mat( const float n[ N ][ N ] )
    {
        for (int i = 0; i < N; ++i) 
        {
            for (int j = 0; j < N; ++j) 
            {
                // Инициализация строка-в-строку! 
                // Т. к. в С/С++ массивы хранятся по строкам, происходит транспонирование.
                m[ i ][ j ] = n[ j ][ i ]; 
            }
        }
    }

    //
    // Zero
    //
    template <int N, typename T>
    inline void Mat<N, T>::Zero()
    {
        for (int i = 0; i < N; ++i)
            m[ i ].Zero();
    }           

    //
    // Identity
    //
    template <int N, typename T>
    inline void Mat<N, T>::Identity()
    {
        for (int i = 0; i < N; ++i) 
        {
            for (int j = 0; j < N; ++j)
                m[ i ][ j ] = (i == j) ? 1.0f : 0.0f;
        }
    }

    //
    // IsIdentity
    //
    template <int N, typename T>
    inline bool Mat<N, T>::IsIdentity( const float& Eps ) const
    {
        return Compare( Mat<N, T>( 1.0f ), Eps );
    }

    //
    // Compare
    //
    template <int N, typename T>
    inline bool Mat<N, T>::Compare( const Mat<N, T>& n, const float& Eps ) const
    {
        for (int i = 0; i < N; ++i) 
        {
            if (!m[ i ].Compare( n[ i ], Eps ))
                return false;
        }

        return true;
    }

    //
    // Trace
    //
    template <int N, typename T>
    inline float Mat<N, T>::Trace() const
    {
        float s = 0.0f;

        for (int i = 0; i < N; ++i)
            s += m[ i ][ i ];

        return s;
    }

    //
    // Transpose
    //
    template <int N, typename T>
    inline void Mat<N, T>::Transpose()
    {
        float Temp;

        for (int i = 0; i < N - 1; ++i) 
        {
            for (int j = i + 1; j < N; ++j)
            {
                Temp = m[ i ][ j ];
                m[ i ][ j ] = m[ j ][ i ];
                m[ j ][ i ] = Temp;
            }
        }
    }

    //
    // ToPtr
    //
    template <int N, typename T>
    inline float *Mat<N, T>::ToPtr()
    {
        return m[ 0 ].ToPtr();
    }

    //
    // ToPtr
    //
    template <int N, typename T>
    inline const float *Mat<N, T>::ToPtr() const
    {   
        return m[ 0 ].ToPtr();
    }

    //
    // operator ==
    //
    template <int N, typename T>
    inline bool Mat<N, T>::operator == (const Mat<N, T>& n) const
    {
        return Compare( n, 0.0f );
    }

    //
    // operator !=
    //
    template <int N, typename T>
    inline bool Mat<N, T>::operator != (const Mat<N, T>& n) const
    {
        return !Compare( n, 0.0f );
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline T& Mat<N, T>::operator [] (const int& n)
    {
        ASSERT_RANGE( n, 0, N );
        return m[ n ];
    }

    //
    // operator []
    //
    template <int N, typename T>
    inline const T& Mat<N, T>::operator [] (const int& n) const
    {
        ASSERT_RANGE( n, 0, N );
        return m[ n ];
    }
}

#endif // __MATH_MAT_H__