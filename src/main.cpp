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
    
    Graphics::Screen screen = Graphics::Screen(120, 30);
    screen.SetSquareCells(true);
    CLGEngine::CORE::MainWindow mainWindow = CLGEngine::CORE::MainWindow();

    
    Character* player = new Character(4);

    while (running) {
        CLGEngine::Time::CalculateDeltaTime();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

#pragma region Logic

    #pragma region Input
        Input::Input::UpdateAllInputState();
    #pragma endregion

#pragma region Gameplay

        if (Input::Input::GetKeyJustPressed(Input::KeyCode::Up)) {
            player->Move(0, -10);
        }
        if (Input::Input::GetKeyJustPressed(Input::KeyCode::Down)) {
            player->Move(0, 10);
        }
        if (Input::Input::GetKeyJustPressed(Input::KeyCode::Left)) {
            player->Move(-10, 0);
        }
        if (Input::Input::GetKeyJustPressed(Input::KeyCode::Right)) {
            player->Move(10, 0);
        }

#pragma endregion
        // Exit condition
        if (Input::Input::GetKeyJustPressed(Input::KeyCode::Space)) {
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
