/*
OpenGL Shell - convenient OpenGL wrapper for use in OOP programs.
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

e-mail: bob.vilson@gmail.com
*/

// Τΰιλ: /GL/VertexStruct.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "VertexStruct.h"

#pragma warning (disable : 4312) // type cast

namespace GL
{
    //
    // Constructor
    //
    CVertexStructure::CVertexStructure( 
                                       const TDesc *Attributes, int Count 
                                       ):
        m_VertexSize( 0 )
    {
        for (int i = 0; i < MAX_VERTEX_STREAMS; ++i)
            m_Strides[ i ] = 0;
           
        m_Involved = vector<bool>( m_Caps.MaxVertexAttribs, false );

        for (int i = 0; i < Count; ++i)
        {
            const TDesc& Desc = Attributes[ i ]; 

            AddAttribute( Desc.StreamIndex, Desc.Attribute, Desc.ComponentsCount, Desc.Type, Desc.Normalized );
        }
        
        Compile();
    }

    //
    // Constructor
    //
    CVertexStructure::CVertexStructure( 
                                       const vector<TDesc>& Attributes
                                       ):
        m_VertexSize( 0 )
    {
        for (int i = 0; i < MAX_VERTEX_STREAMS; ++i)
            m_Strides[ i ] = 0;
          
        m_Involved = vector<bool>( m_Caps.MaxVertexAttribs, false );

        for (VECTOR_CONST_ITERATION( TDesc, Attributes, i ))
            AddAttribute( i->StreamIndex, i->Attribute, i->ComponentsCount, i->Type, i->Normalized );

        Compile();
    }
    
    //
    // GetVertexSize
    //
    GLsizei CVertexStructure::GetVertexSize() const
    {
        return m_VertexSize;
    }
    
    //
    // AddAttribute
    //
    void CVertexStructure::AddAttribute( 
                                        GLuint StreamIndex, EVertexAttribute Attribute, GLint ComponentsCount, GLenum Type, GLboolean Normalized
                                        )
    {
        if (StreamIndex >= MAX_VERTEX_STREAMS)
            throw Sys::CDeveloperException( this, "::AddAttribute() : Invalid <StreamIndex> parameter." );

        GLuint Index = Attribute - VA_ATTRIB0;

        if (Index > static_cast<GLuint>( m_Caps.MaxVertexAttribs ))
        {
            throw Sys::CException( this, "::AddAttribute() : Invalid <Attrib> parameter.\nAttribute index %d exceed implementation-dependent constant GL_MAX_VERTEX_ATTRIBS (%d).", 
                Index, m_Caps.MaxVertexAttribs );
        }

        for (int i = 0; i < MAX_VERTEX_STREAMS; ++i)
        {
            if (m_Attributes[ i ].find( Index ) != m_Attributes[ i ].end())
                throw Sys::CDeveloperException( this, "::AddAttribute() : Attribute index %d already exist in attribute list.", Index );
        }

        if (ComponentsCount <= 0 || ComponentsCount > 4)
            throw Sys::CDeveloperException( this, "::AddAttribute() : Invalid <ComponentsCount> parameter. Should be one of the following: 0, 1, 2 or 3." );      
        if (Type != GL_BYTE && Type != GL_UNSIGNED_BYTE && Type != GL_SHORT && Type != GL_UNSIGNED_SHORT && Type != GL_INT && Type != GL_UNSIGNED_INT && Type != GL_FLOAT)
        {
            throw Sys::CDeveloperException( this, "::AddAttribute() : Invalid <Type> parameter.\nShould be one of the following: "
                "GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT or GL_FLOAT." );
        }

        {
            TAttrib Attrib;

            Attrib.Size = ComponentsCount;
            Attrib.Type = Type;
            Attrib.Normalized = Normalized;
            Attrib.Offset = 0;

            m_Attributes[ StreamIndex ][ Index ] = Attrib;
        }
        
        m_Involved[ Index ] = true;
    }

    //
    // Compile
    //
    void CVertexStructure::Compile()
    {
        for (int StreamIndex = 0; StreamIndex < MAX_VERTEX_STREAMS; ++StreamIndex)
        {
            if (m_Attributes[ StreamIndex ].empty())
                continue;

            GLsizei BytesCount = 0;

            for (MAP_ITERATION( GLuint, TAttrib, m_Attributes[ StreamIndex ], i ))
            {
                i->second.Offset = reinterpret_cast<GLubyte *>( BytesCount );

                GLint SizeOf;

                switch (i->second.Type) 
                {
                case GL_BYTE:
                case GL_UNSIGNED_BYTE:
                    SizeOf = sizeof( GLushort );
                    break;
                case GL_SHORT:
                case GL_UNSIGNED_SHORT:
                    SizeOf = sizeof( GLushort );
                    break;
                case GL_INT:
                case GL_UNSIGNED_INT:
                    SizeOf = sizeof( GLuint );
                    break;
                case GL_FLOAT:
                    SizeOf = sizeof( GLfloat );
                    break;
                }

                BytesCount += i->second.Size * SizeOf;
            }

            m_VertexSize += BytesCount;
            m_Strides[ StreamIndex ] = (m_Attributes[ StreamIndex ].size() == 1) ? 0 : BytesCount;
        }

        if (m_VertexSize == 0)
            throw Sys::CDeveloperException( this, "::Compile() : Vertex structure description is empty." );
    }
} 