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

// Файл: /GL/GL/Texture.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Texture.h"

namespace GL
{
    //
    // Contructor
    //
	CTexture::TDesc::TDesc():
		RedSize( 0 ),
		GreenSize( 0 ),
		BlueSize( 0 ),
		AlphaSize( 0 ),
		LuminanceSize( 0 ),
		IntensitySize( 0 ),
		DepthSize( 0 ),
		StencilSize( 0 ),
		IndexSize( 0 ),
		HiSize( 0 ),
		LoSize( 0 ),
		DsSize( 0 ),
		DtSize( 0 ),
		MagSize( 0 )
	{
	}

    //
    // Contructor
    //
	CTexture::CTexture( 
                       GLenum Target, 
                       bool MipMap 
                       ):
		m_Texture( 0 ),
		m_Target( Target ),
		m_MipMap( MipMap )
	{
        glClearErrors();
        glGenTextures( 1, &m_Texture );
        glBindTexture( m_Target, m_Texture );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( "GL::CTexture", Error, "::CTexture() : Failed to generate texture object." );
	}

    //
    // Destructor
    //
	CTexture::~CTexture()
	{
        glClearErrors();
        glDeleteTextures( 1, &m_Texture );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CTexture() : Failed to delete texture object." );
	}

    //
    // EnumCompressedFormats
    //
	void CTexture::EnumCompressedFormats( 
                                         vector<CInternalFormat> *Formats 
                                         )
	{
        throw Sys::CDeveloperException( "GL::CTexture", Sys::CDeveloperException::ERROR_METHOD_NOT_IMPLEMENTED, 
            "::EnumCompressedFormats() : This method is not implemented, and should not be used." );
	}

    //
    // GetWidth
    //
	GLsizei CTexture::GetWidth( 
                               GLint Level 
                               ) const
	{
		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		GLint Width;
		if (m_Target != GL_TEXTURE_CUBE_MAP)
			glGetTexLevelParameteriv( m_Target, Level, GL_TEXTURE_WIDTH, &Width );
		else
			glGetTexLevelParameteriv( GL_TEXTURE_CUBE_MAP_POSITIVE_X, Level, GL_TEXTURE_WIDTH, &Width );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWidth() : An OpenGL error has occured." );

		return Width;
	}

    //
    // GetHeight
    //
	GLsizei CTexture::GetHeight( 
                                GLint Level 
                                ) const
	{
		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		GLint Height;
		if (m_Target != GL_TEXTURE_CUBE_MAP)
			glGetTexLevelParameteriv( m_Target, Level, GL_TEXTURE_HEIGHT, &Height );
		else
			glGetTexLevelParameteriv( GL_TEXTURE_CUBE_MAP_POSITIVE_X, Level, GL_TEXTURE_HEIGHT, &Height );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
			throw CException( this, Error, "::GetHeight() : An OpenGL error has occured." );

		return Height;
	}

    //
    // GetBorder
    //
	GLint CTexture::GetBorder() const
	{
		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		GLint Border;
		if (m_Target != GL_TEXTURE_CUBE_MAP)
			glGetTexLevelParameteriv( m_Target, 0, GL_TEXTURE_BORDER, &Border );
		else
			glGetTexLevelParameteriv( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_BORDER, &Border );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetBorder() : An OpenGL error has occured." );

        return Border;
	}

    //
    // GetInternalFormat
    //
	GLenum CTexture::GetInternalFormat() const
	{
		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		GLint InternalFormat;
		if (m_Target != GL_TEXTURE_CUBE_MAP)
		    glGetTexLevelParameteriv( m_Target, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );
		else
		    glGetTexLevelParameteriv( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetInternalFormat() : An OpenGL error has occured." );

		return InternalFormat;
	}

    //
    // GetDesc
    //
    void CTexture::GetDesc( 
                           TDesc *Desc 
                           ) const
	{	
		GLenum Target;
    
		if (m_Target == GL_TEXTURE_CUBE_MAP)
			Target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		else
			Target = m_Target;

		glClearErrors();
		glBindTexture( Target, m_Texture );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_RED_SIZE, &Desc->RedSize );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_GREEN_SIZE, &Desc->GreenSize );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_BLUE_SIZE, &Desc->BlueSize );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_ALPHA_SIZE, &Desc->AlphaSize );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_LUMINANCE_SIZE, &Desc->LuminanceSize );
		glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_INTENSITY_SIZE, &Desc->IntensitySize );
		if (m_Extensions->OpenGL_1_4 || m_Extensions->ARB_depth_texture)
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_DEPTH_SIZE, &Desc->DepthSize );
		if (m_Extensions->EXT_packed_depth_stencil)
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_STENCIL_SIZE_EXT, &Desc->StencilSize );
		if (m_Extensions->EXT_paletted_texture)
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_INDEX_SIZE_EXT, &Desc->IndexSize );
		if (m_Extensions->NV_texture_shader) 
        {
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_HI_SIZE_NV, &Desc->HiSize );
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_LO_SIZE_NV, &Desc->LoSize );
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_DS_SIZE_NV, &Desc->DsSize );
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_DT_SIZE_NV, &Desc->DtSize );
			glGetTexLevelParameteriv( Target, 0, GL_TEXTURE_MAG_SIZE_NV, &Desc->MagSize );
		}
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetDesc() : An OpenGL error has occured." );
	}

    //
    // IsMipMap
    //
    bool CTexture::IsMipMap() const
    {
        return m_MipMap;
    }

    //
    // SetFilter
    //
	void CTexture::SetFilter( 
                             GLenum Mag, 
                             GLenum Min 
                             )
	{
        if (!IsFilter( Mag ))
            throw Sys::CDeveloperException( this, "::SetFilter() : Invalid <Mag> parameter." );
        if (!IsFilter( Min ))
            throw Sys::CDeveloperException( this, "::SetFilter() : Invalid <Min> parameter." );

		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		glTexParameteri( m_Target, GL_TEXTURE_MAG_FILTER, Mag );
		glTexParameteri( m_Target, GL_TEXTURE_MIN_FILTER, Min ); 
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetFilter() : An OpenGL error has occured." );
	}

    //
    // GetFilter
    //
	GLenum CTexture::GetFilter( 
                               GLenum Pname 
                               ) const
	{
		if (Pname != GL_TEXTURE_MAG_FILTER && Pname != GL_TEXTURE_MIN_FILTER)
            throw Sys::CDeveloperException( this, "::GetFilter() : Invalid <Pname> parameter." );

		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		GLint Param;
		glGetTexParameteriv( m_Target, Pname, &Param );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetFilter() : An OpenGL error has occured." );

		return Param;
	}

    //
    // SetFilterAnisotropy
    //
	void CTexture::SetFilterAnisotropy( 
                                       GLfloat MaxAnisotropy 
                                       )
	{
		if (!m_Extensions->EXT_texture_filter_anisotropic)
            throw CExtensionException( this, "::SetFilterAnisotropy()", "GL_EXT_texture_filter_anisotropic" );

		glClearErrors();
		glBindTexture( m_Target, m_Texture );
		glTexParameteri( m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameterf( m_Target, GL_TEXTURE_MAX_ANISOTROPY_EXT, MaxAnisotropy );
		GLenum Error = glGetError();                                                                
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetFilterAnisotropy() : An OpenGL error has occured." );
    }

    //
    // SetBorderColor
    //
    void CTexture::SetBorderColor( 
                                  const GLfloat *Color
                                 )
    {
        glClearErrors();
		glBindTexture( m_Target, m_Texture );
        glTexParameterfv( m_Target, GL_TEXTURE_BORDER_COLOR, Color );
		GLenum Error = glGetError();                                                                
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetBorderColor() : An OpenGL error has occured." );                              
    }

    //
    // SetCompareMode
    //
    void CTexture::SetCompareMode( 
                                  GLenum Mode 
                                  )
    {
        if (Mode != GL_COMPARE_R_TO_TEXTURE)
            throw Sys::CDeveloperException( this, "Invalid <Mode> parameter." );

        glClearErrors();
		glBindTexture( m_Target, m_Texture );
        glTexParameteri( m_Target, GL_TEXTURE_COMPARE_MODE, Mode );
		GLenum Error = glGetError();                                                                
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetCompareMode() : An OpenGL error has occured." );
    }

    //
    // SetCompareFunc
    //
    void CTexture::SetCompareFunc( 
                                  GLenum Func 
                                  )
    {
        // TODO: Check <Func> parameter.

        glClearErrors();
		glBindTexture( m_Target, m_Texture );
        glTexParameteri( m_Target, GL_TEXTURE_COMPARE_FUNC, Func );
		GLenum Error = glGetError();                                                                
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetCompareFunc() : An OpenGL error has occured." );
    }

    //
    // SetGenerateMipMap
    //
	void CTexture::SetGenerateMipMap( 
                                     bool Gen 
                                     )
	{
		glClearErrors();
		glBindTexture( m_Target, m_Texture );
        glHint( GL_GENERATE_MIPMAP, GL_NICEST );
        glTexParameteri( m_Target, GL_GENERATE_MIPMAP, Gen ? GL_TRUE : GL_FALSE );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetGenerateMipMap() : An OpenGL error has occured" );
	}

    //
    // EnumInternalFormats
    //
	void CTexture::EnumInternalFormats( 
                                       GLenum Target, 
                                       vector<CInternalFormat> *Formats 
                                       )
	{
		GLenum ProxyTarget;

		Formats->clear();

		switch (Target) 
        {
		case GL_TEXTURE_1D:
			ProxyTarget = GL_PROXY_TEXTURE_1D;
			break;
		case GL_TEXTURE_2D:
			ProxyTarget = GL_PROXY_TEXTURE_2D;
			break;
		case GL_TEXTURE_RECTANGLE_ARB:
			if (!m_Extensions->ARB_texture_rectangle && !m_Extensions->EXT_texture_rectangle && !m_Extensions->NV_texture_rectangle)
                throw CExtensionException( "GL::CTexture", "::EnumInternalFormats()", "GL_ARB[EXT, NV]_texture_rectangle." );
			ProxyTarget = GL_PROXY_TEXTURE_RECTANGLE_ARB;
			break;
		case GL_TEXTURE_3D:
			ProxyTarget = GL_PROXY_TEXTURE_3D;
			break;
		case GL_TEXTURE_CUBE_MAP:
			ProxyTarget = GL_PROXY_TEXTURE_CUBE_MAP;
			break;
		default:
            throw Sys::CDeveloperException( "GL::CTexture", "::EnumInternalFormats() : Invalid <Target> parameter." );
		};

		GLuint Texture;
                            
		glGenTextures( 1, &Texture );
		glBindTexture( ProxyTarget, Texture );

		for (int i = 0; m_InternalFormats[i].GetSizedFormat() != GL_NONE; ++i) 
        {
			const CInternalFormat& Format = m_InternalFormats[i];

			glClearErrors();
			switch (ProxyTarget) 
			{
			case GL_PROXY_TEXTURE_1D:
				glTexImage1D( ProxyTarget, 0, Format.GetSizedFormat(), 32, 0, 
					Format.GetExternalFormat(), Format.GetType(), NULL );
				break;
			case GL_PROXY_TEXTURE_2D:
			case GL_PROXY_TEXTURE_RECTANGLE_ARB:
			case GL_PROXY_TEXTURE_CUBE_MAP:
				glTexImage2D( ProxyTarget, 0, Format.GetSizedFormat(), 32, 32, 0, 
					Format.GetExternalFormat(), Format.GetType(), NULL );
				break;
			case GL_PROXY_TEXTURE_3D:
				glTexImage3D( ProxyTarget, 0, Format.GetSizedFormat(), 32, 32, 32, 0, 
					Format.GetExternalFormat(), Format.GetType(), NULL );
				break;
			}
			if (glGetError() != GL_NO_ERROR)
				continue;

			GLint InternalFormat;
			glGetTexLevelParameteriv( ProxyTarget, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );
			if (InternalFormat == Format.GetSizedFormat())
				Formats->push_back( Format );
		}

		glBindTexture( ProxyTarget, 0 );
		glDeleteTextures( 1, &Texture );

        if (Formats->empty())
            throw Sys::CException( 0, "GL::CTexture", "::EnumInternalFormats() : Supported texture formats are not found." );
	}

    //
    // IsFilter
    //
    bool CTexture::IsFilter(
                            GLenum Filter 
                            ) const
    {
        static const GLenum TexFilters[] = 
        {
			GL_NEAREST, 
            GL_LINEAR, 
			GL_NEAREST_MIPMAP_NEAREST, 
            GL_LINEAR_MIPMAP_NEAREST, 
			GL_NEAREST_MIPMAP_LINEAR, 
            GL_LINEAR_MIPMAP_LINEAR, 
			0
		};

		int i;

		for (i = 0; TexFilters[ i ] != 0; ++i) 
        {
			if (Filter == TexFilters[ i ])
				break;
		}

		if (TexFilters[i] == 0)
			return false;

        return true;
    }
        
    //
    // IsWrapMode
    //
    bool CTexture::IsWrapMode( 
                              GLenum Wrap 
                              ) const
    {
        static const GLenum WrapModes[] = 
        {
            // OpenGL 1.1
            GL_CLAMP,
            GL_REPEAT,
            // OpenGL 1.2
            GL_CLAMP_TO_EDGE,
            // OpenGL 1.3
            GL_CLAMP_TO_BORDER,
            // OpenGL 1.4
            GL_MIRRORED_REPEAT,
            // GL_EXT_texture_mirror_clamp/GL_ATI_texture_mirror_once
            GL_MIRROR_CLAMP_EXT, // GL_MIRROR_CLAMP_ATI
            GL_MIRROR_CLAMP_TO_EDGE_EXT, // GL_MIRROR_CLAMP_TO_EDGE_ATI
            GL_MIRROR_CLAMP_TO_BORDER_EXT,
            0
        };

        int i;

        for (i = 0; WrapModes[i] != 0; ++i) 
        {
            if (Wrap == WrapModes[i])
                break;
        }

        if (WrapModes[i] == 0)
            return false;

        return true;
    }

    //
    // Constructor
    //
	CTexture1D::CTexture1D( 
                           GLenum InternalFormat,  GLsizei Width, GLint Border, bool MipMap, 
                           GLenum Format, GLenum Type, const GLvoid *Pixels 
                           ):
		CTexture( GL_TEXTURE_1D, MipMap )
	{
		if (!MipMap)
			glTexImage1D( GL_TEXTURE_1D, 0, InternalFormat, Width, Border, Format, Type, Pixels );
		else 
        {
			glTexParameteri( GL_TEXTURE_1D, GL_GENERATE_MIPMAP, GL_TRUE );
			glTexImage1D( GL_TEXTURE_1D, 0, InternalFormat, Width, Border, Format, Type, Pixels );
			glTexParameteri( GL_TEXTURE_1D, GL_GENERATE_MIPMAP, GL_FALSE );
		}

		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CTexture1D() : Failed to create 1D texture." );
	}
    
    //
    // Constructor
    //
	CTexture1D::CTexture1D( 
                           GLenum InternalFormat, GLsizei Width, GLint Border, bool MipMap 
                           ):
		CTexture( GL_TEXTURE_1D, MipMap )
	{
        CInternalFormat FormatObj( InternalFormat ); 

		if (!MipMap) 
        {
			glTexImage1D( GL_TEXTURE_1D, 0, InternalFormat, Width, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );          
			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CTexture1D() : Failed to allocate 1D texture." );
		}
		else 
        {
			GLint Level = 0;

			while (true) 
            {
				glTexImage1D( GL_TEXTURE_1D, Level, InternalFormat, Width, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
				GLenum Error = glGetError();
				if (Error != GL_NO_ERROR)
                    throw CException( this, Error, "::CTexture1D() : Failed to allocate 1D texture." );

				if (Width == 1)
					break;
				++Level;
				if (Width > 1)
					Width >>= 1;
			}
		}
	}

    //
    // Constructor
    //
	void CTexture1D::EnumInternalFormats( 
                                         vector<CInternalFormat> *Formats 
                                         )
	{
		CTexture::EnumInternalFormats( GL_TEXTURE_1D, Formats );
	}

    //
    // SetWrap
    //
	void CTexture1D::SetWrap( 
                             GLenum s 
                             )
	{
        if (!IsWrapMode( s ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <s> parameter." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, s );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetWrap() : An OpenGL error has occured." );
	}

    //
    // GetWrap
    //
	GLenum CTexture1D::GetWrap() const
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		GLint Wrap;
		glGetTexParameteriv( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, &Wrap );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWrap() : An OpenGL error has occured." );

		return Wrap;
	}

    //
    // Resize
    //
    void CTexture1D::Resize( 
                            GLsizei Width, GLint Border 
                            )
	{
		GLint InternalFormat;

		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		glGetTexLevelParameteriv( GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );

		CInternalFormat FormatObj( InternalFormat ); 

		if (!m_MipMap) 
        {
            glTexImage1D( GL_TEXTURE_1D, 0, InternalFormat, Width, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );          
			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::Resize() : An OpenGL error has occured." );
		}
		else 
        {
			GLint Level = 0;

			while (true) 
            {
				glTexImage1D( GL_TEXTURE_1D, Level, InternalFormat, Width, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
				GLenum Error = glGetError();
				if (Error != GL_NO_ERROR)
                    throw CException( this, Error, "::Resize() : An OpenGL error has occured." );

				if (Width == 1)
					break;
				++Level;
				if (Width > 1)
					Width >>= 1;
			}
		}
	}

    //
    // SetSubImage
    //
	void CTexture1D::SetSubImage( 
                                 GLint Level, GLint xOffset, GLsizei Width,
                                 GLenum Format, GLenum Type, const GLvoid *Pixels 
                                 )
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		glTexSubImage1D( GL_TEXTURE_1D, Level, xOffset, Width, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubImage() : An OpenGL error has occured.." );
	}

    //
    // GetImage
    //
	void CTexture1D::GetImage( 
                              GLint Level, GLenum Format, GLenum Type, 
                              GLvoid *Pixels 
                              ) const
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		glGetTexImage( GL_TEXTURE_1D, Level, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetImage() : An OpenGL error has occured." );
	}

    //
    // GenerateMipMap
    //
	void CTexture1D::GenerateMipMap()
	{
		if (!m_Extensions->EXT_framebuffer_object)
            throw CExtensionException( this, "::GenerateMipMap()", "GL_EXT_framebuffer_object." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_1D, m_Texture );
		glGenerateMipmapEXT( GL_TEXTURE_1D );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GenerateMipMap() : An OpenGL error has occured." );
	}

    //
    // Constructor
    //
	CTexture2D::CTexture2D( 
                           GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border, bool MipMap, 
                           GLenum Format, GLenum Type, const GLvoid *Pixels 
                           ):
		CTexture( GL_TEXTURE_2D, MipMap )
	{
		if (!MipMap)
			glTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, Format, Type, Pixels );           
		else 
        {
			glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
			glTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, Format, Type, Pixels );
			glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE );
		}

		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CTexture2D() : Failed to create 2D texture." );
	}

    //
    // CTexture2D
    // Данный конструктор вызывается в том случае, когда текстура создаётся из сжатых DDS данных.
    //
	CTexture2D::CTexture2D( 
                           GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border, bool MipMap, 
                           const vector<GLsizei>& MipSizes, const GLvoid *Data 
                           ):
        CTexture( GL_TEXTURE_2D, MipMap )
	{
        if (MipSizes.empty())
            throw Sys::CDeveloperException( this, "::CTexture2D() : Invalid <MipSizes> parameter." );
    
		if (!MipMap)
			glCompressedTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, MipSizes[0], Data );      
		else 
        {
			if (MipSizes.size() == 1) 
            {
				glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
				glCompressedTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, MipSizes[0], Data );
				glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE );
			}
			else 
            {
				GLint Level = 0;
				GLsizei Offset = 0;
            
                for (CONST_VECTOR_ITERATION( GLsizei, MipSizes, i ))
                {
					glCompressedTexImage2D( GL_TEXTURE_2D, Level, InternalFormat, Width, Height, Border, *i, static_cast<const GLubyte *>( Data ) + Offset );
					GLenum Error = glGetError();
					if (Error != GL_NO_ERROR)
                        throw CException( this, Error, "::CTexture2D() : Failed to create compressed 2D texture, index of MIP level: %d.", Level ); 
                    
                    ++Level;
                    if (Width > 1)
						Width >>= 1;
                    if (Height > 1)
						Height >>= 1;
                    Offset += (*i); // Increase by size of processed MIP level.
				}
			}
		}

		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CTexrure2D() : Failed to create compressed 2D texture." );
	}
    
    //
    // Constructor
    //
	CTexture2D::CTexture2D( 
                           GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border, bool MipMap 
                           ):
		CTexture( GL_TEXTURE_2D, MipMap )
	{
		CInternalFormat FormatObj( InternalFormat ); 

		if (!MipMap) 
        {
			glTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );          
			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CTexture2D() : Failed to allocate 2D texture." );
		}
		else 
        {
			GLint Level = 0;

			while (true) 
            {
				glTexImage2D( GL_TEXTURE_2D, Level, InternalFormat, Width, Height, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
				GLenum Error = glGetError();
				if (Error != GL_NO_ERROR)
                    throw CException( this, Error, "::CTexture2D() : Failed to allocate 2D texture." );

				if (Width == 1 && Height == 1)
				    break;
				++Level;
				if (Width > 1)
					Width >>= 1;
				if (Height > 1)
					Height >>= 1;
			}
		}
	}

    //
    // EnumInternalFormats
    //
	void CTexture2D::EnumInternalFormats( 
                                         vector<CInternalFormat> *Formats
                                         )
	{
		CTexture::EnumInternalFormats( GL_TEXTURE_2D, Formats );
	}

    //
    // SetWrap
    //
	void CTexture2D::SetWrap( 
                             GLenum s, GLenum t 
                             )
	{
        if (!IsWrapMode( s ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <s> parameter." );
        if (!IsWrapMode( t ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <t> parameter." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetWrap() : An OpenGL error has occured." );
	}

    //
    // GetWrap
    //
	GLenum CTexture2D::GetWrap( 
                               GLenum Pname 
                               ) const
	{
		if (Pname != GL_TEXTURE_WRAP_S && Pname != GL_TEXTURE_WRAP_T)
            throw Sys::CDeveloperException( this, "::GetWrap() : Invalid <Pname> parameter." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		GLint Wrap;
		glGetTexParameteriv( GL_TEXTURE_2D, Pname, &Wrap );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWrap() : An OpenGL error has occured." );

		return Wrap;
	}

    //
    // Resize
    //
    void CTexture2D::Resize( 
                            GLsizei Width, GLsizei Height, GLint Border 
                            )
	{
		GLint InternalFormat;

		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );

		CInternalFormat FormatObj( InternalFormat ); 	

		if (!m_MipMap) 
        {
			glTexImage2D( GL_TEXTURE_2D, 0, InternalFormat, Width, Height, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );          
			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
				throw CException( this, Error, "::Resize() : An OpenGL error has occured." );
		}
		else 
        {
			GLint Level = 0;

			while (true)
            {
				glTexImage2D( GL_TEXTURE_2D, Level, InternalFormat, Width, Height, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
				GLenum Error = glGetError();
				if (Error != GL_NO_ERROR)
					throw CException( this, Error, "::Resize() : An OpenGL error has occured." );

				if (Width == 1 && Height == 1)
				    break;
				++Level;
				if (Width > 1)
				    Width >>= 1;
				if (Height > 1)
				    Height >>= 1;
			}
		}
	}

    //
    // SetSubImage
    //
	void CTexture2D::SetSubImage( 
                                 GLint Level, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height,
                                 GLenum Format,  GLenum Type, const GLvoid *Pixels 
                                 )
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glTexSubImage2D( GL_TEXTURE_2D, Level, xOffset, yOffset, Width, Height, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubImage() : An OpenGL error has occured." );
	}

    //
    // SetCompressedSubImage
    //
	void CTexture2D::SetCompressedSubImage( 
                                           GLint Level, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height,
                                           GLenum Format, GLsizei ImageSize, const GLvoid *Data 
                                           )
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glCompressedTexSubImage2D( GL_TEXTURE_2D, Level, xOffset, yOffset, Width, Height, Format, ImageSize, Data );    
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
		    throw CException( this, Error, "::SetCompressedSubImage() : An OpenGL error has occured." );
    }

    //
    // GetImage
    //
	void CTexture2D::GetImage( 
                              GLint Level, GLenum Format, GLenum Type, 
                              GLvoid *Pixels 
                              ) const
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glGetTexImage( GL_TEXTURE_2D, Level, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetImage() : An OpenGL error has occured." );
	}

    //
    // GetCompressedImage
    //
	void CTexture2D::GetCompressedImage( 
                                        GLint Level, 
                                        GLvoid *Data 
                                        ) const
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glGetCompressedTexImage( GL_TEXTURE_2D, Level, Data );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetCompressedImage() : An OpenGL error has occured." );
	}

    //
    // GenerateMipMap
    //
	void CTexture2D::GenerateMipMap()
	{
		if (!m_Extensions->EXT_framebuffer_object)
            throw CExtensionException( this, "::GenerateMipMap()", "GL_EXT_framebuffer_object." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_2D, m_Texture );
		glGenerateMipmapEXT( GL_TEXTURE_2D );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
			throw CException( this, Error, "::GenerateMipMap() : An OpenGL error has occured." );
	}

    //
    // Constructor
    //
	CTextureRectangle::CTextureRectangle( 
                                         GLenum InternalFormat, GLsizei Width, GLsizei Height, 
                                         GLenum Format, GLenum Type, const GLvoid *Pixels 
                                         ):
		CTexture( GL_TEXTURE_RECTANGLE_ARB )
	{
		glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, InternalFormat, Width, Height, 0, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CTextureRectangle() : Failed to create rectangle texture." );
	}
    
    //
    // Constructor
    //
	CTextureRectangle::CTextureRectangle( 
                                         GLenum InternalFormat, GLsizei Width, GLsizei Height 
                                         ):
		CTexture( GL_TEXTURE_RECTANGLE_ARB )
	{
		CInternalFormat FormatObj( InternalFormat ); 

		glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, InternalFormat, Width, Height, 0, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );          
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
			throw CException( this, Error, "::CTextureRectangle() : Failed to allocate rectangle texture." );
	}                                      

    //
    // EnumInternalFormats
    //
	void CTextureRectangle::EnumInternalFormats( 
                                                vector<CInternalFormat> *Formats 
                                                )
	{
		CTexture::EnumInternalFormats( GL_TEXTURE_RECTANGLE_ARB, Formats );
	}

    //
    // SetWrap
    //
	void CTextureRectangle::SetWrap( 
                                    GLenum s, GLenum t 
                                    )
	{
        // TODO: GL_REPEAT на ATI переводит в Software Render, протестировать!

		if (!IsWrapMode( s ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <s> parameter." );
        if (!IsWrapMode( t ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <t> parameter." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_RECTANGLE_ARB, m_Texture );
		glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, s ); 
		glTexParameteri( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, t );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetWrap() : An OpenGL error has occured." );
	}

    //
    // GetWrap
    //
	GLenum CTextureRectangle::GetWrap( 
                                      GLenum Pname 
                                      ) const
	{
		if (Pname != GL_TEXTURE_WRAP_S && Pname != GL_TEXTURE_WRAP_T)
            throw Sys::CDeveloperException( this, "::GetWrap() : Invalid <Pname> parameter." );

		glClearErrors();
		glBindTexture( GL_TEXTURE_RECTANGLE_ARB, m_Texture );
		GLint Wrap;
		glGetTexParameteriv( GL_TEXTURE_RECTANGLE_ARB, Pname, &Wrap );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWrap() : An OpenGL error has occured." );

		return Wrap;
	}

    //
    // Resize
    //
    void CTextureRectangle::Resize( 
                                   GLsizei Width, GLsizei Height 
                                   )
	{
		GLint InternalFormat;

		glClearErrors();
		glBindTexture( GL_TEXTURE_RECTANGLE_ARB, m_Texture );
		glGetTexLevelParameteriv( GL_TEXTURE_RECTANGLE_ARB, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );

		CInternalFormat FormatObj( InternalFormat ); 	

		glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, InternalFormat, Width, Height, 0, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::Resize() : An OpenGL error has occured." );
	}

    //
    // SetSubImage
    //
	void CTextureRectangle::SetSubImage( 
                                        GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height,
                                        GLenum Format, GLenum Type, const GLvoid *Pixels 
                                        )
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_RECTANGLE_ARB, m_Texture );
		glTexSubImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, xOffset, yOffset, Width, Height, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubImage() : An OpenGL error has occured." );
	}

    //
    // GetImage
    //
	void CTextureRectangle::GetImage( 
                                     GLenum Format, GLenum Type, GLvoid *Pixels 
                                     ) const
	{
		glClearErrors();
		glBindTexture( GL_TEXTURE_RECTANGLE_ARB, m_Texture );
		glGetTexImage( GL_TEXTURE_RECTANGLE_ARB, 0, Format, Type, Pixels );
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetImage() : An OpenGL error has occured." );
	}

    //
    // Constructor
    //
    CTextureCubeMap::CTextureCubeMap():
        CTexture( GL_TEXTURE_CUBE_MAP )
    {
    }

    //
    // Constructor
    //
    CTextureCubeMap::CTextureCubeMap( 
                                     GLenum InternalFormat, GLsizei Size, GLint Border ):
        CTexture( GL_TEXTURE_CUBE_MAP )
    {
        CInternalFormat FormatObj( InternalFormat ); 

        for (int i = 0; i < NUM_CUBE_MAP_FACES; ++i) 
        {
            glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, InternalFormat, Size, Size, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
            GLenum Error = glGetError();
            if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::CTextureCubeMap() : Failed to allocate CUBE texture." );
        }
    }

    //
    // SetWrap
    //
    void CTextureCubeMap::SetWrap( 
                                  GLenum s, GLenum t 
                                  )
    {
        if (!IsWrapMode( s ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <s> parameter." );
        if (!IsWrapMode( t ))
            throw Sys::CDeveloperException( this, "::SetWrap() : Invalid <t> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        // Once face selection is performed for a cube map texture, texture fetching and
        // filtering operates just as is does for a 2D texture. This means that both the
        // <s> and <t> wrap modes are used, but not the <r> wrap mode.
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, s );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, t );
        GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetWrap() : An OpenGL error has occured." );
    }

    //
    // GetWrap
    //
    GLenum CTextureCubeMap::GetWrap( 
                                    GLenum Pname 
                                    ) const
    {
        if (Pname != GL_TEXTURE_WRAP_S && Pname != GL_TEXTURE_WRAP_T)
            throw Sys::CDeveloperException( this, "::GetWrap() : Invalid <Pname> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        GLint Wrap;
        glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, Pname, &Wrap );
        GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetWrap() : An OpenGL error has occured." );

        return Wrap;
    }

    //
    // Resize
    //
    void CTextureCubeMap::Resize( 
                                 GLsizei Size, GLint Border 
                                 )
    {
        GLint InternalFormat;

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glGetTexLevelParameteriv( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_INTERNAL_FORMAT, &InternalFormat );

        CInternalFormat FormatObj( InternalFormat ); 	

        for (int i = 0; i < NUM_CUBE_MAP_FACES; ++i) 
        {
            glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, InternalFormat, Size, Size, Border, FormatObj.GetExternalFormat(), FormatObj.GetType(), NULL );
            GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
                throw CException( this, Error, "::Resize() : An OpenGL error has occured." );
        }
    }

    //
    // SetImage
    //
    void CTextureCubeMap::SetImage( 
                                   GLenum Face, GLenum InternalFormat, GLsizei Size, GLint Border, 
                                   GLenum Format, GLenum Type, const GLvoid *Pixels 
                                   )
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::SetImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glTexImage2D( Face, 0, InternalFormat, Size, Size, Border, Format, Type, Pixels );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetImage() : An OpenGL error has occured." );
    }
      
    //
    // SetCompressedImage
    //
    void CTextureCubeMap::SetCompressedImage( 
                                             GLenum Face, GLenum InternalFormat, GLsizei Size, GLint Border, 
                                             GLsizei ImageSize, const GLvoid *Data 
                                             )
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::SetCompressedImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glCompressedTexImage2D( Face, 0, InternalFormat, Size, Size, Border, ImageSize, Data );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetCompressedImage() : An OpenGL error has occured." );
    }

    //
    // SetSubImage
    //
    void CTextureCubeMap::SetSubImage( 
                                      GLenum Face, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                      GLenum Format, GLenum Type, const GLvoid *Pixels 
                                      )
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::SetSubImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glTexSubImage2D( Face, 0, xOffset, yOffset, Width, Height, Format, Type, Pixels );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetSubImage() : An OpenGL error has occured." );
    }
        
    //
    // SetCompressedSubImage
    //
    void CTextureCubeMap::SetCompressedSubImage( 
                                                GLenum Face, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                                GLenum Format, GLsizei ImageSize, const GLvoid *Data
                                                )
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::SetCompressedSubImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glCompressedTexSubImage2D( Face, 0, xOffset, yOffset, Width, Height, Format, ImageSize, Data );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::SetCompressedSubImage() : An OpenGL error has occured." );
    }
        
    //
    // GetImage
    //
    void CTextureCubeMap::GetImage( 
                                   GLenum Face, GLenum Format, GLenum Type, 
                                   GLvoid *Pixels 
                                   ) const
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::GetImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glGetTexImage( Face, 0, Format, Type, Pixels );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetImage() : An OpenGL error has occured." );
    }

    //
    // GetCompressedImage
    //
    void CTextureCubeMap::GetCompressedImage( 
                                             GLenum Face, 
                                             GLvoid *Data 
                                             ) const
    {
        if (!IsFace( Face ))
            throw Sys::CDeveloperException( this, "::GetCompressedImage() : Invalid <Face> parameter." );

        glClearErrors();
        glBindTexture( GL_TEXTURE_CUBE_MAP, m_Texture );
        glGetCompressedTexImage( Face, 0, Data );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::GetCompressedImage() : An OpenGL error has occured." );
    }

    //
    // IsFace
    //
    bool CTextureCubeMap::IsFace( 
                                 GLenum Face 
                                 ) const
    {
        static const GLenum CubeFaces[] = 
        {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
            0
        };

        int i;

		for (i = 0; CubeFaces[ i ] != 0; ++i) 
        {
			if (Face == CubeFaces[ i ])
				break;
		}

		if (CubeFaces[ i ] == 0)
			return false;

        return true;
    }
} 