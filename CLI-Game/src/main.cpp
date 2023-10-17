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

Block blockN = {9, 6, width, height};
Block blockW = {4, 9, width, height};
Block blockS = {9, 9, width, height};
Block blockE = {14, 9, width, height};

int main()
{
    std::cout << "Hello and Welcome!\n";
    bool running = true;
    int count = 0;

    while (running) {
        // Debug Info
        SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
        
          // Display cycle
        count++;
        std::cout << "Running... Cycle: " << count << std::endl;


        SHORT aKS = GetKeyState(0x41);
        std::bitset<8> aBin(aKS);

          // Display input 
        std::cout << "Key state of 'A' byte: " << aBin << std::endl;
        std::cout << "Key state of 'A' SHORT: " << aKS << std::endl;

        std::cout << "A Down State: " << (GetKeyDown(KeyCode_A)) << std::endl;
        std::cout << "size of short: " << sizeof(SHORT);

        bool upKey = GetKeyDown(KeyCode_Up);
        bool leftKey = GetKeyDown(KeyCode_Left);
        bool downKey = GetKeyDown(KeyCode_Down);
        bool rightKey = GetKeyDown(KeyCode_Right);

        // This is somehow TOGGLING...
        // From my understanding, should only appear when held.

        DrawBlockBasedOnInput(upKey, blockN, '^');
        DrawBlockBasedOnInput(leftKey, blockW, '<');
        DrawBlockBasedOnInput(downKey, blockS, 'v');
        DrawBlockBasedOnInput(rightKey, blockE, '>');



        if (GetKeyDown(KeyCode_Space)){
            system("cls");
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();

}
