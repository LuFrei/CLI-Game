#pragma once

#include "../CLGEngine/Entity.h"
#include "../CLGEngine/CORE/Vector2.h"
#include "TileMap.h"
#include "Character.h"

// I'm tired, headache. i just want to hash somethign dumb up...
// !! This will be EXTREMELY hardcoded because i can't be bothered to look into the future and figure out 20 million ways this should work.

// This will take a tilemap and anything that should be interacting with it,
//   and track it's movement across the tilemap.
// We will track a Rect's vertices to get best precision for colision against Tiles.
class TileMapChecker : Entity {
    // We will only check the player for now.
    Character* player;
    // Need to make vertices from Player's rect.
    // note we only need the whole number it's in. No float, just integer.
    CORE::Vector2<float> TL,
        TR,
        BR,
        BL;
    TileMap* map;
public:
    TileMapChecker(Character* player, TileMap* map);
    void Update();
};