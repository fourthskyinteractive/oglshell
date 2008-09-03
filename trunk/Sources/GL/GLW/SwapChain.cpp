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

// Τΰιλ: /GL/GLW/SwapChain.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "SwapChain.h"
using namespace GL;

namespace GLW
{
    //
    // Constructor
    //
    CWindowSwapChain::TSampleDesc::TSampleDesc():
        BuffersCount( 0 ),
        SamplesCount( 0 ),
        QuincunxFilterNV( GL_FALSE )
    {
    }

    //
    // Constructor
    //
    CWindowSwapChain::TPixelFormatDesc::TPixelFormatDesc():
        Flags( 0 ),

        ColorBitsCount( 0 ),
        RedBitsCount( 0 ),
        RedShift( 0 ),
        GreenBitsCount( 0 ),
        GreenShift( 0 ),
        BlueBitsCount( 0 ),
        BlueShift( 0 ),
        AlphaBitsCount( 0 ),
        AlphaShift( 0 ),
        AccumBitsCount( 0 ),
        AccumRedBitsCount( 0 ),
        AccumGreenBitsCount( 0 ),
        AccumBlueBitsCount( 0 ),
        AccumAlphaBitsCount( 0 ),
        DepthBitsCount( 0 ),
        StencilBitsCount( 0 ),

        AuxBuffersCount( 0 )
    {
    }

    //
    // GetPixelFormatDesc
    //
    void CWindowSwapChain::GetPixelFormatDesc( 
                                              TPixelFormatDesc *Desc 
                                              ) const
    {
        *Desc = m_Desc;
    }

    //
    // CopySubImage1D
    //
    void CWindowSwapChain::CopySubImage1D( 
                                          GLenum Buffer, GLint Level, 
                                          GLint xOffset, GLint x, GLint y, GLsizei Width, 
                                          Ptr<CTexture1D> Texture 
                                          ) const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        glActiveTexture( GL_TEXTURE0 );      
        glBindTexture( GL_TEXTURE_1D, Texture->m_Texture );
        glReadBuffer( Buffer );
        glCopyTexSubImage1D( GL_TEXTURE_1D, Level, xOffset, x, y, Width );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CopySubImage1D() : An OpenGL error has occured." );
    #endif
    }
        
    //
    // CopySubImage2D
    //
    void CWindowSwapChain::CopySubImage2D( 
                                          GLenum Buffer, GLint Level, 
                                          GLint xOffset, GLint yOffset, GLint x, GLint y, GLsizei Width, GLsizei Height, 
                                          Ptr<CTexture> Texture
                                          ) const
    {
        if (Texture->m_Target != GL_TEXTURE_2D && Texture->m_Target != GL_TEXTURE_RECTANGLE_ARB) 
            throw Sys::CDeveloperException( this, "::CopySubImage2D() : Invalid <Texture> parameter.\nTexture target should be GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE." );

    #ifdef _DEBUG
        glClearErrors();
    #endif
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( Texture->m_Target, Texture->m_Texture );
        glReadBuffer( Buffer );
        glCopyTexSubImage2D( Texture->m_Target, Level, xOffset, yOffset, x, y, Width, Height );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::CopySubImage2D() : An OpenGL error has occured." );
    #endif
    }

    //
    // IsExtensionSuppported
    //
    bool CWindowSwapChain::IsExtensionSupported( 
                                                const char *Name 
                                                ) const
    {
        const char *NAME_SEPARATOR = " ";

        const char *GLStr, *Token;
        vector<char> Str;

        GLStr = reinterpret_cast<const char *>( glGetString( GL_EXTENSIONS ) );
        Str.resize( strlen( GLStr ) + 1 );
        strcpy( &Str[ 0 ], GLStr ); // Becuase strtok() accept non-constant string.

        Token = strtok( &Str[ 0 ], NAME_SEPARATOR );
        while (Token)
        {
            if (strcmp( Token, Name ) == 0)
                return true;
            Token = strtok( NULL, NAME_SEPARATOR );
        }

    #ifdef _WIN32
        HDC DC = wglGetCurrentDC();
        if (!DC)
            throw Sys::CException( this, "::IsExtensionSupported() : Invalid current DC." );

        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress( "wglGetExtensionsStringARB" );
        if (!wglGetExtensionsStringARB)
            return false;
        GLStr = wglGetExtensionsStringARB( DC );
    #else
        // TODO:
    #endif
        Str.resize( strlen( GLStr ) + 1 );
        strcpy( &Str[ 0 ], GLStr );

        Token = strtok( &Str[ 0 ], NAME_SEPARATOR );
        while (Token)
        {
            if (strcmp( Token, Name ) == 0)
                return true;
            Token = strtok( NULL, NAME_SEPARATOR );
        }

        return false;
    }
}