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

// Файл: /GL/GLU/Font.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GLU_FONT_H__
#define __GLU_FONT_H__

namespace GLU
{
    //  Интерфейс шрифта.

    class DLLAPI IFont : public GL::CObject
    {
    public:

        //
        // Interface
        //

        virtual void        DrawText            ( GLint x, GLint y, const string& Str ) const = 0;
        virtual void        DrawText            ( GLint x, GLint y, const char *Str ) const = 0;
        virtual void        DrawFormatText      ( GLint x, GLint y, const char *FormatStr, ... ) const = 0;
    };

    //  Базовый класс шрифта, генерируемого Window-System API.

    class DLLAPI CFont : public IFont
    {
    public:
        enum
        {
            MAX_STRING = 1024
        };

        struct DLLAPI TDesc
        {
                            TDesc               ();

    #ifdef _WIN32
            int             Height;
            UINT            Width;
            UINT            Weight;
            bool            Italic;
            bool            Underline;
            BYTE            CharSet;
            BYTE            OutputPrecision;
            BYTE            Quality;
            BYTE            PitchAndFamily;
            WCHAR           FaceName[ LF_FACESIZE ];
    #elif defined (__linux__)
            //
    #endif
            
        };

    protected:
                            CFont               ( UINT GlyphsCount );

    public:
                            ~CFont              ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GLU::CFont"; }

    protected:

        //
        // Class members
        //

        GLuint              m_ListBase;
        UINT                m_GlyphsCount;
    };

    //  Шрифт на основе битмапов, функции wglUseFontBitmaps/glXUseXFont.

    class DLLAPI CBitmapFont : public CFont
    {
    public:
                            CBitmapFont         ( const TDesc& Desc, UINT FirstGlyph = 0, UINT GlyphsCount = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GLU::CBitmapFont"; }

        //
        // Interface
        //

        virtual void        DrawText            ( GLint x, GLint y, const string& Str ) const;
        virtual void        DrawText            ( GLint x, GLint y, const char *Str ) const;
        virtual void        DrawFormatText      ( GLint x, GLint y, const char *FormatStr, ... ) const;
    };

    //  Шрифт на основе TrueType B-splines, функция wglUseFontOutlines.

    class DLLAPI COutlineFont : public CFont
    {
    public:
                            COutlineFont        ( const TDesc& Desc, float Deviation, float Extrusion, UINT FirstGlyph = 0, UINT GlyphsCount = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GLU::COutlineFont"; }

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

#endif // __GLU_FONT_H__