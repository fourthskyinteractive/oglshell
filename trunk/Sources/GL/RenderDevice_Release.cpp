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

// Τΰιλ: /GL/RenderDevice_Release.cpp
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
    //
    // SetFrameBuffer
    //
    void CRenderDeviceRelease::SetFrameBuffer( 
                                              Ptr<IFrameBuffer> FrameBuffer 
                                              )
    {
        if (m_FrameBuffer)
        {
            if ((m_FrameBuffer->m_Type == IFrameBuffer::FBT_FRAMEBUFFER_OBJECT) && (FrameBuffer->m_Type == IFrameBuffer::FBT_PBUFFER))
            {
                if (m_Extensions->EXT_framebuffer_blit)
                {
                    glBindFramebufferEXT( GL_READ_FRAMEBUFFER_EXT, 0 );
                    glBindFramebufferEXT( GL_DRAW_FRAMEBUFFER_EXT, 0 ); 
                }
                else if (m_Extensions->EXT_framebuffer_object) 
                {
                    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
                }
            }
        }

        FrameBuffer->Set();

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
            else if (m_Extensions->OpenGL_2_0)
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

        if (m_FrameBuffer)
            m_FrameBuffer->m_Current = false;
        m_FrameBuffer = FrameBuffer;
        m_FrameBuffer->m_Current = true;
    }

    //
    // Blit
    //
    void CRenderDeviceRelease::Blit( 
                                    Ptr<CFrameBufferObject> DestFrameBuffer, Ptr<const CFrameBufferObject> SrcFrameBuffer, GLbitfield Mask, GLenum Filter 
                                    ) const
    {
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
    }

    //
    // CopyDepthStencilToColor
    //
    void CRenderDeviceRelease::CopyDepthStencilToColor( 
                                                       GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum Type 
                                                       ) const
    {
        glPushAttrib( GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
        glDisable( GL_STENCIL_TEST );
        glDisable( GL_DEPTH_TEST );
        glWindowPos2i( x, y );                                 
        glCopyPixels( x, y, Width, Height, Type );
        glPopAttrib();
    }

    //
    // CopyPixels
    //
    void CRenderDeviceRelease::CopyPixels( 
                                          GLint x, GLint y, GLsizei Width, GLsizei Height, GLenum InputFormat, GLenum OutputFormat, GLenum Type, 
                                          Ptr<CBuffer> Buffer 
                                          ) const
    {
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
    }

    //
    // SetTexture
    //
    void CRenderDeviceRelease::SetTexture( 
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

        GLint UnitIndex = Unit - GL_TEXTURE0;
        GLenum Target = GL_NONE;

        for (int i = 0; Targets[ i ] != 0; ++i) 
        {
            if (glIsEnabled( Targets[ i ] )) 
            {
                Target = Targets[ i ];
                break;
            }
        }

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

        m_Textures[ UnitIndex ] = Texture;
    }

    //
    // SetShadingProgram
    //
    void CRenderDeviceRelease::SetShadingProgram( 
                                                 Ptr<const IShadingProgram> Program 
                                                 )
    {
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
                    for (vector<CGprofile>::const_iterator i = Program->m_Profiles.begin(); i != Program->m_Profiles.end(); ++i)
                        cgGLEnableProfile( *i );
                }
                else
                {
                    vector<CGprofile> Disable( m_Program->m_Profiles.size() );
                
                    vector<CGprofile>::const_iterator end = set_difference( m_Program->m_Profiles.begin(), m_Program->m_Profiles.end(),
                        Program->m_Profiles.begin(), Program->m_Profiles.end(), Disable.begin() );
                    for (vector<CGprofile>::iterator i = Disable.begin(); i != end; ++i)
                        cgGLDisableProfile( *i );
                    
                    vector<CGprofile> Enable( Program->m_Profiles.size() );
                
                    end = set_difference( Program->m_Profiles.begin(), Program->m_Profiles.end(),
                        m_Program->m_Profiles.begin(), m_Program->m_Profiles.end(), Enable.begin() );
                    for (vector<CGprofile>::iterator i = Enable.begin(); i != end; ++i)
                        cgGLEnableProfile( *i );
                }
                
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
                for (vector<CGprofile>::const_iterator i = m_Program->m_Profiles.begin(); i != m_Program->m_Profiles.end(); ++i)
                    cgGLDisableProfile( *i );
            }
    #endif // CG_SDK
        }
        
        m_Program = Program;
    }
    
    //
    // SetVertexStructure
    //
    void CRenderDeviceRelease::SetVertexStructure( 
                                                  Ptr<const CVertexStructure> Struct
                                                  )
    {
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

        m_VertexStruct = Struct;
    }
        
    //
    // SetVertexBuffer
    //
    void CRenderDeviceRelease::SetVertexBuffer( 
                                               GLuint StreamIndex, Ptr<const CBuffer> Buffer, GLintptr Offset,
                                               GLsizei Stride 
                                               )
    {
        if (StreamIndex >= MAX_VERTEX_STREAMS)
            return;

        if (!Buffer)
            glBindBuffer( GL_ARRAY_BUFFER, 0 );
        else 
        { 
            if (Stride < 0)
                Stride = m_VertexStruct->m_Strides[ StreamIndex ];
                
            glBindBuffer( GL_ARRAY_BUFFER, Buffer->m_Buffer );
            for (MAP_CONST_ITERATION( GLuint, CVertexStructure::TAttrib, m_VertexStruct->m_Attributes[ StreamIndex ], i ))
                glVertexAttribPointer( i->first, i->second.Size, i->second.Type, i->second.Normalized, Stride, i->second.Offset + Offset );
        }  

        m_VertexBuffers[ StreamIndex ] = Buffer;
    }

    //
    // SetIndexBuffer
    //
    void CRenderDeviceRelease::SetIndexBuffer( 
                                              Ptr<const CIndexBuffer> Buffer 
                                              )
    {
        SetIndexBuffer( Buffer, Buffer ? Buffer->GetIndexType() : GL_NONE );
    }

    //
    // SetIndexBuffer
    //
    void CRenderDeviceRelease::SetIndexBuffer( 
                                              Ptr<const CBuffer> Buffer, GLenum IndexType 
                                              )
    {
        if (!Buffer)
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        else 
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, Buffer->m_Buffer );

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
    void CRenderDeviceRelease::SetPackPixelBuffer( 
                                                  Ptr<CBuffer> Buffer 
                                                  )
    {
        if (!Buffer)
            glBindBuffer( GL_PIXEL_PACK_BUFFER, 0 );
        else
            glBindBuffer( GL_PIXEL_PACK_BUFFER, Buffer->m_Buffer );

        m_PackBuffer = Buffer;
    }
		
    //
    // SetUnpackPixelBuffer
    //
    void CRenderDeviceRelease::SetUnpackPixelBuffer(
                                                    Ptr<const CBuffer> Buffer
                                                    )
    {
        if (!Buffer)
            glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
        else
            glBindBuffer( GL_PIXEL_UNPACK_BUFFER, Buffer->m_Buffer );

        m_UnpackBuffer = Buffer;
    }

    //
    // SetTransformFeedbackBuffer
    //
    void CRenderDeviceRelease::SetTransformFeedbackBuffer( 
                                                          GLuint Index, Ptr<CBuffer> Buffer, GLintptr Offset, 
                                                          GLsizeiptr Size
                                                          )
    {
        if (!m_Extensions->NV_transform_feedback)
            return;
            
        if (!Buffer)
            glBindBufferBaseNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, 0 );
		else
		{
		    if (Size < 0)
		        glBindBufferOffsetNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, Buffer->m_Buffer, Offset );
		    else
		        glBindBufferRangeNV( GL_TRANSFORM_FEEDBACK_BUFFER_NV, Index, Buffer->m_Buffer, Offset, Size );
		}
		
        m_FeedbackBuffer = Buffer;
    }

    //
    // BeginConditionalRender
    //
    void CRenderDeviceRelease::BeginConditionalRender( 
                                                      Ptr<const CQuery> Query, GLenum Mode 
                                                      )
    {
        if (m_Extensions->NV_conditional_render)
            glBeginConditionalRenderNV( Query->m_Query, Mode );
        else if (m_Extensions->NVX_conditional_render)
            glBeginConditionalRenderNVX( Query->m_Query );
    }

    //
    // EndConditionalRender
    //
    void CRenderDeviceRelease::EndConditionalRender()                                                              
    {
        if (m_Extensions->NV_conditional_render)
            glEndConditionalRenderNV();
        else if (m_Extensions->NVX_conditional_render)
            glEndConditionalRenderNVX();
    }

    //
    // BeginTransformFeedback
    //
    void CRenderDeviceRelease::BeginTransformFeedback( 
                                                      GLenum Mode 
                                                      )
    {
        if (m_Extensions->NV_transform_feedback)
            glBeginTransformFeedbackNV( Mode );
    }

    //
    // EndTransformFeedback
    //
    void CRenderDeviceRelease::EndTransformFeedback()
    {
        if (m_Extensions->NV_transform_feedback)
            glEndTransformFeedbackNV();
    }

    //
    // DrawArrays
    //
    void CRenderDeviceRelease::DrawArrays( 
                                          GLenum Mode, GLint First, GLsizei Count 
                                          ) const
    {
        glDrawArrays( Mode, First, Count );
    }

    //
    // DrawArraysInstanced
    //
    void CRenderDeviceRelease::DrawArraysInstanced( 
                                                   GLenum Mode, GLint First, GLsizei Count, GLsizei PrimCount 
                                                   ) const
    {
        if (m_Extensions->EXT_draw_instanced)
            glDrawArraysInstancedEXT( Mode, First, Count, PrimCount );       
    }

    //
    // DrawElements
    //
    void CRenderDeviceRelease::DrawElements( 
                                            GLenum Mode, GLint First, GLsizei Count 
                                            ) const
    {
        glDrawElements( Mode, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ) );
    }

    //
    // DrawElementsInstanced
    //
    void CRenderDeviceRelease::DrawElementsInstanced( 
                                                     GLenum Mode, GLint First, GLsizei Count, GLsizei PrimCount 
                                                     ) const
    {
        if (m_Extensions->EXT_draw_instanced)
            glDrawElementsInstancedEXT( Mode, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ), PrimCount );
    }

    //
    // DrawRangeElements
    //
    void CRenderDeviceRelease::DrawRangeElements( 
                                                 GLenum Mode, GLint First, GLuint Start, GLuint End, GLsizei Count 
                                                 ) const
    {
        glDrawRangeElements( Mode, Start, End, Count, m_IndexType, reinterpret_cast<const GLvoid *>( First * m_IndexSize ) );
    }
}