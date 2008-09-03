// Файл: /Samples/Shared/Demo.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SHARED_DEMO_H__
#define __SHARED_DEMO_H__

#include "FrameCounter.h"

namespace Demo
{
    //  Базовый класс приложения.

    class IDemo : public Sys::IRTTIObject, public Sys::CNonCopyable 
    {
        friend 
        LRESULT CALLBACK    WindowProc          ( HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam );

    public:
                            IDemo               ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
        virtual             ~IDemo              ();

        //
        // Interface
        //

        void                Run                 ();

    protected:
        virtual void        Draw                () = 0;

        virtual void        OnKeyDown           ( UINT Key, int Repeat, UINT Flags );
        virtual void        OnKeyUp             ( UINT Key, int Repeat, UINT Flags );
        virtual void        OnMouseMove         ( int PosX, int PosY );
        virtual void        OnMouseLButton      ( bool Down, int PosX, int PosY );
        virtual void        OnMouseRButton      ( bool Down, int PosX, int PosY );
        virtual void        OnMouseMButton      ( bool Down, int PosX, int PosY );

        void                OnClose             ();

    protected:

        //
        // Class members
        //

        HINSTANCE           m_Instance;
        HWND                m_Window;
        HDC                 m_DC;

        UINT                m_Width;
        UINT                m_Height;

        Ptr<CFrameCounter>  m_FrameCounter;
        Ptr<CTimer>         m_Timer;

    private:
        bool                m_Active;
        bool                m_Closed;
    };

    //  OpenGL-приложение.

    class CDemo_GL : public IDemo
    {
    public:
                            CDemo_GL                ( HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption );
                            ~CDemo_GL               ();

        //
        // RTTI
        //

        virtual string      GetClassName            () const { return "Demo::CDemo_GL"; }

        //
        // Interface
        //

    protected:
        void                CreateRender            ();
        void                DestroyRender           ();

        string              LoadStringFromFile      ( const string& FileName ) const;

        //
        // Class members
        //
        
    __M(
        m_WSSwapChain,      Ptr<GLW::CWindowSwapChain>,

        m_RenderDevice,     Ptr<GL::IRenderDevice>,

        m_Extensions,       Ptr<const GL::CExtensionRegistry>,
        m_DriverDesc,       GL::CDriver::TDesc,

        m_Font,             Ptr<GLU::CBitmapFont>,
        m_Stack,            Ptr<GLU::CMatrixStack>,

        m_World,            Mat4,
        m_View,             Mat4, 
        m_Proj,             Mat4, 
        m_Ortho,            Mat4,
        m_Identity,         Mat4,
        );
    };
}

#endif // __SHARED_DEMO_H__