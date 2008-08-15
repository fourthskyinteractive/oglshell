// Τΰιλ: /Samples/Sample01/Main.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Sample01.h"

//
// WinMain
//
int WINAPI WinMain( 
                   HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow 
                   )
{
	try 
    {
        Ptr<Demo::IDemo> Sample01 = new Demo::CSample01( 
            Instance, 
            800, 600, 
            L"OpenGL Sample 01 - Basic OpenGL Program" 
            );
        
        Sample01->Run();
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