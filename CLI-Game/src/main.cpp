#include <iostream>
#include <Windows.h>

#include <bitset>

struct Block {
    int x, y;
    int width, height;
};

bool GetKeyDown(int key) {
    return GetKeyState(key) & 0x8000;
}

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

        // !! Our answer right here!
        std::cout << "A Down State: " << (GetKeyDown(0x41)) << std::endl;
        std::cout << "size of short: " << sizeof(SHORT);


        // === Get key presses === 
            //KeyState spacebar = GetKeyDown(VK_SPACE);

            //KeyState upArrow = GetKeyDown(VK_UP);
            //KeyState leftArrow = GetKeyDown(VK_LEFT);
            //KeyState downArrow = GetKeyDown(VK_DOWN);
            //KeyState rightArrow = GetKeyDown(VK_RIGHT);

            //KeyState wKey = GetKeyDown(87);
            //KeyState aKey = GetKeyDown(0x41);
            //KeyState sKey = GetKeyDown(83);
            //KeyState dKey = GetKeyDown(0x44);

        bool wKey = GetKeyDown(87);
        bool aKey = GetKeyDown(0x41);
        bool sKey = GetKeyDown(83);
        bool dKey = GetKeyDown(0x44);

        // This is somehow TOGGLING...
        // From my understanding, should only appear when held.

        DrawBlockBasedOnInput(wKey, blockN, '^');
        DrawBlockBasedOnInput(aKey, blockW, '<');
        DrawBlockBasedOnInput(sKey, blockS, 'v');
        DrawBlockBasedOnInput(dKey, blockE, '>');



        if (GetKeyDown(VK_SPACE))
        {
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
