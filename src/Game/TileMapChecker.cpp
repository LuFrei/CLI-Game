#include "TileMapChecker.h"


TileMapChecker::TileMapChecker(Character* player, TileMap* map)
: Entity(0, 0, 0, 0)
, player(player)
, map(map)
{ }


void TileMapChecker::Update(){
    // update vertices
    TL = player->rect.position;
    TR = {player->rect.position.x + player->rect.size.x, player->rect.position.y};
    BR = {player->rect.position.x + player->rect.size.x, player->rect.position.y + player->rect.size.y};
    BL = {player->rect.position.x, player->rect.position.y + player->rect.size.y};

    // check for overlap.
    bool playerCollided = false;
    if(map->GetTile(TL) == '#'){
        playerCollided = true;
    }
    if(map->GetTile(TR) == '#'){
        playerCollided = true;
    }
    if(map->GetTile(BR) == '#'){
        playerCollided = true;
    }
    if(map->GetTile(BL) == '#'){
        playerCollided = true;
    }

    // Do something if we collided...
    // We need to trigger the same effect that Collider does..
}