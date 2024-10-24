#pragma once

#include "Graphics/Screen.h"
#include "CORE/ConsoleWindow.h"


namespace CLGEngine{
class Game {
private:
    static Game* _instance;
    
    bool running = true;
public:
    static Game* GetGameInstance() {return _instance;};
    
    CLGEngine::CORE::ConsoleWindow mainWindow;
    Game();
    ~Game();
    void Play();
    void Exit();
};
}