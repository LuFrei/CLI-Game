#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EntityManager.h"

namespace CLGEngine{
Game* Game::_instance = nullptr;
CORE::MainWindow* secondWindow;

Game::Game()
: mainWindow(new CORE::MainWindow()){
    try{
        if(_instance != nullptr){
            throw "a Game object already exists.";
        }
    } catch(std::string) 
    { }


    _instance = this;
}

Game::~Game(){
    _instance = nullptr;
    delete mainWindow;
}

void Game::Play() {
    while(running){
        CLGEngine::Time::CalculateDeltaTime();

        Input::Input::UpdateAllInputState();

        CLGEngine::EntityManager::UpdateEntities();

        mainWindow->screen->Draw();
    }

    //clean up
}

void Game::Exit(){
    running = false;
    // Find a way to break the game loop
}
}