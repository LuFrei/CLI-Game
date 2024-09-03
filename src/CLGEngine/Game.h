#pragma once

#include "Graphics/Screen.h"
#include "CORE/ConsoleWindow.h"



class Game {
private:
    bool running = true;
public:
    CLGEngine::CORE::ConsoleWindow mainWindow;
    Game();
    void Play();
    void Exit();
};