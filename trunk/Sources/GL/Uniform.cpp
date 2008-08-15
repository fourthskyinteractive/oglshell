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

// Τΰιλ: /GL/Uniform.cpp
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
    void CUniform::SetBool( bool x )
    {
    #ifdef _DEBUG
        if (m_Type != GL_BOOL)
            Throw( "SetBool" );
    #endif
        glUniform1i( m_Location, x ? GL_TRUE : GL_FALSE );
    }

    //
    // SetFloat
    //
    void CUniform::SetFloat( GLfloat x )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT)
            Throw( "SetFloat" );
    #endif
        glUniform1f( m_Location, x );
    }

    //
    // SetInt
    //
    void CUniform::SetInt( GLint x )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT)
            Throw( "SetInt" );
    #endif
        glUniform1i( m_Location, x );
    }

    //
    // SetFloat2
    //
    void CUniform::SetFloat2( GLfloat x, GLfloat y )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC2)
            Throw( "SetFloat2" );
    #endif
        glUniform2f( m_Location, x, y );
    }

    //
    // SetInt2
    //
    void CUniform::SetInt2( GLint x, GLint y )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC2)
            Throw( "SetInt2" );
    #endif
        glUniform2i( m_Location, x, y );
    }

    //
    // SetFloat3
    //
    void CUniform::SetFloat3( GLfloat x, GLfloat y, GLfloat z )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC3)
            Throw( "SetFloat3" );
    #endif
        glUniform3f( m_Location, x, y, z );
    }

    //
    // SetInt3
    //
    void CUniform::SetInt3( GLint x, GLint y, GLint z )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC3)
            Throw( "SetInt3" );
    #endif
        glUniform3i( m_Location, x, y, z );
    }

    //
    // SetFloat4
    //
    void CUniform::SetFloat4( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC4)
            Throw( "SetFloat4" );
    #endif
        glUniform4f( m_Location, x, y, z, w );
    }

    //
    // SetInt4
    //
    void CUniform::SetInt4( GLint x, GLint y, GLint z, GLint w )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC4)
            Throw( "SetInt4" );
    #endif
        glUniform4i( m_Location, x, y, z, w );
    }

    //
    // SetFloatArray
    //
    void CUniform::SetFloatArray( GLsizei Dimension, GLsizei Count, const GLfloat *Array )
    {
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
    }

    //
    // SetIntArray
    //
    void CUniform::SetIntArray( GLsizei Dimension, GLsizei Count, const GLint *Array )
    {
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
    }

    #ifdef MATH_LIB_INCLUDED
         
    //
    // SetFloatVec2
    //
    void CUniform::SetFloatVec2( const Vec2<GLfloat>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC2)
            Throw( "SetFloatVec2" );
    #endif
        glUniform2fv( m_Location, 1, &v[ 0 ] );
    }

    //
    // SetIntVec2
    //
    void CUniform::SetIntVec2( const Vec2<GLint>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC2)
            Throw( "SetIntVec2" );
    #endif
        glUniform2iv( m_Location, 1, &v[ 0 ] );
    }

    //
    // SetFloatVec3
    //
    void CUniform::SetFloatVec3( const Vec3<GLfloat>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC3)
            Throw( "SetFloatVec3" );
    #endif
        glUniform3fv( m_Location, 1, &v[ 0 ] ); 
    }

    //
    // SetIntVec3
    //
    void CUniform::SetIntVec3( const Vec3<GLint>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC3)
            Throw( "SetIntVec3" );
    #endif
        glUniform3iv( m_Location, 1, &v[ 0 ] ); 
    }

    //
    // SetFloatVec4
    //
    void CUniform::SetFloatVec4( const Vec4<GLfloat>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_VEC4)
            Throw( "SetFloatVec4" );
    #endif
        glUniform4fv( m_Location, 1, &v[ 0 ] ); 
    }

    //
    // SetIntVec4
    //
    void CUniform::SetIntVec4( const Vec4<GLint>& v )
    {
    #ifdef _DEBUG
        if (m_Type != GL_INT_VEC4)
            Throw( "SetIntVec4" );
    #endif
        glUniform4iv( m_Location, 1, &v[ 0 ] ); 
    }
         
    //
    // SetFloatMat2
    //
    void CUniform::SetFloatMat2( EMatrixOrder Order, const Mat2& m )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_MAT2)
            Throw( "SetFloatMat2" );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix2fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix2fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    }

    //
    // SetFloatMat3
    //
    void CUniform::SetFloatMat3( EMatrixOrder Order, const Mat3& m )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_MAT3)
            Throw( "SetFloatMat3" );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix3fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix3fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    }

    //
    // SetFloatMat4
    //
    void CUniform::SetFloatMat4( EMatrixOrder Order, const Mat4& m )
    {
    #ifdef _DEBUG
        if (m_Type != GL_FLOAT_MAT4)
            Throw( "SetFloatMat4" );
    #endif
        if (Order == MO_COLUMN_MAJOR)
            glUniformMatrix4fv( m_Location, 1, GL_FALSE, &m[ 0 ][ 0 ] );
        else
            glUniformMatrix4fv( m_Location, 1, GL_TRUE, &m[ 0 ][ 0 ] );
    }

    #endif // MATH_LIB_INCLUDED

    #ifdef _DEBUG
    //
    // Throw
    //
    void CUniform::Throw( const char *Method ) const
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
            // GL_EXT_gpu_shader4 TODO:
            {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},  
            {GL_UNSIGNED_INT_VEC2_EXT, "GL_UNSIGNED_INT_VEC2"}, 
            {GL_UNSIGNED_INT_VEC3_EXT, "GL_UNSIGNED_INT_VEC3"}, 
            {GL_UNSIGNED_INT_VEC4_EXT, "GL_UNSIGNED_INT_VEC4"},
            // Terminator
            {GL_NONE, NULL}
        };

        const char *TypeName = "<UNKNOWN>";

        for (int i = 0; Uniforms[ i ].Type != GL_NONE; ++i)
        {
            if (Uniforms[ i ].Type == m_Type)
            {
                TypeName = Uniforms[ i ].Name;
                break;
            }
        }

        throw Sys::CDeveloperException( this, "::%s() : Uniform variable \"%s\" has type %s.", 
            Method, m_Name.c_str(), TypeName );
    }

    #endif

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
    void CSamplerUniform::SetSampler( Ptr<const CTexture> Texture )
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
    GLintptr CBindableUniform::GetElementOffset( GLuint Index )
    {
        char IndexStr[ 10 ];
        string Name;
        
        sprintf( IndexStr, "%d", Index ); 
        
        Name = m_Name;
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
    void CBindableUniform::AttachBuffer( Ptr<const CBuffer> Buffer )
    {
		glClearErrors();
        glUniformBufferEXT( m_Program, m_Location, Buffer->m_Buffer );
		GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::AttachBuffer() : Failed to attach buffer to bindable uniform \"%s\".", m_Name.c_str() );
    }
}