// Τΰιλ: /Samples/Sample05/Main.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample05.h"

//
// WinMain
//
int WINAPI WinMain( 
                   HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow 
                   )
{
	try 
    {
        Ptr<Demo::IDemo> Sample05 = new Demo::CSample05( 
            Instance, 
            800, 600, 
            L"OpenGL Sample 05 - Render to Texture" 
            );
        
        Sample05->Run();
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