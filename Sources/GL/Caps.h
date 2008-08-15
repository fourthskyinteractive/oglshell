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

// Файл: /GL/Caps.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_CAPS_H__
#define __GL_CAPS_H__

namespace GL
{
    //  Описание установленного драйвера OpenGL.

    class DLLAPI CDriver : public CObject
    {
    public:
        struct DLLAPI TVersionDesc
        {
                                TVersionDesc    ();

            string              String;
            string              VendorSpecificInfoString;

            GLint               MajorNumber;
            GLint               MinorNumber;
            GLint               ReleaseNumber;
        };

        struct DLLAPI TDesc
        {
            string              Vendor;
            string              Renderer;
        
            TVersionDesc        Version;
            TVersionDesc        GLSLVersion;
            TVersionDesc        GLUVersion;
        };

    public:

        //
        // Interface
        //

        static void         GetDesc             ( TDesc *Desc );

    private:
        static void         TokenizeVersion     ( const char *VersionStr, TVersionDesc *Desc );
    };

    //  Описание возможностей установленного ускорителя OpenGL.

    class DLLAPI CCaps : public CObject
    {
    public:
        struct DLLAPI TDesc
        {
                                TDesc();

                                // OpenGL 2.0/GL_EXT_framebuffer_object
            GLint               MaxDrawBuffers;
            GLint               MaxColorAttachments;
            GLint               MaxSamples;
            GLint               MaxRenderbufferSize;
            GLint               MaxViewportDims[ 2 ];

            GLint               MaxTextureSize;
            GLint               MaxRectangleTextureSize;
            GLint               Max3DTextureSize;
            GLint               MaxCubeMapTextureSize;
            GLfloat             MaxTextureMaxAnisotropy;

                                // OpenGL 2.0/GL_EXT_geometry_shader4/GL_EXT_bindable_uniform
            GLint               MaxVaryingComponents;
            GLint               MaxCombinedTextureImageUnits;
            GLint               MaxBindableUniformSize;
            GLint               MaxVertexVaryingComponents;
            GLint               MaxVertexUniformComponents;                                     
            GLint               MaxVertexBindableUniforms;
            GLint               MaxVertexTextureImageUnits;
            GLint               MaxVertexAttribs;      
            GLint               MaxGeometryVaryingComponents;  
            GLint               MaxGeometryUniformComponents;
            GLint               MaxGeometryBindableUniforms;
            GLint               MaxGeometryTextureImageUnits;
            GLint               MaxGeometryOutputVertices;
            GLint               MaxGeometryTotalOutputComponents;
            GLint               MaxFragmentUniformComponents;
            GLint               MaxFragmentBindableUniforms;
            GLint               MaxTextureCoords;
            GLint               MaxTextureImageUnits;
            
                                // GL_NV/EXT_transform_feedback
            GLint               MaxTransformFeedbackSeparateComponents;
            GLint               MaxTransformFeedbackInterleavedAttribs;
            GLint               MaxTransformFeedbackSeparateAttribs;

            GLint               MaxElementsVertices;
            GLint               MaxElementsIndices;

            GLint               QueryCounterBits;
        };

    public:

        //
        // Interface
        //
                                        
        static void         GetDesc             ( TDesc *Desc );
    };
}

#endif // __GL_CAPS_H__