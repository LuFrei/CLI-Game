#pragma once

#include "../CLGEngine/Entity.h"
#include "Character.h"
#include "TileMap.h"

class GameManager {
public:
    static Character* player;
    static TileMap* tileMap;
};