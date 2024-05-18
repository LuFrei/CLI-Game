#pragma once

#include "Graphics/Screen.h"


class Game {
public:
    Game();
    void Play();
    void Exit();
private:
    bool running = true;
    Graphics::Screen screen;
    
};