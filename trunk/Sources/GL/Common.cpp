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

// Файл: /GL/Common.cpp
//

#include "Precompiled.h"
#pragma hdrstop

namespace GL 
{
    Ptr<const CExtensionRegistry> CObject::m_Extensions;
    CObject::TCaps CObject::m_Caps;
    bool CObject::m_CgShaders = false;

    int CObject::m_Count = 0;

    //
    // Constructor
    //
    CObject::CObject()
    {
        ++m_Count;

        // Сбросим кэш ошибок OpenGL перед тем, как будет вызван конструктор производного класса.          
        glClearErrors();
    }

    //
    // Constructor
    //
    CObject::CObject( 
                     int Dummy 
                     )
    {
    }

    //
    // Destructor
    //
    CObject::~CObject()
    {
        --m_Count;
    }

    //
    // Init
    //
    void CObject::Init(  
                       Ptr<const CExtensionRegistry> Extensions,
                       bool CgShaders
                       )
    {
    #ifndef CG_SDK
        if (CgShaders)
            throw Sys::CDeveloperException( "GL::CObject", "::Init() : This program was not built with NVIDIA Cg SDK." );
    #endif // CG_SDK

        m_Extensions = Extensions;

        if (m_Extensions->OpenGL_2_0) 
        {
            glClearErrors();
            glGetIntegerv( GL_MAX_DRAW_BUFFERS, &m_Caps.MaxDrawBuffers );
            glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &m_Caps.MaxTextureImageUnits );
            glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &m_Caps.MaxVertexAttribs );
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw Sys::CException( 0, "GL::CObject", "::Init() : An OpenGL error has occured." );
        }

        m_CgShaders = CgShaders;
    }

    //
    // Release
    //
    void CObject::Release()
    {
    }

    //
    // Constructor
    //
    CException::CException( 
                           const Sys::IRTTIObject *Obj, GLenum Code, const char *FormatStr, ... 
                           )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );
        sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", Obj->GetClassName().c_str(), ToString( Code ), MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[ 1 ] );
    }

    //
    // Constructor
    //
    CException::CException( 
                           const char *ClsName, GLenum Code, const char *FormatStr, ... 
                           )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );
        sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", ClsName, ToString( Code ), MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[ 1 ] );
    }

    //
    // ToString
    //
    const char *CException::ToString( 
                                     GLenum Code
                                     ) const
    {
        switch (Code) 
        {
        case GL_NO_ERROR:
            throw Sys::CDeveloperException( Sys::CDeveloperException::ERR_INVALID_THROW, "No OpenGL errors has occured." ); 
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_TABLE_TOO_LARGE: // GL_ARB_imaging 
            return "GL_TABLE_TOO_LARGE"; 
        case GL_INVALID_FRAMEBUFFER_OPERATION_EXT: // GL_EXT_framebuffer_object
            return "GL_INVALID_FRAMEBUFFER_OPERATION"; 
     
        // Obsolete?

        case GLU_INVALID_ENUM:
            return "GLU_INVALID_ENUM";
        case GLU_INVALID_VALUE:
            return "GLU_INVALID_VALUE";
        case GLU_OUT_OF_MEMORY:
            return "GLU_OUT_OF_MEMORY";
    #ifdef GLU_INVALID_OPERATION
        case GLU_INVALID_OPERATION:
            return "GLU_INVALID_OPERATION";
    #endif
    #ifdef GLU_INCOMPATIBLE_GL_VERSION
        case GLU_INCOMPATIBLE_GL_VERSION:
            return "GLU_INCOMPATIBLE_GL_VERSION";
    #endif

        default:
            throw Sys::CDeveloperException( Sys::CDeveloperException::ERR_INVALID_ENUM, "Unknown OpenGL error code." );
        }

        return "";
    }

    #ifdef _WIN32

    //
    // Constructor
    //
    CWGLException::CWGLException( 
                                 const Sys::IRTTIObject *Obj, const char *FormatStr, ... 
                                 )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;
        
        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );

        DWORD dwLastError = GetLastError();
        const char *ErrorStr = ToString( dwLastError );

        if (!ErrorStr)
            sprintf( MessageStr[ 1 ], "%s\n\n%s", Obj->GetClassName().c_str(), MessageStr[ 0 ] );
        else
            sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", Obj->GetClassName().c_str(), ErrorStr, MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[1] );
    }
    
    //
    // Constructor
    //
    CWGLException::CWGLException( 
                                 const char *ClsName, const char *FormatStr, ... 
                                 )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;
        
        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );

        DWORD dwLastError = GetLastError();
        const char *ErrorStr = ToString( dwLastError );

        if (!ErrorStr)
            sprintf( MessageStr[ 1 ], "%s\n\n%s", ClsName, MessageStr[ 0 ] );
        else
            sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", ClsName, ErrorStr, MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[ 1 ] );
    }
    
    //
    // ToString
    //
    const char* CWGLException::ToString( 
                                        DWORD dwLastError 
                                        ) const
    {
        switch (dwLastError) 
        {
		case ERROR_SUCCESS:
            return NULL;
		case ERROR_INVALID_PIXEL_FORMAT:
			return "ERROR_INVALID_PIXEL_FORMAT";
		case ERROR_INVALID_WINDOW_STYLE:
			return "ERROR_INVALID_WINDOW_STYLE";
		// WGL
        case ERROR_INVALID_HANDLE:
            return "ERROR_INVALID_HANDLE";
        case ERROR_INVALID_DATA:
            return "ERROR_INVALID_DATA";
        case ERROR_INVALID_OPERATION:
            return "ERROR_INVALID_OPERATION";
        case ERROR_NO_SYSTEM_RESOURCES:
            return "ERROR_NO_SYSTEM_RESOURCES";
        }

        return NULL;
    }

    #elif defined (__linux__)

    //
    // Constructor
    //
    CGLXException::CGLXException( 
                                 const Sys::IRTTIObject *Obj, const char *FormatStr, ... 
                                 )
    {
    }
      
    //
    // Constructor
    //
    CGLXException::CGLXException( 
                                 const char *ClsName, const char *FormatStr, ... 
                                 )
    {
    }

    //
    // ToStringX
    //
    const char* CGLXException::ToStringX( 
                                         int Code 
                                         ) const
    {
    }

    //
    // ToStringGLX
    //
    const char* CGLXException::ToStringGLX( 
                                           int Code 
                                           ) const
    {
    }

    #endif // _WIN32
    #ifdef CG_SDK

    //
    // Constructor
    //
    CCgException::CCgException( 
                               const Sys::IRTTIObject *Obj, CGerror Code, const char *FormatStr, ... 
                               )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );
        sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", Obj->GetClassName().c_str(), ToString( Code ), MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[ 1 ] );
    }
      
    //
    // Constructor
    //
    CCgException::CCgException( 
                               const char *ClsName, CGerror Code, const char *FormatStr, ... 
                               )
    {
        char MessageStr[ 2 ][ MAX_STRING ];
        va_list ArgList;

        va_start( ArgList, FormatStr );
        vsprintf( MessageStr[ 0 ], FormatStr, ArgList );
        va_end( ArgList );
        sprintf( MessageStr[ 1 ], "%s\n\n%s\n%s", ClsName, ToString( Code ), MessageStr[ 0 ] );

        throw Sys::CException( MessageStr[ 1 ] );
    }

    //
    // ToString
    //
    const char *CCgException::ToString( 
                                       CGerror Code
                                       ) const
    {
        switch (Code) 
        {
        case CG_NO_ERROR:
            throw Sys::CDeveloperException( Sys::CDeveloperException::ERR_INVALID_THROW, "No Cg errors has occured." ); 
        case CG_COMPILER_ERROR:
            return "CG_COMPILER_ERROR";
        case CG_INVALID_PARAMETER_ERROR:
            return "CG_INVALID_PARAMETER_ERROR";
        case CG_INVALID_PROFILE_ERROR:
            return "CG_INVALID_PROFILE_ERROR";
        case CG_PROGRAM_LOAD_ERROR:
            return "CG_PROGRAM_LOAD_ERROR";
        case CG_PROGRAM_BIND_ERROR:
            return "CG_PROGRAM_BIND_ERROR";
        case CG_PROGRAM_NOT_LOADED_ERROR:
            return "CG_PROGRAM_NOT_LOADED_ERROR";
        case CG_UNSUPPORTED_GL_EXTENSION_ERROR:
            return "CG_UNSUPPORTED_GL_EXTENSION_ERROR";
        case CG_INVALID_VALUE_TYPE_ERROR:
            return "CG_INVALID_VALUE_TYPE_ERROR";
        case CG_NOT_MATRIX_PARAM_ERROR:
            return "CG_NOT_MATRIX_PARAM_ERROR";
        case CG_INVALID_ENUMERANT_ERROR:
            return "CG_INVALID_ENUMERANT_ERROR";
        case CG_NOT_4x4_MATRIX_ERROR:
            return "CG_NOT_4x4_MATRIX_ERROR";
        case CG_FILE_READ_ERROR:
            return "CG_FILE_READ_ERROR";
        case CG_FILE_WRITE_ERROR:
            return "CG_FILE_WRITE_ERROR";
        case CG_NVPARSE_ERROR:
            return "CG_NVPARSE_ERROR";
        case CG_MEMORY_ALLOC_ERROR:
            return "CG_MEMORY_ALLOC_ERROR";
        case CG_INVALID_CONTEXT_HANDLE_ERROR:
            return "CG_INVALID_CONTEXT_HANDLE_ERROR";
        case CG_INVALID_PROGRAM_HANDLE_ERROR:
            return "CG_INVALID_PROGRAM_HANDLE_ERROR";
        case CG_INVALID_PARAM_HANDLE_ERROR:
            return "CG_INVALID_PARAM_HANDLE_ERROR";
        case CG_UNKNOWN_PROFILE_ERROR:
            return "CG_UNKNOWN_PROFILE_ERROR";
        case CG_VAR_ARG_ERROR:
            return "CG_VAR_ARG_ERROR";
        case CG_INVALID_DIMENSION_ERROR:
            return "CG_INVALID_DIMENSION_ERROR";
        case CG_ARRAY_PARAM_ERROR:
            return "CG_ARRAY_PARAM_ERROR";
        case CG_OUT_OF_ARRAY_BOUNDS_ERROR:
            return "CG_OUT_OF_ARRAY_BOUNDS_ERROR";
        case CG_CONFLICTING_TYPES_ERROR:
            return "CG_CONFLICTING_TYPES_ERROR";
        case CG_CONFLICTING_PARAMETER_TYPES_ERROR:
            return "CG_CONFLICTING_PARAMETER_TYPES_ERROR";
        case CG_PARAMETER_IS_NOT_SHARED_ERROR:
            return "CG_PARAMETER_IS_NOT_SHARED_ERROR";
        case CG_INVALID_PARAMETER_VARIABILITY_ERROR:
            return "CG_INVALID_PARAMETER_VARIABILITY_ERROR";
        case CG_CANNOT_DESTROY_PARAMETER_ERROR:
            return "CG_CANNOT_DESTROY_PARAMETER_ERROR";
        case CG_NOT_ROOT_PARAMETER_ERROR:
            return "CG_NOT_ROOT_PARAMETER_ERROR";
        case CG_PARAMETERS_DO_NOT_MATCH_ERROR:
            return "CG_PARAMETERS_DO_NOT_MATCH_ERROR";
        case CG_IS_NOT_PROGRAM_PARAMETER_ERROR:
            return "CG_IS_NOT_PROGRAM_PARAMETER_ERROR";
        case CG_INVALID_PARAMETER_TYPE_ERROR:
            return "CG_INVALID_PARAMETER_TYPE_ERROR";
        case CG_PARAMETER_IS_NOT_RESIZABLE_ARRAY_ERROR:
            return "CG_PARAMETER_IS_NOT_RESIZABLE_ARRAY_ERROR";
        case CG_INVALID_SIZE_ERROR:
            return "CG_INVALID_SIZE_ERROR";
        case CG_BIND_CREATES_CYCLE_ERROR:
            return "CG_BIND_CREATES_CYCLE_ERROR";
        case CG_ARRAY_TYPES_DO_NOT_MATCH_ERROR:
            return "CG_ARRAY_TYPES_DO_NOT_MATCH_ERROR";
        case CG_ARRAY_DIMENSIONS_DO_NOT_MATCH_ERROR:
            return "CG_ARRAY_DIMENSIONS_DO_NOT_MATCH_ERROR";
        case CG_ARRAY_HAS_WRONG_DIMENSION_ERROR:
            return "CG_ARRAY_HAS_WRONG_DIMENSION_ERROR";
        case CG_TYPE_IS_NOT_DEFINED_IN_PROGRAM_ERROR:
            return "CG_TYPE_IS_NOT_DEFINED_IN_PROGRAM_ERROR";
        case CG_INVALID_EFFECT_HANDLE_ERROR:
            return "CG_INVALID_EFFECT_HANDLE_ERROR";
        case CG_INVALID_STATE_HANDLE_ERROR:
            return "CG_INVALID_STATE_HANDLE_ERROR";
        case CG_INVALID_STATE_ASSIGNMENT_HANDLE_ERROR:
            return "CG_INVALID_STATE_ASSIGNMENT_HANDLE_ERROR";
        case CG_INVALID_PASS_HANDLE_ERROR:
            return "CG_INVALID_PASS_HANDLE_ERROR";
        case CG_INVALID_ANNOTATION_HANDLE_ERROR:
            return "CG_INVALID_ANNOTATION_HANDLE_ERROR";
        case CG_INVALID_TECHNIQUE_HANDLE_ERROR:
            return "CG_INVALID_TECHNIQUE_HANDLE_ERROR";
        case CG_INVALID_PARAMETER_HANDLE_ERROR:
            return "CG_INVALID_PARAMETER_HANDLE_ERROR";
        case CG_STATE_ASSIGNMENT_TYPE_MISMATCH_ERROR:
            return "CG_STATE_ASSIGNMENT_TYPE_MISMATCH_ERROR";
        case CG_INVALID_FUNCTION_HANDLE_ERROR:
            return "CG_INVALID_FUNCTION_HANDLE_ERROR";
        case CG_INVALID_TECHNIQUE_ERROR:
            return "CG_INVALID_TECHNIQUE_ERROR";
        case CG_INVALID_POINTER_ERROR:
            return "CG_INVALID_POINTER_ERROR";
        case CG_NOT_ENOUGH_DATA_ERROR:
            return "CG_NOT_ENOUGH_DATA_ERROR";
        case CG_NON_NUMERIC_PARAMETER_ERROR:
            return "CG_NON_NUMERIC_PARAMETER_ERROR";
        case CG_ARRAY_SIZE_MISMATCH_ERROR:
            return "CG_ARRAY_SIZE_MISMATCH_ERROR";
        case CG_CANNOT_SET_NON_UNIFORM_PARAMETER_ERROR:
            return "CG_CANNOT_SET_NON_UNIFORM_PARAMETER_ERROR";
        case CG_DUPLICATE_NAME_ERROR:
            return "CG_DUPLICATE_NAME_ERROR";
        case CG_INVALID_OBJ_HANDLE_ERROR:
            return "CG_INVALID_OBJ_HANDLE_ERROR";
        case CG_INVALID_BUFFER_HANDLE_ERROR:
            return "CG_INVALID_BUFFER_HANDLE_ERROR";
        case CG_BUFFER_INDEX_OUT_OF_RANGE_ERROR:
            return "CG_BUFFER_INDEX_OUT_OF_RANGE_ERROR";
        case CG_BUFFER_ALREADY_MAPPED_ERROR:
            return "CG_BUFFER_ALREADY_MAPPED_ERROR";
        case CG_BUFFER_UPDATE_NOT_ALLOWED_ERROR:
            return "CG_BUFFER_UPDATE_NOT_ALLOWED_ERROR";

        default:
            throw Sys::CDeveloperException( Sys::CDeveloperException::ERR_INVALID_ENUM, "Unknown Cg error code." );
        }
      
        return "";
    }
   
    #endif // CG_SDK

    //
    // Constructor
    //
    CExtensionException::CExtensionException( 
                                             const Sys::IRTTIObject *Obj, const char *Method, const char *Extension 
                                             )
    {
        char MessageStr[ MAX_STRING ];
        
        sprintf( MessageStr, "%s\n\n%s : OpenGL extension \"%s\" unsupported.", 
            Obj->GetClassName().c_str(), Method, Extension );

        throw Sys::CException( MessageStr );
    }
    
    //
    // Constructor
    //
    CExtensionException::CExtensionException( 
                                             const char *ClsName, const char *Method, const char *Extension 
                                             )
    {
        char MessageStr[ MAX_STRING ];
        
        sprintf( MessageStr, "%s\n\n%s : OpenGL extension \"%s\" unsupported.", 
            ClsName, Method, Extension );

        throw Sys::CException( MessageStr );
    }
    
    //
    // Constructor
    //
    CExtensionException::CExtensionException( 
                                             const Sys::IRTTIObject *Obj, const char *Method, int MajorNumber, int MinorNumber
                                             )
    {
        char MessageStr[ MAX_STRING ];
        
        sprintf( MessageStr, "%s\n\n%s : OpenGL version %d.%d unsupported.", 
            Obj->GetClassName().c_str(), Method, MajorNumber, MinorNumber );

        throw Sys::CException( MessageStr );
    }

    //
    // Constructor
    //
    CExtensionException::CExtensionException( 
                                             const char *ClsName, const char *Method, int MajorNumber, int MinorNumber
                                             )
    {
        char MessageStr[ MAX_STRING ];
        
        sprintf( MessageStr, "%s\n\n%s : OpenGL version %d.%d unsupported.", 
            ClsName, Method, MajorNumber, MinorNumber );

        throw Sys::CException( MessageStr );
    }
    
    //
    //
    //
    void glClearErrors() 
    {
        while (glGetError() != GL_NO_ERROR) {}
    }

    #ifdef MATH_LIB_INCLUDED

    //
    //
    //
    void glVertex2fv( const Vec2<GLfloat>& v ) 
    { 
        ::glVertex2fv( &v.x ); 
    }

    //
    //
    //
    void glVertex2iv( const Vec2<GLint>& v )
    {
        ::glVertex2iv( &v.x );
    }

    //
    //
    //
    void glVertex3fv( const Vec3<GLfloat>& v )
    { 
        ::glVertex3fv( &v.x ); 
    }

    //
    //
    //
    void glVertex3fv( const Vec4_SSE& v )
    { 
        ::glVertex3fv( &v.x ); 
    }
    
    //
    //
    //
    void glVertex3iv( const Vec3<GLint>& v )
    {
        ::glVertex2iv( &v.x );
    }

    //
    //
    //
    void glVertex4fv( const Vec4<GLfloat>& v )
    {
        ::glVertex4fv( &v.x );
    }

    //
    //
    //
    void glVertex4fv( const Vec4_SSE& v )
    { 
        ::glVertex3fv( &v.x ); 
    }
    
    //
    //
    //
    void glVertex4iv( const Vec4<GLint>& v )
    {
        ::glVertex4iv( &v.x );
    }

    //
    //
    //
    void glTranslatefv( const Vec2<GLfloat>& v )
    {
        ::glTranslatef( v.x, v.y, 0.0f );
    }

    //
    //
    //
    void glTranslatefv( const Vec3<GLfloat>& v )
    {
        ::glTranslatef( v.x, v.y, v.z );
    }

    //
    //
    //
    void glLoadMatrixf( const Mat4& m )
    {
        ::glLoadMatrixf( &m[ 0 ][ 0 ] );
    }

    //
    //
    //
    void glMultMatrixf( const Mat3& m )
    {
        Mat4 n( m );
        ::glMultMatrixf( &n[ 0 ][ 0 ] );
    }

    //
    //
    //
    void glMultMatrixf( const Mat4& m )
    {
        ::glMultMatrixf( &m[ 0 ][ 0 ] );
    }

    #endif // MATH_LIB_INCLUDED
}