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

// Τΰιλ: /GL/Buffer.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Buffer.h"

namespace GL
{
    //
    // Constructor
    //
    CBuffer::CBuffer( 
                     GLenum Target 
                     ):
        m_Target( Target ),
        m_Buffer( 0 )
    {
        if (!m_Extensions->OpenGL_1_5)
        {
            throw CExtensionException( this, "::CBuffer()", 1, 5 );
        }

        glGenBuffers( 1, &m_Buffer );
        glBindBuffer( m_Target, m_Buffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CBuffer() : Failed to generate buffer object." );
    }

    //
    // Destructor
    //
    CBuffer::~CBuffer()
    {
        glDeleteBuffers( 1, &m_Buffer );
    }

    //
    // Map
    //
    GLvoid *CBuffer::Map( 
                         GLenum Access 
                         )
    {
    #ifdef _DEBUG
        if (Access != GL_READ_ONLY && Access != GL_WRITE_ONLY && Access != GL_READ_WRITE)
            throw Sys::CDeveloperException( this, "::Map() : Invalid <Access> parameter." );
    #endif

        glBindBuffer( m_Target, m_Buffer );
        GLvoid *Pointer = glMapBuffer( m_Target, Access );
        if (!Pointer) 
        {
            // GL_OUT_OF_MEMORY
            GLenum Error = glGetError();
            throw CException( this, Error, "::Map() : An OpenGL error has occured." ); 
        }

        return Pointer;
    }

    //
    // UnMap
    //
    void CBuffer::UnMap()
    {
        glBindBuffer( m_Target, m_Buffer );
        if (!glUnmapBuffer( m_Target ))
        {
        #ifdef _DEBUG
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::UnMap() : An OpenGL error has occured." );
            else
                throw Sys::CException( this, "::UnMap() : Failed to unmap buffer." );
        #endif // _DEBUG
        }
    }

    //
    // IsMapped
    //
    bool CBuffer::IsMapped() const
    {
        glClearErrors();
        glBindBuffer( m_Target, m_Buffer );
        GLint Mapped;
        glGetBufferParameteriv( m_Target, GL_BUFFER_MAPPED, &Mapped );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::IsMapped() : An OpenGL error has occured." );

        return Mapped != GL_FALSE;
    }

    //
    // GetMapPointer
    //
    GLvoid *CBuffer::GetMapPointer() const
    {
        glClearErrors();
        glBindBuffer( m_Target, m_Buffer );
        GLvoid *Pointer;
        glGetBufferPointerv( m_Target, GL_BUFFER_MAP_POINTER, &Pointer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetMapPointer() : An OpenGL error has occured." );

        return Pointer;
    }

    //
    // GetSize
    //
    GLsizeiptr CBuffer::GetSize() const
    {
        glClearErrors();
        glBindBuffer( m_Target, m_Buffer );
        GLint Size;
        glGetBufferParameteriv( m_Target, GL_BUFFER_SIZE, &Size );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetSize() : An OpenGL error has occured." );

        return Size;
    }
    
    //
    // GetUsage
    //
    GLenum CBuffer::GetUsage() const
    {
        glClearErrors();
        glBindBuffer( m_Target, m_Buffer );
        GLint Usage;
        glGetBufferParameteriv( m_Target, GL_BUFFER_USAGE, &Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetUsage() : An OpenGL error has occured." );

        return Usage;
    }

    //
    // GetAccess
    //
    GLenum CBuffer::GetAccess() const
    {
        glClearErrors();
        glBindBuffer( m_Target, m_Buffer );
        GLint Access;
        glGetBufferParameteriv( m_Target, GL_BUFFER_ACCESS, &Access );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetAccess() : An OpenGL error has occured." );

        return Access;
    }

    //
    // Constructor
    //
    CVertexBuffer::CVertexBuffer( 
                                 GLsizei VertexCount, GLsizei VertexSize, GLenum Usage, 
                                 const GLvoid *Data 
                                 ): 
        CBuffer( GL_ARRAY_BUFFER ),

        m_VertexCount( VertexCount ),
        m_VertexSize( VertexSize )
    {
        if (VertexCount <= 0)
            throw Sys::CDeveloperException( this, "::CVertexBuffer() : Invalid <VertexCount> parameter: %d.", VertexCount );
        if (VertexSize <= 0)
            throw Sys::CDeveloperException( this, "::CVertexBuffer() : Invalid <VertexSize> parameter: %d.", VertexSize );

        if (Usage != GL_STREAM_DRAW && Usage != GL_STREAM_READ && Usage != GL_STREAM_COPY && 
            Usage != GL_STATIC_DRAW && Usage != GL_STATIC_READ && Usage != GL_STATIC_COPY && 
            Usage != GL_DYNAMIC_DRAW && Usage != GL_DYNAMIC_READ && Usage != GL_DYNAMIC_COPY)
        {
            throw Sys::CDeveloperException( this, "::CVertexBuffer() : Invalid <Usage> parameter." );
        }

        glBufferData( GL_ARRAY_BUFFER, m_VertexCount * m_VertexSize, Data, Usage );
        GLenum Error = glGetError();          
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CVertexBuffer() : Failed to create vertex buffer." );      
    }                                                                               

    //
    // SetSubData
    //
    void CVertexBuffer::SetSubData( 
                                   GLsizei OffsetCount, GLsizei CopyCount, 
                                   const GLvoid *Data 
                                   )
    {
    #ifdef _DEBUG
        if (OffsetCount + CopyCount > m_VertexCount)
            throw Sys::CDeveloperException( this, "::SetSubData() : Invalid <OffsetCount> or <CopyCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::SetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( GL_ARRAY_BUFFER, m_Buffer ); 
        glBufferSubData( GL_ARRAY_BUFFER, OffsetCount * m_VertexSize, CopyCount * m_VertexSize, Data );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // GetSubData
    //
    void CVertexBuffer::GetSubData( 
                                   GLsizei OffsetCount, GLsizei ReadCount, 
                                   GLvoid *Data 
                                   ) const
    {
    #ifdef _DEBUG
        if (OffsetCount + ReadCount > m_VertexCount)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <OffsetCount> or <ReadCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( GL_ARRAY_BUFFER, m_Buffer ); 
        glGetBufferSubData( GL_ARRAY_BUFFER, OffsetCount * m_VertexSize, ReadCount * m_VertexSize, Data );  
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // Resize
    //
    void CVertexBuffer::Resize( 
                               GLsizeiptr VertexCount, 
                               const GLvoid *Data 
                               )
    {
        if (VertexCount <= 0)
            throw Sys::CDeveloperException( this, "::Resize() : Invalid <VertexCount> parameter: %d.", VertexCount );

        glClearErrors();
        glBindBuffer( GL_ARRAY_BUFFER, m_Buffer ); 
        GLint Usage;
        glGetBufferParameteriv( GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &Usage );
        glBufferData( GL_ARRAY_BUFFER, VertexCount * m_VertexSize, Data, Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Resize() : An OpenGL error has occured." );

        m_VertexCount = static_cast<GLsizei>( VertexCount );
    }

    //
    // GetVertexCount
    //
    GLsizei CVertexBuffer::GetVertexCount() const 
    { 
        return m_VertexCount; 
    }

    // GetVertexSize
    //
    GLint CVertexBuffer::GetVertexSize() const
    {
        return m_VertexSize;
    }

    //
    // Constuctor
    //
    CIndexBuffer::CIndexBuffer( 
                               GLsizei IndexCount, GLenum IndexType, GLenum Usage, 
                               const GLvoid *Data 
                               ):
        CBuffer( GL_ELEMENT_ARRAY_BUFFER ),

        m_IndexCount( IndexCount ),
        m_IndexType( IndexType ),
        m_IndexSize( 0 )
    {
        if (IndexCount <= 0)
            throw Sys::CDeveloperException( this, "::CIndexBuffer() : Invalid <IndexCount> parameter: %d.", IndexCount );
        if (IndexType != GL_UNSIGNED_BYTE && IndexType != GL_UNSIGNED_SHORT && IndexType != GL_UNSIGNED_INT)
            throw Sys::CDeveloperException( this, "::CIndexBuffer() : Invalid <IndexType> parameter." );

        if (Usage != GL_STREAM_DRAW && Usage != GL_STREAM_READ && Usage != GL_STREAM_COPY && 
            Usage != GL_STATIC_DRAW && Usage != GL_STATIC_READ && Usage != GL_STATIC_COPY && 
            Usage != GL_DYNAMIC_DRAW && Usage != GL_DYNAMIC_READ && Usage != GL_DYNAMIC_COPY)
        {
            throw Sys::CDeveloperException( this, "::CIndexBuffer() : Invalid <Usage> parameter." );
        }

        if (IndexType == GL_UNSIGNED_BYTE)
            m_IndexSize = sizeof( GLubyte );
        else if (IndexType == GL_UNSIGNED_SHORT)
            m_IndexSize = sizeof( GLushort );
        else // GL_UNSIGNED_INT
            m_IndexSize = sizeof( GLuint );

        glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * m_IndexSize, Data, Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CIndexBuffer() : Failed to create index buffer." );    
    }

    //
    // SetSubData
    //
    void CIndexBuffer::SetSubData( 
                                  GLsizei OffsetCount, GLsizei CopyCount, 
                                  const GLvoid *Data 
                                  )
    {
    #ifdef _DEBUG
        if (OffsetCount + CopyCount > m_IndexCount)
            throw Sys::CDeveloperException( this, "::SetSubData() : Invalid <OffsetCount> or <CopyCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::SetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Buffer ); 
        glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, OffsetCount * m_IndexSize, CopyCount * m_IndexSize, Data );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // GetSubData
    //
    void CIndexBuffer::GetSubData( 
                                  GLsizei OffsetCount, GLsizei ReadCount, 
                                  GLvoid *Data 
                                  ) const
    {
    #ifdef _DEBUG
        if (OffsetCount + ReadCount > m_IndexCount)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <OffsetCount> or <ReadCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Buffer ); 
        glGetBufferSubData( GL_ELEMENT_ARRAY_BUFFER, OffsetCount * m_IndexSize, ReadCount * m_IndexSize, Data );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // Resize
    //
    void CIndexBuffer::Resize( 
                              GLsizeiptr IndexCount,
                              const GLvoid *Data
                              )
    {
        if (IndexCount <= 0)
            throw Sys::CDeveloperException( this, "::Resize() : Invalid <IndexCount> parameter: %d.", IndexCount );

        glClearErrors();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Buffer ); 
        GLint Usage;
        glGetBufferParameteriv( GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &Usage );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, IndexCount * m_IndexSize, Data, Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Resize() : An OpenGL error has occured." );

        m_IndexCount = static_cast<GLsizei>( IndexCount );
    }

    //
    // GetIndexCount
    //
    GLsizei CIndexBuffer::GetIndexCount() const 
    { 
        return m_IndexCount; 
    }

    //
    // GetIndexType
    //
    GLenum CIndexBuffer::GetIndexType() const 
    { 
        return m_IndexType; 
    }

    //
    // GetIndexSize
    //
    GLint CIndexBuffer::GetIndexSize() const
    {
        return m_IndexSize;
    }

    //
    // Constructor
    //
	CGenericBuffer::CGenericBuffer( 
                                   GLenum Target, GLsizeiptr BytesCount, GLenum Usage, 
                                   const GLvoid *Data 
                                   ):
		CBuffer( Target ),

        m_BytesCount( BytesCount )
	{
		switch (Target)
		{
		case GL_PIXEL_PACK_BUFFER:
		case GL_PIXEL_UNPACK_BUFFER:
			if (!m_Extensions->OpenGL_2_1 && !m_Extensions->ARB_pixel_buffer_object)
				throw CExtensionException( this, "::CGenericBuffer()", "GL_ARB_pixel_buffer_object" );
			break;
		case GL_UNIFORM_BUFFER_EXT:
		    if (!m_Extensions->EXT_bindable_uniform)
                throw CExtensionException( this, "::CGenericBuffer()", "GL_EXT_bindable_uniform" );
			break;

		default:
			throw Sys::CDeveloperException( this, "::CGenericBuffer() : Invalid <Target> parameter." );
		}

		if (BytesCount <= 0)
            throw Sys::CDeveloperException( this, "::CGenericBuffer() : Invalid <BytesCount> parameter: %d", BytesCount );

		if (Usage != GL_STREAM_DRAW && Usage != GL_STREAM_READ && Usage != GL_STREAM_COPY && 
            Usage != GL_STATIC_DRAW && Usage != GL_STATIC_READ && Usage != GL_STATIC_COPY && 
            Usage != GL_DYNAMIC_DRAW && Usage != GL_DYNAMIC_READ && Usage != GL_DYNAMIC_COPY)
        {
            throw Sys::CDeveloperException( this, "::CGenericBuffer() : Invalid <Usage> parameter." );
        }

		glBufferData( m_Target, BytesCount, Data, Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CGenericBuffer() : Failed to create buffer." );
	}

    //
    // SetSubData
    //
    void CGenericBuffer::SetSubData( 
                                    GLintptr OffsetCount, GLsizeiptr CopyCount,
                                    const GLvoid *Data 
                                    )
    {
    #ifdef _DEBUG
        if (OffsetCount + CopyCount > m_BytesCount)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <OffsetCount> or <CopyCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::SetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( m_Target, m_Buffer ); 
        glBufferSubData( m_Target, OffsetCount, CopyCount, Data ); 
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // GetSubData
    //
    void CGenericBuffer::GetSubData( 
                                    GLintptr OffsetCount, GLsizeiptr ReadCount,
                                    GLvoid *Data 
                                    ) const
    {
    #ifdef _DEBUG
        if (OffsetCount + ReadCount > m_BytesCount)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <OffsetCount> or <ReadCount> parameter." );
        if (!Data)
            throw Sys::CDeveloperException( this, "::GetSubData() : Invalid <Data> parameter." );

        glClearErrors();
    #endif // _DEBUG
        glBindBuffer( m_Target, m_Buffer ); 
        glGetBufferSubData( m_Target, OffsetCount, ReadCount, Data ); 
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetSubData() : An OpenGL error has occured." );
    #endif // _DEBUG
    }

    //
    // Resize
    //
	void CGenericBuffer::Resize( 
                                GLsizeiptr BytesCount, 
                                const GLvoid *Data 
                                )
    {
        if (BytesCount <= 0)
            throw Sys::CDeveloperException( this, "::Resize() : Invalid <BytesCount> parameter: %d.", BytesCount );

        glClearErrors();
        glBindBuffer( m_Target, m_Buffer ); 
        GLint Usage = GL_NONE;
        glGetBufferParameteriv( m_Target, GL_BUFFER_USAGE, &Usage );
        glBufferData( m_Target, BytesCount, Data, Usage );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Resize() : An OpenGL error has occured." );
    }
}