#include <iostream>
#include <Windows.h>

struct Block {
    int x, y;
    int width, height;
};

enum KeyStatus {
    KeyStateUp = 0,         // no signal
    KeyStateDown = 0x8000,  // high-order bit
    KeyStateToggled = 1     // lower-order bit
};

KeyStatus GetKeyInput(int key) {
    switch (GetKeyState(key)) {
    case(1):
        return KeyStateToggled;
    case(0x8000):
        return KeyStateDown;
    case(0):
        return KeyStateUp;
    }
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


void DrawBlockBasedOnInput(KeyStatus key, Block block, char texture) {
    FillBlock(
        block,
        key == KeyStateUp ? ' ' : texture
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
        count++;
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            { 0, 0 }
        );
        std::cout << "Running... Cycle: " << count;

        // === Get key presses === 
        KeyStatus spacebar = GetKeyInput(VK_SPACE);

        KeyStatus upArrow = GetKeyInput(VK_UP);
        KeyStatus leftArrow = GetKeyInput(VK_LEFT);
        KeyStatus downArrow = GetKeyInput(VK_DOWN);
        KeyStatus rightArrow = GetKeyInput(VK_RIGHT);

        KeyStatus wKey = GetKeyInput(87);
        KeyStatus aKey = GetKeyInput(65);
        KeyStatus sKey = GetKeyInput(83);
        KeyStatus dKey = GetKeyInput(68);

        // This is somehow TOGGLING...
        // From my understanding, should only appear when held.

        DrawBlockBasedOnInput(wKey, blockN, '^');
        DrawBlockBasedOnInput(aKey, blockW, '<');
        DrawBlockBasedOnInput(sKey, blockS, 'v');
        DrawBlockBasedOnInput(dKey, blockE, '>');



        if (spacebar & KeyStateDown)
        {
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }
    }

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        { 0, 0 }
    );

    std::cout << "Exiting..." << std::endl;

    std::cin.get();

}
