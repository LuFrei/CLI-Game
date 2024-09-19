#pragma once

#include "../CLGEngine/Entity.h"
#include "Entities/Character.h"
#include "../CLGEngine/TileMap.h"

class GameManager {
public:
    static Character* player;
    static TileMap* tileMap;
};