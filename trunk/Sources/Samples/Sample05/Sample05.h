// ‘айл: /Samples/Sample05/Sample05.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SAMPLE_05_H__
#define __SAMPLE_05_H__

#include "../Shared/Demo.h"

namespace Demo
{
    //  ƒемонстрирует простой рендер в текстуру, использу€ по выбору расширение GL_EXT_framebuffer_object
    //  или старое расширение WGL_ARB_pbuffer.

    class CSample05 : public CDemo_GL
    {
        enum
        {
            NUM_CUBE_VERTICES = 8,
            NUM_CUBE_INDICES = 36
        };

        enum
        {
            FB_WIDTH = 256,
            FB_HEIGHT = 256
        };

    public:
                            CSample05           ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
           
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "Demo::CSample05"; }

    protected:
        virtual void        Draw                ();
    
        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );

    private:
        void                RenderToTexture     ();

        void                CreateFrameBuffer   ( bool FBO );
        void                CreateShaders       ();
        void                CreateVertexBuffers ();
        void                CreateIndexBuffers  ();

        //
        // Class members
        //

    __M(
        m_FrameBuffer,      Ptr<GL::IFrameBuffer>,
        m_Texture,          Ptr<GL::CTexture2D>,
        m_FBO,              bool,

        m_Programs[ 2 ],    Ptr<GL::CCgShadingProgram>,   
        m_UTexture,         Ptr<GL::ISamplerUniform>,
        
        m_VSPos3Color3,     Ptr<GL::CVertexStructure>,
        m_VSPos3TexCoord2,  Ptr<GL::CVertexStructure>,
        
        m_VB[ 3 ],          Ptr<GL::CVertexBuffer>,      
        m_IB[ 2 ],          Ptr<GL::CIndexBuffer>,
        );
    };
}

#endif // __SAMPLE_05_H__