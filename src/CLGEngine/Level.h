#pragma once

#include <vector>
#include <string>
#include "Entity.h"
#include "TileMap.h"

class Level{
private:
    static std::vector<Level*> _levels;
public:
    std::string name;
    std::vector<CLGEngine::Entity*> entities;
    TileMap* tileMap;
    Level();
    ~Level();
    static void Load(int);
    static void Unload(int);
};