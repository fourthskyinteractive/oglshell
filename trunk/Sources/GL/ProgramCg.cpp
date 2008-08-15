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

// Τΰιλ: /GL/ProgramCg.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#ifdef CG_SDK

#include "Program.h"
#include "ShaderCg.h"
#include "ContextCg.h"
#include "Uniform.h"

namespace GL
{
    //
    // Constructor
    //
    CCgShadingProgram::CCgShadingProgram():
        m_Program( NULL ),
        
        m_FeedbackMode( GL_NONE )
    {
        CCgContext::AddRef();
    }
                  
    //
    // Destructor
    //
    CCgShadingProgram::~CCgShadingProgram()
    {
        if (cgIsProgram( m_Program ))
            cgDestroyProgram( m_Program );

        CCgContext::Release();
    }

    //
    // AttachShader
    //
    void CCgShadingProgram::AttachShader( 
                                         Ptr<const CCgShader> Shader 
                                         )
    {
        m_Shaders.push_back( Shader );
        m_Profiles.push_back( Shader->GetProfile() );
    }
        
    //
    // DetachShader
    //
    void CCgShadingProgram::DetachShader( 
                                         Ptr<const CCgShader> Shader 
                                         )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERR_METHOD_NOT_IMPLEMENTED, 
            "::DetachShader() : This method is not implemented, and should not be used." );
    }
    
    //
    // Link
    //
    void CCgShadingProgram::Link()
    {
        m_UniformCache.clear();
        m_SamplerUniformCache.clear();
        m_BindableUniformCache.clear();
    
        //m_Samplers.clear();

        if (cgIsProgram( m_Program ))
            cgDestroyProgram( m_Program );
            
        if (m_Shaders.size() == 1)
            m_Program = m_Shaders[ 0 ]->m_Program;
        else
        {
            vector<CGprogram> Programs;

            for (VECTOR_CONST_ITERATION( Ptr<const CCgShader>, m_Shaders, i ))
                Programs.push_back( (*i)->m_Program );
                
            m_Program = cgCombinePrograms( static_cast<int>( Programs.size() ), &Programs[ 0 ] );
            CGerror Error = cgGetError();
            if (Error != CG_NO_ERROR)
                throw CCgException( this, Error, "::Link() : Failed to combine Cg program." );
        }

        cgGLLoadProgram( m_Program );
        CGerror Error = cgGetError();
        if (Error != CG_NO_ERROR)
            throw CCgException( this, Error, "::Link() : Failed to load Cg program. Program may fails to load for any reason." );

         sort( m_Profiles.begin(), m_Profiles.end() );
    }

    //
    // GetInfoLog
    //
    string CCgShadingProgram::GetInfoLog() const
    {
        return "";
    }
      
    //
    // SetFeedbackAttribs
    //
    void CCgShadingProgram::SetFeedbackAttribs( 
                                               const vector<TFeedbackAttribDesc>& Attribs, GLenum Mode 
                                               )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::SetFeedbackAttribs()", "GL_NV_transform_feedback" );
            
        if (Attribs.empty())
            throw Sys::CDeveloperException( this, "::SetFeedbackAttribs() : Invalid <Attribs> parameter." );
        if (Mode != GL_INTERLEAVED_ATTRIBS_NV && Mode != GL_SEPARATE_ATTRIBS_NV)
            throw Sys::CDeveloperException( this, "::SetFeedbackAttribs() : Invalid <Mode> parameter." );
            
        m_FeedbackAttribs.clear();
        
        for (VECTOR_CONST_ITERATION( TFeedbackAttribDesc, Attribs, i ))
        {
            switch (i->Attrib)
            {
            case GL_POSITION: 
            case GL_PRIMARY_COLOR: 
            case GL_SECONDARY_COLOR_NV:  
            case GL_BACK_PRIMARY_COLOR_NV:
            case GL_BACK_SECONDARY_COLOR_NV:
                CheckAttrib( i->Attrib, i->NumComponents, 1, 4 );
                break;   
            case GL_FOG_COORDINATE:
            case GL_POINT_SIZE:
                CheckAttrib( i->Attrib, i->NumComponents, 1, 1 );
                break;        
            case GL_TEXTURE_COORD_NV:
                CheckAttrib( i->Attrib, i->NumComponents, 1, 4 );
                break;   
            case GL_CLIP_DISTANCE_NV:
            case GL_VERTEX_ID_NV: 
            case GL_PRIMITIVE_ID_NV:
                CheckAttrib( i->Attrib, i->NumComponents, 1, 1 );
                break;     
            case GL_GENERIC_ATTRIB_NV:
                CheckAttrib( i->Attrib, i->NumComponents, 1, 4 );
                break;      
            //case GL_LAYER_NV:
            //    CheckAttrib( i->Attrib, i->NumComponents, 1, 1 );
            //    break;   
                     
            default:
                throw Sys::CDeveloperException( this, "::SetFeedbackAttribs() : Invalid <Attrib> field of feedback attribute description." );
            }
            
            m_FeedbackAttribs.push_back( static_cast<GLint>( i->Attrib ) );
            m_FeedbackAttribs.push_back( static_cast<GLint>( i->NumComponents ) );
            m_FeedbackAttribs.push_back( static_cast<GLint>( i->Index ) );
        }
        
        m_FeedbackMode = Mode;  
    }
      
    //
    // SetFeedbackAttribs
    //  
    void CCgShadingProgram::SetFeedbackAttribs( 
                                               const TFeedbackAttribDesc Attribs[], GLuint NumAttribs, GLenum Mode 
                                               )
    {
        if (NumAttribs == 0)
        {
            if (Attribs != NULL)
                throw Sys::CDeveloperException( this, "::SetFeedbackAttribs() : Invalid <NumAttribs> parameter." );
            else
            {
                m_FeedbackAttribs.clear();
                m_FeedbackMode = GL_NONE;
            }
        }
        else
        {
            vector<TFeedbackAttribDesc> Attribs2;
        
            for (GLuint i = 0; i < NumAttribs; ++i)
                Attribs2.push_back( Attribs[ i ] );
                
            SetFeedbackAttribs( Attribs2, Mode );
        }
    }
          
    //
    // GetUniform
    //
    void CCgShadingProgram::GetUniform( 
                                       const string& Name, 
                                       Ptr<IUniform> *Uniform 
                                       ) const
    {
        map<string, Ptr<IUniform> >::const_iterator i = m_UniformCache.find( Name );
        if (i != m_UniformCache.end())
        {
            *Uniform = i->second;
            return;
        }
        
        CGparameter Parameter = cgGetNamedParameter( m_Program, Name.c_str() );
        if (!Parameter)
        {
            *Uniform = NULL;
            throw Sys::CException( this, "::GetUniform() : Failed to get a program parameter by name \"%s\".", Name.c_str() );
        }

        *Uniform = new CCgUniform( Name, Parameter );
        m_UniformCache[ Name ] = *Uniform;
    }

    //
    // GetSamplerUniform
    //
    void CCgShadingProgram::GetSamplerUniform( 
                                              const string& Name, 
                                              Ptr<ISamplerUniform> *Uniform 
                                              ) const
    {
        map<string, Ptr<ISamplerUniform> >::const_iterator i = m_SamplerUniformCache.find( Name );
        if (i != m_SamplerUniformCache.end())
        {
            *Uniform = i->second;
            return;
        }

        CGparameter Parameter = cgGetNamedParameter( m_Program, Name.c_str() );
        if (!Parameter)
        {
            *Uniform = NULL;
            throw Sys::CException( this, "::GetSamplerUniform() : Failed to get a program parameter by name \"%s\".", Name.c_str() );
        }

        *Uniform = new CCgSamplerUniform( Name, Parameter );
        m_SamplerUniformCache[ Name ] = *Uniform;
    }

    //
    // GetBindableUniform
    //
    void CCgShadingProgram::GetBindableUniform( 
                                               const string& Name, 
                                               Ptr<IBindableUniform> *Uniform 
                                               ) const
    {
        if (!m_Extensions->EXT_bindable_uniform)
            throw CExtensionException( this, "::GetBindableUniform()", "GL_EXT_bindable_uniform" );
            
        map<string, Ptr<IBindableUniform> >::const_iterator i = m_BindableUniformCache.find( Name );
        if (i != m_BindableUniformCache.end())
        {
            *Uniform = i->second;
            return;
        }

        CGparameter Parameter = cgGetNamedParameter( m_Program, Name.c_str() );
        if (!Parameter)
        {
            *Uniform = NULL;
            throw Sys::CException( this, "::GetBindableUniform() : Failed to get a program parameter by name \"%s\".", Name.c_str() );
        }

        *Uniform = new CCgBindableUniform( Name, m_Program, Parameter );
        m_BindableUniformCache[ Name ] = *Uniform;
    }
        
    //
    // Validate
    //
    bool CCgShadingProgram::Validate() const
    {
        return true;
    }
    
    //
    // Set
    //
    void CCgShadingProgram::Set() const
    {
        cgGLBindProgram( m_Program );
    #ifdef _DEBUG
        CGerror Error = cgGetError();
        if (Error != CG_NO_ERROR)
            throw CCgException( this, Error, "::Set() : A Cg error has occured." );
    #endif
        
        if (!m_FeedbackAttribs.empty())
        {
    #ifdef _DEBUG
            glClearErrors();
    #endif
            glTransformFeedbackAttribsNV( static_cast<GLsizei>( m_FeedbackAttribs.size() / 3 ), &m_FeedbackAttribs[ 0 ], m_FeedbackMode );
    #ifdef _DEBUG
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::Set() : An OpenGL error has occured." );
    #endif
        }
    }
    
    #ifdef CG_SDK
    //
    // GetAPIType
    //
    IShadingProgram::EShaderAPI CCgShadingProgram::GetAPIType() const
    {
        return SA_CG;
    }
    
    #endif // CG_SDK
    
    //
    // CheckAttrib
    //
    void CCgShadingProgram::CheckAttrib( 
                                        GLenum Attrib, GLuint Num, GLuint Min, GLuint Max
                                        ) const
    {
        struct
        {
            GLenum Attrib;
            const char *Name;
        } 
        static const Attribs[] =
        {
            GL_POSITION, "GL_POSITION",
            GL_PRIMARY_COLOR, "GL_PRIMARY_COLOR",   
            GL_SECONDARY_COLOR_NV, "GL_SECONDARY_COLOR_NV",    
            GL_BACK_PRIMARY_COLOR_NV, "GL_BACK_PRIMARY_COLOR_NV",   
            GL_BACK_SECONDARY_COLOR_NV, "GL_BACK_SECONDARY_COLOR_NV",  
            GL_FOG_COORDINATE, "GL_FOG_COORDINATE",    
            GL_POINT_SIZE, "GL_POINT_SIZE",     
            GL_TEXTURE_COORD_NV, "GL_TEXTURE_COORD_NV",   
            GL_CLIP_DISTANCE_NV, "GL_CLIP_DISTANCE_NV",  
            GL_VERTEX_ID_NV, "GL_VERTEX_ID_NV",        
            GL_PRIMITIVE_ID_NV, "GL_PRIMITIVE_ID_NV",    
            GL_GENERIC_ATTRIB_NV, "GL_GENERIC_ATTRIB_NV",   
            //GL_LAYER_NV, "GL_LAYER_NV",
            GL_NONE, NULL   
        };
        
        if (Num >= Min && Num <= Max)
            return;
        
        int i;
        for (i = 0; Attribs[ i ].Attrib != GL_NONE; ++i)
        {
            if (Attrib == Attribs[ i ].Attrib)
                break;
        }
            
        throw Sys::CDeveloperException( this, "::SetFeedbackAttribs() : Invalid number of components to be fed back for attribute %s.", 
            Attribs[ i ].Name );
    }
}

#endif // CG_SDK