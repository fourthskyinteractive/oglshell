/*
This file is a part of Z-Trek 3D engine math library. 
You can use it freely in your proprietary applications.

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
*/

// Τΰιλ: /Math/Pch.h
//

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef __PCH_H__
#define __PCH_H__

#ifdef _MSC_VER
#pragma message ("------ Compiling project: Math ------")
#endif // _MSC_VER

#include <assert.h>

#include <map>
#include <vector>

using std::exception;
using std::map;
using std::vector;

#include "Math.h"
#include "Math_SIMD.h"
#include "Vector/Vec.h"
#include "Vector/Vec2.h"
#include "Vector/Vec3.h"
#include "Vector/Vec4.h"
#include "Matrix/Mat.h"
#include "Matrix/Mat2.h"
#include "Matrix/Mat3.h"
#include "Matrix/Mat43.h"
#include "Matrix/Mat4.h"
#include "Quaternion/Quat.h"
#include "Quaternion/Quat4.h"
#include "Quaternion/Quat3.h"
#include "Plane/Plane.h"
#include "Postponed.h"

#endif // __PCH_H__