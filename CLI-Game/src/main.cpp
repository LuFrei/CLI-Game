#include <iostream>
#include <Windows.h>

struct Vector2 {
    int x, y;
};

enum KeyStatus {
    KeyStateUp = 0,         // no signal
    KeyStateDown = 0x8000,  // high-order bit
    KeyStateToggled = 1     // lower-order bit
};

KeyStatus GetKeyInput(int key) {
    switch (GetKeyState(key)) {
    case(0):
        return KeyStateUp;
    case(1):
        return KeyStateToggled;
    case(0x8000):
        return KeyStateDown;
    }
}

void FillBlock(Vector2 position, int width, int height, char character) {

    for (short i = 0; i < height; i++) {
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)position.x, (short)(position.y + i) }
        );
        for (int j = 0; j < width; j++) {
            std::cout << character;
        }
    }

}

int main()
{
    std::cout << "Hello and Welcome!\n";
    bool running = true;
    int count = 0;

    while (running) {
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            { 0, 0 }
        );
        count++;

        std::cout << "Running... Cycle: " << count;

        // Get key presses 
        KeyStatus spacebar = GetKeyInput(VK_SPACE);

        if (spacebar & KeyStateDown)
        {
            std::cout << "Space Detected. " << std::endl;
            running = false;
        }

    }

    std::cout << "Exiting..." << std::endl;

    std::cin.get();

}
