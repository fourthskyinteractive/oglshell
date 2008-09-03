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

// Τΰιλ: /GL/GL/Interfaces.cpp
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
    // Constructor
    //
    IUniform::IUniform( 
                       const string& Name 
                       ): 
        CBaseUniform( Name )
    {
    }

    //
    // Constructor
    //
    ISamplerUniform::ISamplerUniform( 
                                     const string& Name 
                                     ): 
        CBaseUniform( Name )
    {
    }

    //
    // Constructor
    //
    IBindableUniform::IBindableUniform( 
                                       const string& Name 
                                       ): 
        CBaseUniform( Name )
    {
    }

    //
    // GetLastInfoLog
    //
    const string& IShadingProgram::GetLastInfoLog() 
    { 
        return m_LastInfoLog; 
    }
}