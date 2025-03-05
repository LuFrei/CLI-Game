#pragma once

#include <vector>
#include <string>
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/TileMap.h"
#include "../CLGEngine/CORE/Vector2.h"

/* Level will hold imp

!!- Should we skip this type and just do a level datafile using JSON or XML?
  - Just need a way to translate in LevelManager when Adding or reading.
  - THEIMPROTANT QUESTION HERE IS:
  "is JSON/XML translation as-needed slow enough where we need to store the data first some otherway?"
*/

class Level{
private:
public:
    std::string name;
    TileMap* tileMap;
    CLGEngine::Vector2<int> offset;
    Level();
    ~Level();
};