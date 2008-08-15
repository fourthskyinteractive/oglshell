// Τΰιλ: /Samples/Sample03/Main.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample03.h"

//
// WinMain
//
int WINAPI WinMain( 
                   HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow 
                   )
{
	try 
    {
        Ptr<Demo::IDemo> Sample03 = new Demo::CSample03( 
            Instance, 
            800, 600, 
            L"OpenGL Sample 03 - Occlusion Query" 
            );
        
        Sample03->Run();
    }
    catch (const Sys::CFatalException& Ex)
    {
        MessageBoxA( NULL, Ex.GetErrorString().c_str(), "Fatal Error", MB_ICONERROR );
    }
    catch (const Sys::CException& Ex)
    {
        MessageBoxA( NULL, Ex.GetErrorString().c_str(), "Error", MB_ICONERROR );
    }
    catch (...)
    {
        MessageBox( NULL, L"Unknown error has occured!", L"Error", MB_ICONERROR );
    }

	return 0;
}