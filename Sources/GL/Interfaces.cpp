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

e-mail: victor.coda@gmail.com
*/

// Τΰιλ: /GL/Interfaces.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Interfaces.h"

namespace GL
{
    string IShadingProgram::m_LastInfoLog;

    //
    // Constructor
    //
    IFrameBuffer::IFrameBuffer( 
                               EFrameBufferType Type,
                               GLsizei Width, GLsizei Height 
                               ):
        m_Type( Type ),
        m_Width( Width ),
        m_Height( Height ),

        m_Current( false )
    {
    }

    //
    // GetFrameWidth
    //
    GLsizei IFrameBuffer::GetFrameWidth() const
    {
        return m_Width;
    }
        
    //
    // GetFrameHeight
    //
    GLsizei IFrameBuffer::GetFrameHeight() const
    {
        return m_Height;
    }

    //
    // IsCurrent
    //
    bool IFrameBuffer::IsCurrent() const
    {
        return m_Current;
    }

    //
    // Constructor
    //
    CBaseUniform::CBaseUniform( const string& Name ):
        m_Name( Name )
    {
    }

    //
    // GetName
    //
    const string& CBaseUniform::GetName() const 
    {
        return m_Name; 
    }

    //
    // GetLastInfoLog
    //
    const string& IShadingProgram::GetLastInfoLog() 
    { 
        return m_LastInfoLog; 
    }

    //
    // Constructor
    //
    IFont::TDesc::TDesc():
    #ifdef _WIN32
        Height( 0 ),
        Width( 0 ),
        Weight( 0 ),
        Italic( false ),
        Underline( false ),
        CharSet( DEFAULT_CHARSET ),
        OutputPrecision( OUT_DEFAULT_PRECIS ),
        Quality( DEFAULT_QUALITY ),
        PitchAndFamily( DEFAULT_PITCH )
    #elif defined (__linux__)
    //
    #endif // _WIN32
    {
    }

    //
    // Constructor
    //
    IFont::IFont( 
                 UINT GlyphsCount 
                 ):
        m_ListBase( 0 ),
        m_GlyphsCount( GlyphsCount )
    {
        if (m_GlyphsCount == 0)
            m_GlyphsCount = 256;

        m_ListBase = glGenLists( m_GlyphsCount );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::IFont", Error, "::IFont() : Failed to generate display lists." );
    }

    //
    // Destructor
    //
    IFont::~IFont()
    {
        glDeleteLists( m_ListBase, m_GlyphsCount );
    }
}