// Файл: /Samples/Sample07/Sample07.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SAMPLE_07_H__
#define __SAMPLE_07_H__

#include "../Shared/Demo.h"

namespace Demo
{
    //  Демонстрирует правильную работу с расширением GL_EXT_bindable_uniform.
    //  На текущий момент драйверы ATI не поддерживают это расширение.

    class CSample07 : public CDemo_GL
    {
    public:
                            CSample07           ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
           
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "Demo::CSample07"; }

    protected:
        virtual void        Draw                ();
    
        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );

    private:
        void                CreateShaders       ();
        void                CreateVertexBuffers ();

        //
        // Class members
        //

    __M(
        m_Program,          Ptr<GL::CShadingProgram>,   
        m_Uniform,          Ptr<GL::IBindableUniform>,
        
        m_VSPos3,           Ptr<GL::CVertexStructure>,
        m_VB,               Ptr<GL::CVertexBuffer>,
        m_UB,               Ptr<GL::CGenericBuffer>
        );
    };
}

#endif // __SAMPLE_07_H__