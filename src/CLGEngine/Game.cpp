#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EntityManager.h"
#include "Collider.h"


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

        CLGEngine::Collider::CheckCollisions();

        screen.Draw();
    }
}

void Game::Exit(){
    running = false;
}