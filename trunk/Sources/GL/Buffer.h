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

// Τΰιλ: /GL/Buffer.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_BUFFER_H__
#define __GL_BUFFER_H__

namespace GL
{
	//  Vertex buffer object, OpenGL 1.5.

    class DLLAPI CBuffer : public CObject  
    {
        friend              CBindableUniform;
        friend              CCgBindableUniform;

        friend              CRenderDeviceDebug; 
        friend              CRenderDeviceRelease;

    public:
                            ~CBuffer            ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CBuffer"; }

        //
        // Interface
        //

        GLvoid*             Map                 ( GLenum Access );
        void                UnMap               ();      

        bool                IsMapped            () const;
        GLvoid*             GetMapPointer       () const;
        GLsizeiptr          GetSize             () const;
        GLenum              GetUsage            () const;
        GLenum              GetAccess           () const;

    protected:
                            CBuffer             ( GLenum Target );

		//
		// Class members
		//

        GLenum              m_Target;
        GLuint              m_Buffer;
    };

    //  Vertex buffer, OpenGL 1.5.

    class DLLAPI CVertexBuffer : public CBuffer
    {
    public:
                            CVertexBuffer       ( GLsizei VertexCount, GLsizei VertexSize, GLenum Usage, const GLvoid *Data = NULL );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CVertexBuffer"; }

        //
        // Interface
        //

        void                SetSubData          ( GLsizei OffsetCount, GLsizei CopyCount, const GLvoid *Data );
        void                GetSubData          ( GLsizei OffsetCount, GLsizei ReadCount, GLvoid *Data ) const;

        void                Resize              ( GLsizeiptr VertexCount, const GLvoid *Data );

        GLsizei             GetVertexCount      () const;
        GLsizei             GetVertexSize       () const;

    private:
		
		//
		// Class members
		//

        GLsizei             m_VertexCount; 
        GLsizei             m_VertexSize;
    };

    //  Index buffer, OpenGL 1.5.

    class DLLAPI CIndexBuffer : public CBuffer
    {
    public:
                            CIndexBuffer        ( GLsizei IndexCount, GLenum Type, GLenum Usage, const GLvoid *Data = NULL );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CIndexBuffer"; }

        //
        // Interface
        //

        void                SetSubData          ( GLsizei OffsetCount, GLsizei CopyCount, const GLvoid *Data );
        void                GetSubData          ( GLsizei OffsetCount, GLsizei ReadCount, GLvoid *Data ) const;

        void                Resize              ( GLsizeiptr IndexCount, const GLvoid *Data );

        GLsizei             GetIndexCount       () const;
        GLenum              GetIndexType        () const;
        GLint               GetIndexSize        () const;

    private:

		//
		// Class members
		//

        GLsizei             m_IndexCount;
        GLenum              m_IndexType;
        GLint               m_IndexSize;
    };

	//  Raw data buffer (pixel/uniform etc.).

	class DLLAPI CGenericBuffer : public CBuffer
	{
	public:
                            CGenericBuffer      ( GLenum Target, GLsizeiptr BytesCount, GLenum Usage, const GLvoid *Data = NULL );

		//
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CGenericBuffer"; }

		//
        // Interface
        //

		void                SetSubData          ( GLintptr OffsetCount, GLsizeiptr CopyCount, const GLvoid *Data );
        void                GetSubData          ( GLsizei OffsetCount, GLsizei ReadCount, GLvoid *Data ) const;

        void                Resize              ( GLsizeiptr BytesCount, const GLvoid *Data );

    private:
        
        //
        // Class members
        //

        GLsizeiptr          m_BytesCount;
	};
}

#endif // __GL_BUFFER_H__ 