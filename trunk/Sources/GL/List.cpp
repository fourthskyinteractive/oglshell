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

// Τΰιλ: /GL/List.cpp
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
        m_List( 0 ),
        m_Compiled( false )
    {
        m_List = glGenLists( 1 );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CDisplayList() : Failed to generate display list." );
    }

    //
    // Destructor
    //
    CDisplayList::~CDisplayList()
    {
        glDeleteLists( m_List, 1 );
    }

    //
    // Begin
    //
    void CDisplayList::Begin( GLenum Mode )                              
    {                                                               
        if (Mode != GL_COMPILE)
        {
            if (Mode == GL_COMPILE_AND_EXECUTE)
                throw Sys::CDeveloperException( this, "::Begin() : Deprecated <Mode> parameter: GL_COMPILE_AND_EXECUTE." );
            else
                throw Sys::CDeveloperException( this, "::Begin() : Invalid <Mode> parameter." );
        }

        glClearErrors();
        glNewList( m_List, Mode );
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
        if (m_List != ListIndex)
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
        glCallList( m_List );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::ApplyList() : An OpenGL error has occured." );
    #endif
    }
} 