#include "ConsoleWindow.h"
#include "../Time.h"

namespace CLGEngine {
namespace CORE {
	ConsoleWindow::ConsoleWindow() {
        // ! Could this cause a bug if the user clicks on something else while the game iss tarting??
        // 
        h_window = GetConsoleWindow();
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


} // namespace CORE
} // namespace CLGEngine
