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

// Файл: /GL/RenderDevice_Debug.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Extensions.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "Buffer.h"
#include "Program.h"
#include "VertexStruct.h"
#include "Query.h"

#include "RenderDevice.h"

namespace GL
{
    using namespace std;

    //
    // SetFrameBuffer
    //
    void CRenderDeviceDebug::SetFrameBuffer( 
                                            Ptr<IFrameBuffer> FrameBuffer 
                                            )
    {
        if (m_FrameBuffer)
        {
            if ((m_FrameBuffer->m_Type == IFrameBuffer::FBT_FRAMEBUFFER_OBJECT) && (FrameBuffer->m_Type == IFrameBuffer::FBT_PBUFFER))
            {
                glClearErrors();
                if (m_Extensions->EXT_framebuffer_blit)
                {
                    glBindFramebufferEXT( GL_READ_FRAMEBUFFER_EXT, 0 );
                    glBindFramebufferEXT( GL_DRAW_FRAMEBUFFER_EXT, 0 ); 
                }
                else if (m_Extensions->EXT_framebuffer_object) 
                {
                    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
                }
                GLenum Error = glGetError();
                if (Error != GL_NO_ERROR)
                    throw CException( this, Error, "::SetFrameBuffer() : An OpenGL error has occured." );
            }
        }

        FrameBuffer->Set();

        glClearErrors();
        if (FrameBuffer->m_DrawBuffers.empty()) 
        {
            glDrawBuffer( GL_NONE );     
            glReadBuffer( GL_NONE );
        }
        else 
        {
            if (FrameBuffer->m_DrawBuffers.size() == 1) 
            {
                glDrawBuffer( *FrameBuffer->m_DrawBuffers.begin() );
                glReadBuffer( *FrameBuffer->m_DrawBuffers.begin() );
            }
            else 
            {
                if (!m_Extensions->OpenGL_2_0)
                    throw CExtensionException( this, "::SetFrameBuffer()", 2, 0 );
                else 
                {
                    int NumDrawBuffers = static_cast<int>( FrameBuffer->m_DrawBuffers.size() );
                    vector<GLenum> Buffers;
                    
                    if (NumDrawBuffers > m_Caps.MaxDrawBuffers)
                        throw Sys::CException( this, "::SetFrameBuffer() : Number of draw buffers (%d) exceed implementation-dependent constant GL_MAX_DRAW_BUFFERS.", NumDrawBuffers );
                    for (SET_CONST_ITERATION( GLenum, FrameBuffer->m_DrawBuffers, i ))
                        Buffers.push_back( *i );

                    glDrawBuffers( static_cast<GLsizei>( Buffers.size() ), &Buffers[0] );
                }
            }
        }
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetFrameBuffer() : An OpenGL error has occured." );

        if (m_FrameBuffer)
            m_FrameBuffer->m_Current = false;
        m_FrameBuffer = FrameBuffer;
        m_FrameBuffer->m_Current = true;
    }

    //
    // Blit
    //
    void CRenderDeviceDebug::Blit( 
                                  Ptr<CFrameBufferObject> DestFrameBuffer, Ptr<const CFrameBufferObject> SrcFrameBuffer, GLbitfield Mask, GLenum Filter 
                                  ) const
    {
        if (!m_Extensions->EXT_framebuffer_blit)
            throw CExtensionException( this, "::Blit()", "GL_EXT_framebuffer_blit" );
        if (!(Mask & GL_COLOR_BUFFER_BIT) && !(Mask & GL_DEPTH_BUFFER_BIT))
            throw Sys::CDeveloperException( this, "::Blit() : Invalid <Mask> parameter." );
        if (Filter != GL_NEAREST && Filter != GL_LINEAR)
            throw Sys::CDeveloperException( this, "::Blit() : Invalid <Filter> parameter." );

        glClearErrors();
        glBindFramebufferEXT( GL_READ_FRAMEBUFFER_EXT, SrcFrameBuffer->m_Framebuffer );
        glBindFramebufferEXT( GL_DRAW_FRAMEBUFFER_EXT, DestFrameBuffer->m_Framebuffer );
        glBlitFramebufferEXT( 
            0, 0, 
            SrcFrameBuffer->GetFrameWidth(), SrcFrameBuffer->GetFrameHeight(), 
            0, 0, 
            DestFrameBuffer->GetFrameWidth(), DestFrameBuffer->GetFrameHeight(), 
            Mask, 
            Filter 
            );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Blit() : An OpenGL error has occured." );
    }

    //
    // CopyDepthStencilToColor
    //
    void CRenderDeviceDebug::CopyDepthStencilToColor( 
                                                     GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum Type 
                                                     ) const
    {
        if (!m_Extensions->NV_copy_depth_to_color)
            throw CExtensionException( this, "::CopyDepthStencilToColor()", "GL_NV_copy_depth_to_color" );
        if (Type != GL_DEPTH_STENCIL_TO_RGBA_NV && Type != GL_DEPTH_STENCIL_TO_BGRA_NV)
            throw Sys::CDeveloperException( this, "Invalid <Type> parameter." );

        glClearErrors();
        // Строго (!) необходимо отключать тесты трафарета и глубины, иначе драйвер NVidia 
        // не выполняет копирование или входит в Software Mode. 
        glPushAttrib( GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
        glDisable( GL_STENCIL_TEST );
        glDisable( GL_DEPTH_TEST );
        glWindowPos2i( x, y );                                 
        glCopyPixels( x, y, Width, Height, Type );
        glPopAttrib();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CopyDepthStencilToColor() : An OpenGL error has occured." );
    }

    //
    // CopyPixels
    //
    void CRenderDeviceDebug::CopyPixels( 
                                        GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum InputFormat, GLenum OutputFormat, GLenum Type, 
                                        Ptr<CBuffer> Buffer 
                                        ) const
    {
        if (!m_Extensions->OpenGL_2_1 && !m_Extensions->ARB_pixel_buffer_object)
            throw CExtensionException( this, "::CopyPixels()", "GL_ARB_pixel_buffer_object" );

        glClearErrors();
        glBindBuffer( GL_PIXEL_PACK_BUFFER, Buffer->m_Buffer );
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, Buffer->m_Buffer );
        glPushAttrib( GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
        glDisable( GL_STENCIL_TEST );
        glDisable( GL_DEPTH_TEST );
        glWindowPos2i( x, y );
        glReadPixels( x, y, Width, Height, InputFormat, Type, NULL );
        glDrawPixels( Width, Height, OutputFormat, Type, NULL );
        glPopAttrib();
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 ); // ?
        glBindBuffer( GL_PIXEL_PACK_BUFFER, 0 ); // ?
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CopyPixels() : An OpenGL error has occured." );
    }

    //
    // SetTexture
    //
    void CRenderDeviceDebug::SetTexture( 
                                        GLenum Unit, Ptr<const CTexture> Texture 
                                        )
    {
        static const GLenum Targets[] = 
        {
            GL_TEXTURE_1D, 
            GL_TEXTURE_2D, 
            GL_TEXTURE_RECTANGLE_ARB, 
            GL_TEXTURE_3D, 
            GL_TEXTURE_CUBE_MAP, 
            0
        };

        if (Unit < GL_TEXTURE0)
            throw Sys::CDeveloperException( this, "::SetTexture() : Invalid <Unit> parameter." );

        GLint UnitIndex = Unit - GL_TEXTURE0;
        GLenum Target = GL_NONE;

        if (UnitIndex > m_Caps.MaxTextureImageUnits)
            throw Sys::CDeveloperException( this, "::SetTexture() : Invalid <Unit> parameter. Unit index %d exceed implementation-dependent constant GL_MAX_TEXTURE_IMAGE_UNITS.", UnitIndex );

        for (int i = 0; Targets[ i ] != 0; ++i) 
        {
            if (glIsEnabled( Targets[ i ] )) 
            {
                Target = Targets[ i ];
                break;
            }
        }

        glClearErrors();
        glActiveTexture( Unit );
        if (Texture) 
        {
            glBindTexture( Texture->m_Target, Texture->m_Texture );
            if (Target == GL_NONE)
                glEnable( Texture->m_Target );
            else if (Target != Texture->m_Target) 
            {
                glDisable( Target );
                glEnable( Texture->m_Target );
            }
        } 
        else 
        {
            if (Target != GL_NONE) 
                glDisable( Target );
        }
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetTexture() : An OpenGL error has occured." );

        m_Textures[ UnitIndex ] = Texture;
    }

    //
    // SetShadingProgram
    //
    void CRenderDeviceDebug::SetShadingProgram( 
                                               Ptr<const IShadingProgram> Program 
                                               )
    {
    #ifdef CG_SDK
        if (Program)
        {
            if (m_APIType == IShadingProgram::SA_UNKNOWN)
                m_APIType = Program->GetAPIType();
            else
            {
                if (Program->GetAPIType() != m_APIType)
                    throw Sys::CDeveloperException( this, "::SetShadingProgram() : Mixing of GLSL/Cg shaders disallowed." );
            }
        }
    #endif // CG_SDK
    
        if (Program)
        {
    #ifdef CG_SDK
            if (Program->GetAPIType() == IShadingProgram::SA_GLSL)
    #endif // CG_SDK
            {
                Program->Set();
            }
    #ifdef CG_SDK
            else // IShadingProgram::SA_CG
            {
                if (!m_Program)
                {
                    // Включаем все профили устанавливаемой программы.
                    for (vector<CGprofile>::const_iterator i = Program->m_Profiles.begin(); i != Program->m_Profiles.end(); ++i)
                        cgGLEnableProfile( *i );
                }
                else
                {
                    vector<CGprofile> Disable( m_Program->m_Profiles.size() );
                
                    // Составляем список профилей, которые необходимо отключить.
                    vector<CGprofile>::const_iterator end = set_difference( m_Program->m_Profiles.begin(), m_Program->m_Profiles.end(),
                        Program->m_Profiles.begin(), Program->m_Profiles.end(), Disable.begin() );
                    for (vector<CGprofile>::iterator i = Disable.begin(); i != end; ++i)
                        cgGLDisableProfile( *i );
                    
                    vector<CGprofile> Enable( Program->m_Profiles.size() );
                
                    // Составляем список профилей, которые необходимо включить.
                    end = set_difference( Program->m_Profiles.begin(), Program->m_Profiles.end(),
                        m_Program->m_Profiles.begin(), m_Program->m_Profiles.end(), Enable.begin() );
                    for (vector<CGprofile>::iterator i = Enable.begin(); i != end; ++i)
                        cgGLEnableProfile( *i );
                }
                
                CGerror Error = cgGetError();
                if (Error != CG_NO_ERROR)
                    throw CCgException( this, Error, "::SetShadingProgram()) : A Cg error has occured." );
                    
                Program->Set();
            }
    #endif // CG_SDK
        }
        else if (m_Program) 
        {
    #ifdef CG_SDK
            if (m_Program->GetAPIType() == IShadingProgram::SA_GLSL)
    #endif // CG_SDK
                glUseProgram( 0 );
    #ifdef CG_SDK
            else // IShadingProgram::SA_CG
            {
                // Отключаем все задействованные профили.
                for (vector<CGprofile>::const_iterator i = m_Program->m_Profiles.begin(); i != m_Program->m_Profiles.end(); ++i)
                    cgGLDisableProfile( *i );
                    
                CGerror Error = cgGetError();
                if (Error != CG_NO_ERROR)
                    throw CCgException( this, Error, "::SetShadingProgram()) : A Cg error has occured." );
            }
    #endif // CG_SDK
        }
        
        m_Program = Program;
    }

    //
    // SetVertexStructure
    //
    void CRenderDeviceDebug::SetVertexStructure( 
                                                Ptr<const CVertexStructure> Struct
                                                )
    {
        glClearErrors();
        if (!Struct)
        {
            for (int Index = 0; Index < m_Caps.MaxVertexAttribs; ++Index)
                glDisableVertexAttribArray( Index );
        }
        else
        {
            for (int Index = 0; Index < m_Caps.MaxVertexAttribs; ++Index)
            {
                if (Struct->m_Involved[ Index ])
                    glEnableVertexAttribArray( Index );
                else
                    glDisableVertexAttribArray( Index );
            }
        }
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetVertexStructure() : An OpenGL error has occured." );

        m_VertexStruct = Struct;
    }
        
    //
    // SetVertexBuffer
    //
    void CRenderDeviceDebug::SetVertexBuffer( 
                                             GLuint StreamIndex, Ptr<const CBuffer> Buffer, GLintptr Offset, 
                                             GLsizei Stride
                                             )
    {
        if (StreamIndex >= MAX_VERTEX_STREAMS)
            throw Sys::CDeveloperException( this, "::SetVertexBuffer() : Invalid <StreamIndex> parameter." );
        if (!m_VertexStruct)
            throw Sys::CDeveloperException( this, "::SetVertexBuffer() : Invalid current vertex structure." );

        glClearErrors();
        if (!Buffer)
            glBindBuffer( GL_ARRAY_BUFFER, 0 );
        else 
        { 
            if (m_VertexStruct->m_Attributes[ StreamIndex ].size() == 0)
                throw Sys::CDeveloperException( this, "::SetVertexBuffer() : Invalid <StreamIndex> parameter for current vertex structure." );
                
            if (Stride < 0)
                Stride = m_VertexStruct->m_Strides[ StreamIndex ];
                
            glBindBuffer( GL_ARRAY_BUFFER, Buffer->m_Buffer );
            for (MAP_CONST_ITERATION( GLuint, CVertexStructure::TAttrib, m_VertexStruct->m_Attributes[ StreamIndex ], i ))
                glVertexAttribPointer( i->first, i->second.Size, i->second.Type, i->second.Normalized, Stride, i->second.Offset + Offset );
        }  
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetVertexBuffer() : An OpenGL error has occured." );

        m_VertexBuffers[ StreamIndex ] = Buffer;
    }
    
    //
    // SetIndexBuffer
    //
    void CRenderDeviceDebug::SetIndexBuffer( 
                                            Ptr<const CIndexBuffer> Buffer 
                                            )
    {
        SetIndexBuffer( Buffer, Buffer ? Buffer->GetIndexType() : GL_NONE );
    }

    //
    // SetIndexBuffer
    //
    void CRenderDeviceDebug::SetIndexBuffer( 
                                            Ptr<const CBuffer> Buffer, GLenum IndexType 
                                            )
    {
        glClearErrors();
        if (!Buffer)
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        else 
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, Buffer->m_Buffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetIndexBuffer() : An OpenGL error has occured." );

        m_IndexBuffer = Buffer;
        m_IndexType = IndexType;
        if (!Buffer)
            m_IndexSize = 0;
        else
            m_IndexSize = GetIndexSize( IndexType );
    }

    //
    // SetPackPixelBuffer
    //
    void CRenderDeviceDebug::SetPackPixelBuffer( 
                                                Ptr<CBuffer> Buffer 
                                                )
    {
        if (!m_Extensions->OpenGL_2_1 && !m_Extensions->ARB_pixel_buffer_object)
            throw CExtensionException( this, "::SetPackPixelBuffer()", "GL_ARB_pixel_buffer_object" );

        glClearErrors();
        if (!Buffer)
            glBindBuffer( GL_PIXEL_PACK_BUFFER, 0 );
        else
            glBindBuffer( GL_PIXEL_PACK_BUFFER, Buffer->m_Buffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetPackPixelBuffer() : An OpenGL error has occured." );

        m_PackBuffer = Buffer;
    }
		
    //
    // SetUnpackPixelBuffer
    //
    void CRenderDeviceDebug::SetUnpackPixelBuffer(
                                                  Ptr<const CBuffer> Buffer
                                                  )
    {
        if (!m_Extensions->OpenGL_2_1 && !m_Extensions->ARB_pixel_buffer_object)
            throw CExtensionException( this, "::SetUnpackPixelBuffer()", "GL_ARB_pixel_buffer_object" );

        glClearErrors();
        if (!Buffer)
            glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        else
            glBindBuffer( GL_PIXEL_UNPACK_BUFFER, Buffer->m_Buffer );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetUnpackPixelBuffer() : An OpenGL error has occured." );

        m_UnpackBuffer = Buffer;
    }

    //
    // SetTransformFeedbackBuffer
    //
    void CRenderDeviceDebug::SetTransformFeedbackBuffer( 
                                                        GLuint Index, Ptr<CBuffer> Buffer, GLintptr Offset, 
                                                        GLsizeiptr Size
                                                        )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::SetTransformFeedbackBuffer()", "GL_NV_transform_feedback" );

        glClearErrors();
        if (!Buffer)
            glBindBufferBaseNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, 0 );
		else
		{
		    if (Size < 0)
		        glBindBufferOffsetNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, Buffer->m_Buffer, Offset );
		    else
		    {
		        // <Size> specifies the number of elements that can be written during transform feedback mode. 
		        // This is useful to prevent the GL from writing past a certain position in the buffer object.
		        glBindBufferRangeNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, Buffer->m_Buffer, Offset, Size );
		    } 
		}
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetTransformFeedbackBuffer() : An OpenGL error has occured." );

        m_FeedbackBuffer = Buffer;
    }

    //
    // BeginConditionalRender
    //
    void CRenderDeviceDebug::BeginConditionalRender( 
                                                    Ptr<const CQuery> Query, GLenum Mode 
                                                    )
    {
        if (!m_Extensions->NV_conditional_render && !m_Extensions->NVX_conditional_render)
            throw CExtensionException( this, "::BeginConditionalRender()", "GL_NV[X]_conditional_render" );
            
        if (Mode != GL_QUERY_WAIT_NV && Mode != GL_QUERY_NO_WAIT_NV && Mode != GL_QUERY_BY_REGION_WAIT_NV && Mode != GL_QUERY_BY_REGION_NO_WAIT_NV)
            throw Sys::CDeveloperException( this, "::BeginConditionalRender() : Invalid <Mode> parameter." );

        glClearErrors();
        if (m_Extensions->NV_conditional_render)
            glBeginConditionalRenderNV( Query->m_Query, Mode );
        else
            glBeginConditionalRenderNVX( Query->m_Query );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::BeginConditionalRender() : An OpenGL error has occured." );
    }

    //
    // EndConditionalRender
    //
    void CRenderDeviceDebug::EndConditionalRender()                                                              
    {
        if (!m_Extensions->NV_conditional_render && !m_Extensions->NVX_conditional_render)
            throw CExtensionException( this, "::EndConditionalRender()", "GL_NV/NVX_conditional_render" );

        glClearErrors();
        if (m_Extensions->NV_conditional_render)
            glEndConditionalRenderNV();
        else
            glEndConditionalRenderNVX();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::EndConditionalRender() : An OpenGL error has occured." );
    }

    //
    // BeginTransformFeedback
    //
    void CRenderDeviceDebug::BeginTransformFeedback( 
                                                    GLenum Mode 
                                                    )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::BeginTransformFeedback()", "GL_NV_transform_feedback" );
        if (Mode != GL_POINTS && Mode != GL_LINES && Mode != GL_TRIANGLES)
            throw Sys::CDeveloperException( this, "::BeginTransformFeedback() : Invalid <Mode> parameter." );

        glClearErrors();
        glBeginTransformFeedbackNV( Mode );      
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::BeginTransformFeedback() : An OpenGL error has occured." );
    }

    //
    // EndTransformFeedback
    //
    void CRenderDeviceDebug::EndTransformFeedback()
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::EndTransformFeedback()", "GL_NV_transform_feedback" );

        glClearErrors();
        glEndTransformFeedbackNV();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::EndTransformFeedback() : An OpenGL error has occured." );
    }

    //
    // DrawArrays
    //
    void CRenderDeviceDebug::DrawArrays( 
                                        GLenum Mode, GLint First, GLsizei Count 
                                        ) const
    {
        CheckPrimitiveTopology( Mode, "::DrawArrays()" );

        glClearErrors();
        glDrawArrays( Mode, First, Count );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::DrawArrays() : An OpenGL error has occured." );
    }

    //
    // DrawArraysInstanced
    //
    void CRenderDeviceDebug::DrawArraysInstanced( 
                                                 GLenum Mode, GLint First, GLsizei Count, GLsizei PrimCount 
                                                 ) const
    {
        if (!m_Extensions->EXT_draw_instanced)
            throw CExtensionException( this, "::DrawArraysInstanced()", "GL_EXT_draw_instanced" );
            
        CheckPrimitiveTopology( Mode, "::DrawArraysInstanced()" );

        glClearErrors();
        glDrawArraysInstancedEXT( Mode, First, Count, PrimCount );       
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::DrawArraysInstanced() : An OpenGL error has occured." );
    }

    //
    // DrawElements
    //
    void CRenderDeviceDebug::DrawElements( 
                                          GLenum Mode, GLint First, GLsizei Count 
                                          ) const
    {
        if (!m_IndexBuffer)
            throw Sys::CDeveloperException( this, "::DrawElements() : Index buffer not bound." );

        CheckPrimitiveTopology( Mode, "::DrawElements()" );

        glClearErrors();
        glDrawElements( Mode, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ) );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::DrawElements() : An OpenGL error has occured." );
    }

    //
    // DrawElementsInstanced
    //
    void CRenderDeviceDebug::DrawElementsInstanced( 
                                                   GLenum Mode, GLint First, GLsizei Count, GLsizei PrimCount 
                                                   ) const
    {
        if (!m_Extensions->EXT_draw_instanced)
            throw CExtensionException( this, "::DrawElementsInstanced()", "GL_EXT_draw_instanced" );
        if (!m_IndexBuffer)
            throw Sys::CDeveloperException( this, "::DrawElementsInstanced() : Index buffer not bound." );

        CheckPrimitiveTopology( Mode, "::DrawElementsInstanced()" );

        glClearErrors();
        glDrawElementsInstancedEXT( Mode, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ), PrimCount );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
           throw CException( this, Error, "::DrawElementsInstanced() : An OpenGL error has occured." );
    }

    //
    // DrawRangeElements
    //
    void CRenderDeviceDebug::DrawRangeElements( 
                                               GLenum Mode, GLint First, GLuint Start, GLuint End, GLsizei Count 
                                               ) const
    {
        if (!m_IndexBuffer)
            throw Sys::CDeveloperException( this, "::DrawRangeElements() call : Index buffer not bound." );

        CheckPrimitiveTopology( Mode, "::DrawRangeElements()" );

        glClearErrors();
        glDrawRangeElements( Mode, Start, End, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ) );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::DrawRangeElements() : An OpenGL error has occured." );
    }
}