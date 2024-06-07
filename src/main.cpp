#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/Wall.h"
#include "CLGEngine/Entity.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    Character* player = new Character(10);
    Wall* wall = new Wall();

    game.Play();
    
    delete player;
    delete wall;
}
