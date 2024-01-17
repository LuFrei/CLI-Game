#include <iostream>
#include <Windows.h>
<<<<<<< HEAD
#include <chrono>
#include "Input.h"
#include "Character.h"
#include "Render.h"
=======
#include <bitset>
#include "Game/Character.h"
#include "CLGEngine/Input.h"
#include "CLGEngine/Graphics/Render.h"
#include "CLGEngine/Graphics/Screen.h"


>>>>>>> f2e691b9b861c164de7ad20f97aa42d6f4f89a3d

int main()
{
    bool running = true;
<<<<<<< HEAD
    int count = 0;
    int countsThisSec = 0;
    int countsPerSec = 0;
    
=======

    CLGEngine::Screen screen = CLGEngine::Screen(120, 30);
>>>>>>> f2e691b9b861c164de7ad20f97aa42d6f4f89a3d
    Character* player = new Character();
    time_t now = time(0);



    while (running) {
#pragma region Debug Info
<<<<<<< HEAD
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        if (time(0) != now) {
            // 1 second elapsed
            now = time(0);
            countsPerSec = countsThisSec;
            countsThisSec = 0;
        }

        // Display cycle
        count++;
        countsThisSec++;
        std::cout << "Running... Cycle: " << count << std::endl;
        std::cout << "Time: " << now << std::endl;

        std::cout << "Frames This Second: " << countsThisSec << std::endl;
        std::cout << "Frames Per Second: " << countsPerSec << std::endl;


=======
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });;
>>>>>>> f2e691b9b861c164de7ad20f97aa42d6f4f89a3d

#pragma endregion

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

        

        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Up)) {
            player->Move(0, -1);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Down)) {
            player->Move(0, 1);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Left)) {
            player->Move(-2, 0);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Right)) {
            player->Move(2, 0);
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
