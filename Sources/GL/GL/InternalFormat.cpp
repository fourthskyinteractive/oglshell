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

// Τΰιλ: /GL/GL/InternalFormat.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "InternalFormat.h"

namespace GL
{
    const CInternalFormat CObject::m_InternalFormats[] = 
    {
        // Alpha
        CInternalFormat( GL_ALPHA4, "GL_ALPHA4" ),                     
        CInternalFormat( GL_ALPHA8, "GL_ALPHA8" ), 
        CInternalFormat( GL_ALPHA8I_EXT, "GL_ALPHA8I" ),
        CInternalFormat( GL_ALPHA8UI_EXT, "GL_ALPHA8UI" ),    
        CInternalFormat( GL_ALPHA12, "GL_ALPHA12" ),          
        CInternalFormat( GL_ALPHA16, "GL_ALPHA16" ),  
        CInternalFormat( GL_ALPHA16I_EXT, "GL_ALPHA16I" ), 
        CInternalFormat( GL_ALPHA16UI_EXT, "GL_ALPHA16UI" ),
        CInternalFormat( GL_ALPHA16F_ARB, "GL_ALPHA16F" ),
        CInternalFormat( GL_ALPHA32I_EXT, "GL_ALPHA32I" ), 
        CInternalFormat( GL_ALPHA32UI_EXT, "GL_ALPHA32UI" ),
        CInternalFormat( GL_ALPHA32F_ARB, "GL_ALPHA32F" ),
        // Luminance
        CInternalFormat( GL_LUMINANCE4, "GL_LUMINANCE4" ), 
        CInternalFormat( GL_LUMINANCE8, "GL_LUMINANCE8" ), 
        CInternalFormat( GL_LUMINANCE8I_EXT, "GL_LUMINANCE8I" ), 
        CInternalFormat( GL_LUMINANCE8UI_EXT, "GL_LUMINANCE8UI" ), 
        CInternalFormat( GL_LUMINANCE12, "GL_LUMINANCE12" ), 
        CInternalFormat( GL_LUMINANCE16, "GL_LUMINANCE16" ),
        CInternalFormat( GL_LUMINANCE16I_EXT, "GL_LUMINANCE16I" ),
        CInternalFormat( GL_LUMINANCE16UI_EXT, "GL_LUMINANCE16UI" ),
        CInternalFormat( GL_LUMINANCE16F_ARB, "GL_LUMINANCE16F" ),
        CInternalFormat( GL_LUMINANCE32I_EXT, "GL_LUMINANCE32I" ),
        CInternalFormat( GL_LUMINANCE32UI_EXT, "GL_LUMINANCE32UI" ),
        CInternalFormat( GL_LUMINANCE32F_ARB, "GL_LUMINANCE32F" ),
        // LuminanceAlpha
        CInternalFormat( GL_LUMINANCE4_ALPHA4, "GL_LUMINANCE4_ALPHA4" ),  
        CInternalFormat( GL_LUMINANCE6_ALPHA2, "GL_LUMINANCE6_ALPHA2" ),
        CInternalFormat( GL_LUMINANCE8_ALPHA8, "GL_LUMINANCE8_ALPHA8" ), 
        CInternalFormat( GL_LUMINANCE_ALPHA8I_EXT, "GL_LUMINANCE_ALPHA8I" ),
        CInternalFormat( GL_LUMINANCE_ALPHA8UI_EXT, "GL_LUMINANCE_ALPHA8UI" ),
        CInternalFormat( GL_LUMINANCE12_ALPHA4, "GL_LUMINANCE12_ALPHA4" ),
        CInternalFormat( GL_LUMINANCE12_ALPHA12, "GL_LUMINANCE12_ALPHA12" ),
        CInternalFormat( GL_LUMINANCE16_ALPHA16, "GL_LUMINANCE16_ALPHA16" ), 
        CInternalFormat( GL_LUMINANCE_ALPHA16I_EXT, "GL_LUMINANCE_ALPHA16I" ),
        CInternalFormat( GL_LUMINANCE_ALPHA16UI_EXT, "GL_LUMINANCE_ALPHA16UI" ),
        CInternalFormat( GL_LUMINANCE_ALPHA16F_ARB, "GL_LUMINANCE_ALPHA16F" ),
        CInternalFormat( GL_LUMINANCE_ALPHA32I_EXT, "GL_LUMINANCE_ALPHA32I" ),
        CInternalFormat( GL_LUMINANCE_ALPHA32UI_EXT, "GL_LUMINANCE_ALPHA32UI" ),
        CInternalFormat( GL_LUMINANCE_ALPHA32F_ARB, "GL_LUMINANCE_ALPHA32F" ),
        // Intensity
        CInternalFormat( GL_INTENSITY4, "GL_INTENSITY4" ),
        CInternalFormat( GL_INTENSITY8, "GL_INTENSITY8" ),  
        CInternalFormat( GL_INTENSITY8I_EXT, "GL_INTENSITY8I" ),  
        CInternalFormat( GL_INTENSITY8UI_EXT, "GL_INTENSITY8UI" ),  
        CInternalFormat( GL_INTENSITY12, "GL_INTENSITY12" ), 
        CInternalFormat( GL_INTENSITY16, "GL_INTENSITY16" ),
        CInternalFormat( GL_INTENSITY16I_EXT, "GL_INTENSITY16I" ),  
        CInternalFormat( GL_INTENSITY16UI_EXT, "GL_INTENSITY16UI" ), 
        CInternalFormat( GL_INTENSITY16F_ARB, "GL_INTENSITY16F" ),
        CInternalFormat( GL_INTENSITY32I_EXT, "GL_INTENSITY32I" ),  
        CInternalFormat( GL_INTENSITY32UI_EXT, "GL_INTENSITY32UI" ),
        CInternalFormat( GL_INTENSITY32F_ARB, "GL_INTENSITY32F" ),
        // PackedRGB
        CInternalFormat( GL_R3_G3_B2, "GL_R3_G3_B2" ), 
        CInternalFormat( GL_R11F_G11F_B10F_EXT, "GL_R11F_G11F_B10F" ), // GL_EXT_packed_float
        // RGB
        CInternalFormat( GL_RGB4, "GL_RGB4" ),                                                                          
        CInternalFormat( GL_RGB5, "GL_RGB5" ), 
        CInternalFormat( GL_RGB8, "GL_RGB8" ),  
        CInternalFormat( GL_RGB8I_EXT, "GL_RGB8I" ), 
        CInternalFormat( GL_RGB8UI_EXT, "GL_RGB8UI" ), 
        CInternalFormat( GL_RGB10, "GL_RGB10" ),                                                                         
        CInternalFormat( GL_RGB12, "GL_RGB12" ), 
        CInternalFormat( GL_RGB16, "GL_RGB16" ),
        CInternalFormat( GL_RGB16I_EXT, "GL_RGB16I" ),
        CInternalFormat( GL_RGB16UI_EXT, "GL_RGB16UI" ),
        CInternalFormat( GL_RGB16F_ARB, "GL_RGB16F" ),
        CInternalFormat( GL_RGB32I_EXT, "GL_RGB32I" ),
        CInternalFormat( GL_RGB32UI_EXT, "GL_RGB32UI" ),
        CInternalFormat( GL_RGB32F_ARB, "GL_RGB32F" ),
        // RGBA
        CInternalFormat( GL_RGBA2, "GL_RGBA2" ),                                                                        
        CInternalFormat( GL_RGBA4, "GL_RGBA4" ),                                                                         
        CInternalFormat( GL_RGB5_A1, "GL_RGB5_A1" ), 
        CInternalFormat( GL_RGBA8, "GL_RGBA8" ),
        CInternalFormat( GL_RGBA8I_EXT, "GL_RGBA8I" ), 
        CInternalFormat( GL_RGBA8UI_EXT, "GL_RGBA8UI" ),
        CInternalFormat( GL_RGB10_A2, "GL_RGB10_A2" ),                                                               
        CInternalFormat( GL_RGBA12, "GL_RGBA12" ), 
        CInternalFormat( GL_RGBA16, "GL_RGBA16" ), 
        CInternalFormat( GL_RGBA16I_EXT, "GL_RGBA16I" ), 
        CInternalFormat( GL_RGBA16UI_EXT, "GL_RGBA16UI" ), 
        CInternalFormat( GL_RGBA16F_ARB, "GL_RGBA16F" ),
        CInternalFormat( GL_RGBA32I_EXT, "GL_RGBA32I" ), 
        CInternalFormat( GL_RGBA32UI_EXT, "GL_RGBA32UI" ),
        CInternalFormat( GL_RGBA32F_ARB, "GL_RGBA32F" ),
        // Depth
        CInternalFormat( GL_DEPTH_COMPONENT16, "GL_DEPTH_COMPONENT16" ),
        CInternalFormat( GL_DEPTH_COMPONENT24, "GL_DEPTH_COMPONENT24" ),
        CInternalFormat( GL_DEPTH_COMPONENT32, "GL_DEPTH_COMPONENT32" ),
        CInternalFormat( GL_DEPTH_COMPONENT32F_NV, "GL_DEPTH_COMPONENT32F" ),
        // DepthStencil
        CInternalFormat( GL_DEPTH24_STENCIL8_EXT, "GL_DEPTH24_STENCIL8" ), // GL_EXT_packed_depth_stencil
        CInternalFormat( GL_DEPTH32F_STENCIL8_NV, "GL_DEPTH32F_STENCIL8" ), // GL_NV_depth_buffer_float
        // Stencil
        CInternalFormat( GL_STENCIL_INDEX1_EXT, "GL_STENCIL_INDEX1" ),
        CInternalFormat( GL_STENCIL_INDEX4_EXT, "GL_STENCIL_INDEX4" ),
        CInternalFormat( GL_STENCIL_INDEX8_EXT, "GL_STENCIL_INDEX8" ),
        CInternalFormat( GL_STENCIL_INDEX16_EXT, "GL_STENCIL_INDEX16" ),
        // ColorIndex
        CInternalFormat( GL_COLOR_INDEX1_EXT, "GL_COLOR_INDEX1" ),                        
        CInternalFormat( GL_COLOR_INDEX2_EXT, "GL_COLOR_INDEX2" ),                                    
        CInternalFormat( GL_COLOR_INDEX4_EXT, "GL_COLOR_INDEX4" ),                           
        CInternalFormat( GL_COLOR_INDEX8_EXT, "GL_COLOR_INDEX8" ),                                    
        CInternalFormat( GL_COLOR_INDEX12_EXT, "GL_COLOR_INDEX12" ),                           
        CInternalFormat( GL_COLOR_INDEX16_EXT, "GL_COLOR_INDEX16" ),
        // Compressed 
        // GL_EXT_texture_compression_s3tc
        CInternalFormat( GL_COMPRESSED_RGB_S3TC_DXT1_EXT, "GL_COMPRESSED_RGB_S3TC_DXT1" ), 
        CInternalFormat( GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, "GL_COMPRESSED_RGBA_S3TC_DXT1" ),  
        CInternalFormat( GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, "GL_COMPRESSED_RGBA_S3TC_DXT3" ),
        CInternalFormat( GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, "GL_COMPRESSED_RGBA_S3TC_DXT5" ),

        // Vendor-specific

        // GL_ATI_texture_compression_3dc
        CInternalFormat( GL_COMPRESSED_RGB_3DC_ATI, "GL_COMPRESSED_RGB_3DC_ATI" ),
	    // GL_NV_float_buffer
        CInternalFormat( GL_FLOAT_R16_NV, "GL_FLOAT_R16_NV" ),                                                 
        CInternalFormat( GL_FLOAT_R32_NV, "GL_FLOAT_R32_NV" ),	                                       
        CInternalFormat( GL_FLOAT_RG16_NV, "GL_FLOAT_RG16_NV" ),
        CInternalFormat( GL_FLOAT_RG32_NV, "GL_FLOAT_RG32_NV" ),
        CInternalFormat( GL_FLOAT_RGB16_NV, "GL_FLOAT_RGB16_NV" ),               
        CInternalFormat( GL_FLOAT_RGB32_NV, "GL_FLOAT_RGB32_NV" ),                                                             
        CInternalFormat( GL_FLOAT_RGBA16_NV, "GL_FLOAT_RGBA16_NV" ),               
        CInternalFormat( GL_FLOAT_RGBA32_NV, "GL_FLOAT_RGBA32_NV" ),
	    // GL_NV_texture_shader, GL_NV_texture_shader3
        CInternalFormat( GL_SIGNED_ALPHA8_NV, "GL_SIGNED_ALPHA8_NV" ),                                      
        CInternalFormat( GL_SIGNED_LUMINANCE8_NV, "GL_SIGNED_LUMINANCE8_NV" ),                                    
        CInternalFormat( GL_SIGNED_LUMINANCE8_ALPHA8_NV, "GL_SIGNED_LUMINANCE8_ALPHA8_NV" ),   
        CInternalFormat( GL_SIGNED_INTENSITY8_NV, "GL_SIGNED_INTENSITY8_NV" ),                          
        CInternalFormat( GL_SIGNED_RGB8_NV, "GL_SIGNED_RGB8_NV" ),                                       
        CInternalFormat( GL_SIGNED_RGBA8_NV, "GL_SIGNED_RGBA8_NV" ),                                    
        CInternalFormat( GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV, "GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV" ), 
        CInternalFormat( GL_HILO8_NV, "GL_HILO8_NV" ),                                                                        
        CInternalFormat( GL_SIGNED_HILO8_NV, "GL_SIGNED_HILO8_NV" ), 
        CInternalFormat( GL_HILO16_NV, "GL_HILO16_NV" ),                                                            
        CInternalFormat( GL_SIGNED_HILO16_NV, "GL_SIGNED_HILO16_NV" ),                                      
        CInternalFormat( GL_DSDT8_NV, "GL_DSDT8_NV" ),                                                              
        CInternalFormat( GL_DSDT8_MAG8_NV, "GL_DSDT8_MAG8_NV" ),                                                 
        CInternalFormat( GL_DSDT8_MAG8_INTENSITY8_NV, "GL_DSDT8_MAG8_INTENSITY8_NV" ),
        // Terminator
        CInternalFormat( GL_NONE, "" )
    };

    //
    // Constructor
    //
    CInternalFormat::CInternalFormat( 
                                     GLenum SizedFormat, const string &Name 
                                     ):
        m_Name( Name ),

        m_SizedFormat( SizedFormat ),
        m_BaseFormat( GL_NONE )
    {
        //if (SizedFormat == GL_NONE)
        //    throw Sys::CDeveloperException( "GL::InternalFormat", "Invalid <SizedFormat> parameter." );
    }

    //
    // Constructor
    //
    CInternalFormat::CInternalFormat( 
                                     GLenum SizedFormat, GLenum BaseFormat, const string &Name 
                                     ):
        m_Name( Name ),

        m_SizedFormat( SizedFormat ),
        m_BaseFormat( BaseFormat )
    {
        //if (SizedFormat == GL_NONE)
        //    throw Sys::CDeveloperException( "GL::InternalFormat", "Invalid <SizedFormat> parameter." );
        //if (BaseFormat == GL_NONE)
        //    throw Sys::CDeveloperException( "GL::InternalFormat", "Invalid <BaseFormat> parameter." );
    }

    //
    // ConvertFormatToString
    //
    string CInternalFormat::ConvertFormatToString( 
                                                  GLenum Format
                                                  )
    {
        int i = 0;

        /*
        while (true) 
        {
            if (Format == m_InternalFormats[i].m_SizedFormat || Format == m_InternalFormats[i].m_BaseFormat)
                return m_InternalFormats[i].m_Name;

            if (m_InternalFormats[i].m_SizedFormat == GL_NONE)
                break;
            ++i;
        }
        */

        throw Sys::CDeveloperException( "GL::InternalFormat", "Unknown <Format> parameter." );
    }

    //
    // GetName
    //
    const string &CInternalFormat::GetName() const
    {
        return m_Name;
    }
      
    //
    // GetSizedFormat
    //
    GLenum CInternalFormat::GetSizedFormat() const
    {
        return m_SizedFormat;
    }

    //
    // GetBaseFormat
    //
    GLenum CInternalFormat::GetBaseFormat() const
    {
        return m_BaseFormat;
    }

    //
    // GetExternalFormat
    //
    GLenum CInternalFormat::GetExternalFormat() const
    {
        switch (m_SizedFormat) 
        {
        case GL_ALPHA4:
        case GL_ALPHA8:
        case GL_ALPHA12:
        case GL_ALPHA16:
        case GL_ALPHA16F_ARB:
        case GL_ALPHA32F_ARB:
            return GL_ALPHA;

        case GL_ALPHA8I_EXT:
        case GL_ALPHA8UI_EXT:
        case GL_ALPHA16I_EXT:
        case GL_ALPHA16UI_EXT:
        case GL_ALPHA32I_EXT:
        case GL_ALPHA32UI_EXT:
            return GL_ALPHA_INTEGER_EXT;

        case GL_LUMINANCE4:
        case GL_LUMINANCE8:
        case GL_LUMINANCE12:
        case GL_LUMINANCE16:
        case GL_LUMINANCE16F_ARB:
        case GL_LUMINANCE32F_ARB:
            return GL_LUMINANCE;

        case GL_LUMINANCE8I_EXT:
        case GL_LUMINANCE8UI_EXT:
        case GL_LUMINANCE16I_EXT:
        case GL_LUMINANCE16UI_EXT:
        case GL_LUMINANCE32I_EXT:
        case GL_LUMINANCE32UI_EXT:
            return GL_LUMINANCE_INTEGER_EXT;

        case GL_LUMINANCE4_ALPHA4:
        case GL_LUMINANCE6_ALPHA2:
        case GL_LUMINANCE8_ALPHA8:
        case GL_LUMINANCE12_ALPHA4:
        case GL_LUMINANCE12_ALPHA12:
        case GL_LUMINANCE16_ALPHA16:
        case GL_LUMINANCE_ALPHA16F_ARB:
        case GL_LUMINANCE_ALPHA32F_ARB:
            return GL_LUMINANCE_ALPHA;

        case GL_LUMINANCE_ALPHA8I_EXT:
        case GL_LUMINANCE_ALPHA8UI_EXT:
        case GL_LUMINANCE_ALPHA16I_EXT:
        case GL_LUMINANCE_ALPHA16UI_EXT:
        case GL_LUMINANCE_ALPHA32I_EXT:
        case GL_LUMINANCE_ALPHA32UI_EXT:
            return GL_LUMINANCE_ALPHA_INTEGER_EXT;

        case GL_INTENSITY4:
        case GL_INTENSITY8:
        case GL_INTENSITY12:
        case GL_INTENSITY16:
        case GL_INTENSITY16F_ARB:
        case GL_INTENSITY32F_ARB:
            return GL_INTENSITY;

        case GL_INTENSITY8I_EXT:
        case GL_INTENSITY8UI_EXT:
        case GL_INTENSITY16I_EXT:
        case GL_INTENSITY16UI_EXT:
        case GL_INTENSITY32I_EXT:
        case GL_INTENSITY32UI_EXT:
            return GL_RED_INTEGER_EXT; // ?

        case GL_R3_G3_B2:
        case GL_RGB4:
        case GL_RGB5:
        case GL_RGB8:
        case GL_RGB10:
        case GL_RGB12:
        case GL_RGB16:
            // For 8-bit textures, NVIDIA graphics cards are built to match the Microsoft GDI
            // pixel layout, so make sure the pixel format in system memory is BGRA.
            return GL_BGR;

        case GL_RGB8I_EXT:
        case GL_RGB8UI_EXT:
        case GL_RGB16I_EXT:
        case GL_RGB16UI_EXT:
        case GL_RGB32I_EXT:
        case GL_RGB32UI_EXT:
            return GL_BGR_INTEGER_EXT;

        case GL_RGBA2:
        case GL_RGBA4:
        case GL_RGB5_A1:
        case GL_RGBA8:
        case GL_RGB10_A2:
        case GL_RGBA12:
        case GL_RGBA16:
            // For 8-bit textures, NVIDIA graphics cards are built to match the Microsoft GDI
            // pixel layout, so make sure the pixel format in system memory is BGRA.
            return GL_BGRA;

        case GL_RGBA8I_EXT:
        case GL_RGBA8UI_EXT:
        case GL_RGBA16I_EXT:
        case GL_RGBA16UI_EXT:
        case GL_RGBA32I_EXT:
        case GL_RGBA32UI_EXT:
            return GL_BGRA_INTEGER_EXT;

        // GL_EXT_packed_float
        case GL_R11F_G11F_B10F_EXT: 
            return GL_RGB;

        case GL_DEPTH_COMPONENT16:
        case GL_DEPTH_COMPONENT24:
        case GL_DEPTH_COMPONENT32:
        case GL_DEPTH_COMPONENT32F_NV:
            return GL_DEPTH_COMPONENT;

        // GL_EXT_packed_depth_stencil
        case GL_DEPTH24_STENCIL8_EXT:
        case GL_DEPTH32F_STENCIL8_NV:
            return GL_DEPTH_STENCIL_EXT;

        case GL_COLOR_INDEX1_EXT:
        case GL_COLOR_INDEX2_EXT:
        case GL_COLOR_INDEX4_EXT:
        case GL_COLOR_INDEX8_EXT:
        case GL_COLOR_INDEX12_EXT:
        case GL_COLOR_INDEX16_EXT:
            return GL_COLOR_INDEX;

        // GL_NV_texture_shader, GL_NV_texture_shader3
        case GL_HILO8_NV:
        case GL_SIGNED_HILO8_NV:
        case GL_HILO16_NV:              
        case GL_SIGNED_HILO16_NV:
            return GL_HILO_NV;
        case GL_DSDT8_NV:
            return GL_DSDT_NV;
        case GL_DSDT8_MAG8_NV:
            return GL_DSDT_MAG_NV;
        case GL_DSDT8_MAG8_INTENSITY8_NV:
            return GL_DSDT_MAG_VIB_NV;

        case GL_FLOAT_R16_NV:
        case GL_FLOAT_R32_NV:
            return GL_FLOAT_R_NV;
        case GL_FLOAT_RG16_NV:
        case GL_FLOAT_RG32_NV:
            return GL_FLOAT_RG_NV;
        case GL_FLOAT_RGB16_NV:
        case GL_FLOAT_RGB32_NV:
            return GL_FLOAT_RGB_NV;
        case GL_FLOAT_RGBA16_NV: 
        case GL_FLOAT_RGBA32_NV:
            return GL_FLOAT_RGBA_NV;

        default:
            throw Sys::CDeveloperException( "GL::InternalFormat", "Unknown <m_SizedFormat> member." );
        }

        return GL_NONE;
    }
    
    //
    // GetType
    //
    GLenum CInternalFormat::GetType() const
    {
        switch (m_SizedFormat) 
        {
        case GL_ALPHA8:
        case GL_LUMINANCE8:
        case GL_LUMINANCE8_ALPHA8:
        case GL_INTENSITY8:
        case GL_RGB8:
        case GL_RGBA8:
            return GL_UNSIGNED_BYTE;

        case GL_ALPHA16:
        case GL_LUMINANCE16:
        case GL_LUMINANCE16_ALPHA16:
        case GL_INTENSITY16:
        case GL_RGB16:
        case GL_RGBA16:
        case GL_DEPTH_COMPONENT16:
            return GL_UNSIGNED_SHORT;

        case GL_DEPTH_COMPONENT24:
        case GL_DEPTH_COMPONENT32:
            return GL_UNSIGNED_INT;

        case GL_ALPHA16F_ARB:
        case GL_LUMINANCE16F_ARB:
        case GL_LUMINANCE_ALPHA16F_ARB:
        case GL_INTENSITY16F_ARB:
            return GL_FLOAT; //(m_Extensions->ARB_half_float_pixel) ? GL_HALF_FLOAT_ARB : GL_FLOAT;

        case GL_ALPHA32F_ARB:
        case GL_LUMINANCE32F_ARB:
        case GL_LUMINANCE_ALPHA32F_ARB:
        case GL_INTENSITY32F_ARB:
        case GL_DEPTH_COMPONENT32F_NV: 
            return GL_FLOAT;

        case GL_FLOAT_R16_NV:
        case GL_FLOAT_R32_NV:
        case GL_FLOAT_RG16_NV:
        case GL_FLOAT_RG32_NV:
        case GL_FLOAT_RGB16_NV:
        case GL_FLOAT_RGB32_NV:
        case GL_FLOAT_RGBA16_NV: 
        case GL_FLOAT_RGBA32_NV:
            return GL_FLOAT;

        case GL_R11F_G11F_B10F_EXT:
            return GL_UNSIGNED_INT_10F_11F_11F_REV_EXT;

        // GL_EXT_packed_depth_stencil
        case GL_DEPTH24_STENCIL8_EXT:
            return GL_UNSIGNED_INT_24_8_EXT;

        // GL_NV_depth_buffer_float
        case GL_DEPTH32F_STENCIL8_NV:
            return GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV;

        default:
            throw Sys::CDeveloperException( "GL::InternalFormat", "Unknown <m_SizedFormat> member." );
        }

        return GL_NONE;
    }

}