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

// Τΰιλ: /GL/GL/Uniform.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Uniform.h"
#include "Buffer.h"

namespace GL
{
    //
    // Constructor
    //
    CUniform::CUniform( 
                       const string& Name, GLint Location
    #ifdef _DEBUG
                       ,GLenum Type
    #endif
                       ):
        IUniform( Name ),

        m_Location( Location )
    #ifdef _DEBUG
        ,m_Type( Type )
    #endif
    {
    }

    //
    // SetBool
    //
    void CUniform::SetBool( 
                           bool x 
                           )
    {
    #ifdef _DEBUG
        Try( "SetBool", GL_BOOL );
    #endif
        glUniform1i( m_Location, x ? GL_TRUE : GL_FALSE );
    #ifdef _DEBUG
        Catch( "SetBool" );
    #endif
    }

    //
    // SetFloat
    //
    void CUniform::SetFloat( 
                            GLfloat x 
                            )
    {
    #ifdef _DEBUG
        Try( "SetFloat", GL_FLOAT );
    #endif
        glUniform1f( m_Location, x );
    #ifdef _DEBUG
        Catch( "SetFloat" );
    #endif
    }

    //
    // SetInt
    //
    void CUniform::SetInt( 
                          GLint x 
                          )
    {
    #ifdef _DEBUG
        Try( "SetInt", GL_INT );
    #endif
        glUniform1i( m_Location, x );
    #ifdef _DEBUG
        Catch( "SetInt" );
    #endif
    }

    //
    // SetUnsignedInt
    //
    void CUniform::SetUnsignedInt( 
                                  GLuint x 
                                  )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedInt", GL_UNSIGNED_INT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform1uiEXT( m_Location, x );
    #ifdef _DEBUG
        Catch( "SetUnsignedInt" );
    #endif
    }

    //
    // SetFloat2
    //
    void CUniform::SetFloat2( 
                             GLfloat x, GLfloat y 
                             )
    {
    #ifdef _DEBUG
        Try( "SetFloat2", GL_FLOAT_VEC2 );
    #endif
        glUniform2f( m_Location, x, y );
    #ifdef _DEBUG
        Catch( "SetFloat2" );
    #endif
    }

    //
    // SetInt2
    //
    void CUniform::SetInt2( 
                           GLint x, GLint y 
                           )
    {
    #ifdef _DEBUG
        Try( "SetInt2", GL_INT_VEC2 );
    #endif
        glUniform2i( m_Location, x, y );
    #ifdef _DEBUG
        Catch( "SetInt2" );
    #endif
    }

    //
    // SetUnsignedInt2
    //
    void CUniform::SetUnsignedInt2( 
                                   GLuint x, GLuint y 
                                   )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt2()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedInt2", GL_UNSIGNED_INT_VEC2_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform2uiEXT( m_Location, x, y );
    #ifdef _DEBUG
        Catch( "SetUnsignedInt2" );
    #endif
    }

    //
    // SetFloat3
    //
    void CUniform::SetFloat3( 
                             GLfloat x, GLfloat y, GLfloat z 
                             )
    {
    #ifdef _DEBUG
        Try( "SetFloat3", GL_FLOAT_VEC3 );
    #endif
        glUniform3f( m_Location, x, y, z );
    #ifdef _DEBUG
        Catch( "SetFloat3" );
    #endif
    }

    //
    // SetInt3
    //
    void CUniform::SetInt3( 
                           GLint x, GLint y, GLint z 
                           )
    {
    #ifdef _DEBUG
        Try( "SetInt3", GL_INT_VEC3 );
    #endif
        glUniform3i( m_Location, x, y, z );
    #ifdef _DEBUG
        Catch( "SetInt3" );
    #endif
    }

    //
    // SetUnsignedInt3
    //
    void CUniform::SetUnsignedInt3( 
                                   GLuint x, GLuint y, GLuint z 
                                   )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt3()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedInt3", GL_UNSIGNED_INT_VEC3_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform3uiEXT( m_Location, x, y, z );
    #ifdef _DEBUG
        Catch( "SetUnsignedInt3" );
    #endif
    }

    //
    // SetFloat4
    //
    void CUniform::SetFloat4(  
                             GLfloat x, GLfloat y, GLfloat z, GLfloat w
                             )
    {
    #ifdef _DEBUG
        Try( "SetFloat4", GL_FLOAT_VEC4 );
    #endif
        glUniform4f( m_Location, x, y, z, w );
    #ifdef _DEBUG
        Catch( "SetFloat4" );
    #endif
    }

    //
    // SetInt4
    //
    void CUniform::SetInt4( 
                           GLint x, GLint y, GLint z, GLint w 
                           )
    {
    #ifdef _DEBUG
        Try( "SetInt4", GL_INT_VEC4 );
    #endif
        glUniform4i( m_Location, x, y, z, w );
    #ifdef _DEBUG
        Catch( "SetInt4" );
    #endif
    }

    //
    // SetUnsignedInt4
    //
    void CUniform::SetUnsignedInt4( 
                                   GLuint x, GLuint y, GLuint z, GLuint w 
                                   )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt4()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedInt4", GL_UNSIGNED_INT_VEC4_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform4uiEXT( m_Location, x, y, z, w );
    #ifdef _DEBUG
        Catch( "SetUnsignedInt4" );
    #endif
    }

    //
    // SetFloatArray
    //
    void CUniform::SetFloatArray( 
                                 GLsizei Dimension, GLsizei Count, 
                                 const GLfloat *Array 
                                 )
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        switch (Dimension) 
        {
        case 1: glUniform1fv( m_Location, Count, Array );
            break;
        case 2: glUniform2fv( m_Location, Count, Array );
            break;
        case 3: glUniform3fv( m_Location, Count, Array );
            break;
        case 4: glUniform4fv( m_Location, Count, Array );
            break;
        default:
            throw Sys::CDeveloperException( this, "::SetFloatArray() : Invalid <Dimension> parameter." );
        }
     #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetFloatArray() : An OpenGL error has occured." );
    #endif
    }

    //
    // SetIntArray
    //
    void CUniform::SetIntArray( 
                               GLsizei Dimension, GLsizei Count, 
                               const GLint *Array 
                               )
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        switch (Dimension) 
        {
        case 1: glUniform1iv( m_Location, Count, Array );
            break;
        case 2: glUniform2iv( m_Location, Count, Array );
            break;
        case 3: glUniform3iv( m_Location, Count, Array );
            break;
        case 4: glUniform4iv( m_Location, Count, Array );
            break;
        default:
            throw Sys::CDeveloperException( this, "::SetIntArray() : Invalid <Dimension> parameter." );
        }
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetIntArray() : An OpenGL error has occured." );
    #endif
    }

    //
    // SetUnsignedIntArray
    //
    void CUniform::SetUnsignedIntArray( 
                                       GLsizei Dimension, GLsizei Count, 
                                       const GLuint *Array 
                                       )
    {
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntArray()", "GL_EXT_gpu_shader4" );

    #ifdef _DEBUG
        glClearErrors();
    #endif
        switch (Dimension) 
        {
        case 1: glUniform1uivEXT( m_Location, Count, Array );
            break;
        case 2: glUniform2uivEXT( m_Location, Count, Array );
            break;
        case 3: glUniform3uivEXT( m_Location, Count, Array );
            break;
        case 4: glUniform4uivEXT( m_Location, Count, Array );
            break;
        default:
            throw Sys::CDeveloperException( this, "::SetUnsignedIntArray() : Invalid <Dimension> parameter." );
        }
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetUnsignedIntArray() : An OpenGL error has occured." );
    #endif
    }

    #ifdef MATH_LIB_INCLUDED
         
    //
    // SetFloatVec2
    //
    void CUniform::SetFloatVec2( 
                                const Vec2<GLfloat>& v 
                                )
    {
    #ifdef _DEBUG
        Try( "SetFloatVec2", GL_FLOAT_VEC2 );
    #endif
        glUniform2fv( m_Location, 1, &v[ 0 ] );
    #ifdef _DEBUG
        Catch( "SetFloatVec2" );
    #endif
    }

    //
    // SetIntVec2
    //
    void CUniform::SetIntVec2(  
                              const Vec2<GLint>& v 
                              )
    {
    #ifdef _DEBUG
        Try( "SetIntVec2", GL_INT_VEC2 );
    #endif
        glUniform2iv( m_Location, 1, &v[ 0 ] );
    #ifdef _DEBUG
        Catch( "SetIntVec2" );
    #endif
    }

    //
    // SetUnsignedIntVec2
    //
    void CUniform::SetUnsignedIntVec2(  
                                      const Vec2<GLuint>& v 
                                      )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec2()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedIntVec2", GL_UNSIGNED_INT_VEC2_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform2uivEXT( m_Location, 1, &v[ 0 ] );
    #ifdef _DEBUG
        Catch( "SetUnsignedIntVec2" );
    #endif
    }

    //
    // SetFloatVec3
    //
    void CUniform::SetFloatVec3( 
                                const Vec3<GLfloat>& v 
                                )
    {
    #ifdef _DEBUG
        Try( "SetFloatVec3", GL_FLOAT_VEC3 );
    #endif
        glUniform3fv( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetFloatVec3" );
    #endif
    }

    //
    // SetIntVec3
    //
    void CUniform::SetIntVec3( 
                              const Vec3<GLint>& v 
                              )
    {
    #ifdef _DEBUG
        Try( "SetIntVec3", GL_INT_VEC3 );
    #endif
        glUniform3iv( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetIntVec3" );
    #endif
    }

    //
    // SetUnsignedIntVec3
    //
    void CUniform::SetUnsignedIntVec3( 
                                      const Vec3<GLuint>& v 
                                      )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec3()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedIntVec3", GL_UNSIGNED_INT_VEC3_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform3uivEXT( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetUnsignedIntVec3" );
    #endif
    }

    //
    // SetFloatVec4
    //
    void CUniform::SetFloatVec4( 
                                const Vec4<GLfloat>& v 
                                )
    {
    #ifdef _DEBUG
        Try( "SetFloatVec4", GL_FLOAT_VEC4 );
    #endif
        glUniform4fv( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetFloatVec4" );
    #endif
    }

    //
    // SetIntVec4
    //
    void CUniform::SetIntVec4(     
                              const Vec4<GLint>& v 
                              )
    {
    #ifdef _DEBUG
        Try( "SetIntVec4", GL_INT_VEC4 );
    #endif
        glUniform4iv( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetIntVec4" );
    #endif
    }
         
    //
    // SetUnsignedIntVec4
    //
    void CUniform::SetUnsignedIntVec4(     
                                      const Vec4<GLuint>& v 
                                      )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec4()", "GL_EXT_gpu_shader4" );
        Try( "SetUnsignedIntVec4", GL_UNSIGNED_INT_VEC4_EXT );
    #endif
        if (m_Extensions->EXT_gpu_shader4)
            glUniform4uivEXT( m_Location, 1, &v[ 0 ] ); 
    #ifdef _DEBUG
        Catch( "SetUnsignedIntVec4" );
    #endif
    }

    //
    // SetFloatMat2
    //
    void CUniform::SetFloatMat2( 
                                const Mat2& m, EMatrixOrder Order 
                                )
    {
    #ifdef _DEBUG
        Try( "SetFloatMat2", GL_FLOAT_MAT2 );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix2fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix2fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    #ifdef _DEBUG
        Catch( "SetFloatMat2" );
    #endif
    }

    //
    // SetFloatMat3
    //
    void CUniform::SetFloatMat3( 
                                const Mat3& m, EMatrixOrder Order 
                                )
    {
    #ifdef _DEBUG
        Try( "SetFloatMat3", GL_FLOAT_MAT3 );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix3fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix3fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    #ifdef _DEBUG
        Catch( "SetFloatMat3" );
    #endif
    }

    //
    // SetFloatMat4
    //
    void CUniform::SetFloatMat4( 
                                const Mat4& m, EMatrixOrder Order 
                                ) 
    {
    #ifdef _DEBUG
        Try( "SetFloatMat4", GL_FLOAT_MAT4 );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix4fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix4fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    #ifdef _DEBUG
        Catch( "SetFloatMat4" );
    #endif
    }

    #endif // MATH_LIB_INCLUDED
    #ifdef _DEBUG

    //
    // Try
    //
    void CUniform::Try( 
                       const char *Name, GLenum Type
                       ) const
    {
        struct
        {
            GLenum Type;
            const char *Name;
        } 
        static const Uniforms[] =
        {
            // OpenGL 2.0
            {GL_FLOAT, "GL_FLOAT"},
            {GL_FLOAT_VEC2, "GL_FLOAT_VEC2"},
            {GL_FLOAT_VEC3, "GL_FLOAT_VEC3"},
	        {GL_FLOAT_VEC4, "GL_FLOAT_VEC4"},
            {GL_INT, "GL_INT"},
            {GL_INT_VEC2, "GL_INT_VEC2"},
            {GL_INT_VEC3, "GL_INT_VEC3"},
            {GL_INT_VEC4, "GL_INT_VEC4"},
            {GL_BOOL, "GL_BOOL"},	
            {GL_BOOL_VEC2, "GL_BOOL_VEC2"},
            {GL_BOOL_VEC3, "GL_BOOL_VEC3"},
            {GL_BOOL_VEC4, "GL_BOOL_VEC4"},
            {GL_FLOAT_MAT2, "GL_FLOAT_MAT2"},
            {GL_FLOAT_MAT3, "GL_FLOAT_MAT3"},
            {GL_FLOAT_MAT4, "GL_FLOAT_MAT4"},
            // GL_EXT_gpu_shader4
            {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},  
            {GL_UNSIGNED_INT_VEC2_EXT, "GL_UNSIGNED_INT_VEC2"}, 
            {GL_UNSIGNED_INT_VEC3_EXT, "GL_UNSIGNED_INT_VEC3"}, 
            {GL_UNSIGNED_INT_VEC4_EXT, "GL_UNSIGNED_INT_VEC4"},
            // Terminator
            {GL_NONE, NULL}
        };

        if (m_Type != Type)
        {
            const char *TypeName = "<UNKNOWN>";

            for (int i = 0; Uniforms[ i ].Type != GL_NONE; ++i)
            {
                if (m_Type == Uniforms[ i ].Type) 
                {
                    TypeName = Uniforms[ i ].Name;
                    break;
                }
            }

            throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_INVALID_CALL, 
                "::%s() : Uniform variable \"%s\" has type %s.", Name, m_Name.c_str(), TypeName );
        }

        glClearErrors();
    }

    //
    // Catch
    //
    void CUniform::Catch( 
                         const char *Name
                         ) const
    {
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::%s() : An OpenGL error has occured." );
    }

    #endif // _DEBUG

    //
    // Constructor
    //
    CSamplerUniform::CSamplerUniform( 
                                     const string& Name, GLint Location, GLenum Unit 
                                     ):
        ISamplerUniform( Name ),

        m_Location( Location ),
        m_Unit( Unit )
    {
    }

    //
    // SetSampler
    //
    void CSamplerUniform::SetSampler( 
                                     Ptr<const CTexture> Texture 
                                     )
    {
        m_Texture = Texture;
    }

    //
    // EnableSampler
    //
    void CSamplerUniform::EnableSampler() const
    {
        if (!m_Texture)
            throw Sys::CDeveloperException( this, "Invalid ::EnableSampler() call. Uniform variable \"%s\" has no assigned texture object.", m_Name.c_str() );

    #ifdef _DEBUG
        glClearErrors();
    #endif

        glActiveTexture( m_Unit );
        glBindTexture( m_Texture->m_Target, m_Texture->m_Texture );

        // Really FFP stuff, we don't need to support it.
        /*
        static const GLenum Targets[] = 
        {
            GL_TEXTURE_1D, 
            GL_TEXTURE_2D, 
            GL_TEXTURE_RECTANGLE_ARB, 
            GL_TEXTURE_3D, 
            GL_TEXTURE_CUBE_MAP, 
            0
        };

        GLenum Target = GL_NONE;

        // Only one texture target must be enabled for specified TMU.
        // Thus, implement simple target enable/disable manager.

        for (int i = 0; Targets[ i ] != 0; ++i) 
        {
            if (glIsEnabled( Targets[ i ] )) 
            {
                Target = Targets[ i ];
                break;
            }
        }
            
        if (Target == GL_NONE)
            glEnable( m_Texture->m_Target );
        else if (Target != m_Texture->m_Target) 
        {
            glDisable( Target );
            glEnable( m_Texture->m_Target );
        }
        */
        glUniform1i( m_Location, m_Unit - GL_TEXTURE0 );

    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::EnableSampler() : An OpenGL error has occured." );
    #endif
    }
       
    //
    // DisableSampler
    //
    void CSamplerUniform::DisableSampler() const
    {
        if (!m_Texture)
            throw Sys::CDeveloperException( this, "Invalid ::DisableSampler() call. Uniform variable \"%s\" has no assigned texture object.", m_Name.c_str() );

        glActiveTexture( m_Unit );
        glBindTexture( m_Texture->m_Target, 0 );
    }

    //
    // Constructor
    //
    CBindableUniform::CBindableUniform( 
                                       const string& Name, GLuint Program, GLuint Location 
                                       ):
        IBindableUniform( Name ),

        m_Program( Program ),
        m_Location( Location )
    {
    }

    //
    // GetBufferSize
    //
    GLsizei CBindableUniform::GetBufferSize() const
    {
		glClearErrors();
		GLint Size = glGetUniformBufferSizeEXT( m_Program, m_Location );
		GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetBufferSize() : Failed to get size of bindable uniform \"%s\".", m_Name.c_str() );

        return Size; 
    }
    
    //
    // GetElementOffset
    // 
    GLintptr CBindableUniform::GetElementOffset( 
                                                GLuint Index 
                                                )
    {
        char IndexStr[ 10 ];
        string Name;
      
        sprintf( IndexStr, "%d", Index ); 
        Name.append( "[" );
        Name.append( IndexStr );
        Name.append( "]" );
         
        glClearErrors();
        GLint Location = glGetUniformLocation( m_Program, Name.c_str() );
        if (Location == -1)
            throw Sys::CDeveloperException( this, "::GetElementOffset() : Failed to determine location of element \"%s\".", Name.c_str() );            
        GLintptr Offset = glGetUniformOffsetEXT( m_Program, Location );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetElementOffset() : Failed to determine offset of element \"%s\".", Name.c_str() );
            
        return Offset;
    }

    //
    // AttachBuffer
    //
    void CBindableUniform::AttachBuffer(
                                        Ptr<const CBuffer> Buffer
                                        )
    {
		glClearErrors();
        glUniformBufferEXT( m_Program, m_Location, Buffer->m_Buffer );
		GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::AttachBuffer() : Failed to attach buffer to bindable uniform \"%s\".", m_Name.c_str() );
    }
}