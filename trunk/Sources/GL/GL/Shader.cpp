/*
OpenGL Shell - open source C++ wrapper for use in OOP programs.
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

// Τΰιλ: /GL/GL/Shader.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Shader.h"

namespace GL
{
    string CShader::m_LastInfoLog;

    //
    // Constructor
    //
    CShader::TCaps::TCaps():
        MaxVaryingComponents( 0 ),      
        MaxBindableUniformSize( 0 ),
        MaxCombinedTextureImageUnits( 0 )
    {
    }

    //
    // Constructor
    //
    CShader::CShader( 
                     GLenum Target, const string& SourceStr, const TMacro *Defines, GLuint Count 
                     ):
        m_Shader( 0 ),
        m_Target( Target )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( this, "::CShader()", 2, 0 );
        }

        if (Target == GL_GEOMETRY_SHADER_EXT && !m_Extensions->EXT_geometry_shader4)
            throw CExtensionException( this, "::CShader()", "GL_EXT_geometry_shader4" );
        // http://download.nvidia.com/developer/GLSL/GLSL%20Release%20Notes%20for%20Release%2060.pdf
        if ((Target == GL_CG_VERTEX_SHADER_EXT || Target == GL_CG_FRAGMENT_SHADER_EXT) && !m_Extensions->EXT_Cg_shader)
            throw CExtensionException( this, "::CShader()", "GL_EXT_Cg_shader" );

        const char *TypeName = NULL;
        switch (Target)
        {
        // OpenGL 2.0
        case GL_VERTEX_SHADER:
            TypeName = "GLSL vertex";
            break;
        case GL_FRAGMENT_SHADER:
            TypeName = "GLSL fragment";
            break;
        // GL_EXT_geometry_shader4
        case GL_GEOMETRY_SHADER_EXT:
            TypeName = "GLSL geometry";
            break;
        // GL_EXT_Cg_shader
        case GL_CG_VERTEX_SHADER_EXT:
            TypeName = "Cg vertex";
            break;
        case GL_CG_FRAGMENT_SHADER_EXT:
            TypeName = "Cg fragment";
            break;
        default:
            throw Sys::CDeveloperException( this, "::CShader() : Unknown <Target> parameter." );
        }

        if (SourceStr.length() == 0)
            throw Sys::CException( 0, this, "::CShader() : Invalid <SourceStr> parameter." );

        glClearErrors();
        m_Shader = glCreateShader( Target );
        if (m_Shader == 0) 
        {                         
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CShader() : Failed to create %s shader.", TypeName );
        }

        const GLchar *Strings = static_cast<const GLchar *>( 
            SetStringMacro( SourceStr, Defines, Count ).c_str() 
        );

        glShaderSource( m_Shader, 1, &Strings, NULL );
        glCompileShader( m_Shader );

        try 
        {
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CShader() : Failed to load %s shader.", TypeName );

            GLint CompileStatus;
            glGetShaderiv( m_Shader, GL_COMPILE_STATUS, &CompileStatus );
            if (CompileStatus != GL_TRUE)
            {
                m_LastInfoLog = GetInfoLog().c_str();
    #ifdef _DEBUG
                OutputDebugLog();
    #endif
                throw Sys::CException( this, "::CShader() : Failed to compile %s shader. See program log for more details.", TypeName );
            }
        }
        catch (const Sys::CException& Ex) 
        {
            glDeleteShader( m_Shader );
            m_Shader = 0;

            throw Ex;
        }
    }

    //
    // Destructor
    //
    CShader::~CShader()
    {
        glClearErrors();
        glDeleteShader( m_Shader );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CShader() : Failed to delete shader." );
    }

    //
    // GetCaps
    //
    void CShader::GetCaps( 
                          TCaps *Caps 
                          )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( "GL::CShader", "::GetCaps()", 2, 0 );
        }

        glClearErrors();
        glGetIntegerv( GL_MAX_VARYING_COMPONENTS_EXT, &Caps->MaxVaryingComponents );
        if (m_Extensions->EXT_bindable_uniform)
            glGetIntegerv( GL_MAX_BINDABLE_UNIFORM_SIZE_EXT, &Caps->MaxBindableUniformSize );
        glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Caps->MaxCombinedTextureImageUnits );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CShader", Error, "::GetCaps() : An OpenGL error has occured." );
    }

    //
    // GetLastInfoLog
    //
    const string& CShader::GetLastInfoLog()
    {
        return m_LastInfoLog;
    }

    //
    // GetInfoLog
    //
    string CShader::GetInfoLog() const
    {
        vector<GLchar> InfoLog;
        GLint InfoLogLength;

        glClearErrors();
        glGetShaderiv( m_Shader, GL_INFO_LOG_LENGTH, &InfoLogLength );
        if (InfoLogLength > 1)
			InfoLog.resize( InfoLogLength, '\0' );
		else
			return "";

        glGetShaderInfoLog( m_Shader, InfoLogLength, NULL, &InfoLog[ 0 ] );
        GLenum Error = glGetError();
        if (Error)
            throw CException( this, Error, "::GetInfoLog() : An OpenGL error has occured." );

		if (InfoLogLength > 2)
		{
			if (InfoLog[ InfoLogLength - 2 ] == '\n') // ATI.
				InfoLog[ InfoLogLength - 2 ] = '\0';
		}

        return &InfoLog[ 0 ];
    }

    //
    // GetSourceString
    //
    string CShader::GetSourceString() const
    {
        vector<GLchar> SourceString;
        GLint SourceLength;

        glClearErrors();
        glGetShaderiv( m_Shader, GL_SHADER_SOURCE_LENGTH, &SourceLength );
        if (SourceLength > 1)
			SourceString.resize( SourceLength, '\0' );
		else
			return "";

        glGetShaderSource( m_Shader, SourceLength, NULL, &SourceString[ 0 ] );
        GLenum Error = glGetError();
        if (Error)
            throw CException( this, Error, "::GetSourceString() : An OpenGL error has occured." );

        return &SourceString[ 0 ];
    }

    //
    // SetStringMacro
    //
    const string& CShader::SetStringMacro( 
                                          const string& SourceStr, const TMacro *Defines, GLuint Count 
                                          ) const
    {
        if (!Defines)
            return SourceStr;

        const string DEFINE = "#define";
        const string VERSION = "#version";
        
        string MacroStr;

        for (GLuint i = 0; i < Count; ++i)
        {
            const TMacro& Macro = Defines[ i ];
            if (Macro.Definition.length() > 0)
                MacroStr += (DEFINE + " " + Macro.Name + " " + Macro.Definition + "\n");
            else
                MacroStr += (DEFINE + " " + Macro.Name + "\n" );
        }
        MacroStr += "\n";

        static string SourceStrEx;
      
        SourceStrEx = SourceStr;
        string::size_type Index = SourceStrEx.find( VERSION );
        if (Index == END_OF_STRING)
            SourceStrEx.insert( 0, MacroStr );
        else
        {
            Index = SourceStrEx.find( '\n', Index ); // First '\n' after #version XXX.
            if (Index != END_OF_STRING)
                SourceStrEx.insert( ++Index, "\n" + MacroStr );
        }
        
        return SourceStrEx;
    }

    #ifdef _DEBUG

    //
    // OutputDebugLog
    //
    void CShader::OutputDebugLog() const
    {
    #ifdef _MSC_VER
        OutputDebugStringA( "\n----- An GLSL compiler error has occured! -----\n\n" );
        OutputDebugStringA( m_LastInfoLog.c_str() );
        OutputDebugStringA( "\n----- End of log -----\n\n" );
    #endif
    }
    
    #endif // _DEBUG
    
    //
    // Constructor
    //
    CVertexShader::TCaps::TCaps():
        MaxVaryingComponents( 0 ),
        MaxUniformComponents( 0 ),
        MaxBindableUniforms( 0 ),
        MaxTextureImageUnits( 0 ),
        MaxAttribs( 0 )
    {
    }

    //
    // Constructor
    //
    CVertexShader::CVertexShader(
                                 const string& SourceStr, const TMacro *Defines, GLuint Count, GLboolean CgShader 
                                 ): 
        CShader( !CgShader ? GL_VERTEX_SHADER : GL_CG_VERTEX_SHADER_EXT, SourceStr, Defines, Count ) 
    {
    }

    //
    // GetCaps
    //
    void CVertexShader::GetCaps( 
                                TCaps *Caps 
                                )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( "GL::CVertexShader", "::GetCaps()", 2, 0 );
        }

        glClearErrors();
        if (m_Extensions->EXT_geometry_shader4)
            glGetIntegerv( GL_MAX_VERTEX_VARYING_COMPONENTS_EXT, &Caps->MaxVaryingComponents );
        glGetIntegerv( GL_MAX_VERTEX_UNIFORM_COMPONENTS, &Caps->MaxUniformComponents );
        if (m_Extensions->EXT_bindable_uniform)
            glGetIntegerv( GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT, &Caps->MaxBindableUniforms );
        glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &Caps->MaxTextureImageUnits ); 
        glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &Caps->MaxAttribs );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CVertexShader", Error, "::GetCaps() : An OpenGL error has occured." );
    }

    //
    // Constructor
    //
    CGeometryShader::TCaps::TCaps():
        MaxVaryingComponents( 0 ),
        MaxUniformComponents( 0 ),
        MaxBindableUniforms( 0 ),
        MaxTextureImageUnits( 0 ),
        MaxOutputVertices( 0 ),
        MaxTotalOutputComponents( 0 )
    {
    }
    
    //
    // Constructor
    //
    CGeometryShader::CGeometryShader( 
                                     const string& SourceStr, const TMacro *Defines, GLuint Count
                                     ): 
        CShader( GL_GEOMETRY_SHADER_EXT, SourceStr, Defines, Count ),

        // OpenGL Specification, Section 2.15.5, Required State.
        m_VerticesOut( 0 ),
        m_InputTopology( GL_TRIANGLES ),
        m_OutputTopology( GL_TRIANGLE_STRIP )
    {
    }

    //
    // GetCaps
    //
    void CGeometryShader::GetCaps( 
                                  TCaps *Caps 
                                  )
    {
        if (!m_Extensions->EXT_geometry_shader4)
        {
            throw CExtensionException( "GL::CGeometryCShader", "::GetCaps()", "GL_EXT_geometry_shader4" );
        }

        glClearErrors();
        glGetIntegerv( GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT, &Caps->MaxVaryingComponents );
        glGetIntegerv( GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT, &Caps->MaxUniformComponents );
        if (m_Extensions->EXT_bindable_uniform)
            glGetIntegerv( GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT, &Caps->MaxBindableUniforms );
        glGetIntegerv( GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT, &Caps->MaxTextureImageUnits );
        glGetIntegerv( GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &Caps->MaxOutputVertices );
        glGetIntegerv( GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT, &Caps->MaxTotalOutputComponents );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CGeometryShader", Error, "::GetCaps() : An OpenGL error has occured." );
    }

    //
    // SetVerticesOut
    //
    void CGeometryShader::SetVerticesOut( 
                                         GLuint VerticesOut
                                         )
    {
        m_VerticesOut = VerticesOut;
    }
     
    //
    // SetInputTopology
    //
    void CGeometryShader::SetInputTopology( 
                                           GLenum Topology 
                                           )
    {
        if (Topology != GL_POINTS && Topology != GL_LINES && Topology != GL_LINES_ADJACENCY_EXT && 
            Topology != GL_TRIANGLES && Topology != GL_TRIANGLES_ADJACENCY_EXT)
        {
            throw Sys::CDeveloperException( this, "::SetInputToplogy() : Invalid <Topology> parameter." );
        }

        m_InputTopology = Topology;
    }

    //
    // SetOutputTopology
    //
    void CGeometryShader::SetOutputTopology( 
                                            GLenum Topology
                                            )
    {
        if (Topology != GL_POINTS && Topology != GL_LINE_STRIP && Topology != GL_TRIANGLE_STRIP)
            throw Sys::CDeveloperException( this, "::SetOutputTopology() : Invalid <Topology> parameter." );

        m_OutputTopology = Topology;
    }

    //
    // Constructor
    //
    CFragmentShader::TCaps::TCaps():
        MaxUniformComponents( 0 ),
        MaxBindableUniforms( 0 ),
        MaxTextureCoords( 0 ),
        MaxTextureImageUnits( 0 )
    {
    }

    //
    // Constructor
    //
    CFragmentShader::CFragmentShader( 
                                     const string& SourceStr, const TMacro *Defines, GLuint Count, GLboolean CgShader 
                                     ): 
        CShader( !CgShader ? GL_FRAGMENT_SHADER : GL_CG_FRAGMENT_SHADER_EXT, SourceStr, Defines, Count ) 
    {
    }

    //
    // GetCaps
    //
    void CFragmentShader::GetCaps( 
                                  TCaps *Caps 
                                  )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( "GL::CFragmentShader", "::GetCaps()", 2, 0 );
        }

        glClearErrors();
        glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &Caps->MaxUniformComponents );
        if (m_Extensions->EXT_bindable_uniform)
            glGetIntegerv( GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT, &Caps->MaxBindableUniforms );
        glGetIntegerv( GL_MAX_TEXTURE_COORDS, &Caps->MaxTextureCoords );
        glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &Caps->MaxTextureImageUnits );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CFragmentShader", Error, "::GetCaps() : An OpenGL error has occured." );
    }
} 