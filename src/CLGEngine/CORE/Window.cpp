#include "Window.h"

#include <Windows.h>
#include <iostream>

namespace CLGEngine{
Window::Window(){
    PROCESS_INFORMATION ProcInfo;
    // LPSTR cmdLine = GetCommandLine();
    CreateProcess(
        NULL,                    // App Name
        NULL,                    // CommandLine (??)
        NULL,                    // Process Attributes
        NULL,                    // ThreadAttributes
        TRUE,                   // InheritHAndles
        CREATE_NEW_CONSOLE,      // CreationFlags
        NULL,                    // Environment
        NULL,                    // Curr Dir
        NULL,                    // Startup Info
        &ProcInfo
    );

    // h_window = ;              // Hard coded to be the main window console.
    // GetWindowRect(h_window, &windowRect);
    // screen = new CLGEngine::Screen(120, 30);

    // position = { windowRect.left , windowRect.top };
    // size = { 
    //     windowRect.right - windowRect.left,
    //     windowRect.bottom - windowRect.top
    // };

    // std::cout << "Where will this output? hmmmm" << std::endl;
};

Window::~Window(){

};

}
