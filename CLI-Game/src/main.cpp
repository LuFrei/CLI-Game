#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Input.h"
#include "Character.h"
#include "Render.h"

int main()
{
    bool running = true;
    int count = 0;
    int countsThisSec = 0;
    int countsPerSec = 0;
    
    Character* player = new Character();
    time_t now = time(0);


    while (running) {
#pragma region Debug Info
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



#pragma endregion

        // Erase last cycle's visual data
        Render::Renderer::EraseBlocks();

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

#pragma region Render
        //std::cout << "playerBlock: " << std::endl
        //    << "x: " << player->rend->block.x << ", y: " << player->rend->block.y << std::endl
        //    << "width: " << player->rend->block.width << ", height: " << player->rend->block.height << std::endl
        //    << "material: " << player->rend->block.material << std::endl;
        Render::Renderer::DrawBlocks();
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
