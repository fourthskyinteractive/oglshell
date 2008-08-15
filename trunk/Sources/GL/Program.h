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

// Файл: /GL/Program.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_PROGRAM_H__
#define __GL_PROGRAM_H__

namespace GL
{                          
    //  Программа GPU на языке высокого уровня OpenGL Shading Language, OpenGL 2.0.

    class DLLAPI CShadingProgram : public IShadingProgram 
    {
    public:
        struct DLLAPI TVariableDesc
        {
            GLuint              Index;
            string              Name;
            GLint               Size;
            GLenum              Type;
        };

    public:
                            CShadingProgram     ();
                            ~CShadingProgram    ();

        //
        // RTTI
        //
                                                
        virtual string      GetClassName        () const { return "GL::CShadingProgram"; }

		//
        // Interface
        //

		void                AttachShader        ( Ptr<const CShader> Shader );
        void                DetachShader        ( Ptr<const CShader> Shader );
        void                BindAttribLocation  ( const string& Name, GLuint Index );
        void                SetActiveVarying    ( const string& Name );
        
        virtual void        Link                ();
        virtual string      GetInfoLog          () const;
        
        virtual void        GetUniform          ( const string& Name, Ptr<IUniform> *Uniform ) const;
        virtual void        GetSamplerUniform   ( const string& Name, Ptr<ISamplerUniform> *Uniform ) const;
        virtual void        GetBindableUniform  ( const string& Name, Ptr<IBindableUniform> *Uniform ) const;
        
        virtual bool        Validate            () const;
        
        void                SetFeedbackVaryings ( const vector<string>& Varyings, GLenum Mode );
        void                SetFeedbackVaryings ( const string Varyings[], GLuint NumVaryings, GLenum Mode );
        
        GLuint              GetNumAttribs       () const;
        void                GetAttribDesc       ( GLuint Index, TVariableDesc *Desc ) const;
        GLuint              GetNumUniforms      () const;
        void                GetUniformDesc      ( GLuint Index, TVariableDesc *Desc ) const;
        
    private:
        virtual void        Set                 () const;
    #ifdef CG_SDK
        virtual EShaderAPI  GetAPIType          () const;
    #endif

        //
		// Class members
		//

        GLuint              m_Program;
        map<GLint, GLenum>  m_Samplers;
    };

    #ifdef CG_SDK

    //  Программа GPU на языке высокого уровня NVIDIA Cg.
    //  http://developer.nvidia.com/object/cg_toolkit.html

    class DLLAPI CCgShadingProgram : public IShadingProgram 
    {
    public:
        struct DLLAPI TFeedbackAttribDesc
        {
            GLenum              Attrib;
            GLuint              NumComponents;
            GLuint              Index;
        };
        
    public:
                            CCgShadingProgram     ();
                            ~CCgShadingProgram    ();

        //
        // RTTI
        //
                                                
        virtual string      GetClassName        () const { return "GL::CCgShadingProgram"; }

		//
        // Interface
        //

		void                AttachShader        ( Ptr<const CCgShader> Shader );
        void                DetachShader        ( Ptr<const CCgShader> Shader );  
            
        virtual void        Link                ();
        virtual string      GetInfoLog          () const;
        
        virtual void        GetUniform          ( const string& Name, Ptr<IUniform> *Uniform ) const;
        virtual void        GetSamplerUniform   ( const string& Name, Ptr<ISamplerUniform> *Uniform ) const;
        virtual void        GetBindableUniform  ( const string& Name, Ptr<IBindableUniform> *Uniform ) const;
        
        virtual bool        Validate            () const;
        
        void                SetFeedbackAttribs  ( const vector<TFeedbackAttribDesc>& Attribs, GLenum Mode );
        void                SetFeedbackAttribs  ( const TFeedbackAttribDesc Attribs[], GLuint NumAttribs, GLenum Mode );
        
    private:
        virtual void        Set                 () const;
    #ifdef CG_SDK
        virtual EShaderAPI  GetAPIType          () const;
    #endif
        
        void                CheckAttrib         ( GLenum Attrib, GLuint Num, GLuint Min, GLuint Max ) const;

        //
		// Class members
		//

        CGprogram           m_Program;

        vector<Ptr<const CCgShader> > m_Shaders;
        
        vector<GLint>       m_FeedbackAttribs;
        GLenum              m_FeedbackMode;
    };
    
    #endif // CG_SDK
}

#endif // __GL_PROGRAM_H__