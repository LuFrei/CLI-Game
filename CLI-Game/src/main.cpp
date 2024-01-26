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
        // Init inputs
        Input::Input::InitActiveKeys(
            {
            Input::KeyCode::Left,
            Input::KeyCode::Right,
            Input::KeyCode::Up,
            Input::KeyCode::Down,
            Input::KeyCode::Space,
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
