#include <iostream>
#include <Windows.h>
#include <chrono>
#include <bitset>
#include "Game/Character.h"
#include "CLGEngine/Input.h"
#include "CLGEngine/Graphics/Render.h"
#include "CLGEngine/Graphics/Screen.h"
#include "CLGEngine/Time.h"


int main()
{
    bool running = true;
    
    CLGEngine::Screen screen = CLGEngine::Screen(120, 30);
    screen.SetSquareCells(true);
    
    Character* player = new Character(4);

    while (running) {
        CLGEngine::Time::CalculateDeltaTime();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

#pragma region Logic

    #pragma region Input
        Input::Input::InitActiveKeys(
            {
            Input::KeyCode::Left,
            Input::KeyCode::Right,
            Input::KeyCode::Up,
            Input::KeyCode::Down,
            Input::KeyCode::Space,
            // For Debugging
            Input::KeyCode::F4,
            // For window resizing tests.
            Input::KeyCode::I,
            Input::KeyCode::J,
            Input::KeyCode::K,
            Input::KeyCode::L
            }
        );

        Input::Input::UpdateActiveKeys();
    #pragma endregion

#pragma region Gameplay

        

        if (Input::Input::GetKeyDown(Input::KeyCode::Up)) {
            player->Move(0, -1);
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::Down)) {
            player->Move(0, 1);
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::Left)) {
            player->Move(-1, 0);
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::Right)) {
            player->Move(1, 0);
        }
        
        // -- Begin window resizing tests

        

        HWND h_window = GetForegroundWindow();
        RECT windowRect;
        GetWindowRect(h_window, &windowRect);

        int width = windowRect.right - windowRect.left;
        int height = windowRect.bottom - windowRect.top;

        if (Input::Input::GetKeyDown(Input::KeyCode::J)) {
            width -= 100;
            HDWP h_windowPosition = BeginDeferWindowPos(1); 
            DeferWindowPos(
                h_windowPosition,
                h_window,
                NULL,
                windowRect.left,
                windowRect.top,
                width,
                height,
                SWP_SHOWWINDOW
            );
            EndDeferWindowPos(h_windowPosition);
        }

        // -- end Window Resizing tests



#pragma endregion
        // Exit condition
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Space)) {
            system("cls");
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }
#pragma endregion

#pragma region Graphics
        screen.Draw();
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );
}
