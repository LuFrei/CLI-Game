#include "MainWindow.h"
#include "../Time.h"

namespace CLGEngine {
namespace CORE {

	MainWindow::MainWindow() {
        h_window = GetConsoleWindow();              // Hard coded to be the main window console.
        GetWindowRect(h_window, &windowRect);
        screen = new clr::Screen(120, 30);

        position = { windowRect.left , windowRect.top };
        size = { 
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top
        };
	}

    /*! To be moved to Window.cpp !*/
	// MainWindow::MainWindow(bool unimportant) {

    //     PROCESS_INFORMATION ProcInfo;

    //     CreateProcess(
    //         NULL,                    // App Name
    //         NULL,                    // CommandLine (??)
    //         NULL,                    // Process Attributes
    //         NULL,                    // ThreadAttributes
    //         FALSE,                   // InheritHandles
    //         CREATE_NEW_CONSOLE,      // CreationFlags
    //         NULL,                    // Environment
    //         NULL,                    // Curr Dir
    //         NULL,                    // Startup Info
    //         &ProcInfo
    //     );

        // h_window = ;              // Hard coded to be the main window console.
        // GetWindowRect(h_window, &windowRect);
        // screen = new CLGEngine::Screen(120, 30);

        // position = { windowRect.left , windowRect.top };
        // size = { 
        //     windowRect.right - windowRect.left,
        //     windowRect.bottom - windowRect.top
        // };
	// }

    MainWindow::~MainWindow(){
        delete screen;
    }

    void MainWindow::Move(Vector2<LONG> distance) { 
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

    void MainWindow::Resize(Vector2<LONG> deltaSize){
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

    /*! Not needed anymore !*/
    // MainWindow* MainWindow::GetMainWindow(){
    //     if(_mainWindow != nullptr){
    //         return _mainWindow;
    //     }
    //     _mainWindow = new MainWindow(GetConsoleWindow());
    //     return _mainWindow;
    // }

} // namespace CORE
} // namespace CLGEngine
