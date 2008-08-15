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

// Файл: /GL/Font.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_FONT_H__
#define __GL_FONT_H__

namespace GL
{
    //  Шрифт на основе битмапов, функции wglUseFontBitmaps/glXUseXFont.

    class DLLAPI CFont : public IFont
    {
    public:
                            CFont               ( const TDesc& Desc, UINT FirstGlyph = 0, UINT GlyphsCount = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CFont"; }

        //
        // Interface
        //

        virtual void        DrawText            ( GLint x, GLint y, const string& Str ) const;
        virtual void        DrawText            ( GLint x, GLint y, const char *Str ) const;
        virtual void        DrawFormatText      ( GLint x, GLint y, const char *FormatStr, ... ) const;
    };

    //  Шрифт на основе TrueType B-splines, функция wglUseFontOutlines.

    class DLLAPI COutlineFont : public IFont
    {
    public:
                            COutlineFont        ( const TDesc& Desc, float Deviation, float Extrusion, UINT FirstGlyph = 0, UINT GlyphsCount = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::COutlineFont"; }

        //
        // Interface
        //

        virtual void        DrawText            ( GLint x, GLint y, const string& Str ) const;
        virtual void        DrawText            ( GLint x, GLint y, const char *Str ) const;
        virtual void        DrawFormatText      ( GLint x, GLint y, const char *FormatStr, ... ) const;

    private:

        //
        // Class members
        //

        int                 m_Height;
    };
}

#endif // __GL_FONT_H__