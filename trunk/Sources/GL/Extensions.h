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

// Τΰιλ: /GL/Extensions.h
//                                                                

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_EXTENSIONS_H__
#define __GL_EXTENSIONS_H__

//
// GL_NVX_conditional_render
//

#ifndef GL_NVX_conditional_render
#define GL_NVX_conditional_render 1

typedef void (GLAPIENTRY * PFNGLBEGINCONDITIONALRENDERNVXPROC) (GLuint id);
typedef void (GLAPIENTRY * PFNGLENDCONDITIONALRENDERNVXPROC) (void);

extern PFNGLBEGINCONDITIONALRENDERNVXPROC glBeginConditionalRenderNVX;
extern PFNGLENDCONDITIONALRENDERNVXPROC glEndConditionalRenderNVX;

#endif // GL_NVX_conditional_render

//
// GL_NV_conditional_render
//

#ifndef GL_NV_conditional_render
#define GL_NV_conditional_render 1

#define GL_QUERY_WAIT_NV 0x8E13
#define GL_QUERY_NO_WAIT_NV 0x8E14
#define GL_QUERY_BY_REGION_WAIT_NV 0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT_NV 0x8E16

typedef void (GLAPIENTRY * PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum mode);
typedef void (GLAPIENTRY * PFNGLENDCONDITIONALRENDERNVPROC) (void);

extern PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV;
extern PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV;

#endif // GL_NV_conditional_render

//
// GL_EXT_framebuffer_multisample
//

#ifndef GL_MAX_SAMPLES_EXT
#define GL_MAX_SAMPLES_EXT 0x8D57
#endif 

#ifndef GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#endif

#endif // __GL_EXTENSIONS_H__