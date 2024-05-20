#pragma once

#include "Graphics/Screen.h"
#include "CORE/MainWindow.h"



class Game {
public:
    Game();
    void Play();
    void Exit();
private:
    bool running = true;
    CLGEngine::CORE::MainWindow mainWindow;
    Graphics::Screen screen;
};