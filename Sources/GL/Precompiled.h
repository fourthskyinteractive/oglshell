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

// Файл: /GL/Precompiled.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#ifdef _MSC_VER
    #pragma message ("------ Compiling project: GL ------")
#endif

#ifdef _MSC_VER 
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include <assert.h>
#include <stdarg.h>

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define STRICT
    #include <windows.h>
    
    // http://glew.sourceforge.net/
    #include <GL/glew.h>
    #include <GL/wglew.h>
#endif // _WIN32

// Макрос определяет, будет ли враппер OpenGL использовать Cg Run-Time.
#define CG_SDK

#ifdef CG_SDK
    // http://developer.nvidia.com/object/cg_toolkit.html
    #include <Cg/cg.h>
    #include <Cg/cgGL.h>
#endif // CG_SDK

// Макрос определяет, будет ли враппер OpenGL собираться как статическая DLL.
// FIXME: проблемы с вызовом деструкторов в Release-версиях при закрытии приложения.
//#define GLWRAPPER_DLL

#ifdef GLWRAPPER_DLL   
    #ifdef _MSC_VER 
        #define DLLAPI __declspec (dllexport)
    #endif
#else
    #define DLLAPI 
#endif // GLWRAPPER_DLL

#ifdef _MSC_VER
    #ifndef _DEBUG
        #define inline __forceinline
    #endif
#endif // _MSC_VER

#ifdef _MSC_VER 
    #ifdef GLWRAPPER_DLL
        #pragma warning (disable: 4251) // class 'X' needs to have dll-interface to be used by clients of class 'Y'
    #endif // GLWRAPPER_DLL 
    #pragma warning (disable: 4312) // 'reinterpret_cast' : conversion from 'X' to 'Y' of greater size
#endif // _MSC_VER

#include "../Sys/Sys.h"
#include "../Sys/Common.h"
#include "../Sys/Ptr.h"

using Sys::Ptr;

#include "../Math/Math.h"
#include "../Math/Math_SIMD.h"
#include "../Math/Vector/Vec.h"
#include "../Math/Vector/Vec2.h"
#include "../Math/Vector/Vec3.h"
#include "../Math/Vector/Vec4.h"
#include "../Math/Vector/Vec4_SIMD.h"
#include "../Math/Vector/Vec4_SSE.h"
#include "../Math/Matrix/Mat.h"
#include "../Math/Matrix/Mat2.h"
#include "../Math/Matrix/Mat3.h"
#include "../Math/Matrix/Mat43.h"
#include "../Math/Matrix/Mat4.h"
#include "../Math/Postponed.h"

using Math::Vec;
using Math::Vec2;
using Math::Vec3;
using Math::Vec4;
using MathSIMD::Vec4_SSE;
using Math::Mat;
using Math::Mat2;
using Math::Mat3;
using Math::Mat43;
using Math::Mat4;

#include "Common.h"
#include "Interfaces.h"
#include "ExtensionRegistry.h"

#include "../Sys/RefCounterPost.h"

#endif // __PRECOMPILED_H__