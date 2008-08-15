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

// Файл: /GL/InternalFormat.h
//                                                                

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_INTERNAL_FORMAT_H__
#define __GL_INTERNAL_FORMAT_H__

namespace GL
{
    //  Внутренний формат текстуры/буфера кадра.
    //  С Sized форматом ассоциируется его Base формат, а также формат и тип исходных данных. 

    // TODO: GL::CFormat, разместить в отдельном файле.
    // Ещё раз провести анализ кода и переписать класс. мне это всё не нравится.

    class DLLAPI CInternalFormat
    {          
    public:
                            CInternalFormat     ( GLenum SizedFormat, const string& Name = "" );
                            CInternalFormat     ( GLenum SizedFormat, GLenum BaseFormat, const string& Name = "" );

        //
        // Interface
        //

        static string       ConvertFormatToString( GLenum Format ); 

        const string&       GetName             () const;

        GLenum              GetSizedFormat      () const;
        GLenum              GetBaseFormat       () const;
        GLenum              GetExternalFormat   () const;
        GLenum              GetType             () const;

    private:

		//
		// Class members
		//

        string              m_Name;  
        GLenum              m_SizedFormat;
        GLenum              m_BaseFormat;   
    };
}

#endif // __GL_INTERNAL_FORMAT_H__