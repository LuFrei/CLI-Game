#include <iostream>
#include <Windows.h>
#include <chrono>
#include <bitset>
#include "Game/Character.h"
#include "CLGEngine/Input.h"
#include "CLGEngine/Graphics/Render.h"
#include "CLGEngine/Graphics/Screen.h"
#include "CLGEngine/Time.h"
#include "CLGEngine/CORE/Utility.h"
#include "CLGEngine/CORE/MainWindow.h"

using namespace CLGEngine;

int main()
{
    bool running = true;
    
    CLGEngine::Screen screen = CLGEngine::Screen(120, 30);
    screen.SetSquareCells(true);
    CLGEngine::CORE::MainWindow mainWindow = CLGEngine::CORE::MainWindow();

    
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
            Input::KeyCode::L,
            Input::KeyCode::W,
            Input::KeyCode::A,
            Input::KeyCode::S,
            Input::KeyCode::D
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

        int windowSpeed = 10;

        // Grow Window
        if (Input::Input::GetKeyDown(Input::KeyCode::J)) {
            float sizeTraj = 1 * windowSpeed;
            float moveTraj = -1 * windowSpeed;
            
            // TODO: Make conversion functions for Vector2.
            //       i.e. (LONG)Vector2<float>.
            mainWindow.Move({(LONG)moveTraj, 0});
            mainWindow.Resize({(LONG)sizeTraj, 0});
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::K)) {
            float sizeTraj = 1 * windowSpeed;

            mainWindow.Resize({ 0, (LONG)sizeTraj });
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::L)) {
            float sizeTraj = 1 * windowSpeed;

            mainWindow.Resize({ (LONG)sizeTraj, 0 });
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::I)) {
            float sizeTraj = 1 * windowSpeed;
            float moveTraj = -1 * windowSpeed;

            mainWindow.Move({ 0, (LONG)moveTraj });
            mainWindow.Resize({ 0, (LONG)sizeTraj });
        }

        // Shrink Window
        if (Input::Input::GetKeyDown(Input::KeyCode::A)) {
            float sizeTraj = -1 * windowSpeed;

            mainWindow.Resize({ (LONG)sizeTraj, 0 });
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::S)) {
            float sizeTraj = -1 * windowSpeed;
            float moveTraj = 1 * windowSpeed;

            mainWindow.Move({ 0, (LONG)moveTraj });
            mainWindow.Resize({ 0, (LONG)sizeTraj });
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::D)) {
            float sizeTraj = -1 * windowSpeed;
            float moveTraj = 1 * windowSpeed;

            mainWindow.Move({ (LONG)moveTraj, 0 });
            mainWindow.Resize({ (LONG)sizeTraj, 0 });
        }
        if (Input::Input::GetKeyDown(Input::KeyCode::W)) {
            float sizeTraj = -1 * windowSpeed;

            mainWindow.Resize({ 0, (LONG)sizeTraj });
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
