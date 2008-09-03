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

// Файл: /GL/GL/Query.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_QUERY_H__
#define __GL_QUERY_H__

namespace GL
{
    //  Асинхронный запрос к графическому ускорителю, OpenGL 1.5.

    class DLLAPI CQuery : public CObject
    {
        friend              CRenderDeviceDebug; 
        friend              CRenderDeviceRelease;

    public:                                   
                            CQuery              ();
                            ~CQuery             ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CQuery"; }

        //
        // Interface
        //

        void                BeginQuery          ( GLenum Target );
        void                EndQuery            ();

		GLenum              GetTarget           () const;
        GLboolean           IsCurrent           () const;

        GLboolean           IsResultAvailable   () const;        
        void                GetResult           ( GLint *Result ) const;
        void                GetResult           ( GLuint *Result ) const;
                            // GL_EXT_timer_query
        void                GetResult           ( GLint64EXT *Result ) const;
        void                GetResult           ( GLuint64EXT *Result ) const;

    private:

		//
		// Class members
		//

        GLuint              m_Query;
        GLenum              m_Target;
    };
} 

#endif // __GL_QUERY_H__