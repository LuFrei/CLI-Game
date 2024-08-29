#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/Maps.h"
#include "Game/TileMap.h"
#include "Game/Wall.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    TileMap* level = new TileMap(30, 30, map01);
    Character* player = new Character({20, 11});
    player->AddTileMap(level);
    game.screen.SetTileMap(level);
    
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete level;
    delete player;
}
