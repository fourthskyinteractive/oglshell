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

// Файл: /GL/GLW/SwapChain.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GLW_WINDOW_SWAP_CHAIN_H__
#define __GLW_WINDOW_SWAP_CHAIN_H__

#include "../GL/Texture.h"

namespace GLW
{
    //  Оконный контекст рендеринга (WGL/GLX).
    //  Конфигурирует формат пикселя кадрового буфера, связанного с главным окном программы.

    class DLLAPI CWindowSwapChain : public GL::CObject
    {
    public:
        enum
        {
            WSC_DOUBLE_BUFFER = 1,
            WSC_STEREO
        };

        struct DLLAPI TSampleDesc
        {
                            TSampleDesc         ();

            GLubyte         BuffersCount;
            GLubyte         SamplesCount;
            GLboolean       QuincunxFilterNV;
        };

        struct DLLAPI TPixelFormatDesc
        { 
                            TPixelFormatDesc    ();

            UINT            Flags; // WSC_ flags.

            GLubyte         ColorBitsCount;
            GLubyte         RedBitsCount;
            GLubyte         RedShift;
            GLubyte         GreenBitsCount;
            GLubyte         GreenShift;
            GLubyte         BlueBitsCount;
            GLubyte         BlueShift;
            GLubyte         AlphaBitsCount;
            GLubyte         AlphaShift;
            GLubyte         AccumBitsCount;
            GLubyte         AccumRedBitsCount;
            GLubyte         AccumGreenBitsCount;
            GLubyte         AccumBlueBitsCount;
            GLubyte         AccumAlphaBitsCount;
            GLubyte         DepthBitsCount;
            GLubyte         StencilBitsCount;
            
            GLubyte         AuxBuffersCount;

            TSampleDesc     SampleDesc;
        };

    public:
    #ifdef _WIN32
                            CWindowSwapChain    ( HWND Window, const TPixelFormatDesc& Desc, GLsizei Width, GLsizei Height );
    #elif defined (__linux__)
                            CWindowSwapChain    ( const TPixelFormatDesc& Desc );
    #endif // _WIN32                              

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CWindowSwapChain"; }

        //
        // Interface
        //

        void                GetPixelFormatDesc  ( TPixelFormatDesc *Desc ) const;

        void                MakeCurrent         () const;
        void                SwapBuffers         ();        
        void                SetVSync            ( bool Sync );
        bool                IsVSynced           () const;

        void                CopySubImage1D      ( GLenum Buffer, GLint Level, GLint xOffset, GLint x, GLint y, GLsizei Width, Ptr<GL::CTexture1D> Texture ) const;
        void                CopySubImage2D      ( GLenum Buffer, GLint Level, GLint xOffset, GLint yOffset, GLint x, GLint y, GLsizei Width, GLsizei Height, Ptr<GL::CTexture> Texture ) const;

    private:
    #ifdef _WIN32
        int                 ChoosePixelFormatEx ( HDC DC, const TPixelFormatDesc& Desc ) const;
        HWND                CreateDummyWindow   ( HINSTANCE Instance, const WCHAR *ClassName ) const;
    #elif defined (__linux__)
        Window              CreateWindow        ( Display *Dpy, GLXFBConfig Config ) const;
    #endif // _WIN32

        bool                IsExtensionSupported( const char *Name ) const;

        //
        // Class members
        //

        TPixelFormatDesc    m_Desc;

        GLsizei             m_Width;
        GLsizei             m_Height;

    #ifdef _WIN32
        HWND                m_Window;
        HDC                 m_DC;
        HGLRC               m_Context;
        int                 m_PixelFormat;
    #elif defined (__linux__)
        Window              m_Window;
        Display*            m_Display; // Specifies the connection to the X server.      
        GLXContext          m_Context;
        GLXFBConfig*        m_Config; 
        GLXDrawable         m_Drawable;
    #endif // _WIN32
    };
}

#endif // __GLW_WINDOW_SWAP_CHAIN_H__ 