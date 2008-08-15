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

// Файл: /GL/Texture.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_TEXTURE_H__
#define __GL_TEXTURE_H__

namespace GL
{
    //  Базовый класс текстуры.

    class DLLAPI CTexture : public CObject
    {
    public:
        struct DLLAPI TDesc
        {
                                TDesc           ();
                                
                                // OpenGL 1.1
            GLint               RedSize;
            GLint               GreenSize;
            GLint               BlueSize;
            GLint               AlphaSize;
            GLint               LuminanceSize;
            GLint               IntensitySize;               
            GLint               DepthSize;   // OpenGL 1.4      
            GLint               StencilSize; // GL_EXT_packed_depth_stencil               
            GLint               IndexSize;   // GL_EXT_paletted_texture
                                // GL_NV_texture_shader
            GLint               HiSize, LoSize;
            GLint               DsSize, DtSize;
            GLint               MagSize;
        };

        friend              CWindowSwapChain;
        friend              CFrameBuffer;
        friend              CFrameBufferObject;
        friend              CSamplerUniform;
        friend              CCgSamplerUniform;
        friend              CRenderDeviceDebug;
        friend              CRenderDeviceRelease;

    public:
                            ~CTexture           ();

        //
        // Interface 
        //

        static void         EnumCompressedFormats   ( vector<CInternalFormat> *Formats );

        GLsizei             GetWidth            ( GLint Level ) const;     
        GLsizei             GetHeight           ( GLint Level ) const;
        GLint               GetBorder           () const;
        GLenum              GetInternalFormat   () const;
        void                GetDesc             ( TDesc *Desc ) const;   
        bool                IsMipMap            () const;

        void                SetFilter           ( GLenum Mag, GLenum Min );
        GLenum              GetFilter           ( GLenum Pname ) const;
        void                SetFilterAnisotropy ( GLfloat MaxAnisotropy );
        void                SetBorderColor      ( const GLfloat *Color );
        void                SetCompareMode      ( GLenum Mode );
        void                SetCompareFunc      ( GLenum Func );
        void                SetGenerateMipMap   ( bool Gen );

    protected:
                            CTexture            ( GLenum Target, bool MipMap = false );

        static void         EnumInternalFormats ( GLenum Target, vector<CInternalFormat> *Formats );

        bool                IsFilter            ( GLenum Filter ) const;
        bool                IsWrapMode          ( GLenum Wrap ) const;

		//
        // Class members
        //

        GLuint              m_Texture;
        bool                m_MipMap;

    private:
        GLenum              m_Target;
    };

    //  Одномерная текстура.

    class DLLAPI CTexture1D : public CTexture
    {
    public:
                            CTexture1D          ( GLenum InternalFormat, GLsizei Width, GLint Border, bool MipMap, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
                            CTexture1D          ( GLenum InternalFormat, GLsizei Width, GLint Border = 0, bool MipMap = false );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CTexture1D"; }

        //
        // Interface
        //

        static void         EnumInternalFormats ( vector<CInternalFormat> *Formats );

        void                SetWrap             ( GLenum s );
        GLenum              GetWrap             () const;

        void                Resize              ( GLsizei Width, GLint Border = 0 );

        void                SetSubImage         ( GLint Level, GLint xOffset, GLsizei Width, GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                GetImage            ( GLint Level, GLenum Format, GLenum Type, GLvoid *Pixels ) const;

        void                GenerateMipMap      ();
    };

    //  Двумерная текстура.

	class DLLAPI CTexture2D : public CTexture
    {
    public:
                            CTexture2D          ( GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border, bool MipMap, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
                            CTexture2D          ( GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border, bool MipMap, 
                                                    const vector<GLsizei>& MipSizes, const GLvoid *Data );
                            CTexture2D          ( GLenum InternalFormat, GLsizei Width, GLsizei Height, GLint Border = 0, bool MipMap = false );
        
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CTexture2D"; }

        //
        // Interface
        //

        static void         EnumInternalFormats ( vector<CInternalFormat> *Formats );

        void                SetWrap             ( GLenum s, GLenum t );
        GLenum              GetWrap             ( GLenum Pname ) const;

        void                Resize              ( GLsizei Width, GLsizei Height, GLint Border = 0 );

        void                SetSubImage         ( GLint Level, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                SetCompressedSubImage( GLint Level, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                                    GLenum Format, GLsizei ImageSize, const GLvoid *Data );
        
        void                GetImage            ( GLint Level, GLenum Format, GLenum Type, GLvoid *Pixels ) const;
        void                GetCompressedImage  ( GLint Level, GLvoid *Data ) const;

        void                GenerateMipMap      ();
    };

    //  Прямоугольная текстура.
    //  http://oss.sgi.com/projects/ogl-sample/Extensions/ARB/texture_rectangle.txt

    class DLLAPI CTextureRectangle : public CTexture
    {
    public:
                            CTextureRectangle   ( GLenum InternalFormat, GLsizei Width, GLsizei Height,
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
                            CTextureRectangle   ( GLenum InternalFormat, GLsizei Width, GLsizei Height );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CTextureRectangle"; }

        //
        // Interface
        //

        static void         EnumInternalFormats ( vector<CInternalFormat> *Formats );

        void                SetWrap             ( GLenum s, GLenum t );
        GLenum              GetWrap             ( GLenum Pname ) const;

        void                Resize              ( GLsizei Width, GLsizei Height );

        void                SetSubImage         ( GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                GetImage            ( GLenum Format, GLenum Type, GLvoid *Pixels ) const;
    };

    //  Трёхмерная текстура.

    class DLLAPI CTexture3D : public CTexture
    {
    public:
                            CTexture3D          ( GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, bool MipMap,
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
                            CTexture3D          ( GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, bool MipMap,
                                                    GLsizei ImageSize, const GLvoid *Data );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CTexture3D"; }

        //
        // Interface
        //

        static void         EnumInternalFormats ( vector<CInternalFormat> *Formats );

        void                SetWrap             ( GLenum s, GLenum t, GLenum r );
        GLenum              GetWrap             ( GLenum Pname ) const;
        GLsizei             GetDepth            () const;

        void                SetSubImage         ( GLint xOffset, GLint yOffset, GLint zOffset, GLsizei Width, GLsizei Height, GLsizei Depth, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                SetCompressedSubImage( GLint xOffset, GLint yOffset, GLint zOffset, GLsizei Width, GLsizei Height, GLsizei Depth, 
                                                    GLenum Format, GLsizei ImageSize, const GLvoid *Data );
    };

    //  Кубическая текстура.

	class DLLAPI CTextureCubeMap : public CTexture
    {
        enum 
        {
            NUM_CUBE_MAP_FACES = 6
        };

    public:
                            CTextureCubeMap     ();
                            CTextureCubeMap     ( GLenum InternalFormat, GLsizei Size, GLint Border = 0 );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CTextureCubeMap"; }

        //
        // Interface
        //

        void                SetWrap             ( GLenum s, GLenum t );
        GLenum              GetWrap             ( GLenum Pname ) const;
    
        void                Resize              ( GLsizei Size, GLint Border = 0 );

        void                SetImage            ( GLenum Face, GLenum InternalFormat, GLsizei Size, GLint Border, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                SetCompressedImage  ( GLenum Face, GLenum InternalFormat, GLsizei Size, GLint Border, 
                                                    GLsizei ImageSize, const GLvoid *Data );

        void                SetSubImage         ( GLenum Face, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                                    GLenum Format, GLenum Type, const GLvoid *Pixels );
        void                SetCompressedSubImage( GLenum Face, GLint xOffset, GLint yOffset, GLsizei Width, GLsizei Height, 
                                                    GLenum Format, GLsizei ImageSize, const GLvoid *Data );

        void                GetImage            ( GLenum Face, GLenum Format, GLenum Type, GLvoid *Pixels ) const;
        void                GetCompressedImage  ( GLenum Face, GLvoid *Data ) const;
    
    private:
        bool                IsFace              ( GLenum Face ) const;
    };
}

#endif // __GL_TEXTURE_H__