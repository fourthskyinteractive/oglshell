// Файл: /Samples/Sample02/Sample02.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SAMPLE_02_H__
#define __SAMPLE_02_H__

#include "../Shared/Demo.h"

namespace Demo
{
    //  Демонстрирует работу с шейдерами Cg, вершинными и индексными буферами,
    //  организацию нескольких вершинных потоков в один общий формат вершины.

    class CSample02 : public CDemo_GL
    {
        enum
        {
            NUM_CUBE_VERTICES = 8,
            NUM_CUBE_INDICES = 36
        };

    public:
                            CSample02           ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
           
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "Demo::CSample02"; }

    protected:
        virtual void        Draw                ();
    
        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );

    private:
        void                CreateShaders       ();
        void                CreateVertexBuffers ();
        void                CreateIndexBuffers  ();

        //
        // Class members
        //

    __M(
        m_Programs[ 2 ],    Ptr<GL::CCgShadingProgram>,    

        m_VSPos3,           Ptr<GL::CVertexStructure>,
        m_VSPos3Color3,     Ptr<GL::CVertexStructure>,
        m_VB[ 2 ],          Ptr<GL::CVertexBuffer>,      
        m_IB,               Ptr<GL::CIndexBuffer>,
        );
    };
}

#endif // __SAMPLE_02_H__