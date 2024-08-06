#pragma once

#include "Graphics/Screen.h"
#include "CORE/MainWindow.h"



class Game {
private:
    bool running = true;
    CLGEngine::CORE::MainWindow mainWindow;
public:
    Graphics::Screen screen;
    Game();
    void Play();
    void Exit();
};