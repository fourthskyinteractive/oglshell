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

// Τΰιλ: /GL/Main.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Main.h"

//
// GL_NVX_conditional_render
//

PFNGLBEGINCONDITIONALRENDERNVXPROC glBeginConditionalRenderNVX;
PFNGLENDCONDITIONALRENDERNVXPROC glEndConditionalRenderNVX;

//
// GL_NV_conditional_render
//

PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV;
PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV;

namespace GL
{
    //
    // CreateShellAPI
    //
    DLLAPI void CreateShellAPI( 
                               UINT Flags, 
                               Ptr<GL::IRenderDevice> *RenderDevice, 
                               Ptr<const GL::CExtensionRegistry> *Registry
                               )
    {
    #ifdef _WIN32
        if (wglGetCurrentDC() == NULL || wglGetCurrentContext() == NULL)
    #elif defined __linux__
        if (!glXGetCurrentContext())
    #endif // _WIN32
        {
            throw Sys::CDeveloperException( Sys::CDeveloperException::ERR_INVALID_CALL, 
                "GL::CreateShellAPI() : Invalid current rendering context." );
        }

        Ptr<const GL::CExtensionRegistry> Extensions = new CExtensionRegistry();

        if (Extensions->NVX_conditional_render)
        {
            glBeginConditionalRenderNVX = (PFNGLBEGINCONDITIONALRENDERNVXPROC)wglGetProcAddress( "glBeginConditionalRenderNVX" );
            glEndConditionalRenderNVX = (PFNGLENDCONDITIONALRENDERNVXPROC)wglGetProcAddress( "glEndConditionalRenderNVX" );
        }

        if (Extensions->NV_conditional_render)
        {
            glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)wglGetProcAddress( "glBeginConditionalRenderNV" );
            glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)wglGetProcAddress( "glEndConditionalRenderNV" );
        }

        CObject::Init( Extensions, true ); // ?

        // BUG in Release configuration!

        /*
        if (Flags & CREATE_DEBUG_RENDER_DEVICE)
            *RenderDevice = new CRenderDeviceDebug();
        else 
            *RenderDevice = new CRenderDeviceRelease();
        */

        if (Registry)
        {
            *Registry = Extensions;
        }
    }
};

#ifdef GLWRAPPER_DLL
#ifdef _WIN32

//
// Entry point into DLL
//
BOOL APIENTRY DllMain(
					  HMODULE Module,
                      DWORD Reason,
                      LPVOID Reserved
					  )
{
    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

#endif // _WIN32
#endif // GLWRAPPER_DLL