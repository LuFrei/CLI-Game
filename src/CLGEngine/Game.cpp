#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EntityManager.h"


Game::Game() :
    mainWindow() 
{ }

void Game::Play() {
    while(running){
        CLGEngine::Time::CalculateDeltaTime();

        Input::Input::UpdateAllInputState();

        CLGEngine::EntityManager::UpdateEntities();

        mainWindow.screen->Draw();
    }
}

void Game::Exit(){
    running = false;
}