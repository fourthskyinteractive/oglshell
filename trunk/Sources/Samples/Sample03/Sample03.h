// Файл: /Samples/Sample03/Sample03.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SAMPLE_03_H__
#define __SAMPLE_03_H__

#include "../Shared/Demo.h"
#include "../Shared/TrackBall.h"

namespace Demo
{
    //  Демонстрирует работу Occlusion Query.

    class CSample03 : public CDemo_GL
    {
        enum
        {
            NUM_CUBE_VERTICES = 8,
            NUM_CUBE_INDICES = 36
        };

    public:
                            CSample03           ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
           
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "Demo::CSample03"; }

    protected:
        virtual void        Draw                ();
    
        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );
        virtual void        OnMouseMove         ( int PosX, int PosY );
        virtual void        OnMouseLButton      ( bool Down, int PosX, int PosY );

    private:
        void                CreateShaders       ();
        void                CreateVertexBuffers ();
        void                CreateIndexBuffers  ();

        //
        // Class members
        //

    __M(
        m_CgWVP,            Ptr<GL::CCgShadingProgram>,
        m_UWorldViewProj,   Ptr<GL::IUniform>,
        m_UColor,           Ptr<GL::IUniform>,

        m_VSPos3,           Ptr<GL::CVertexStructure>,
        m_VB,               Ptr<GL::CVertexBuffer>,      
        m_IB,               Ptr<GL::CIndexBuffer>,
        
        m_OcclusionQuery,   Ptr<GL::CQuery>,

        m_TrackBall,        Ptr<UI::CTrackBall>
        );
    };
}

#endif // __SAMPLE_03_H__