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

e-mail: victor.coda@gmail.com
*/

// Τΰιλ: /GL/ExtensionRegistry.cpp
//    

#include "Precompiled.h"
#pragma hdrstop

#ifdef _DEBUG
//#define GLWRAPPER_VALIDATE_EXTENSIONS_NAMES
#endif

namespace GL 
{
    //
    // Constructor
    //
    CRegistry::CRegistry( 
                         bool WindowSystem 
                         ):
        m_VersionStr( NULL ),
        m_ExtensionsStr( NULL )
    {
        if (WindowSystem)
        {
	#ifdef _WIN32
            if (!wglGetExtensionsStringARB)
                throw Sys::CException( this, "::CRegistry() : Failed to obtain wglGetExtensionsStringARB entry point." );
                
            HDC DC = wglGetCurrentDC();
            if (!DC)
                throw Sys::CException( this, "::CRegistry() : Invalid current DC." );
       
            m_ExtensionsStr = wglGetExtensionsStringARB( DC );
	#elif defined (__linux__)
            Display *Dpy = glXGetCurrentDisplay();
            if (!Dpy)
                throw Sys::CException( this, "::CRegistry() : Invalid current Display." );
                
            m_ExtensionsString = glXGetClientString( Dpy, GLX_EXTENSIONS );
	#endif
        }
		else
        {
            m_VersionStr = reinterpret_cast<const char *>( glGetString( GL_VERSION ) );
            m_ExtensionsStr = reinterpret_cast<const char *>( glGetString( GL_EXTENSIONS ) );
        }

        TokenizeString();
    }

    //
    // GetExtensionsList
    //
    const set<string>& CRegistry::GetExtensionsList() const
    {
        return m_Extensions;
    }

    //
    // QueryVersion
    //
    bool CRegistry::QueryVersion( 
                                 int MajorNumber, int MinorNumber 
                                 ) const
    {
        int Major;
        int Minor;
      
        int NumScan = sscanf( m_VersionStr, "%d.%d", &Major, &Minor );
        if (NumScan != 2)
            throw Sys::CException( this, "::QueryVersion() : Failed to query version.\nOpenGL version string malformed!" );

        if (Major < MajorNumber)
            return false;
        else if (Major == MajorNumber) 
        {
            if (Minor < MinorNumber)
                return false;
        }

        return true;
    }
    
    //
    // QueryExtension
    //
    bool CRegistry::QueryExtension( 
                                   const string& Name 
                                   ) const
    {
    #ifdef GLWRAPPER_VALIDATE_EXTENSIONS_NAMES

        if (Name.find( CH_WHITE_SPACE ) != END_OF_STRING)
            throw Sys::CDeveloperException( this, "::QueryExtension() : Invalid OpenGL extension name: \n\n\"%s\".\n\nWhitespaces are not allowed.", Name.c_str() );

        const char *DomainPrefixes[] =
        {
            "GL_",
            "WGL_",
            "GLX_",
            NULL
        };

        const char *VendorPrefixes[] =
        {
            "AMD_",
            "AMDX_",
            "ARB_",
            "ATI_",
            "ATIX_",
            "EXT_",
            "EXTX_",
            "HP_",
            "IBM_",
            "KTX_",
            "NV_",
            "NVX_",
            "OES_",
            "S3_",
            "SGI_",
            "SGIS_",
            "SGIX_",
            NULL
        };

        int Index;

        for (Index = 0; DomainPrefixes[ Index ]; ++Index)
        {
            if (Name.find( DomainPrefixes[ Index ] ) != END_OF_STRING)
                break;
        }

        if (!DomainPrefixes[ Index ])
            throw Sys::CDeveloperException( this, "::QueryExtension() : Invalid OpenGL extension name: \n\n\"%s\".\n\nUnknown domain prefix.", Name.c_str() );

        for (Index = 0; VendorPrefixes[ Index ]; ++Index)
        {
            if (Name.find( VendorPrefixes[ Index ] ) != END_OF_STRING)
                break;
        }

        if (!VendorPrefixes[ Index ])
            throw Sys::CDeveloperException( this, "::QueryExtension() : Invalid OpenGL extension name: \n\n\"%s\".\n\nUnknown vendor prefix.", Name.c_str() );
    
    #endif // GLWRAPPER_VALIDATE_EXTENSIONS_NAMES

        set<string>::const_iterator i = m_Extensions.find( Name );
        if (i != m_Extensions.end())
            return true;

        return false;
    }

    //
    // TokenizeString
    //
    void CRegistry::TokenizeString()
    {
        int Length = static_cast<int>( strlen( m_ExtensionsStr ) );

        for (int First = 0, Curr = 0; Curr < Length; ++Curr)
        {
            if (m_ExtensionsStr[ Curr ] == CH_WHITE_SPACE)
            {
                string Token;

                for (int i = First; i < Curr; ++i)
                    Token.push_back( m_ExtensionsStr[ i ] );
                m_Extensions.insert( Token );

                First = Curr + 1;
            }
        }
    }

    //
    // Constructor
    //
    CExtensionRegistry::CExtensionRegistry():
        CRegistry( false )
    {
        OpenGL_1_1 = QueryVersion( 1, 1 );
        OpenGL_1_2 = QueryVersion( 1, 2 );
        OpenGL_1_3 = QueryVersion( 1, 3 );
        OpenGL_1_4 = QueryVersion( 1, 4 );
        OpenGL_1_5 = QueryVersion( 1, 5 );
        OpenGL_2_0 = QueryVersion( 2, 0 );
        OpenGL_2_1 = QueryVersion( 2, 1 );

        AMD_performance_monitor = QueryExtension( "GL_AMD_performance_monitor" );
        AMDX_vertex_shader_tesselator = QueryExtension( "GL_AMDX_vertex_shader_tesselator" );

        ARB_color_buffer_float = QueryExtension( "GL_ARB_color_buffer_float" );
        ARB_depth_texture = QueryExtension( "GL_ARB_depth_texture" );
        ARB_draw_buffers = QueryExtension( "GL_ARB_draw_buffers" );
        ARB_fragment_program = QueryExtension( "GL_ARB_fragment_program" );
        ARB_fragment_program_shadow = QueryExtension( "GL_ARB_fragment_program_shadow" );
        ARB_fragment_shader = QueryExtension( "GL_ARB_fragment_shader" );
        ARB_half_float_pixel = QueryExtension( "GL_ARB_half_float_pixel" );
        ARB_imaging = QueryExtension( "GL_ARB_imaging" );
        ARB_matrix_palette = QueryExtension( "GL_ARB_matrix_palette" );
        ARB_multisample = QueryExtension( "GL_ARB_multisample" );
        ARB_multitexture = QueryExtension( "GL_ARB_multitexture" );
        ARB_occlusion_query = QueryExtension( "GL_ARB_occlusion_query" );
        ARB_pixel_buffer_object = QueryExtension( "GL_ARB_pixel_buffer_object" );
        ARB_point_parameters = QueryExtension( "GL_ARB_point_parameters" );
        ARB_point_sprite = QueryExtension( "GL_ARB_point_sprite" );
        ARB_shader_objects = QueryExtension( "GL_ARB_shader_objects" );
        ARB_shading_language_100 = QueryExtension( "GL_ARB_shading_language_100" );
        ARB_shadow = QueryExtension( "GL_ARB_shadow" );
        ARB_shadow_ambient = QueryExtension( "GL_ARB_shadow_ambient" );
        ARB_texture_border_clamp = QueryExtension( "GL_ARB_texture_border_clamp" );
        ARB_texture_compression = QueryExtension( "GL_ARB_texture_compression" );
        ARB_texture_cube_map = QueryExtension( "GL_ARB_texture_cube_map" );
        ARB_texture_env_add = QueryExtension( "GL_ARB_texture_env_add" );
        ARB_texture_env_combine = QueryExtension( "GL_ARB_texture_env_combine" );
        ARB_texture_env_crossbar = QueryExtension( "GL_ARB_texture_env_crossbar" );
        ARB_texture_env_dot3 = QueryExtension( "GL_ARB_texture_env_dot3" );
        ARB_texture_float = QueryExtension( "GL_ARB_texture_float" );
        ARB_texture_mirrored_repeat = QueryExtension( "GL_ARB_texture_mirrored_repeat" );
        ARB_texture_non_power_of_two = QueryExtension( "GL_ARB_texture_non_power_of_two" );
        ARB_texture_rectangle = QueryExtension( "GL_ARB_texture_rectangle" );
        ARB_transpose_matrix = QueryExtension( "GL_ARB_transpose_matrix" );
        ARB_vertex_blend = QueryExtension( "GL_ARB_vertex_blend" );
        ARB_vertex_buffer_object = QueryExtension( "GL_ARB_vertex_buffer_object" );
        ARB_vertex_program = QueryExtension( "GL_ARB_vertex_program" );
        ARB_vertex_shader = QueryExtension( "GL_ARB_vertex_shader" );
        ARB_window_pos = QueryExtension( "GL_ARB_window_pos" );

        ATI_draw_buffers = QueryExtension( "GL_ATI_draw_buffers" );
        ATI_element_array = QueryExtension( "GL_ATI_element_array" );
        ATI_envmap_bumpmap = QueryExtension( "GL_ATI_envmap_bumpmap" );
        ATI_fragment_shader = QueryExtension( "GL_ATI_fragment_shader" );
        ATI_map_buffer_object = QueryExtension( "GL_ATI_map_buffer_object" );
        ATI_meminfo = QueryExtension( "GL_ATI_meminfo" );
        ATI_separate_stencil = QueryExtension( "GL_ATI_separate_stencil" );
        ATI_shader_texture_lod = QueryExtension( "GL_ATI_shader_texture_lod" );
        ATI_texture_compression_3dc = QueryExtension( "GL_ATI_texture_compression_3dc" );
        ATI_texture_env_combine3 = QueryExtension( "GL_ATI_texture_env_combine3" );
        ATI_texture_float = QueryExtension( "GL_ATI_texture_float" );
        ATI_texture_mirror_once = QueryExtension( "GL_ATI_texture_mirror_once" );
        ATI_vertex_array_object = QueryExtension( "GL_ATI_vertex_array_object" );
        ATI_vertex_attrib_array_object = QueryExtension( "GL_ATI_vertex_attrib_array_object" );
        ATI_vertex_streams = QueryExtension( "GL_ATI_vertex_streams" );

        EXT_abgr = QueryExtension( "GL_EXT_abgr" );
        EXT_bgra = QueryExtension( "GL_EXT_bgra" );
        EXT_bindable_uniform = QueryExtension( "GL_EXT_bindable_uniform" );
        EXT_blend_color = QueryExtension( "GL_EXT_blend_color" );
        EXT_blend_equation_separate = QueryExtension( "GL_EXT_blend_equation_separate" );
        EXT_blend_func_separate = QueryExtension( "GL_EXT_blend_func_separate" );
        EXT_blend_minmax = QueryExtension( "GL_EXT_blend_minmax" );
        EXT_blend_subtract = QueryExtension( "GL_EXT_blend_subtract" );
        EXT_Cg_shader = QueryExtension( "GL_EXT_Cg_shader" );
        EXT_clip_volume_hint = QueryExtension( "GL_EXT_clip_volume_hint" );
        EXT_compiled_vertex_array = QueryExtension( "GL_EXT_compiled_vertex_array" );
        EXT_depth_bounds_test = QueryExtension( "GL_EXT_depth_bounds_test" );
        EXT_draw_buffers = QueryExtension( "GL_EXT_draw_buffers" );
        EXT_draw_buffers2 = QueryExtension( "GL_EXT_draw_buffers2" );
        EXT_draw_instanced = QueryExtension( "GL_EXT_draw_instanced" );
        EXT_draw_range_elements = QueryExtension( "GL_EXT_draw_range_elements" );
        EXT_fog_coord = QueryExtension( "GL_EXT_fog_coord" );
        EXT_framebuffer_blit = QueryExtension( "GL_EXT_framebuffer_blit" );
        EXT_framebuffer_multisample = QueryExtension( "GL_EXT_framebuffer_multisample" );
        EXT_framebuffer_object = QueryExtension( "GL_EXT_framebuffer_object" );
        EXT_framebuffer_sRGB = QueryExtension( "GL_EXT_framebuffer_sRGB" );
        EXT_geometry_shader4 = QueryExtension( "GL_EXT_geometry_shader4" );
        EXT_gpu_shader4 = QueryExtension( "GL_EXT_gpu_shader4" );
        EXT_multi_draw_arrays = QueryExtension( "GL_EXT_multi_draw_arrays" );
        EXT_packed_depth_stencil = QueryExtension( "GL_EXT_packed_depth_stencil" );
        EXT_packed_float = QueryExtension( "GL_EXT_packed_float" );
        EXT_packed_pixels = QueryExtension( "GL_EXT_packed_pixels" );
        EXT_paletted_texture = QueryExtension( "GL_EXT_paletted_texture" );
        EXT_pixel_buffer_object = QueryExtension( "GL_EXT_pixel_buffer_object" );
        EXT_point_parameters = QueryExtension( "GL_EXT_point_parameters" );
        EXT_rescale_normal = QueryExtension( "GL_EXT_rescale_normal" );
        EXT_secondary_color = QueryExtension( "GL_EXT_secondary_color" );
        EXT_separate_specular_color = QueryExtension( "GL_EXT_separate_specular_color" );
        EXT_shadow_funcs = QueryExtension( "GL_EXT_shadow_funcs" );
        EXT_stencil_two_side = QueryExtension( "GL_EXT_stencil_two_side" );
        EXT_stencil_wrap = QueryExtension( "GL_EXT_stencil_wrap" );
        EXT_timer_query = QueryExtension( "GL_EXT_timer_query" );
        EXT_texture_3D = QueryExtension( "GL_EXT_texture_3D" );
        EXT_texture_array = QueryExtension( "GL_EXT_texture_array" );
        EXT_texture_buffer_object = QueryExtension( "GL_EXT_texture_buffer_object" );
        EXT_texture_compression_latc = QueryExtension( "GL_EXT_texture_compression_latc" );
        EXT_texture_compression_rgtc = QueryExtension( "GL_EXT_texture_compression_rgtc" );
        EXT_texture_compression_s3tc = QueryExtension( "GL_EXT_texture_compression_s3tc" );
        EXT_texture_cube_map = QueryExtension( "GL_EXT_texture_cube_map" );
        EXT_texture_edge_clamp = QueryExtension( "GL_EXT_texture_edge_clamp" );
        EXT_texture_env_add = QueryExtension( "GL_EXT_texture_env_add" );
        EXT_texture_env_combine = QueryExtension( "GL_EXT_texture_env_combine" );
        EXT_texture_env_dot3 = QueryExtension( "GL_EXT_texture_env_dot3" );
        EXT_texture_filter_anisotropic = QueryExtension( "GL_EXT_texture_filter_anisotropic" );
        EXT_texture_integer = QueryExtension( "GL_EXT_texture_integer" );
        EXT_texture_lod = QueryExtension( "GL_EXT_texture_lod" );
        EXT_texture_lod_bias = QueryExtension( "GL_EXT_texture_lod_bias" );
        EXT_texture_mirror_clamp = QueryExtension( "GL_EXT_texture_mirror_clamp" );
        EXT_texture_object = QueryExtension( "GL_EXT_texture_object" );
        EXT_texture_rectangle = QueryExtension( "GL_EXT_texture_rectangle" );
        EXT_texture_shared_exponent = QueryExtension( "GL_EXT_texture_shared_exponent" );
        EXT_transform_feedback = QueryExtension( "GL_EXT_transform_feedback" );
        EXT_vertex_array = QueryExtension( "GL_EXT_vertex_array" );
        EXT_vertex_shader = QueryExtension( "GL_EXT_vertex_shader" );

        HP_occlusion_test = QueryExtension( "GL_HP_occlusion_test" );

        IBM_rasterpos_clip = QueryExtension( "GL_IBM_rasterpos_clip" );
        IBM_texture_mirrored_repeat = QueryExtension( "GL_IBM_texture_mirrored_repeat" );

        KTX_buffer_region = QueryExtension( "GL_KTX_buffer_region" );

        NV_blend_square = QueryExtension( "GL_NV_blend_square" );
        NV_conditional_render = QueryExtension( "GL_NV_conditional_render" );
        NV_copy_depth_to_color = QueryExtension( "GL_NV_copy_depth_to_color" );
        NV_depth_buffer_float = QueryExtension( "GL_NV_depth_buffer_float" );
        NV_depth_clamp = QueryExtension( "GL_NV_depth_clamp" );
        NV_fence = QueryExtension( "GL_NV_fence" );
        NV_float_buffer = QueryExtension( "GL_NV_float_buffer" );
        NV_fog_distance = QueryExtension( "GL_NV_fog_distance" );
        NV_fragment_program = QueryExtension( "GL_NV_fragment_program" );
        NV_fragment_program2 = QueryExtension( "GL_NV_fragment_program2" );
        NV_fragment_program_option = QueryExtension( "GL_NV_fragment_program_option" );
        NV_framebuffer_multisample_coverage = QueryExtension( "GL_NV_framebuffer_multisample_coverage" );
        NV_geometry_program4 = QueryExtension( "GL_NV_geometry_program4" );
        NV_gpu_program4 = QueryExtension( "GL_NV_gpu_program4" );
        NV_half_float = QueryExtension( "GL_NV_half_float" );
        NV_light_max_exponent = QueryExtension( "GL_NV_light_max_exponent" );
        NV_multisample_filter_hint = QueryExtension( "GL_NV_multisample_filter_hint" );
        NV_occlusion_query = QueryExtension( "GL_NV_occlusion_query" );
        NV_packed_depth_stencil = QueryExtension( "GL_NV_packed_depth_stencil" );
        NV_parameter_buffer_object = QueryExtension( "GL_NV_parameter_buffer_object" );
        NV_pixel_data_range = QueryExtension( "GL_NV_pixel_data_range" );
        NV_point_sprite = QueryExtension( "GL_NV_point_sprite" );
        NV_primitive_restart = QueryExtension( "GL_NV_primitive_restart" );
        NV_register_combiners = QueryExtension( "GL_NV_register_combiners" );
        NV_register_combiners2 = QueryExtension( "GL_NV_register_combiners2" );
        NV_texgen_reflection = QueryExtension( "GL_NV_texgen_reflection" );
        NV_texture_compression_vtc = QueryExtension( "GL_NV_texture_compression_vtc" );
        NV_texture_env_combine4 = QueryExtension( "GL_NV_texture_env_combine4" );
        NV_texture_expand_normal = QueryExtension( "GL_NV_texture_expand_normal" );
        NV_texture_rectangle = QueryExtension( "GL_NV_texture_rectangle" );
        NV_texture_shader = QueryExtension( "GL_NV_texture_shader" );
        NV_texture_shader2 = QueryExtension( "GL_NV_texture_shader2" );
        NV_texture_shader3 = QueryExtension( "GL_NV_texture_shader3" );
        NV_transform_feedback = QueryExtension( "GL_NV_transform_feedback" );
        NV_vertex_array_range = QueryExtension( "GL_NV_vertex_array_range" );
        NV_vertex_array_range2 = QueryExtension( "GL_NV_vertex_array_range2" );
        NV_vertex_program = QueryExtension( "GL_NV_vertex_program" );
        NV_vertex_program1_1 = QueryExtension( "GL_NV_vertex_program1_1" );
        NV_vertex_program2 = QueryExtension( "GL_NV_vertex_program2" );
        NV_vertex_program2_option = QueryExtension( "GL_NV_vertex_program2_option" );
        NV_vertex_program3 = QueryExtension( "GL_NV_vertex_program3" );
        NV_vertex_program4 = QueryExtension( "GL_NV_vertex_program4" );
        NVX_conditional_render = QueryExtension( "GL_NVX_conditional_render" );

        S3_s3tc = QueryExtension( "GL_S3_s3tc" );

        SGIS_generate_mipmap = QueryExtension( "GL_SGIS_generate_mipmap" );
        SGIS_texture_lod = QueryExtension( "GL_SGIS_texture_lod" );
        SGIX_depth_texture = QueryExtension( "GL_SGIX_depth_texture" );
        SGIX_shadow = QueryExtension( "GL_SGIX_shadow" );

	#ifdef _WIN32
		WindowSystem = new CExtensionRegistryWGL();
	#elif defined (__linux__)
		WindowSystem = new CExtensionRegistryGLX();
	#endif // _WIN32
    }

	#ifdef _WIN32

    //
    // Constructor
    //
    CExtensionRegistryWGL::CExtensionRegistryWGL():
        CRegistry( true )
    {
        ARB_buffer_region = QueryExtension( "WGL_ARB_buffer_region" );
        ARB_extensions_string = QueryExtension( "WGL_ARB_extensions_string" );
        ARB_make_current_read = QueryExtension( "WGL_ARB_make_current_read" );
        ARB_multisample = QueryExtension( "WGL_ARB_multisample" );
        ARB_pbuffer = QueryExtension( "WGL_ARB_pbuffer" );
        ARB_pixel_format = QueryExtension( "WGL_ARB_pixel_format" );
        ARB_pixel_format_float = QueryExtension( "WGL_ARB_pixel_format_float" );
        ARB_render_texture = QueryExtension( "WGL_ARB_render_texture" );

        ATI_pixel_format_float = QueryExtension( "WGL_ATI_pixel_format_float" );
        ATI_render_texture_rectangle = QueryExtension( "WGL_ATI_render_texture_rectangle" );

        EXT_extensions_string = QueryExtension( "WGL_EXT_extensions_string" );
        EXT_framebuffer_sRGB = QueryExtension( "WGL_EXT_framebuffer_sRGB" );
        EXT_pixel_format_packed_float = QueryExtension( "WGL_EXT_pixel_format_packed_float" );
        EXT_swap_control = QueryExtension( "WGL_EXT_swap_control" );

        NV_float_buffer = QueryExtension( "WGL_NV_float_buffer" );
        NV_render_depth_texture = QueryExtension( "WGL_NV_render_depth_texture" );
        NV_render_texture_rectangle = QueryExtension( "WGL_NV_render_texture_rectangle" );
    }

	#elif defined (__linux__)

    //
    // Constructor
    //
    CExtensionRegistryGLX::CExtensionRegistryGLX():
        CRegistry( true )
    {
        ARB_fbconfig_float = QueryExtension( "GLX_ARB_fbconfig_float" );
        ARB_get_proc_address = QueryExtension( "GLX_ARB_get_proc_address" );
        ARB_multisample = QueryExtension( "GLX_ARB_multisample" );
        
        EXT_fbconfig_packed_float = QueryExtension( "GLX_EXT_fbconfig_packed_float" );
        EXT_framebuffer_sRGB = QueryExtension( "GLX_EXT_framebuffer_sRGB" );
        EXT_import_context = QueryExtension( "GLX_EXT_import_context" );
        EXT_texture_from_pixmap = QueryExtension( "GLX_EXT_texture_from_pixmap" );
        EXT_visual_info = QueryExtension( "GLX_EXT_visual_info" );
        EXT_visual_rating = QueryExtension( "GLX_EXT_visual_rating" );
           
        NV_float_buffer = QueryExtension( "GLX_NV_float_buffer" );
        NV_swap_group = QueryExtension( "GLX_NV_swap_group" );
        NV_video_out = QueryExtension( "GLX_NV_video_out" );
        
        SGI_video_sync = QueryExtension( "GLX_SGI_video_sync" );
        SGI_swap_control = QueryExtension( "GLX_SGI_swap_control" );  
        SGIX_fbconfig = QueryExtension( "GLX_SGIX_fbconfig" );
        SGIX_pbuffer = QueryExtension( "GLX_SGIX_pbuffer" );
    }
    
	#endif // _WIN32
}