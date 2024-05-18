#include "Game.h"
#include "Input.h"
#include "EntityManager.h"

void Game::Play() {
    while(running){
        // Get Player Input 
        Input::Input::UpdateAllInputState();
        // Update Entities
        CLGEngine::EntityManager::UpdateEntities();
        // Update Render
    }
}

void Game::Exit(){
    running = false;
}