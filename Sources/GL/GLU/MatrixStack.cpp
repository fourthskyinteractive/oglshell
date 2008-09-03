/*
OpenGL Shell - open source C++ wrapper for use in OOP programs.
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

e-mail: victor.coda@gmail.com
*/

// Τΰιλ: /GL/GLU/MatrixStack.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "MatrixStack.h"

#ifdef MATH_LIB_INCLUDED

namespace GLU
{
    //
    // Constructor
    //
    CMatrixStack::CMatrixStack():
        m_Curr( &m_World ) // DEFAULT
    {
        Mat4 m( 1.0f );

        m_World.push( m );
        m_View.push( m );
        m_Projection.push( m );
    }

    //
    // Select
    //
    void CMatrixStack::Select( 
                              EMatrix Type
                              )
    {
        switch (Type)
        {
        case MAT_WORLD:
            m_Curr = &m_World;
            break;
        case MAT_VIEW:
            m_Curr = &m_View;
            break;
        case MAT_PROJECTION:
            m_Curr = &m_Projection;
            break;

        default:
            throw Sys::CDeveloperException( this, "::Select() : Invalid <Type> parameter." );
        }
    }

    //
    // Push
    //    
    void CMatrixStack::Push()
    {
        m_Curr->push( m_Curr->top() );
    }
    
    //
    // Pop
    //
    void CMatrixStack::Pop()
    {
        m_Curr->pop();
    }

    //
    // GetMatrix
    //
    Mat4 CMatrixStack::GetTop(   
                              EMatrix Type 
                              ) const
    {
        switch (Type)
        {
        case MAT_WORLD:
            return m_World.top();
        case MAT_VIEW:
            return m_View.top();
        case MAT_PROJECTION:
            return m_Projection.top();
        case MAT_WORLDVIEW:
            return m_View.top() * m_World.top();
        case MAT_WORLDVIEW_PROJECTION:
            return m_Projection.top() * m_View.top() * m_World.top();
            
        default:
            throw Sys::CDeveloperException( this, "::GetTop() : Invalid <Type> parameter." );
        }
    }

    //
    // SetIdentity
    //
    void CMatrixStack::SetIdentity()
    {
        m_Curr->top().Identity();
    }
        
    //
    // Set
    // 
    void CMatrixStack::Set( 
                           const Mat4& m 
                           )
    {
        m_Curr->top() = m;
    }

    //
    // Multiply
    //
    void CMatrixStack::Multiply( 
                                const Mat4& m
                                )
    {
        m_Curr->top() *= m;
    }

    //
    // Translate
    //
    void CMatrixStack::Translate( 
                                 float x, float y, float z
                                 )
    {
        Translate( Vec3<float>( x, y, z ) );
    }

    //
    // Translate
    //
    void CMatrixStack::Translate( 
                                 const Vec3<float>& v 
                                 )
    {
        Mat4 m;

        m.Translation( v );
        m_Curr->top() *= m;
    }

    //
    // Rotate
    //
    void CMatrixStack::Rotate( 
                              float x, float y, float z, float Angle 
                              )
    {
        Rotate( Vec3<float>( x, y, z ), Angle );
    }

    //
    // Rotate
    //
    void CMatrixStack::Rotate( 
                              const Vec3<float>& Axis, float Angle 
                              )
    {
        Mat4 m;

        m.RotationAroundAxis( Axis, Angle );
        m_Curr->top() *= m;
    }

    //
    // Scale
    //
    void CMatrixStack::Scale( 
                             float x, float y, float z 
                             )
    {
        Mat4 m;

        m.Scaling( x, y, z );
        m_Curr->top() *= m;
    }
}

#endif // MATH_LIB_INCLUDED