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

// Τΰιλ: /GL/GL/Query.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Query.h"

namespace GL
{
    //
    // Constructor
    //
    CQuery::CQuery():
        m_Query( 0 ),
        m_Target( GL_NONE )
    {
        if (!m_Extensions->OpenGL_1_5)
        {
            throw CExtensionException( this, "::CQuery()", 1, 5 );
        }

        glClearErrors();
        glGenQueries( 1, &m_Query );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CQuery() : Failed to generate query." );
    }

    //
    // Destructor
    //
    CQuery::~CQuery()
    {
        glClearErrors();
        glDeleteQueries( 1, &m_Query );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CQuery() : Failed to delete query." );
    }

    //
    // BeginQuery
    //
    void CQuery::BeginQuery( 
                            GLenum Target 
                            )
    {
    #ifdef _DEBUG
        switch (Target) 
        {
        case GL_SAMPLES_PASSED:
            // OpenGL 1.5
            break;
        case GL_TIME_ELAPSED_EXT:
            if (!m_Extensions->EXT_timer_query)
                throw CExtensionException( this, "::BeginQuery()", "GL_EXT_timer_query" );
            break;
        case GL_PRIMITIVES_GENERATED_NV:
        case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV:
            if (!m_Extensions->NV_transform_feedback && !m_Extensions->EXT_transform_feedback)
                throw CExtensionException( this, "::BeginQuery()", "GL_NV/EXT_transform_feedback" );
            break;
            
        default:
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_ENUM, 
                "::BeginQuery() : Invalid <Target> parameter." );
        }
    #endif // _DEBUG

    #ifdef _DEBUG
        glClearErrors();
    #endif
        glBeginQuery( Target, m_Query );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::BeginQuery() : An OpenGL error has occured." );
    #endif

        m_Target = Target;
    }

    //
    // EndQuery
    //
    void CQuery::EndQuery()
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        glEndQuery( m_Target );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::EndQuery() : An OpenGL error has occured." );
    #endif
    }

    //
    // GetTarget
    //
	GLenum CQuery::GetTarget() const
    {
        return m_Target;
    }

    //
    // IsCurrent
    //
    GLboolean CQuery::IsCurrent() const
    {
        GLint CurrentQuery;

        glGetQueryiv( m_Target, GL_CURRENT_QUERY, &CurrentQuery );

        return (m_Query == CurrentQuery) ? GL_TRUE : GL_FALSE;
    }

    //
    // IsResultAvailable
    //
    GLboolean CQuery::IsResultAvailable() const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        GLint ResultAvailable;
        glGetQueryObjectiv( m_Query, GL_QUERY_RESULT_AVAILABLE, &ResultAvailable );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::IsResultAvailable() : An OpenGL error has occured." );
    #endif

        return static_cast<GLboolean>( ResultAvailable );
    }

    //
    // GetResult
    //
    void CQuery::GetResult( 
                           GLint *Result 
                           ) const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        glGetQueryObjectiv( m_Query, GL_QUERY_RESULT, Result );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetResult() : An OpenGL error has occured." );
    #endif
    }

    //
    // GetResult
    //
    void CQuery::GetResult( 
                           GLuint *Result 
                           ) const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        glGetQueryObjectuiv( m_Query, GL_QUERY_RESULT, Result );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetResult() : An OpenGL error has occured." );
    #endif
    }

    //
    // GetResult
    //
    void CQuery::GetResult( 
                           GLint64EXT *Result 
                           ) const
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_timer_query)
            throw CExtensionException( this, "::GetResult()", "GL_EXT_timer_query" );

        glClearErrors();
    #endif
        if (m_Extensions->EXT_timer_query)
            glGetQueryObjecti64vEXT( m_Query, GL_QUERY_RESULT, Result );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetResult() : An OpenGL error has occured." );
    #endif
    }

    //
    // GetResult
    //
    void CQuery::GetResult( 
                           GLuint64EXT *Result 
                           ) const
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_timer_query)
            throw CExtensionException( this, "::GetResult()", "GL_EXT_timer_query" );

        glClearErrors();
    #endif
        if (m_Extensions->EXT_timer_query)
            glGetQueryObjectui64vEXT( m_Query, GL_QUERY_RESULT, Result );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetResult() : An OpenGL error has occured." );
    #endif
    }
} 