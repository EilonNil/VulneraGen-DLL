// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <iostream>

extern "C" __declspec(dllexport) VOID printMessage(std::string message) {
    HWND notepadHandle = FindWindowA(NULL, "Untitled - Notepad");
    if (notepadHandle == NULL) {
        notepadHandle = FindWindowA(NULL, "*Untitled - Notepad");
    }

    // Find the handle to the edit control inside the Notepad window
    HWND editControlHandle = FindWindowEx(notepadHandle, NULL, L"Edit", NULL);
    for (int i = 0; i < message.size(); i++) {
        const char character = message[i];
        PostMessage(editControlHandle, WM_CHAR, (WPARAM)character, 0);
        Sleep(50);
    }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

