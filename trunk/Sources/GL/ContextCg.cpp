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

// Τΰιλ: /GL/ContextCg.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#ifdef CG_SDK

#include "ContextCg.h"

namespace GL
{
    CGcontext CCgContext::m_Context = NULL;
    GLuint CCgContext::m_RefCount = 0;

    //
    // AddRef
    //
    void CCgContext::AddRef()
    {
        if (m_RefCount == 0)
        {
            m_Context = cgCreateContext();
            if (!m_Context)
            {
                CGerror Error = cgGetError();
                if (Error != CG_NO_ERROR)
                    throw CCgException( "GL::CCgContext", Error, "::AddRef() : Failed to create Cg context." );
            }

    #ifdef _DEBUG
            cgGLSetDebugMode( CG_TRUE );
    #else
            cgGLSetDebugMode( CG_FALSE );
    #endif
    
            // Prevent auto compilation of Cg programs during rendering, etc.
            cgSetAutoCompile( m_Context, CG_COMPILE_MANUAL );
        }

        ++m_RefCount;
    }
    
    //
    // Release
    //
    void CCgContext::Release()
    {
        if (m_RefCount == 0)
            return;

        if (--m_RefCount == 0)
        {
            cgDestroyContext( m_Context );
            CGerror Error = cgGetError();
            if (Error != CG_NO_ERROR)
                throw CCgException( "GL::CCgContext", Error, "::Release() : Failed to destroy Cg context." );
                
            m_Context = NULL;
        }
    }

    //
    // GetContext
    //
    CGcontext CCgContext::GetContext()
    {
        return m_Context;
    }

    //
    // GetLastListing
    //
    const char *CCgContext::GetLastListing()
    {
        return cgGetLastListing( m_Context ); 
    }
}

#endif // CG_SDK