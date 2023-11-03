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

        // Display input 
        std::cout << "Key state of 'A' byte: " << aBin << std::endl;
        std::cout << "Key state of 'A' SHORT: " << aKS << std::endl;

        std::cout << "A Down State: " << (GetKeyDown(Input::KeyCode_A)) << std::endl;
        std::cout << "size of short: " << sizeof(SHORT);
        #pragma endregion

#pragma region Logic

        // Grab Inputs
        bool upKey = GetKeyDown(Input::KeyCode_Up);
        bool leftKey = GetKeyDown(Input::KeyCode_Left);
        bool downKey = GetKeyDown(Input::KeyCode_Down);
        bool rightKey = GetKeyDown(Input::KeyCode_Right);



        // Exit condition
        if (GetKeyDown(Input::KeyCode_Space)) {
            system("cls");
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }
#pragma endregion

        #pragma region Render
        DrawBlockBasedOnInput(upKey, blockN, '^');
        DrawBlockBasedOnInput(leftKey, blockW, '<');
        DrawBlockBasedOnInput(downKey, blockS, 'v');
        DrawBlockBasedOnInput(rightKey, blockE, '>');
#pragma endregion 
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
