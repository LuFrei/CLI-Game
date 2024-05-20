#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EntityManager.h"


Game::Game() : 
    screen(120, 30),
    mainWindow() 
{
    screen.SetSquareCells(true);
}

void Game::Play() {
    while(running){
        CLGEngine::Time::CalculateDeltaTime();

        Input::Input::UpdateAllInputState();

        CLGEngine::EntityManager::UpdateEntities();

        screen.Draw();
    }
}

void Game::Exit(){
    running = false;
}