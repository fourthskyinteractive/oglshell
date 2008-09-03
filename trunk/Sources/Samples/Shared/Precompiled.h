// Файл: /Samples/Shared/Precompiled.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#ifdef _MSC_VER 
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::stack;
using std::vector;

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define _WIN32_WINNT 0x0501
    #define STRICT
    #include <windows.h>
#endif // _WIN32

// Подключаем к проекту OpenGL Cg Run-Time. Если Cg Toolkit не установлен, закомментируйте определитель.
#define CG_SDK

#include <GL/glew.h>
#include <GL/wglew.h>
#ifdef CG_SDK
    #include <Cg/cg.h>
    #include <Cg/cgGL.h>
#endif

#ifdef _MSC_VER 
#define DLLEXPORT __declspec (dllexport)
#define DLLIMPORT __declspec (dllimport)
#endif // _MSC_VER

#define DLLAPI //DLLIMPORT

#ifdef _MSC_VER
    #ifndef _DEBUG
        #define inline __forceinline
    #endif // _DEBUG
#endif // _MSC_VER

#ifdef _MSC_VER 
    #pragma warning (disable: 4018)
    #pragma warning (disable: 4244) 
    #pragma warning (disable: 4251) 
    #pragma warning (disable: 4275) 
#endif // _MSC_VER
                             
#include "../../Sys/Sys.h"
#include "../../Sys/Common.h"
#include "../../Sys/Ptr.h"

using Sys::Ptr;

#include "../../Math/Math.h"
#include "../../Math/Math_SIMD.h"
#include "../../Math/Vector/Vec.h"
#include "../../Math/Vector/Vec2.h"
#include "../../Math/Vector/Vec3.h"
#include "../../Math/Vector/Vec4.h"
#include "../../Math/Vector/Vec4_SIMD.h"
#include "../../Math/Vector/Vec4_SSE.h"
#include "../../Math/Vector/Vec4_3DNow.h"
#include "../../Math/Matrix/Mat.h"
#include "../../Math/Matrix/Mat2.h"
#include "../../Math/Matrix/Mat3.h"
#include "../../Math/Matrix/Mat43.h"
#include "../../Math/Matrix/Mat4.h"
#include "../../Math/Plane/Plane.h"
#include "../../Math/Plane/PlaneEx.h"
#include "../../Math/Plane/Plane_SSE.h"
#include "../../Math/Quaternion/Quat.h"
#include "../../Math/Quaternion/Quat4.h"
#include "../../Math/Quaternion/Quat3.h"
#include "../../Math/Quaternion/Quat4_SSE.h"
#include "../../Math/Postponed.h"

using Math::Vec;
using Math::Vec2;
using Math::Vec3;
using Math::Vec4;
using MathSIMD::Vec4_SSE;
using MathSIMD::Vec4_3DNow;
using Math::Mat;
using Math::Mat2;
using Math::Mat3;
using Math::Mat43;
using Math::Mat4;
using Math::Plane;
using MathSIMD::Plane_SSE;
using Math::Quat4;
using Math::Quat3;
using MathSIMD::Quat4_SSE;

#include "../../GL/GL/Main.h"

#include "../../Sys/RefCounterPost.h"

#endif // __PRECOMPILED_H__