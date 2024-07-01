#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/Wall.h"
#include "CLGEngine/Entity.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    Character* player = new Character(10);
    Wall* ground = new Wall(0, 21, 60, 3);
    Wall* wall1 = new Wall(10, 20, 1, 1);
    Wall* wall2 = new Wall(15, 19, 1, 2);
    Wall* wall3 = new Wall(20, 18, 1, 3);
    Wall* wall4 = new Wall(25, 17, 1, 4);
    
    
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete player;
    delete ground;
    delete wall1;
    delete wall2;
    delete wall3;
    delete wall4;
}
