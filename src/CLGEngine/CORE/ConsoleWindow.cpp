#include "ConsoleWindow.h"
#include "../Time.h"

namespace CLGEngine {
namespace CORE {
    ConsoleWindow* ConsoleWindow::_mainWindow = nullptr; 

	ConsoleWindow::ConsoleWindow(HWND windowHandle) {
        h_window = windowHandle;              // Hard coded to be the main window console.
        GetWindowRect(h_window, &windowRect);
        screen = new CLGEngine::Screen(120, 30);

        position = { windowRect.left , windowRect.top };
        size = { 
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top
        };
	}

	ConsoleWindow::ConsoleWindow() {

        PROCESS_INFORMATION ProcInfo;

        CreateProcess(
            NULL,                    // App Name
            NULL,                    // CommandLine (??)
            NULL,                    // Process Attributes
            NULL,                    // ThreadAttributes
            FALSE,                   // InheritHAndles
            CREATE_NEW_CONSOLE,      // CreationFlags
            NULL,                    // Environment
            NULL,                    // Curr Dir
            NULL,                    // Startup Info
            &ProcInfo
        );

        // h_window = ;              // Hard coded to be the main window console.
        GetWindowRect(h_window, &windowRect);
        screen = new CLGEngine::Screen(120, 30);

        position = { windowRect.left , windowRect.top };
        size = { 
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top
        };
	}

    ConsoleWindow::~ConsoleWindow(){
        delete screen;
        // FreeCons
    }

    void ConsoleWindow::Move(Vector2<LONG> distance) { 
        size.x += 10 * Time::deltaTime;
        // TODO: add functionality to make operations with whole Vectors.
        position.x += distance.x;
        position.y += distance.y;

        HDWP h_windowPosition = BeginDeferWindowPos(1);
        DeferWindowPos(
            
            h_windowPosition,
            h_window,
            NULL,
            position.x,
            position.y,
            size.x,
            size.y,
            SWP_SHOWWINDOW
        );
        EndDeferWindowPos(h_windowPosition);
    };

    void ConsoleWindow::Resize(Vector2<LONG> deltaSize){
        size.x += deltaSize.x;
        size.y += deltaSize.y;

        HDWP h_windowPosition = BeginDeferWindowPos(1);
        DeferWindowPos(
            h_windowPosition,
            h_window,
            NULL,
            position.x,
            position.y,
            size.x,
            size.y,
            SWP_SHOWWINDOW
        );
        EndDeferWindowPos(h_windowPosition);
    };

    ConsoleWindow* ConsoleWindow::GetMainWindow(){
        if(_mainWindow != nullptr){
            return _mainWindow;
        }
        _mainWindow = new ConsoleWindow(GetConsoleWindow());
        return _mainWindow;
    }

} // namespace CORE
} // namespace CLGEngine
