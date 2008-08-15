// Файл: /Samples/Shared/Demo.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Demo.h"

namespace Demo
{
    static IDemo *g_Demo = NULL;
    LRESULT CALLBACK WindowProc( HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam );

    static const WCHAR *CLASS_NAME = L"3D Graphics Demo";

    //
    // Constructor
    //
    IDemo::IDemo( 
                 HINSTANCE Instance, UINT Width, UINT Height, const WCHAR *Caption 
                 ):
        m_Instance( Instance ),
        m_Window( NULL ),
        m_DC( NULL ),
        
        m_Width( Width ),
        m_Height( Height ),

        m_Active( false ),
        m_Closed( false )
    {
        g_Demo = this;

        //
        // Window
        //

        WNDCLASS WndClass = 
        {
            CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            WindowProc,
            0,
            0,
            Instance,
            NULL,
            LoadCursor( NULL, IDC_ARROW ),
	        (HBRUSH)GetStockObject( BLACK_BRUSH ),
            NULL,
            CLASS_NAME
        };

        ATOM RetVal = RegisterClass( &WndClass );
        if (RetVal == 0)
            throw Sys::CFatalException( "IDemo", "::IDemo() : Failed to register window class." );

        m_Window = CreateWindow(
            CLASS_NAME,
            Caption,
		    WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		    CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            Instance,
            NULL 
            );

        if (!m_Window)
            throw Sys::CFatalException( "IDemo", "::IDemo() : Failed to create window." );

        m_DC = GetDC( m_Window );

        int ScreenWidth = GetDeviceCaps( m_DC, HORZRES );
        int ScreenHeight = GetDeviceCaps( m_DC, VERTRES );
        int X, Y;
        int cx, cy;

        DWORD Style = 0;

        if (Width == ScreenWidth && Height == ScreenHeight) 
        {
            Style = WS_POPUP;

            cx = Width;
		    cy = Height;
            X = 0;
            Y = 0;
        }
        else
        {
            Style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

            RECT Rect = {0L, 0L, Width, Height};
            AdjustWindowRect( &Rect, Style, FALSE );

            // Вычисляем размеры клиентской области окна и рамещаем окно в центре экрана.
		    cx = Rect.right - Rect.left;
		    cy = Rect.bottom - Rect.top;
            X = (ScreenWidth - Width) / 2;
            Y = (ScreenHeight - Height) / 2;
        }

        SetWindowLong( m_Window, GWL_STYLE, Style | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
        SetWindowPos( m_Window,
    #ifdef _DEBUG
            HWND_TOP,
    #else
            HWND_TOPMOST,
    #endif
            X, Y, 
            cx, cy, 
            SWP_SHOWWINDOW 
            );

        //
        // Other stuff
        //

        m_FrameCounter = new CFrameCounter();
        m_Timer = new CTimer();
    }

    //
    // Destructor
    //
    IDemo::~IDemo()
    {
        g_Demo = NULL;

        ShowWindow( m_Window, SW_HIDE );
        DestroyWindow( m_Window );

        UnregisterClass( CLASS_NAME, m_Instance );
    }

    //
    // Run
    //
    void IDemo::Run()
    {
        MSG Msg;

	    Msg.wParam = 0;

        while (true) 
        {
			if (PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE )) 
            {
                if (m_Closed)
                    break;
				//if (Msg.message == WM_QUIT)
                //break;

				TranslateMessage( &Msg );
				DispatchMessage( &Msg );
			}
			else 
            {
				//if (m_Active)
                {
                    Draw();
                }
			}
        }  
    }

    //
    // OnKeyDown
    //
    void IDemo::OnKeyDown( 
                          UINT Key, int Repeat, UINT Flags 
                          )
    {
        switch (Key) 
        {
        case VK_ESCAPE:
            OnClose();
            break;
        }
    }
    
    //
    // OnKeyUp
    //
    void IDemo::OnKeyUp( 
                        UINT Key, int Repeat, UINT Flags
                        )
    {
    }

    //
    // OnMouseMove
    //
    void IDemo::OnMouseMove( 
                            int PosX, int PosY 
                            )
    {
    }

    //
    // OnMouseLButton
    //
    void IDemo::OnMouseLButton( 
                               bool Down, int PosX, int PosY 
                               )
    {
    }

    //
    // OnMouseRButton
    //
    void IDemo::OnMouseRButton( 
                               bool Down, int PosX, int PosY 
                               )
    {
    }

    //
    // OnMouseMButton
    //
    void IDemo::OnMouseMButton( 
                               bool Down, int PosX, int PosY 
                               )
    {
    }

    //
    // OnClose
    //
    void IDemo::OnClose()
    {
        m_Closed = true;
    }

    //
    // WindowProc
    //
    LRESULT CALLBACK WindowProc( 
                                HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam 
                                )
    {
	    switch (Msg) 
        {
	    case WM_ACTIVATE:
            if (!g_Demo)
                return 0L;
		    if ((UINT)LOWORD(wParam) == WA_INACTIVE)
			    g_Demo->m_Active = false;
		    else
			    g_Demo->m_Active = true;
		    return 0L;

	    case WM_KEYDOWN:
		    g_Demo->OnKeyDown( wParam, (int)LOWORD( lParam ), HIWORD( lParam ) );
		    return 0L;
	    case WM_KEYUP:
		    g_Demo->OnKeyUp( wParam, (int)LOWORD( lParam ), HIWORD( lParam ) );
		    return 0L;

        case WM_MOUSEMOVE:
            g_Demo->OnMouseMove( (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;

        case WM_LBUTTONDOWN:
            g_Demo->OnMouseLButton( true, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;
        case WM_LBUTTONUP:
            g_Demo->OnMouseLButton( false, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;
        case WM_RBUTTONDOWN:
            g_Demo->OnMouseRButton( true, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;
        case WM_RBUTTONUP:
            g_Demo->OnMouseRButton( false, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;
        case WM_MBUTTONDOWN:
            g_Demo->OnMouseMButton( true, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;
        case WM_MBUTTONUP:
            g_Demo->OnMouseMButton( false, (int)LOWORD( lParam ), (int)HIWORD( lParam ) );
            break;

        case WM_CLOSE:
            g_Demo->OnClose();
            return 0L;

        /*
        This cause that MessageBox() doesn't work after PostQuitMessage().

        // The PostQuitMessage function indicates to Windows that a thread has made a request to terminate. 
        // Any window that is created after you call the PostQuitMessage function will be immediately destroyed.
        // http://support.microsoft.com/default.aspx?scid=kb;en-us;138681
	    case WM_DESTROY:
		    PostQuitMessage( 0 );
		    return 0L;
        */
	    }

	    return DefWindowProc( Window, Msg, wParam, lParam );
    }
}