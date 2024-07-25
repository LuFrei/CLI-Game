#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/Wall.h"
#include "CLGEngine/Entity.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();


    Character* player = new Character({7, 20});
    Wall* ground = new Wall(0, 22, 60, 13);
    Wall* borderWallL = new Wall(0, 0, 5, 25);
    Wall* borderWallR = new Wall(55, 0, 5, 25);
    Wall* borderWallT = new Wall(0, 0, 60, 1);

    Wall* wall1 = new Wall(10, 20, 1, 1);
    Wall* wall2 = new Wall(15, 19, 1, 2);
    Wall* wall3 = new Wall(40, 6, 1, 25);
    Wall* wall4 = new Wall(35, 17, 1, 4);
    
    
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete player;
    delete ground;
    delete borderWallL;
    delete borderWallR;
    delete borderWallT;
    delete wall1;
    delete wall2;
    delete wall3;
    delete wall4;
}
