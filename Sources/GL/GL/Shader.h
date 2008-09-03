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

// Файл: /GL/GL/Shader.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_SHADER_H__
#define __GL_SHADER_H__

namespace GL
{
    //  Шейдер на языке высокого уровня OpenGL Shading Language, OpenGL 2.0.

    class DLLAPI CShader : public CObject
    {
    public:
        struct DLLAPI TMacro
        {
            string          Name;
            string          Definition;
        };

        struct DLLAPI TCaps 
        {
                            TCaps               ();

            GLint           MaxVaryingComponents;
            GLint           MaxBindableUniformSize;
            GLint           MaxCombinedTextureImageUnits;
        };

        friend              CShadingProgram;

    public:                          
                            ~CShader            ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CShader"; }

        //
        // Interface
        //

        static void         GetCaps             ( TCaps *Caps );
        static CSTRING&     GetLastInfoLog      (); 

        string              GetInfoLog          () const;
        string              GetSourceString     () const;

    protected:
                            CShader             ( GLenum Target, const string& SourceStr, const TMacro *Defines, GLuint Count );

    private:
        const string&       SetStringMacro      ( const string& SourceStr, const TMacro *Defines, GLuint Count ) const;
    #ifdef _DEBUG
        void                OutputDebugLog      () const;
    #endif
    
		//
		// Class members
		//

        static string       m_LastInfoLog;

        GLuint              m_Shader;
        GLenum              m_Target;
    };

    //  Вершинный шейдер.

    class DLLAPI CVertexShader : public CShader
    {
    public:
        struct DLLAPI TCaps 
        {
                            TCaps               ();

                                        
           GLint            MaxVaryingComponents; // GL_EXT_geometry_shader4 
           GLint            MaxUniformComponents;                                     
           GLint            MaxBindableUniforms;
           GLint            MaxTextureImageUnits;
           GLint            MaxAttribs; 
       };

    public:
                            CVertexShader       ( const string& SourceStr, const TMacro *Defines = NULL, GLuint Count = 0, 
                                                    GLboolean CgShader = GL_FALSE );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CVertexShader"; }

        //
        // Interface
        //
                                        
        static void         GetCaps             ( TCaps *Caps );
    };

    //  Геометрический шейдер, расширение GL_EXT_geometry_shader4.
    //  http://www.opengl.org/registry/specs/EXT/geometry_shader4.txt

    class DLLAPI CGeometryShader : public CShader
    {
    public:
        struct DLLAPI TCaps 
        {
                            TCaps               ();

            GLint           MaxVaryingComponents;
            GLint           MaxUniformComponents;
            GLint           MaxBindableUniforms;
            GLint           MaxTextureImageUnits;
            GLint           MaxOutputVertices;
            GLint           MaxTotalOutputComponents;
        };

        friend              CShadingProgram;

    public:                         
                            CGeometryShader     ( const string& SourceStr, const TMacro *Defines = NULL, GLuint Count = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CGeometryShader"; }

        //
        // Interface
        //

        static void         GetCaps             ( TCaps *Caps );

        void                SetVerticesOut      ( GLuint VerticesOut );
        void                SetInputTopology    ( GLenum Topology );
        void                SetOutputTopology   ( GLenum Topology );

    private:

        //
		// Class members
		//

        GLuint              m_VerticesOut;
        GLenum              m_InputTopology;
        GLenum              m_OutputTopology;
    };

    //  Фрагментный шейдер.

    class DLLAPI CFragmentShader : public CShader
    {
    public:
        struct DLLAPI TCaps 
        {
                            TCaps               ();

            GLint           MaxUniformComponents;
            GLint           MaxBindableUniforms;
            GLint           MaxTextureCoords;
            GLint           MaxTextureImageUnits;
        };                                  

    public:
                            CFragmentShader     ( const string& SourceStr, const TMacro *Defines = NULL, GLuint Count = 0, 
                                                    GLboolean CgShader = GL_FALSE );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CFragmentShader"; }

        //
        // Interface
        //

        static void         GetCaps             ( TCaps *Caps );
    };
} 

#endif // __GL_SHADER_H__