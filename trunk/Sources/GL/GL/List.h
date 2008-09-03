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

// Файл: /GL/GL/List.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_LIST_H__
#define __GL_LIST_H__

namespace GL
{
    //  Дисплейный список - группа команд OpenGL для эффективного многократного исполнения.

    class DLLAPI CDisplayList : public CObject
    {
    public:
                            CDisplayList        ();
                            ~CDisplayList       (); 

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CDisplayList"; }

        //
        // Interface
        //

        void                Begin               ( GLenum Mode );
        void                End                 ();

        void                ApplyList           () const;

    private:

		//
		// Class members
		//

        GLuint              m_DList;
        bool                m_Compiled;
    };
} 

#endif // __GL_LIST_H__