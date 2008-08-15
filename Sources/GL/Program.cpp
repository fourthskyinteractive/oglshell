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

// Файл: /GL/Program.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Program.h"
#include "Shader.h"
#include "Uniform.h"

namespace GL
{
    //
    // Constructor
    //
    CShadingProgram::CShadingProgram():
        m_Program( 0 )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( this, "::CShadingProgram()", 2, 0 );
        }

        m_Program = glCreateProgram();
        if (!m_Program)
        {
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CShadingProgram() : Failed to create GLSL program." );
            else
                throw Sys::CException( this, "::CShadingProgram() : Failed to create GLSL program." ); 
        }
    }

    //
    // Destructor
    //
    CShadingProgram::~CShadingProgram()
    {
        glDeleteProgram( m_Program );   
    }

    //
    // AttachShader
    //
    void CShadingProgram::AttachShader( 
                                       Ptr<const CShader> Shader
                                       )
    {
        glClearErrors();
        glAttachShader( m_Program, Shader->m_Shader );
        
        if (Shader->m_Target == GL_GEOMETRY_SHADER_EXT)
        {
            Ptr<const CGeometryShader> GeometryShader = Shader.CastTo<const CGeometryShader>();

            glProgramParameteriEXT( m_Program, GL_GEOMETRY_VERTICES_OUT_EXT, GeometryShader->m_VerticesOut );
            glProgramParameteriEXT( m_Program, GL_GEOMETRY_INPUT_TYPE_EXT, GeometryShader->m_InputType );
            glProgramParameteriEXT( m_Program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GeometryShader->m_OutputType );
        }
        
		GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::AttachShader() : An OpenGL error has occured." ); 
    }

    //
    // DetachShader
    //
    void CShadingProgram::DetachShader( 
                                       Ptr<const CShader> Shader
                                       )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERR_METHOD_NOT_IMPLEMENTED, 
            "::DetachShader() : This method is not implemented, and should not be used." );
        
        /*
        glClearErrors();
        glDetachShader( m_Program, Shader->m_Shader );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::DetachShader() : Failed to detach shader from GLSL program." );
        */
    }

    //
    // BindAttribLocation
    //
    void CShadingProgram::BindAttribLocation( 
                                             const string& Name, 
                                             GLuint Index 
                                             )
    {
        glClearErrors();
        glBindAttribLocation( m_Program, Index, Name.c_str() );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::BindAttribLocation() : Failed to bind \"%s\" to generic vertex attribute %d.", Name.c_str(), Index );
    }

    //
    // SetActiveVarying
    //
    void CShadingProgram::SetActiveVarying( 
                                           const string& Name 
                                           )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw Sys::CDeveloperException( this, "Invalid ::SetActiveVarying() call.\nExtension GL_NV_transform_feedback unsupported." );

        glClearErrors();
        glActiveVaryingNV( m_Program, Name.c_str() );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetActiveVarying() : Failed to force the linker to mark a varying variable \"%s\" as active.", Name.c_str() );
    }
    
    //
    // Link
    //
    void CShadingProgram::Link()
    {    
        m_UniformCache.clear();
        m_SamplerUniformCache.clear();
        m_BindableUniformCache.clear();
    
        m_Samplers.clear();
        
        glLinkProgram( m_Program );
        GLint LinkStatus;
        glGetProgramiv( m_Program, GL_LINK_STATUS, &LinkStatus );
        if (LinkStatus != GL_TRUE)
        {
            m_LastInfoLog = GetInfoLog().c_str();
            throw Sys::CException( this, "::Link() : Failed to link GLSL program. See program log for more details." );
        }

        GLint ActiveUniforms;
        GLint MaxLength;
        
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORMS, &ActiveUniforms );
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &MaxLength );

        vector<GLchar> Name( MaxLength, '\0' );
        GLenum Unit = GL_TEXTURE0;

        // Получаем описание всех юниформов, и если очередной юниформ является самплером,
        // резервируем для него текстурный блок и заносим его и местоположение юниформа в список.

        for (int i = 0; i < ActiveUniforms; ++i)
        {
            GLint Size;
            GLenum Type;
            //GLint Location;
            
            glGetActiveUniform( m_Program, i, MaxLength, NULL, &Size, &Type, &Name[ 0 ] );
            switch (Type)
            {
            // OpenGL 2.0
            case GL_SAMPLER_1D:
            case GL_SAMPLER_2D:
            case GL_SAMPLER_3D:
            case GL_SAMPLER_CUBE:
            case GL_SAMPLER_1D_SHADOW:
            case GL_SAMPLER_2D_SHADOW:
            // GL_ARB_shader_objects/GL_ARB_texture_rectangle
            case GL_SAMPLER_2D_RECT_ARB:
            case GL_SAMPLER_2D_RECT_SHADOW_ARB:
            // GL_EXT_gpu_shader4
            case GL_SAMPLER_1D_ARRAY_EXT:  
            case GL_SAMPLER_2D_ARRAY_EXT:  
            //case GL_SAMPLER_BUFFER_EXT: ?
            case GL_SAMPLER_1D_ARRAY_SHADOW_EXT: 
            case GL_SAMPLER_2D_ARRAY_SHADOW_EXT:
            case GL_SAMPLER_CUBE_SHADOW_EXT:
            case GL_INT_SAMPLER_1D_EXT:  
            case GL_INT_SAMPLER_2D_EXT:
            case GL_INT_SAMPLER_3D_EXT:
            case GL_INT_SAMPLER_CUBE_EXT:
            case GL_INT_SAMPLER_2D_RECT_EXT:
            case GL_INT_SAMPLER_1D_ARRAY_EXT:
            case GL_INT_SAMPLER_2D_ARRAY_EXT:
            //case GL_INT_SAMPLER_BUFFER_EXT: ?
            case GL_UNSIGNED_INT_SAMPLER_1D_EXT:
            case GL_UNSIGNED_INT_SAMPLER_2D_EXT:
            case GL_UNSIGNED_INT_SAMPLER_3D_EXT:
            case GL_UNSIGNED_INT_SAMPLER_CUBE_EXT:
            case GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT:
            case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT:
            case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT:
            //case GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT: ?
                if (Unit - GL_TEXTURE0 == m_Caps.MaxTextureImageUnits)
                    throw Sys::CException( this, "::Link() : Too many active uniforms of sampler type.\nNumber of samplers exceed implementation-dependent constant GL_MAX_TEXTURE_IMAGE_UNITS." );
                {
                    GLint Location = glGetUniformLocation( m_Program, &Name[ 0 ] );
                    m_Samplers[ Location ] = Unit++;
                }
                break;
            }
        }
    }

    //
    // GetInfoLog
    //
    string CShadingProgram::GetInfoLog() const
    {
        vector<GLchar> InfoLog;
        GLint InfoLogLength;

        glClearErrors();
        glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &InfoLogLength );
        if (InfoLogLength > 1)
			InfoLog.resize( InfoLogLength, '\0' );
		else
			return "";

        glGetProgramInfoLog( m_Program, InfoLogLength, NULL, &InfoLog[0] );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetInfoLog() : An OpenGL error has occured." );
		
		if (InfoLogLength > 2)
		{
			if (InfoLog[ InfoLogLength - 2 ] == '\n') // ATI.
				InfoLog[ InfoLogLength - 2 ] = '\0';
		}

        return &InfoLog[ 0 ];
    }

    //
    // SetFeedbackVaryings
    // Called after program linking!
    //
    void CShadingProgram::SetFeedbackVaryings( 
                                              const vector<string>& Varyings, 
                                              GLenum Mode 
                                              )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::SetFeedbackVaryings()", "GL_NV_transform_feedback." );
        
        if (Varyings.empty())
            throw Sys::CDeveloperException( this, "::SetFeedbackVaryings() : Invalid <Varyings> parameter." );
        if (Mode != GL_INTERLEAVED_ATTRIBS_NV && Mode != GL_SEPARATE_ATTRIBS_NV)
            throw Sys::CDeveloperException( this, "::SetFeedbackVaryings() : Invalid <Mode> parameter." );

        vector<GLint> Locations;

        glClearErrors();
        for (int i = 0; i < static_cast<int>( Varyings.size() ); ++i) 
        {
            GLint Location = glGetVaryingLocationNV( m_Program, Varyings[ i ].c_str() );
            if (Location == -1)
                throw Sys::CException( this, "::SetFeedbackVaryings() : Failed to determine location of varying \"%s\".", Varyings[ i ].c_str() );
                       
            Locations.push_back( Location );
        }
        glTransformFeedbackVaryingsNV( m_Program, static_cast<GLsizei>( Locations.size() ), &Locations[ 0 ], Mode );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetFeedbackVaryings() : An OpenGL error has occured.." );
    }
    
    //
    // SetFeedbackVaryings
    //
    void CShadingProgram::SetFeedbackVaryings( 
                                              const string Varyings[], GLuint NumVaryings, 
                                              GLenum Mode 
                                              )
    {
        if (!m_Extensions->NV_transform_feedback)
            throw CExtensionException( this, "::SetFeedbackVaryings()", "GL_NV_transform_feedback." );
            
        if (NumVaryings == 0) // FIXME
            throw Sys::CDeveloperException( this, "::SetFeedbackVaryings() : Invalid <NumVaryings> parameter." );
            
        vector<string> Varyings2;
        
        for (GLuint i = 0; i < NumVaryings; ++i)
            Varyings2.push_back( Varyings[ i ] );
            
        SetFeedbackVaryings( Varyings2, Mode );
    }
    
    //
    // GetNumAttribs
    //
    GLuint CShadingProgram::GetNumAttribs() const
    {
        glClearErrors();
        GLint NumAttribs;
        glGetProgramiv( m_Program, GL_ACTIVE_ATTRIBUTES, &NumAttribs );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetNumAttribs() : An OpenGL error has occured." );

        return NumAttribs;
    }
        
    //
    // GetAttribDesc
    //
    void CShadingProgram::GetAttribDesc( 
                                        GLuint Index, 
                                        TVariableDesc *Desc 
                                        ) const
    {
        GLint MaxLength;
        glGetProgramiv( m_Program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &MaxLength );

        vector<GLchar> Name( MaxLength, '\0' );

        glClearErrors();
        glGetActiveAttrib( m_Program, Index, MaxLength, NULL, &Desc->Size, &Desc->Type, &Name[ 0 ] );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetAttribDesc() : An OpenGL error has occured." );

        Desc->Index = Index;
        Desc->Name = &Name[ 0 ];
    }

    //
    // GetNumUniforms
    //
    GLuint CShadingProgram::GetNumUniforms() const
    {
        glClearErrors();
        GLint NumUniforms;
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORMS, &NumUniforms );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetNumUniforms() : An OpenGL error has occured." );

        return NumUniforms;
    }
        
    //
    // GetUniformDesc
    //
    void CShadingProgram::GetUniformDesc( 
                                         GLuint Index, 
                                         TVariableDesc *Desc 
                                         ) const
    {
        GLint MaxLength;
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &MaxLength );

        vector<GLchar> Name( MaxLength, '\0' );

        glClearErrors();
        glGetActiveUniform( m_Program, Index, MaxLength, NULL, &Desc->Size, &Desc->Type, &Name[ 0 ] );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetUniformDesc() : An OpenGL error has occured." );

        Desc->Index = Index;
        Desc->Name = &Name[ 0 ];
    }

    //
    // GetUniform
    //
    void CShadingProgram::GetUniform( 
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
        
        GLint Location = glGetUniformLocation( m_Program, Name.c_str() );
        if (Location == -1)
        {
            *Uniform = NULL;
            throw Sys::CDeveloperException( this, "::GetUniform() : Failed to determine location of uniform \"%s\".", Name.c_str() );
        }

        map<GLint, GLenum>::const_iterator Sampler = m_Samplers.find( Location );
        if (Sampler != m_Samplers.end())
            throw Sys::CDeveloperException( this, "::GetUniform() : Uniform \"%s\" is a sampler.\nCall ::GetSamplerUniform() instead.", Name.c_str() );

    #ifdef _DEBUG
        // В отладочной версии юниформы осуществляет проверку типов, поэтому определяем тип юниформа
        // и передаём его в конструктор класса.
        
        GLint ActiveUniforms;
        GLint MaxLength;
        
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORMS, &ActiveUniforms );
        glGetProgramiv( m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &MaxLength );

        GLint Size;
        GLenum Type;
        vector<GLchar> UniformName( MaxLength, '\0' );

        for (int i = 0; i < ActiveUniforms; ++i)
        {
            Size = -1;
            Type = GL_NONE;

            glGetActiveUniform( m_Program, i, MaxLength, NULL, &Size, &Type, &UniformName[ 0 ] );
            if (strcmp( Name.c_str(), &UniformName[ 0 ] ) == 0)
                break;
        }

        *Uniform = new CUniform( Name, Location, Type );
    #else
        *Uniform = new CUniform( Name, Location );
    #endif // _DEBUG

        m_UniformCache[ Name ] = *Uniform;
    }
    
    //
    // GetSamplerUniform
    //
    void CShadingProgram::GetSamplerUniform( 
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
        
        GLint Location = glGetUniformLocation( m_Program, Name.c_str() );
        if (Location == -1)
        {
            *Uniform = NULL;
            throw Sys::CDeveloperException( this, "::GetSamplerUniform() : Failed to determine location of uniform \"%s\".", Name.c_str() );
        }

        map<GLint, GLenum>::const_iterator Sampler = m_Samplers.find( Location );
        if (Sampler == m_Samplers.end())
            throw Sys::CDeveloperException( this, "::GetSamplerUniform() : Uniform \"%s\" is not a sampler.", Name.c_str() );

        *Uniform = new CSamplerUniform( Name, Location, Sampler->second ); // Unit
        m_SamplerUniformCache[ Name ] = *Uniform;

    }

    //
    // GetBindableUniform
    //
    void CShadingProgram::GetBindableUniform( 
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
            
        GLint Location = glGetUniformLocation( m_Program, Name.c_str() );
        if (Location == -1)
        {
            *Uniform = NULL;
            throw Sys::CDeveloperException( this, "::GetBindableUniform() : Failed to determine location of uniform \"%s\".", Name.c_str() );
        }

        *Uniform = new CBindableUniform( Name, m_Program, Location );
        m_BindableUniformCache[ Name ] = *Uniform;
    }

    //
    // Validate
    //
    bool CShadingProgram::Validate() const
    {
        glValidateProgram( m_Program );

        GLint ValidateStatus;
        glGetProgramiv( m_Program, GL_VALIDATE_STATUS, &ValidateStatus );
        
        return ValidateStatus == GL_TRUE;
    }
    
    //
    // Set
    //
    void CShadingProgram::Set() const
    {
        glUseProgram( m_Program );
    }
    
    #ifdef CG_SDK
    //
    // GetAPIType
    //
    IShadingProgram::EShaderAPI CShadingProgram::GetAPIType() const
    {
        return SA_GLSL;
    }
    
    #endif // CG_SDK
}