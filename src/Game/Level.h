#pragma once

#include <vector>
#include <string>
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "../CLGEngine/CORE/Vector2.h"

class Level{
private:
public:
    std::string name;
    TileMap* tileMap;
    CLGEngine::CORE::Vector2<int> offset;
    Level();
    ~Level();
};