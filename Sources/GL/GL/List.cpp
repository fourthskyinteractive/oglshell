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

// Τΰιλ: /GL/GL/List.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "List.h"

namespace GL
{
    //
    // Constructor
    //
    CDisplayList::CDisplayList():
        m_DList( 0 ),
        m_Compiled( false )
    {
        if (m_Extensions->OpenGL_3_0)
        {
            throw CDeprecatedException( this, "::CDisplayList()", 3, 0 );
        }

        m_DList = glGenLists( 1 );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CDisplayList() : Failed to generate display list." );
    }

    //
    // Destructor
    //
    CDisplayList::~CDisplayList()
    {
        glClearErrors();
        glDeleteLists( m_DList, 1 );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CDisplayList() : Failed to delete display list." );
    }

    //
    // Begin
    //
    void CDisplayList::Begin( 
                             GLenum Mode 
                             )                              
    {                                                               
        if (Mode != GL_COMPILE)
        {
            if (Mode == GL_COMPILE_AND_EXECUTE)
                throw Sys::CDeveloperException( this, "::Begin() : Deprecated <Mode> parameter: GL_COMPILE_AND_EXECUTE." );
            else
                throw Sys::CDeveloperException( this, "::Begin() : Invalid <Mode> parameter." );
        }

        glClearErrors();
        glNewList( m_DList, Mode );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Begin() : An OpenGL error has occured." );

        m_Compiled = false;
    }

    //
    // End
    //
    void CDisplayList::End()
    {
        GLint ListIndex;

        glGetIntegerv( GL_LIST_INDEX, &ListIndex ); // ?
        if (m_DList != ListIndex)
            throw Sys::CDeveloperException( this, "::End() : Display list is not under construction." );

        glClearErrors();
        glEndList();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::End() : An OpenGL error has occured." );
    
        m_Compiled = true;
    }

    //
    // ApplyList
    //
    void CDisplayList::ApplyList() const
    {
    #ifdef _DEBUG
        if (!m_Compiled)
            throw Sys::CDeveloperException( this, "::ApplyList() : Display list is not compiled!" );

        glClearErrors();
    #endif
        glCallList( m_DList );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::ApplyList() : An OpenGL error has occured." );
    #endif
    }
} 