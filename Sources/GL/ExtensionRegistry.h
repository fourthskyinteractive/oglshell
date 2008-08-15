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

// Файл: /GL/ExtensionRegistry.h
//                                                                

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_EXTENSION_REGISTRY_H__
#define __GL_EXTENSION_REGISTRY_H__

namespace GL
{
    //  Базовый класс реестра расширений OpenGL.

    class DLLAPI CRegistry : public CObject
    {
    protected:
                            CRegistry           ( bool WindowSystem );

    public:

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CRegistry"; }

        //
        // Interface
        //

        const set<string>&  GetExtensionsList   () const; 

    protected:
        bool                QueryVersion        ( int MajorNumber, int MinorNumber ) const;
        bool                QueryExtension      ( const string& Name ) const;

    private:
        void                TokenizeString      ();

        //
        // Class members
        //

        const char*         m_VersionStr;
        const char*         m_ExtensionsStr;

        set<string>         m_Extensions;
    };

    #ifdef _WIN32

    //  Реестр оконно-зависимых расширений Microsoft Windows OpenGL.
    //  Расширения располагаются в алфавитном порядке.
    
    class DLLAPI CExtensionRegistryWGL : public CRegistry
    {
    public:
                            CExtensionRegistryWGL();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CExtensionRegistryWGL"; }

        //
        // Class members
        //
                                    
        bool                ARB_buffer_region;
        bool                ARB_extensions_string;
        bool                ARB_make_current_read;
        bool                ARB_multisample;
        bool                ARB_pbuffer;
        bool                ARB_pixel_format;
        bool                ARB_pixel_format_float;
        bool                ARB_render_texture;
        
        bool                ATI_pixel_format_float;
        bool                ATI_render_texture_rectangle;
        
        bool                EXT_extensions_string;
        bool                EXT_framebuffer_sRGB;
        bool                EXT_pixel_format_packed_float;
        bool                EXT_swap_control;
        
        bool                NV_float_buffer;
        bool                NV_render_depth_texture;
        bool                NV_render_texture_rectangle;   
    }; 
       
    #elif defined (__linux__)

    //  Реестр оконно-зависимых расширений X-Windows OpenGL.
    //  Расширения располагаются в алфавитном порядке.
    
    class DLLAPI CExtensionRegistryGLX : public CRegistry
    {
    public:
                            CExtensionRegistryGLX();
    
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CExtensionRegistryGLX"; }

        //
        // Class members
        //
        
        bool                ARB_fbconfig_float;
        bool                ARB_get_proc_address;
        bool                ARB_multisample;
        
        bool                EXT_fbconfig_packed_float;
        bool                EXT_framebuffer_sRGB;
        bool                EXT_import_context;
        bool                EXT_texture_from_pixmap;
        bool                EXT_visual_info;
        bool                EXT_visual_rating;
           
        bool                NV_float_buffer;
        bool                NV_swap_group;
        bool                NV_video_out;
        
        bool                SGI_video_sync;
        bool                SGI_swap_control;  
        bool                SGIX_fbconfig;
        bool                SGIX_pbuffer;  
    };
    
    #endif // _WIN32

    //  Реестр ARB-, EXT- и vendor-specific расширений OpenGL. Новые расширения со временем можно добавлять. 
    //  Расширения располагаются в алфавитном порядке.

    class DLLAPI CExtensionRegistry : public CRegistry
    {
    public:
                            CExtensionRegistry  ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CExtensionRegistry"; }

        //
        // Class members
        //

        bool                OpenGL_1_1;
        bool                OpenGL_1_2;
        bool                OpenGL_1_3;
        bool                OpenGL_1_4;
        bool                OpenGL_1_5;
        bool                OpenGL_2_0;
        bool                OpenGL_2_1;

        bool                AMD_performance_monitor;
        bool                AMDX_vertex_shader_tesselator;

        bool                ARB_color_buffer_float;
        bool                ARB_depth_texture;
        bool                ARB_draw_buffers;
        bool                ARB_fragment_program;
        bool                ARB_fragment_program_shadow;
        bool                ARB_fragment_shader;
        bool                ARB_half_float_pixel;
        bool                ARB_imaging;
        bool                ARB_matrix_palette;
        bool                ARB_multisample;
        bool                ARB_multitexture;
        bool                ARB_occlusion_query;
        bool                ARB_pixel_buffer_object;
        bool                ARB_point_parameters;
        bool                ARB_point_sprite;
        bool                ARB_shader_objects;
        bool                ARB_shading_language_100;
        bool                ARB_shadow;
        bool                ARB_shadow_ambient;
        bool                ARB_texture_border_clamp;
        bool                ARB_texture_compression;
        bool                ARB_texture_cube_map;
        bool                ARB_texture_env_add;
        bool                ARB_texture_env_combine;
        bool                ARB_texture_env_crossbar;
        bool                ARB_texture_env_dot3;
        bool                ARB_texture_float;
        bool                ARB_texture_mirrored_repeat;
        bool                ARB_texture_non_power_of_two;
        bool                ARB_texture_rectangle;
        bool                ARB_transpose_matrix;
        bool                ARB_vertex_blend;
        bool                ARB_vertex_buffer_object;
        bool                ARB_vertex_program;
        bool                ARB_vertex_shader;
        bool                ARB_window_pos;

        bool                ATI_draw_buffers;
        bool                ATI_element_array;
        bool                ATI_envmap_bumpmap;
        bool                ATI_fragment_shader;
        bool                ATI_map_buffer_object;
        bool                ATI_meminfo;
        bool                ATI_separate_stencil;
        bool                ATI_shader_texture_lod;
        bool                ATI_texture_compression_3dc;
        bool                ATI_texture_env_combine3;
        bool                ATI_texture_float;
        bool                ATI_texture_mirror_once;
        bool                ATI_vertex_array_object;
        bool                ATI_vertex_attrib_array_object;
        bool                ATI_vertex_streams;

        bool                EXT_abgr;
        bool                EXT_bgra;
        bool                EXT_bindable_uniform;
        bool                EXT_blend_color;
        bool                EXT_blend_equation_separate;
        bool                EXT_blend_func_separate;
        bool                EXT_blend_minmax;
        bool                EXT_blend_subtract;
        bool                EXT_Cg_shader;
        bool                EXT_clip_volume_hint;
        bool                EXT_compiled_vertex_array;
        bool                EXT_depth_bounds_test;
        bool                EXT_draw_buffers;
        bool                EXT_draw_buffers2;
        bool                EXT_draw_instanced;
        bool                EXT_draw_range_elements;
        bool                EXT_fog_coord;
        bool                EXT_framebuffer_blit;
        bool                EXT_framebuffer_multisample;
        bool                EXT_framebuffer_object;
        bool                EXT_framebuffer_sRGB;
        bool                EXT_geometry_shader4;
        bool                EXT_gpu_shader4;
        bool                EXT_multi_draw_arrays;
        bool                EXT_packed_depth_stencil;
        bool                EXT_packed_float;
        bool                EXT_packed_pixels;
        bool                EXT_paletted_texture;
        bool                EXT_pixel_buffer_object;
        bool                EXT_point_parameters;
        bool                EXT_rescale_normal;
        bool                EXT_secondary_color;
        bool                EXT_separate_specular_color;
        bool                EXT_shadow_funcs;
        bool                EXT_stencil_two_side;
        bool                EXT_stencil_wrap;
        bool                EXT_timer_query;
        bool                EXT_texture_3D;
        bool                EXT_texture_array;
        bool                EXT_texture_buffer_object;
        bool                EXT_texture_compression_latc;
        bool                EXT_texture_compression_rgtc;
        bool                EXT_texture_compression_s3tc;
        bool                EXT_texture_cube_map;
        bool                EXT_texture_edge_clamp;
        bool                EXT_texture_env_add;
        bool                EXT_texture_env_combine;
        bool                EXT_texture_env_dot3;
        bool                EXT_texture_filter_anisotropic;
        bool                EXT_texture_integer;
        bool                EXT_texture_lod;
        bool                EXT_texture_lod_bias;
        bool                EXT_texture_mirror_clamp;
        bool                EXT_texture_object;
        bool                EXT_texture_rectangle;
        bool                EXT_texture_shared_exponent;
        bool                EXT_transform_feedback;
        bool                EXT_vertex_array;
        bool                EXT_vertex_shader;

        bool                HP_occlusion_test;

        bool                IBM_rasterpos_clip;
        bool                IBM_texture_mirrored_repeat;

        bool                KTX_buffer_region;

        bool                NV_blend_square;
        bool                NV_conditional_render;
        bool                NV_copy_depth_to_color;
        bool                NV_depth_buffer_float;
        bool                NV_depth_clamp;
        bool                NV_fence;
        bool                NV_float_buffer;
        bool                NV_fog_distance;
        bool                NV_fragment_program;
        bool                NV_fragment_program2;
        bool                NV_fragment_program4;
        bool                NV_fragment_program_option;
        bool                NV_framebuffer_multisample_coverage;
        bool                NV_geometry_program4;
        bool                NV_gpu_program4;
        bool                NV_half_float;
        bool                NV_light_max_exponent;
        bool                NV_multisample_filter_hint;
        bool                NV_occlusion_query;
        bool                NV_packed_depth_stencil;
        bool                NV_parameter_buffer_object;
        bool                NV_pixel_data_range;
        bool                NV_point_sprite;
        bool                NV_primitive_restart;
        bool                NV_register_combiners;
        bool                NV_register_combiners2;
        bool                NV_texgen_reflection;
        bool                NV_texture_compression_vtc;
        bool                NV_texture_env_combine4;
        bool                NV_texture_expand_normal;
        bool                NV_texture_rectangle;
        bool                NV_texture_shader;
        bool                NV_texture_shader2;
        bool                NV_texture_shader3;
        bool                NV_transform_feedback;
        bool                NV_vertex_array_range;
        bool                NV_vertex_array_range2;
        bool                NV_vertex_program;
        bool                NV_vertex_program1_1;
        bool                NV_vertex_program2;
        bool                NV_vertex_program2_option;
        bool                NV_vertex_program3;
        bool                NV_vertex_program4;
        bool                NVX_conditional_render;

        bool                S3_s3tc;
    
        bool                SGIS_generate_mipmap;
        bool                SGIS_texture_lod;
        bool                SGIX_depth_texture;
        bool                SGIX_shadow;

	#ifdef _WIN32
	    Ptr<CExtensionRegistryWGL> WindowSystem;
	#elif defined (__linux__)
	    Ptr<CExtensionRegistryGLX> WindowSystem;
	#endif
    };
} 

#endif // __GL_EXTENSION_REGISTRY_H__
