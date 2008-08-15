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

// Файл: /GL/ShaderCg.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_SHADER_CG_H__
#define __GL_SHADER_CG_H__

#ifdef CG_SDK

namespace GL
{
	//  Шейдер на языке высокого уровня Cg. Для использования требуется NVIDIA Cg Run-Time Library.
    //  http://developer.nvidia.com/object/cg_toolkit.html

	class DLLAPI CCgShader : public CObject
	{
        friend              CCgShadingProgram;

	public:
                            ~CCgShader          ();

		//
		// Interface
		//

        static CSTRING&     GetLastListing      ();

        CGprofile           GetProfile          () const;
        string              GetString           ( CGenum Type ) const;

    protected:
                            CCgShader           ( CGenum SourceType, const string& SourceStr, CGprofile Profile, CGGLenum ProfileClass, 
                                                    const string& Entry, const string& Arguments );

	private:
        const char*         GetProfileName      ( CGprofile Profile ) const;
        
        void                CheckDomain         ( CGprofile Profile, CGGLenum ProfileClass ) const;

    private:  

		//
		// Class members
		//

        static string       m_LastListing;

        CGprogram           m_Program;
	};

	//  Вершинный шейдер Cg.

	class DLLAPI CCgVertexShader : public CCgShader
	{
	public:
                            CCgVertexShader     ( CGenum SourceType, const string& SourceStr, 
                                                    const string& Entry = "", const string& Arguments = "" );
                            CCgVertexShader     ( CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                                    const string& Entry = "", const string& Arguments = "" );

        //
        // RTTI
        //
                            
        virtual string      GetClassName        () const { return "GL::CCgVertexShader"; }
	};

    //  Геометрический шейдер Cg.

    class DLLAPI CCgGeometryShader : public CCgShader
    {
    public:
                            CCgGeometryShader   ( CGenum SourceType, const string& SourceStr,  
                                                    const string& Entry = "", const string& Arguments = "" );
                            CCgGeometryShader   ( CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                                    const string& Entry = "", const string& Arguments = "" );

        //
        // RTTI
        //
                            
        virtual string      GetClassName        () const { return "GL::CCgGeometryShader"; }
    };

    //  Фрагментный шейдер Cg.

	class DLLAPI CCgFragmentShader : public CCgShader
	{
	public:
                            CCgFragmentShader   ( CGenum SourceType, const string& SourceStr, 
                                                    const string& Entry = "", const string& Arguments = "" );
                            CCgFragmentShader   ( CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                                    const string& Entry = "", const string& Arguments = "" );

        //
        // RTTI
        //
                            
        virtual string      GetClassName        () const { return "GL::CCgFragmentShader"; }
	};
}

#endif // CG_SDK

#endif // __GL_SHADER_CG_H__