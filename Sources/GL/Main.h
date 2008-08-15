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

// Τΰιλ: /GL/Main.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_MAIN_H__
#define __GL_MAIN_H__

#include "Common.h"
#include "Interfaces.h"
#include "ExtensionRegistry.h"
#include "Extensions.h"
#include "Caps.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderCg.h"
#include "Uniform.h"
#include "Program.h"
#include "CgFX.h"
#include "VertexStruct.h"
#include "List.h"
#include "Query.h"
#include "Font.h"
#include "RenderDevice.h"
#include "SwapChain.h"

namespace GL
{
    enum 
    {
        CREATE_DEBUG_RENDER_DEVICE = BIT( 1 )
    };

    //
    // CreateShellAPI
    //
    DLLAPI void CreateShellAPI( 
        UINT Flags, 
        Ptr<GL::IRenderDevice> *RenderDevice, 
        Ptr<const GL::CExtensionRegistry> *Extensions
    );
}

#endif // __GL_MAIN_H__