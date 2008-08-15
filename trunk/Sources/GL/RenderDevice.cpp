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

// Τΰιλ: /GL/RenderDevice.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "FrameBuffer.h"
#include "Texture.h"
#include "Buffer.h"
#include "Program.h"
#include "VertexStruct.h"

#include "RenderDevice.h"

namespace GL
{
    //
    // Constructor
    //
    CRenderDevice::CRenderDevice():
    #ifdef CG_SDK
        m_APIType( CShadingProgram::SA_UNKNOWN ),
    #endif
        
        m_IndexType( GL_NONE ),
        m_IndexSize( 0 )
    {
    }

    //
    // GetFrameBuffer
    //
    void CRenderDevice::GetFrameBuffer( 
                                       Ptr<IFrameBuffer> *FrameBuffer 
                                       ) const
    {
        *FrameBuffer = m_FrameBuffer;
    }

    //
    // GetTexture
    //
    void CRenderDevice::GetTexture( 
                                   GLenum Unit, Ptr<const CTexture> *Texture 
                                   ) const
    {
        if (Unit < GL_TEXTURE0 || Unit > GL_TEXTURE0 + static_cast<GLenum>( m_Caps.MaxTextureImageUnits ))
            throw Sys::CDeveloperException( this, "::GetTexture() : Invalid <Unit> parameter." );

        *Texture = m_Textures[ Unit - GL_TEXTURE0 ];
    }

    //
    // GetShadingProgram
    //
    void CRenderDevice::GetShadingProgram( 
                                          Ptr<const IShadingProgram> *Program 
                                          ) const
    {
        *Program = m_Program;
    }

    //
    // GetVertexStructure
    //
    void CRenderDevice::GetVertexStructure( 
                                           Ptr<const CVertexStructure> *Struct 
                                           ) const
    {
        *Struct = m_VertexStruct;
    }
    
    //
    // GetVertexBuffer
    // 
    void CRenderDevice::GetVertexBuffer( 
                                        GLuint StreamIndex, Ptr<const CBuffer> *Buffer 
                                        ) const
    {
        if (StreamIndex >= MAX_VERTEX_STREAMS)
            throw Sys::CDeveloperException( this, "::GetVertexBuffer() : Invalid <StreamIndex> parameter." );

        *Buffer = m_VertexBuffers[ StreamIndex ];
    }
    
    //
    // GetIndexBuffer
    //
    void CRenderDevice::GetIndexBuffer( 
                                       Ptr<const CBuffer> *Buffer 
                                       ) const
    {
        *Buffer = m_IndexBuffer;
    }
    
    //
    // GetPackPixelBuffer
    //
    void CRenderDevice::GetPackPixelBuffer( 
                                           Ptr<CBuffer> *Buffer 
                                           ) const
    { 
        *Buffer = m_PackBuffer;
    }
    
    //
    // GetUnpackPixelBuffer
    //
    void CRenderDevice::GetUnpackPixelBuffer( 
                                             Ptr<const CBuffer> *Buffer 
                                             ) const
    {
        *Buffer = m_UnpackBuffer;
    }
    
    //
    // GetTransformFeedbackBuffer
    //
    void CRenderDevice::GetTransformFeedbackBuffer( 
                                                   Ptr<CBuffer> *Buffer 
                                                   ) const
    {
        *Buffer = m_FeedbackBuffer;
    }

    //
    // GetIndexSize
    //
    GLsizei CRenderDevice::GetIndexSize( 
                                        GLenum IndexType 
                                        ) const
    {
        switch (IndexType) 
        {
            case GL_UNSIGNED_BYTE:
                return sizeof( GLubyte );
            case GL_UNSIGNED_SHORT:
                return sizeof( GLushort );
            case GL_UNSIGNED_INT:
                return sizeof( GLuint );
            default:
                throw Sys::CDeveloperException( this, "::GetIndexSize() : Invalid <IndexType> parameter." );
        }
    }

    //
    // CheckPrimitiveTopology
    //
    void CRenderDevice::CheckPrimitiveTopology( 
                                               GLenum Mode, const char *Method 
                                               ) const
    {
        switch (Mode)
        {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_STRIP:
        case GL_TRIANGLES:
        case GL_TRIANGLE_STRIP:
            break;
        case GL_LINES_ADJACENCY_EXT:
        case GL_LINE_STRIP_ADJACENCY_EXT:
        case GL_TRIANGLES_ADJACENCY_EXT:
        case GL_TRIANGLE_STRIP_ADJACENCY_EXT:
            if (!m_Extensions->EXT_geometry_shader4)
                throw CExtensionException( this, Method, "GL_EXT_geometry_shader4" );
            break;

        case GL_LINE_LOOP:
        case GL_TRIANGLE_FAN:
        case GL_QUADS:
        case GL_QUAD_STRIP:
        case GL_POLYGON:
            {
                static const char *ModeStr[] =
                {
                    "GL_POINTS",
                    "GL_LINES",
                    "GL_LINE_LOOP",
                    "GL_LINE_STRIP",
                    "GL_TRIANGLES",
                    "GL_TRIANGLE_STRIP",
                    "GL_TRIANGLE_FAN",
                    "GL_QUADS",
                    "GL_QUAD_STRIP",
                    "GL_POLYGON"
                };
            
                throw Sys::CDeveloperException( this, "%s : Deprecated <Mode> parameter: %s.", Method, ModeStr[ Mode - GL_POINTS ] );
            }

        default:
            throw Sys::CDeveloperException( this, "%s : Invalid <Mode> parameter.", Method );
        }
    }
}