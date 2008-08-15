// Файл: /Samples/Sample01/Sample01.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SAMPLE_01_H__
#define __SAMPLE_01_H__

#include "../Shared/Demo.h"

namespace Demo
{
    //  Базовое приложение OpenGL.

    class CSample01 : public CDemo_GL
    {
    public:
                            CSample01           ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
           
        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "Demo::CSample01"; }

    protected:
        virtual void        Draw                ();
    
        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );

    private:

        //
        // Class members
        //
    };
}

#endif // __SAMPLE_01_H__