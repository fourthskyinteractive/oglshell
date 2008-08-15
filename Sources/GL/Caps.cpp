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

// Файл: /GL/Caps.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Caps.h"
#include "Extensions.h"

namespace GL
{
    //
    // Constructor
    //
    CDriver::TVersionDesc::TVersionDesc():
        MajorNumber( 0 ),
        MinorNumber( 0 ),
        ReleaseNumber( 0 )
    {
    }

    //
    // GetDesc
    //
    void CDriver::GetDesc( TDesc *Desc )
    {
    #ifdef _WIN32
        if (!wglGetCurrentContext())
    #elif defined __linux__
        if (!glXGetCurrentContext())
    #endif // _WIN32
        {
            throw Sys::CDeveloperException( "GL::CDriver", "::GetDesc() : Invalid current rendering context." );
        }

        Desc->Vendor = reinterpret_cast<const char *>( glGetString( GL_VENDOR ) );
        Desc->Renderer = reinterpret_cast<const char *>( glGetString( GL_RENDERER ) );

        const char *Str = reinterpret_cast<const char *>( glGetString( GL_VERSION ) );
        TokenizeVersion( Str, &Desc->Version );

        if (m_Extensions->OpenGL_2_0 || m_Extensions->ARB_shading_language_100)
        {
            Str = reinterpret_cast<const char *>( glGetString( GL_SHADING_LANGUAGE_VERSION ) );
            TokenizeVersion( Str, &Desc->GLSLVersion );
        }

        Str = reinterpret_cast<const char *>( gluGetString( GLU_VERSION ) );
        TokenizeVersion( Str, &Desc->GLUVersion );
    }

    //
    // TokenizeVersion
    //
    void CDriver::TokenizeVersion( 
                                  const char *VersionStr, 
                                  TVersionDesc *Desc 
                                  )
    {
        int Count = sscanf( VersionStr, "%d.%d.%d", &Desc->MajorNumber, &Desc->MinorNumber, &Desc->ReleaseNumber );      
        if (Count < 2)
            throw Sys::CException( 0, "GL::CDriver", "::TokenizeVersion() : OpenGL version string malformed!" );

        Desc->String = VersionStr;

        const char *WhiteSpace = strchr( VersionStr, CH_WHITE_SPACE ); 
        if (WhiteSpace)
            Desc->VendorSpecificInfoString = ++WhiteSpace;
    }

    //
    // Constructor
    //
    CCaps::TDesc::TDesc():
        MaxDrawBuffers( 0 ),
        MaxColorAttachments( 0 ),
        MaxSamples( 0 ),
        MaxRenderbufferSize( 0 ),

        MaxTextureSize( 0 ),
        MaxRectangleTextureSize( 0 ),
        Max3DTextureSize( 0 ),
        MaxCubeMapTextureSize( 0 ),
        MaxTextureMaxAnisotropy( 0.0f ),

        MaxVaryingComponents( 0 ),
        MaxBindableUniformSize( 0 ),
        MaxCombinedTextureImageUnits( 0 ),
        MaxVertexVaryingComponents( 0 ),
        MaxVertexUniformComponents( 0 ),                                     
        MaxVertexBindableUniforms( 0 ),
        MaxVertexTextureImageUnits( 0 ),
        MaxVertexAttribs( 0 ),      
        MaxGeometryVaryingComponents( 0 ),
        MaxGeometryUniformComponents( 0 ),
        MaxGeometryBindableUniforms( 0 ),
        MaxGeometryTextureImageUnits( 0 ),
        MaxGeometryOutputVertices( 0 ),
        MaxGeometryTotalOutputComponents( 0 ),
        MaxFragmentUniformComponents( 0 ),
        MaxFragmentBindableUniforms( 0 ),
        MaxTextureCoords( 0 ),
        MaxTextureImageUnits( 0 ),

        MaxTransformFeedbackInterleavedAttribs( 0 ),
        MaxTransformFeedbackSeparateAttribs( 0 ),
        MaxTransformFeedbackSeparateComponents( 0 ),

        MaxElementsVertices( 0 ),
        MaxElementsIndices( 0 ),

        QueryCounterBits( 0 )
    {
        MaxViewportDims[ 0 ] = 0;
        MaxViewportDims[ 1 ] = 0;
    }

    //
    // GetDesc
    //
    void CCaps::GetDesc( TDesc *Desc )
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif

        if (m_Extensions->OpenGL_2_0)
            glGetIntegerv( GL_MAX_DRAW_BUFFERS, &Desc->MaxDrawBuffers );
        if (m_Extensions->EXT_framebuffer_object)
        {
            glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS_EXT, &Desc->MaxColorAttachments );
            glGetIntegerv( GL_MAX_SAMPLES_EXT, &Desc->MaxSamples );
            glGetError();
            glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE_EXT, &Desc->MaxRenderbufferSize );
        }
        glGetIntegerv( GL_MAX_VIEWPORT_DIMS, Desc->MaxViewportDims ); 

        glGetIntegerv( GL_MAX_TEXTURE_SIZE, &Desc->MaxTextureSize );
        if (m_Extensions->ARB_texture_rectangle || m_Extensions->EXT_texture_rectangle || m_Extensions->NV_texture_rectangle)
            glGetIntegerv( GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB, &Desc->MaxRectangleTextureSize );
        glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &Desc->Max3DTextureSize );
        glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &Desc->MaxCubeMapTextureSize );
        if (m_Extensions->EXT_texture_filter_anisotropic) 
            glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Desc->MaxTextureMaxAnisotropy );

        if (m_Extensions->OpenGL_2_0)
        {
            glGetIntegerv( GL_MAX_VARYING_COMPONENTS_EXT, &Desc->MaxVaryingComponents ); // Old token - GL_MAX_VARYING_FLOATS.         
            glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Desc->MaxCombinedTextureImageUnits );
            if (m_Extensions->EXT_bindable_uniform)
                glGetIntegerv( GL_MAX_BINDABLE_UNIFORM_SIZE_EXT, &Desc->MaxBindableUniformSize );

            // VS
            if (m_Extensions->EXT_geometry_shader4)
                glGetIntegerv( GL_MAX_VERTEX_VARYING_COMPONENTS_EXT, &Desc->MaxVertexVaryingComponents );
            glGetIntegerv( GL_MAX_VERTEX_UNIFORM_COMPONENTS, &Desc->MaxVertexUniformComponents );
            if (m_Extensions->EXT_bindable_uniform)
                glGetIntegerv( GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT, &Desc->MaxVertexBindableUniforms );
            glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &Desc->MaxVertexTextureImageUnits ); 
            glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &Desc->MaxVertexAttribs );

            // GS
            if (m_Extensions->EXT_geometry_shader4)
            {
                glGetIntegerv( GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT, &Desc->MaxGeometryVaryingComponents );
                glGetIntegerv( GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT, &Desc->MaxGeometryUniformComponents );
                if (m_Extensions->EXT_bindable_uniform)
                    glGetIntegerv( GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT, &Desc->MaxGeometryBindableUniforms );
                glGetIntegerv( GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT, &Desc->MaxGeometryTextureImageUnits );
                glGetIntegerv( GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &Desc->MaxGeometryOutputVertices );
                glGetIntegerv( GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT, &Desc->MaxGeometryTotalOutputComponents );
            }

            // FS
            glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &Desc->MaxFragmentUniformComponents );
            if (m_Extensions->EXT_bindable_uniform)
                glGetIntegerv( GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT, &Desc->MaxFragmentBindableUniforms );
            glGetIntegerv( GL_MAX_TEXTURE_COORDS, &Desc->MaxTextureCoords );
            glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &Desc->MaxTextureImageUnits );
        }

        if (m_Extensions->NV_transform_feedback || m_Extensions->EXT_transform_feedback) 
        {
            glGetIntegerv( GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV, &Desc->MaxTransformFeedbackSeparateComponents );
            glGetIntegerv( GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_ATTRIBS_NV, &Desc->MaxTransformFeedbackInterleavedAttribs );
            glGetIntegerv( GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV, &Desc->MaxTransformFeedbackSeparateAttribs );
        }

        glGetIntegerv( GL_MAX_ELEMENTS_VERTICES, &Desc->MaxElementsVertices );
        glGetIntegerv( GL_MAX_ELEMENTS_INDICES, &Desc->MaxElementsIndices );

        if (m_Extensions->OpenGL_1_5)
            glGetIntegerv( GL_QUERY_COUNTER_BITS, &Desc->QueryCounterBits );
       
    #ifdef _DEBUG
        // В некоторых драйверах (NVIDIA включительно) может возникать ошибка OpenGL, хотя код полностью легален.
        // Поэтому оставляем проверку только в Debug варианте программы.
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CCaps", Error, "::GetDesc() : An OpenGL error has occured." );
    #endif // _DEBUG
    }
}