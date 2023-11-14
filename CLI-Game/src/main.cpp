#include <iostream>
#include <Windows.h>
#include <bitset>
#include "Input.h"

struct Block {
    int x, y;
    int width, height;
};

void FillBlock(Block block, char character) {

    for (short i = 0; i < block.height; i++) {
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)block.x, (short)(block.y + i) }
        );
        for (int j = 0; j < block.width; j++) {
            std::cout << character;
        }
    }
}

void DrawBlockBasedOnInput(bool keyState, Block block, char texture) {
    FillBlock(
        block,
        keyState ? texture : ' '
    );
}

// Blocks will be 4x4 for now.
const short width = 3;
const short height = 2;

Block blockN = {9, 16, width, height};
Block blockW = {4, 19, width, height};
Block blockS = {9, 19, width, height};
Block blockE = {14, 19, width, height};

int main()
{
    std::cout << "Hello and Welcome!\n";
    bool running = true;
    int count = 0;

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


        // Exit condition
        if (Input::Input::GetKeyDownThisCycle(Input::KeyCode::Space)) {
            system("cls");
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }
#pragma endregion

#pragma region Render
        DrawBlockBasedOnInput(Input::Input::GetKeyDownThisCycle(Input::KeyCode::Up), blockN, '^');
        DrawBlockBasedOnInput(Input::Input::GetKeyUpThisCycle(Input::KeyCode::Left), blockW, '<');
        DrawBlockBasedOnInput(Input::Input::GetKeyDown(Input::KeyCode::Down), blockS, 'v');
        DrawBlockBasedOnInput(Input::Input::GetKeyDown(Input::KeyCode::Right), blockE, '>');
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
