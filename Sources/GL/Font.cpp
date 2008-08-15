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

// Τΰιλ: /GL/Font.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Font.h"

#ifdef _MSC_VER 
#pragma warning (disable: 4244) // conversion from 'const int' to 'GLfloat', possible loss of data
#endif

namespace GL 
{
    //
    // Constructor
    //
    CFont::CFont( 
                 const TDesc& Desc, UINT FirstGlyph, UINT GlyphsCount 
                 ):
        IFont( GlyphsCount )
    {
        //
        // Non-portable Window-System dependent codepath.
        //

    #ifdef _WIN32

        HDC DC = wglGetCurrentDC();
        if (!DC)
            throw Sys::CException( this, "::CBitmapFont() : Failed to get current DC." );

        LOGFONT lf;

        ZeroMemory( &lf, sizeof( LOGFONT ) );

        lf.lfHeight = Desc.Height;
        lf.lfWidth = Desc.Width;
        lf.lfEscapement = 0;
        lf.lfOrientation = 0;
        lf.lfWeight = Desc.Weight;
        lf.lfItalic = Desc.Italic ? TRUE : FALSE;
        lf.lfUnderline = Desc.Underline ? TRUE : FALSE;
        lf.lfStrikeOut = FALSE;
        lf.lfCharSet = Desc.CharSet;
        lf.lfOutPrecision = Desc.OutputPrecision;
        lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lf.lfQuality = Desc.Quality;
        lf.lfPitchAndFamily = Desc.PitchAndFamily; // FF_DONTCARE | DEFAULT_PITCH
        wcscpy( lf.lfFaceName, Desc.FaceName );

        HFONT Font, OldFont;
        
        Font = CreateFontIndirect( &lf );
        if (!Font)
            throw Sys::CException( this, "::CBitmapFont() : Failed to create font." );
        OldFont = (HFONT)SelectObject( DC, Font );

        try 
        {
            if (!wglUseFontBitmaps( DC, FirstGlyph, m_GlyphsCount - 1, m_ListBase ))
                throw Sys::CException( this, "::CBitmapFont() : Failed to create glyph bitmaps." );     
        }
        catch (const Sys::CException& Ex) 
        {
            SelectObject( DC, OldFont );
            DeleteObject( Font );	

            throw Ex;
        }

        SelectObject( DC, OldFont );
        DeleteObject( Font );

    #elif defined (__linux__)

    #endif // _WIN32
    }

    //
    // DrawText
    //
    void CFont::DrawText( GLint x, GLint y, const string& Str ) const
    {
        glPushAttrib( GL_LIST_BIT );
        glRasterPos2i( x, y );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( Str.length() ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str.c_str() ) );
        glPopAttrib();
    }

    //
    // DrawText
    //
    void CFont::DrawText( GLint x, GLint y, const char *Str ) const
    {
    #ifdef _DEBUG
        if (!Str) 
            throw Sys::CDeveloperException( this, "::DrawText() : Invalid <Str> parameter." );
    #endif

        glPushAttrib( GL_LIST_BIT );
        glRasterPos2i( x, y );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( strlen( Str ) ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str ) );
        glPopAttrib();
    }

    //
    // DrawFormatText
    //
    void CFont::DrawFormatText( GLint x, GLint y, const char *FormatStr, ... ) const
    {
    #ifdef _DEBUG
        if (!FormatStr) 
            throw Sys::CDeveloperException( this, "::DrawFormatText() : Invalid <FormatStr> parameter." );
    #endif

        static char Str[ IFont::MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( Str, FormatStr, ArgList );
        va_end( ArgList );

        //for (int i = 0; i < strlen( Str ); ++i)
        //    Str[i] -= 32;

        glPushAttrib( GL_LIST_BIT );
        glRasterPos2i( x, y );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( strlen( Str ) ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str ) );
        glPopAttrib();
    }

    //
    // Constructor
    //
    COutlineFont::COutlineFont( 
                               const TDesc& Desc, float Deviation, float Extrusion, UINT FirstGlyph, UINT GlyphsCount 
                               ):
        IFont( GlyphsCount ),

        m_Height( 0 )
    {
        //
        // Non-portable Window-System dependent codepath.
        //

    #ifdef _WIN32

        HDC DC = wglGetCurrentDC();
        if (!DC)
            throw Sys::CException( this, "::COutlineFont() : Failed to get current DC." );

        LOGFONT lf;

        ZeroMemory( &lf, sizeof( LOGFONT ) );

        lf.lfHeight = Desc.Height;
        lf.lfWidth = Desc.Width;
        lf.lfEscapement = 0;
        lf.lfOrientation = 0;
        lf.lfWeight = Desc.Weight;
        lf.lfItalic = Desc.Italic ? TRUE : FALSE;
        lf.lfUnderline = Desc.Underline ? TRUE : FALSE;
        lf.lfStrikeOut = FALSE;
        lf.lfCharSet = Desc.CharSet;
        lf.lfOutPrecision = Desc.OutputPrecision;
        lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        lf.lfQuality = Desc.Quality;
        lf.lfPitchAndFamily = Desc.PitchAndFamily; // FF_DONTCARE | DEFAULT_PITCH
        wcscpy( lf.lfFaceName, Desc.FaceName );

        HFONT Font, OldFont;
        
        Font = CreateFontIndirect( &lf );
        if (!Font)
            throw Sys::CException( this, "::COutlineFont() : Failed to create font." );
        OldFont = (HFONT)SelectObject( DC, Font );

        try 
        {
            if (!wglUseFontOutlines( DC, FirstGlyph, GlyphsCount, m_ListBase, Deviation, Extrusion, WGL_FONT_POLYGONS, NULL ))
                throw Sys::CException( this, "::COutlineFont() : Failed to create glyph outlines." );  

            TEXTMETRIC Metrics;

            if (!GetTextMetrics( DC, &Metrics ))
                throw Sys::CException( this, "::COutlineFont() : Failed to get text metrics for selected font." );
            m_Height = Metrics.tmHeight;
        }
        catch (const Sys::CException& Ex) 
        {
            SelectObject( DC, OldFont );
            DeleteObject( Font );	

            throw Ex;
        }

        SelectObject( DC, OldFont );
        DeleteObject( Font );

    #elif defined (__linux__)

    #endif // _WIN32
    }

    //
    // DrawText
    //
    void COutlineFont::DrawText( GLint x, GLint y, const string& Str ) const
    {
        glPushAttrib( GL_LIST_BIT );
        glPushMatrix();       
        glTranslatef( x, y, 0.0f );
        glScalef( m_Height, m_Height, 1.0f );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( Str.length() ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str.c_str() ) );
        glPopMatrix();
        glPopAttrib();
    }

    //
    // DrawText
    //
    void COutlineFont::DrawText( GLint x, GLint y, const char *Str ) const
    {
    #ifdef _DEBUG
        if (!Str) 
            throw Sys::CDeveloperException( this, "::DrawText() : Invalid <Str> parameter." );
    #endif

        glPushAttrib( GL_LIST_BIT );
        glPushMatrix();       
        glTranslatef( x, y, 0.0f );
        glScalef( m_Height, m_Height, 1.0f );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( strlen( Str ) ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str ) );
        glPopMatrix();
        glPopAttrib();
    }

    //
    // DrawFormatText
    //
    void COutlineFont::DrawFormatText( GLint x, GLint y, const char *FormatStr, ... ) const
    {
    #ifdef _DEBUG
        if (!FormatStr) 
            throw Sys::CDeveloperException( this, "::DrawFormatText() : Invalid <FormatStr> parameter." );
    #endif

        static char Str[ IFont::MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( Str, FormatStr, ArgList );
        va_end( ArgList );

        glPushAttrib( GL_LIST_BIT );
        glPushMatrix();       
        glTranslatef( x, y, 0.0f );
        glScalef( m_Height, m_Height, 1.0f );
        glListBase( m_ListBase );
        glCallLists( static_cast<GLsizei>( strlen( Str ) ), GL_UNSIGNED_BYTE, static_cast<const GLvoid *>( Str ) );
        glPopMatrix();
        glPopAttrib();
    }
}