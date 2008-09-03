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

// Τΰιλ: /GL/GLW/SwapChainGLX.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#ifdef __linux__

#include "SwapChain.h"
using namespace GL;

namespace GLW
{    
    //
    // Constructor
    //
    CWindowSwapChain::CWindowSwapChain( 
                                       const TPixelFormatDesc& Desc 
                                       )
    {
    }

    //
    // MakeCurrent
    //
    void CWindowSwapChain::MakeCurrent() const
    {
    }

    //
    // SwapBuffers
    //
    void CWindowSwapChain::SwapBuffers()
    {
    }

    //
    // SetVSync
    //
    void CWindowSwapChain::SetVSync( 
                                    bool Sync 
                                    )
    {
    }
        
    //
    // IsVSynced
    //
    bool CWindowSwapChain::IsVSynced() const
    {
        return false;
    }
}

#endif // __linux__