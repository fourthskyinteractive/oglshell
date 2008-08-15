// Τΰιλ: /Sys/Precompiled.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#ifdef _MSC_VER
    #pragma message ("------ Compiling project: Sys ------")
#endif

#ifdef _MSC_VER 
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include <assert.h>
//#include <stdio.h>
#include <stdarg.h>

#include <string>

using std::string;

#define DLLAPI 
#include "Sys.h"

#endif // __PRECOMPILED_H__