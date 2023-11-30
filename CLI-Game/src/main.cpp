#include <iostream>
#include <Windows.h>
#include <bitset>
#include "Input.h"
#include "Character.h"
#include "Render.h"

int main()
{
    std::cout << "Hello and Welcome!\n";
    bool running = true;
    int count = 0;

    Character* player = new Character();

    while (running) {
#pragma region Debug Info
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        // Display cycle
        count++;
        std::cout << "Running... Cycle: " << count << std::endl;


        SHORT aKS = GetKeyState(0x41);
        std::bitset<8> aBin(aKS);

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
            std::cout << "Moving player Up" << std::endl;
            player->Move(0, -1);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Down)) {
            std::cout << "Moving player Down" << std::endl;
            player->Move(0, 1);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Left)) {
            std::cout << "Moving player Left" << std::endl;
            player->Move(-2, 0);
        }
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Right)) {
            std::cout << "Moving player Right" << std::endl;
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

#pragma region Render
        Render::Block playerBlock = CreateBlockFromEntity(*player);
        std::cout << "playerBlock: " << std::endl
            << "x: " << playerBlock.x << ", y: " << playerBlock.y << std::endl
            << "width: " << playerBlock.width << ", height: " << playerBlock.height << std::endl;
        DrawBlock(playerBlock, 'P');
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
