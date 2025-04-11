#pragma once

#include "Graphics/Screen.h"
#include "CORE/MainWindow.h"


namespace CLGEngine{
class Game {
private:
    static Game* _instance;
    
    bool running = true;
public:
    static Game* GetGameInstance() {return _instance;};
    
    CORE::MainWindow* mainWindow;
    Game();
    ~Game();
    void Play();
    void Exit();
};
}