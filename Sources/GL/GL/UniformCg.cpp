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

// Τΰιλ: /GL/GL/UniformCg.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#ifdef CG_SDK

#include "Uniform.h"
#include "Buffer.h"

namespace GL
{
    //
    // Constructor
    //
    CCgUniform::CCgUniform( 
                           const string& Name, CGparameter Parameter 
                           ):
        IUniform( Name ),

        m_Parameter( Parameter )
    {
    }

    //
    // SetBool
    //
    void CCgUniform::SetBool( 
                             bool x 
                             )
    {
        cgSetParameter1i( m_Parameter, x ? CG_TRUE : CG_FALSE );
    }

    //
    // SetFloat
    //
    void CCgUniform::SetFloat( 
                              GLfloat x 
                              )
    {
        cgSetParameter1f( m_Parameter, x );
    }

    //
    // SetInt
    //
    void CCgUniform::SetInt( 
                            GLint x 
                            )
    {
        cgSetParameter1i( m_Parameter, x );
    }

    //
    // SetUnsignedInt
    //
    void CCgUniform::SetUnsignedInt( 
                                    GLuint x 
                                    )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedInt() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloat2
    //
    void CCgUniform::SetFloat2( 
                               GLfloat x, GLfloat y 
                               )
    {
        cgSetParameter2f( m_Parameter, x, y );
    }

    //
    // SetInt2
    //
    void CCgUniform::SetInt2( 
                             GLint x, GLint y 
                             )
    {
        cgSetParameter2i( m_Parameter, x, y );
    }

    //
    // SetUnsignedInt2
    //
    void CCgUniform::SetUnsignedInt2( 
                                     GLuint x, GLuint y 
                                     )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt2()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedInt2() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloat3
    //
    void CCgUniform::SetFloat3( 
                               GLfloat x, GLfloat y, GLfloat z 
                               )
    {
        cgSetParameter3f( m_Parameter, x, y, z );
    }

    //
    // SetInt3
    //
    void CCgUniform::SetInt3( 
                             GLint x, GLint y, GLint z 
                             )
    {
        cgSetParameter3i( m_Parameter, x, y, z );
    }

    //
    // SetUnsignedInt3
    //
    void CCgUniform::SetUnsignedInt3( 
                                     GLuint x, GLuint y, GLuint z 
                                     )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt3()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedInt3() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloat4
    //
    void CCgUniform::SetFloat4( 
                               GLfloat x, GLfloat y, GLfloat z, GLfloat w 
                               )
    {
        cgSetParameter4f( m_Parameter, x, y, z, w );
    }

    //
    // SetInt4
    //
    void CCgUniform::SetInt4( 
                             GLint x, GLint y, GLint z, GLint w 
                             )
    {
        cgSetParameter4i( m_Parameter, x, y, z, w );
    }

    //
    // SetUnsignedInt4
    //
    void CCgUniform::SetUnsignedInt4( 
                                     GLuint x, GLuint y, GLuint z, GLuint w 
                                     )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedInt4()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedInt4() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloatArray
    //
    void CCgUniform::SetFloatArray( 
                                   GLsizei Dimension, GLsizei Count, 
                                   const GLfloat *Array 
                                   )
    {
        cgSetParameterValuefr( m_Parameter, Dimension * Count, Array ); // ???
    }

    //
    // SetIntArray
    //
    void CCgUniform::SetIntArray( 
                                 GLsizei Dimension, GLsizei Count, 
                                 const GLint *Array 
                                 )
    {
        cgSetParameterValueir( m_Parameter, Dimension * Count, Array ); // ???
    }

    //
    // SetIntArray
    //
    void CCgUniform::SetUnsignedIntArray( 
                                         GLsizei Dimension, GLsizei Count, 
                                         const GLuint *Array 
                                         )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntArray()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedIntArray() : This method is not implemented, and should not be used." );
    }

    #ifdef MATH_LIB_INCLUDED
         
    //
    // SetFloatVec2
    //
    void CCgUniform::SetFloatVec2( 
                                  const Vec2<GLfloat>& v 
                                  )
    {
        cgSetParameter2fv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetIntVec2
    //
    void CCgUniform::SetIntVec2( 
                                const Vec2<GLint>& v 
                                )
    {
        cgSetParameter2iv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetUnsignedIntVec2
    //
    void CCgUniform::SetUnsignedIntVec2( 
                                        const Vec2<GLuint>& v 
                                        )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec2()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedIntVec2() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloatVec3
    //
    void CCgUniform::SetFloatVec3( 
                                  const Vec3<GLfloat>& v 
                                  )
    {
        cgSetParameter3fv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetIntVec3
    //
    void CCgUniform::SetIntVec3( 
                                const Vec3<GLint>& v 
                                )
    {
        cgSetParameter3iv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetUnsignedIntVec3
    //
    void CCgUniform::SetUnsignedIntVec3( 
                                        const Vec3<GLuint>& v 
                                        )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec3()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedIntVec3() : This method is not implemented, and should not be used." );
    }

    //
    // SetFloatVec4
    //
    void CCgUniform::SetFloatVec4( 
                                  const Vec4<GLfloat>& v 
                                  )
    {
        cgSetParameter4fv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetIntVec4
    //
    void CCgUniform::SetIntVec4( 
                                const Vec4<GLint>& v 
                                )
    {
        cgSetParameter4iv( m_Parameter, &v[ 0 ] );
    }

    //
    // SetUnsignedIntVec4
    //
    void CCgUniform::SetUnsignedIntVec4( 
                                        const Vec4<GLuint>& v 
                                        )
    {
    #ifdef _DEBUG
        if (!m_Extensions->EXT_gpu_shader4)
            throw CExtensionException( this, "::SetUnsignedIntVec4()", "GL_EXT_gpu_shader4" );
    #endif
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::SetUnsignedIntVec4() : This method is not implemented, and should not be used." );
    }
         
    //
    // SetFloatMat2
    //
    void CCgUniform::SetFloatMat2( 
                                  const Mat2& m, EMatrixOrder Order 
                                  )
    {
        if (Order == MO_COLUMN_MAJOR)
            cgSetMatrixParameterfc( m_Parameter, &m[ 0 ][ 0 ] );
        else
            cgSetMatrixParameterfr( m_Parameter, &m[ 0 ][ 0 ] );
    }

    //
    // SetFloatMat3
    //
    void CCgUniform::SetFloatMat3( 
                                  const Mat3& m, EMatrixOrder Order 
                                  )
    {
        if (Order == MO_COLUMN_MAJOR)
            cgSetMatrixParameterfc( m_Parameter, &m[ 0 ][ 0 ] );
        else
            cgSetMatrixParameterfr( m_Parameter, &m[ 0 ][ 0 ] );
    }

    //
    // SetFloatMat4
    //
    void CCgUniform::SetFloatMat4( 
                                  const Mat4& m, EMatrixOrder Order 
                                  )
    {
        if (Order == MO_COLUMN_MAJOR)
            cgSetMatrixParameterfc( m_Parameter, &m[ 0 ][ 0 ] );
        else
            cgSetMatrixParameterfr( m_Parameter, &m[ 0 ][ 0 ] );
    }

    #endif // MATH_LIB_INCLUDED

    //
    // Constructor
    //
    CCgSamplerUniform::CCgSamplerUniform( 
                                         const string& Name, CGparameter Parameter 
                                         ):
        ISamplerUniform( Name ),

        m_Parameter( Parameter )
    {
    }

    //
    // SetSampler
    //
    void CCgSamplerUniform::SetSampler( 
                                       Ptr<const CTexture> Texture 
                                       )
    {
        cgGLSetTextureParameter( m_Parameter, Texture->m_Texture );
        /*
    #ifdef _DEBUG
        CGerror Error = cgGetError();
        if (Error != CG_NO_ERROR)
            throw CCgException( this, Error, "::SetSampler() : A Cg error has occured." );
    #endif
    */
    }

    //
    // EnableSampler
    //
    void CCgSamplerUniform::EnableSampler() const
    {
        cgGLEnableTextureParameter( m_Parameter );
        /*
    #ifdef _DEBUG
        CGerror Error = cgGetError();
        if (Error != CG_NO_ERROR)
            throw CCgException( this, Error, "::EnableSampler() : A Cg error has occured." );
    #endif
    */
    }
       
    //
    // DisableSampler
    //
    void CCgSamplerUniform::DisableSampler() const
    {
        cgGLDisableTextureParameter( m_Parameter );
        /*
    #ifdef _DEBUG
        CGerror Error = cgGetError();
        if (Error != CG_NO_ERROR)
            throw CCgException( this, Error, "::DisableSampler() : A Cg error has occured." );
    #endif
    */
    }

    //
    // Constructor
    //
    CCgBindableUniform::CCgBindableUniform( 
                                           const string& Name, CGprogram Program, CGparameter Parameter
                                           ):
        IBindableUniform( Name ),

        m_Program( Program ),
        m_Parameter( Parameter )
    {
    }

    //
    // GetBufferSize
    //
    GLsizei CCgBindableUniform::GetBufferSize() const
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::GetBufferSize() : This method is not implemented, and should not be used." );
            
        return 0;
    }
    
    //
    // GetElementOffset
    // 
    GLintptr CCgBindableUniform::GetElementOffset( 
                                                  GLuint Index 
                                                  )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::GetElementOffset() : This method is not implemented, and should not be used." );
    }

    //
    // AttachBuffer
    //
    void CCgBindableUniform::AttachBuffer( 
                                          Ptr<const CBuffer> Buffer 
                                          )
    {
        throw Sys::CDeveloperException( this, Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::AttachBuffer() : This method is not implemented, and should not be used." );
    }
}

#endif // CG_SDK