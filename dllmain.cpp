// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <iostream>
#include <string>

HWND notepadHandle = NULL;

BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
    //this function is the base function that will find the HWND of the
    //injected notepad using it's process ID.
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hwnd, &lpdwProcessId);
    if (lpdwProcessId == lParam)
    //if current process is the same as wanted process
    {
        notepadHandle = hwnd;
        return FALSE;
    }
    return TRUE;
}


extern "C" __declspec(dllexport) VOID printMessage(std::string message, DWORD procID) {
    EnumWindows(EnumWindowsProcMy, procID);
    //go over all the windows and find the HWND of the notepad.

    HWND editControlHandle = FindWindowEx(notepadHandle, NULL, L"Edit", NULL);
    for (int i = 0; i < message.size(); i++) {
        const char character = message[i];
        PostMessage(editControlHandle, WM_CHAR, (WPARAM)character, 0);
        Sleep(50);
    }
    //print the text by sending a message to print each letter with a tiny break in between to
    //make it look flowing like human typing.
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

