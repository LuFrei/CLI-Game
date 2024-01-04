#include <iostream>
#include <Windows.h>
#include <bitset>
#include "Input.h"
#include "Character.h"
#include "Graphics/Render.h"

const int screenWidth = 120;
const int screenHeight = 60;
wchar_t* screenData = new wchar_t[screenWidth * screenHeight];
DWORD screenBounds = 0; // This is needed for WriteConhsoleOutputCharacter()

int main()
{
    std::cout << "Hello and Welcome!\n";
    bool running = true;
    int count = 0;

    Graphics::InitGraphics();

    Character* player = new Character();


    while (running) {
#pragma region Debug Info
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        // Display cycle
        count++;
        std::cout << "Running... Cycle: " << count << std::endl;

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
        Graphics::Renderer::DrawBlocks();
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
