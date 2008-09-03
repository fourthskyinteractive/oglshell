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

// Файл: /GL/GLU/VertexArray.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "VertexArray.h"
using namespace GL;

namespace GLU
{
    //
    // Constructor
    //
    CVertexArray::CVertexArray( 
                               GLsizeiptr MaxVertices, GLuint MaxVertexAttribs 
                               ):
        m_MaxVertices( MaxVertices ),
        m_MaxVertexAttribs( MaxVertexAttribs ),
    
        m_VBSetIndex( 0 ), // At creation time - 0.

        m_Enclosed( false )

    #ifdef _DEBUG
        ,m_NumVertices( 0 )
    #endif
    {
        if (!m_Extensions->OpenGL_1_5)
        {
            throw CExtensionException( this, "::CVertexArray()", 1, 5 );
        }

        if (MaxVertices == 0)
            throw Sys::CDeveloperException( this, "::CVertexArray() : Invalid <MaxVertices> parameter. Should be greater than 0." );
        if (m_MaxVertexAttribs == 0)
            m_MaxVertexAttribs = m_Caps.MaxVertexAttribs;
        else if (m_MaxVertexAttribs > m_Caps.MaxVertexAttribs)
        {
            throw Sys::CDeveloperException( this, "::CVertexArray() : Invalid <MaxVertexAttribs> parameter.\nNumber of attributes "
                "exceed implementation-dependent constant GL_MAX_VERTEX_ATTRIBS=%d.", m_Caps.MaxVertexAttribs );
        }

        try
        {
            for (int N = 0; N < 2; ++N)
            {
                for (int Index = 0; Index < m_MaxVertexAttribs; ++Index)
                {
                    GLuint Buffer;

                    glGenBuffers( 1, &Buffer );
                    glBindBuffer( GL_ARRAY_BUFFER, Buffer );
                    m_VB[ N ].push_back( Buffer );
                    glBufferData( GL_ARRAY_BUFFER, m_MaxVertices * sizeof( TVec4 ), NULL, GL_STREAM_DRAW );
                    if (N == m_VBSetIndex)
                    {
                        TVec4 *Data = static_cast<TVec4 *>( glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY ) );
                        if (!Data) 
                            throw CException( this, glGetError(), "::CVertexArray() : An OpenGL error has occured." ); 
                        m_Data.push_back( Data );
                    }

                    m_VBMapped[ N ].push_back( N == m_VBSetIndex );
                }       
            }
        }
        catch (const Sys::CException& Ex)
        {
            for (int N = 0; N < 2; ++N)
            {
                for (int Index = 0; Index < static_cast<int>( m_VB[ N ].size() ); ++Index)
                {
                    glBindBuffer( GL_ARRAY_BUFFER, m_VB[ N ][ Index ] );
                    GLint Mapped;
                    glGetBufferParameteriv( GL_ARRAY_BUFFER, GL_BUFFER_MAPPED, &Mapped );
                    if (Mapped)
                        glUnmapBuffer( GL_ARRAY_BUFFER );
                    glDeleteBuffers( 1, &m_VB[ N ][ Index ] );
                }
            }

            throw Ex;
        }
    }

    //
    // Destructor
    //
    CVertexArray::~CVertexArray()
    {
        for (int N = 0; N < 2; ++ N)
        {
            for (int Index = 0; Index < static_cast<int>( m_VB[ N ].size() ); ++Index)
            {
                glClearErrors();
                glBindBuffer( GL_ARRAY_BUFFER, m_VB[ N ][ Index ] );
                GLint Mapped;
                glGetBufferParameteriv( GL_ARRAY_BUFFER, GL_BUFFER_MAPPED, &Mapped );
                if (Mapped)
                    glUnmapBuffer( GL_ARRAY_BUFFER );
                glDeleteBuffers( 1, &m_VB[ N ][ Index ] );
                GLenum Error = glGetError();
                if (Error != GL_NO_ERROR)
                    Print( Sys::CLog::PT_ERROR, "::~CVertexArray() : Failed to delete vertex buffers." );
            }
        }
    }

    //
    // Begin
    //
    void CVertexArray::Begin( 
                             GLenum Topology 
                             )
    {
    #ifdef _DEBUG
        switch (Topology)
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_TRIANGLES:
        case GL_TRIANGLE_STRIP:
            break;

        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_QUADS:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                const char *ModeStr[] =
                {
                    "GL_LINE_LOOP",
                    "GL_LINE_STRIP",
                    "GL_TRIANGLES",
                    "GL_TRIANGLE_STRIP",
                    "GL_TRIANGLE_FAN",
                    "GL_QUADS",
                    "GL_QUAD_STRIP",
                    "GL_POLYGON"
                };

                throw Sys::CDeveloperException( this, "::Begin() : Deprecated primitive topology: %s.", 
                    ModeStr[ Topology - GL_LINE_LOOP ] );
            }
            break;

        default:
            throw Sys::CDeveloperException( this, "::Begin() : Invalid <Topology> parameter." );
        }

        if (m_Enclosed)
        {
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL,
                "::Begin() : Invalid usage, call ::End() first." );
        }
    #endif // _DEBUG

        TDrawBatch Batch;

        Batch.Mode = Topology;
        Batch.Count = 0;
        Batch.Counts.resize( m_MaxVertexAttribs, 0 );
        Batch.First = 0;

        m_Batches.push_back( Batch );
        m_Batch = &m_Batches.back();

        m_Enclosed = true;
    }
        
    //
    // End
    //
    void CVertexArray::End()
    {
    #ifdef _DEBUG
        if (!m_Enclosed)
        {
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL,
                "::End() : Invalid usage, call ::Begin() first." );
        }
    #endif // _DEBUG

        // Мы не знаем, какие именно вершинные атрибуты будут заданы пользователем,
        // поэтому перебираем в цикле все до тех пор, пока не найдем первый используемый.
        for (int Index = 0; Index < m_MaxVertexAttribs; ++Index)
        {
            if (m_Batch->Counts[ Index ] > 0)
            {
                m_Batch->Count = m_Batch->Counts[ Index ];
                break;
            }
        }

        if (m_Batch->Count == 0)
            m_Batches.erase( m_Batches.end() - 1 ); // "Пустой" батч, удаляем его.
        else
        {
            const TDrawBatch *PrevBatch = NULL;

            if (m_Batches.size() > 1)
                PrevBatch = &m_Batches[ m_Batches.size() - 2 ];

            for (int Index = 0; Index < m_MaxVertexAttribs; ++Index)
            {
                // Все массивы вершин в батче должны использовать одинаковое кол-во вершин.
                if (m_Batch->Counts[ Index ] > 0 && (m_Batch->Counts[ Index ] != m_Batch->Count))
                    throw Sys::CDeveloperException( this, "::End() : Invalid ::PushVertexAttrib*() usage. All vertex arrays used in batch must contain the same number of elements." ); 
                if (PrevBatch)
                {
                    // Все батчи должны быть когерентными между собой и использовать одни и те же массивы вершинных данных.
                    if (m_Batch->Counts[ Index ] != 0 && PrevBatch->Counts[ Index ] == 0)
                        throw Sys::CDeveloperException( this, "::End() : Invalid ::PushVertexAttrib*() usage. All batches must use the same vertex arrays during ::Draw() call." ); 
                }
            }

            if (PrevBatch)
                m_Batch->First = PrevBatch->First + PrevBatch->Count;
        }

        m_Enclosed = false;
    }

    //
    // Draw
    //
    void CVertexArray::Draw() const
    {
    #ifdef _DEBUG
        if (m_Enclosed)
        {
            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL,
                "::Draw() : Invalid usage, call ::End() first." );
        }
    #endif // _DEBUG

        if (m_Batches.empty())
            return;

    #ifdef _DEBUG
        glClearErrors();
    #endif

        for (int Index = 0; Index < m_MaxVertexAttribs; ++Index)
        {
            if (m_Batches[ 0 ].Counts[ Index ] == 0)
                glDisableVertexAttribArray( Index );
            else
            {    
                glBindBuffer( GL_ARRAY_BUFFER, m_VB[ m_VBSetIndex ][ Index ] );
                glUnmapBuffer( GL_ARRAY_BUFFER );   
                glVertexAttribPointer( Index, 4, GL_FLOAT, GL_FALSE, 0, (char *)NULL + 0 );
                glEnableVertexAttribArray( Index );

                m_VBMapped[ m_VBSetIndex ][ Index ] = false;
            }
        }

    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Draw() : An OpenGL error has occured during vertex array setup stage." );
    #endif

        for (CONST_VECTOR_ITERATION( TDrawBatch, m_Batches, Batch ))
            glDrawArrays( Batch->Mode, Batch->First, Batch->Count );
        
    #ifdef _DEBUG
        Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Draw() : An OpenGL error has occured during drawing." );
    #endif // _DEBUG

        // Чтобы избежать (или уменьшить) GPU stall при вызове glMapBuffer(), в то время, как всё еще идёт рисование вершин,
        // используется два набора вершинных буферов, и переключение между ними в каждом вызове ::Draw().
        m_VBSetIndex = !m_VBSetIndex;

        for (int Index = 0; Index < m_MaxVertexAttribs; ++Index)
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_VB[ m_VBSetIndex ][ Index ] );
            if (m_VBMapped[ m_VBSetIndex ][ Index ] == true)
            {
                GLvoid *Data;
                glGetBufferPointerv( GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &Data );
                m_Data[ Index ] = static_cast<TVec4 *>( Data );
            }
            else
            {
                m_Data[ Index ] = static_cast<TVec4 *>( glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY ) );
                m_VBMapped[ m_VBSetIndex ][ Index ] = true;
            }

            if (!m_Data[ Index ]) 
            {
                GLenum Error = glGetError();
                throw CException( this, Error, "::Draw() : An OpenGL error has occured." ); 
            }
        }

    #ifdef _DEBUG
        m_NumVertices = 0;
    #endif
        m_Batches.clear();
    }
}