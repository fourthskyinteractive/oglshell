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

// Τΰιλ: /GL/GL/ShaderCg.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#ifdef CG_SDK

#include "ShaderCg.h"
#include "ContextCg.h"

namespace GL
{
    string CCgShader::m_LastListing;
    
    //
    // Constructor
    //
    CCgShader::CCgShader( 
                         CGenum SourceType, const string& SourceStr, CGprofile Profile, CGGLenum ProfileClass,
                         const string& Entry, const string& Arguments
                         ):
        m_Program( NULL )
    {
        if (SourceType != CG_SOURCE && SourceType != CG_OBJECT)
            throw Sys::CDeveloperException( "GL::CCgShader", "::CCgShader() : Invalid <SourceType> parameter." );
        if (SourceStr.length() == 0)
            throw Sys::CDeveloperException( "GL::CCgShader", "::CCgShader() : Invalid <SourceStr> parameter." );

        CCgContext::AddRef();

        if (Profile == CG_PROFILE_UNKNOWN)
            Profile = cgGLGetLatestProfile( ProfileClass );
        else 
        {
            CheckDomain( Profile, ProfileClass );
            if (cgGLIsProfileSupported( Profile ) == CG_FALSE)
            {
                const char *ProfileName = GetProfileName( Profile );
                if (!ProfileName)
                    throw Sys::CException( 0, "GL::CCgShader", "::CCgShader() : Unknown shader profile." );
                else
                {
                    throw Sys::CException( 0, "GL::CCgShader", "::CCgShader() : Profile %s unsupported.\n"
                        "A profile may not be supported if required OpenGL extension is not available.", ProfileName );
                }
            }
        }

        try
        {
            const char *TypeName = NULL;
            switch (ProfileClass)
            {
            case CG_GL_VERTEX:
                TypeName = "vertex";
                break;
            case CG_GL_GEOMETRY:
                TypeName = "geometry";
                break;
            case CG_GL_FRAGMENT:
                TypeName = "fragment";
                break;
            }

            const char *Args[ 2 ] =
            {
                Arguments.c_str(),
                NULL
            };
            
            m_Program = cgCreateProgram( CCgContext::GetContext(), SourceType, SourceStr.c_str(), Profile, 
                (Entry.length() == 0) ? NULL : Entry.c_str(), (Arguments.length() == 0) ? NULL : Args );
            if (!m_Program)
            {
                m_LastListing = CCgContext::GetLastListing();
    #ifdef _DEBUG
                OutputDebugLog();
    #endif
                throw CCgException( "GL::CCgShader", cgGetError(), "::CCgShader() : Failed to create Cg %s shader.\nSee program log for more details.", TypeName );
            }

            cgCompileProgram( m_Program );
            CGerror Error = cgGetError();
            if (Error != CG_NO_ERROR)
            {
                m_LastListing = CCgContext::GetLastListing();
    #ifdef _DEBUG
                OutputDebugLog();
    #endif
                throw CCgException( "GL::CCgShader", Error, "::CCgShader() : Failed to compile Cg %s shader.\nSee program log for more details.", TypeName );
            }
        }
        catch (const Sys::CException& Ex)
        {
            if (cgIsProgram( m_Program ))
                cgDestroyProgram( m_Program );

            CCgContext::Release();

            throw Ex;
        }
    }

    //
    // Destructor
    //
    CCgShader::~CCgShader()
    {
        cgDestroyProgram( m_Program );

        CCgContext::Release();
    }

    //
    // GetLastListing
    //
    const string& CCgShader::GetLastListing()
    {
        return m_LastListing;
    }

    //
    // GetProfile
    //
    CGprofile CCgShader::GetProfile() const
    {
        return cgGetProgramProfile( m_Program );
    }

    //
    // GetString
    //
    string CCgShader::GetString( 
                                CGenum Type 
                                ) const
    {
        if (Type != CG_PROGRAM_SOURCE && Type != CG_PROGRAM_ENTRY && Type != CG_PROGRAM_PROFILE && Type != CG_COMPILED_PROGRAM)
            throw Sys::CDeveloperException( this, "::GetString() : Invalid <Type> parameter." );

        return cgGetProgramString( m_Program, Type ); 
    }

    //
    // GetProfileName
    //
    const char *CCgShader::GetProfileName(
                                          CGprofile Profile 
                                          ) const
    {
        switch (Profile)
        {
        case CG_PROFILE_VP20:
            return "CG_PROFILE_VP20";
        case CG_PROFILE_FP20:
            return "CG_PROFILE_FP20";
        case CG_PROFILE_VP30:
            return "CG_PROFILE_VP30";
        case CG_PROFILE_FP30:
            return "CG_PROFILE_FP30";
        case CG_PROFILE_ARBVP1:
            return "CG_PROFILE_ARBVP1";
        case CG_PROFILE_ARBFP1:
            return "CG_PROFILE_ARBFP1";
        case CG_PROFILE_VP40:
            return "CG_PROFILE_VP40";
        case CG_PROFILE_FP40:
            return "CG_PROFILE_FP40";
        case CG_PROFILE_GLSLV:
            return "CG_PROFILE_GLSLV";
        case CG_PROFILE_GLSLF:
            return "CG_PROFILE_GLSLF";
        case CG_PROFILE_GLSLC:
            return "CG_PROFILE_GLSLC";
        case CG_PROFILE_GPU_FP:
            return "CG_PROFILE_GPU_FP";
        case CG_PROFILE_GPU_VP:
            return "CG_PROFILE_GPU_VP";
        case CG_PROFILE_GPU_GP:
            return "CG_PROFILE_GPU_GP";
        }

        return NULL;
    }

    //
    // CheckDomain
    //
    void CCgShader::CheckDomain( 
                                CGprofile Profile, CGGLenum ProfileClass 
                                ) const
    {
        CGdomain ProfileDomain = cgGetProfileDomain( Profile );
        bool Valid = true;

        switch (ProfileClass)
        {
        case CG_GL_VERTEX:
            if (ProfileDomain != CG_VERTEX_DOMAIN)
                Valid = false;
            break;
        case CG_GL_GEOMETRY:
            if (ProfileDomain != CG_GEOMETRY_DOMAIN)
                Valid = false;
            break;
        case CG_GL_FRAGMENT:
            if (ProfileDomain != CG_FRAGMENT_DOMAIN)
                Valid = false;
            break;
        }

        if (!Valid)
            throw Sys::CDeveloperException( "GL::CCgShader", "::CheckDomain() : Invalid profile: %s.", GetProfileName( Profile ) );
    }

    #ifdef _DEBUG

    //
    // OutputDebugLog
    //
    void CCgShader::OutputDebugLog() const
    {
    #ifdef _MSC_VER
        OutputDebugStringA( "\n----- An Cg compiler error has occured! -----\n\n" );
        OutputDebugStringA( m_LastListing.c_str() );
        OutputDebugStringA( "\n----- End of log -----\n\n" );
    #endif
    }
    
    #endif // _DEBUG
    
    //
    // Constructor
    //
    CCgVertexShader::CCgVertexShader( 
                                     CGenum SourceType, const string& SourceStr, 
                                     const string& Entry, const string& Arguments
                                     ):
        CCgShader( SourceType, SourceStr, CG_PROFILE_UNKNOWN, CG_GL_VERTEX, Entry, Arguments )
    {
    }

    //
    // Constructor
    //
    CCgVertexShader::CCgVertexShader( 
                                     CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                     const string& Entry, const string& Arguments
                                     ):
        CCgShader( SourceType, SourceStr, Profile, CG_GL_VERTEX, Entry, Arguments )
    {
    }

    //
    // Constructor
    //
    CCgGeometryShader::CCgGeometryShader( 
                                         CGenum SourceType, const string& SourceStr, 
                                         const string& Entry, const string& Arguments
                                         ):
        CCgShader( SourceType, SourceStr, CG_PROFILE_UNKNOWN, CG_GL_GEOMETRY, Entry, Arguments )
    {
    }

    //
    // Constructor
    //
    CCgGeometryShader::CCgGeometryShader( 
                                         CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                         const string& Entry, const string& Arguments
                                         ):
        CCgShader( SourceType, SourceStr, Profile, CG_GL_GEOMETRY, Entry, Arguments )
    {
    }
    
    //
    // Constructor
    //
    CCgFragmentShader::CCgFragmentShader( 
                                         CGenum SourceType, const string& SourceStr, 
                                         const string& Entry, const string& Arguments
                                         ):
        CCgShader( SourceType, SourceStr, CG_PROFILE_UNKNOWN, CG_GL_FRAGMENT, Entry, Arguments )
    {
    }

    //
    // Constructor
    //
    CCgFragmentShader::CCgFragmentShader( 
                                         CGenum SourceType, const string& SourceStr, CGprofile Profile, 
                                         const string& Entry, const string& Arguments
                                         ):
        CCgShader( SourceType, SourceStr, Profile, CG_GL_FRAGMENT, Entry, Arguments )
    {
    }
}

#endif // CG_SDK