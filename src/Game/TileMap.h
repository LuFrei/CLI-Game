#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include "../CLGEngine/CORE/Utility.h"

class TileMap{
    std::vector<CHAR_INFO> map;
    /// @brief Whether the contents of map should be displayed literal.
    const bool coded;
    std::map<std::string, CHAR_INFO> codeMapping;
public:
    const int width, height;
    TileMap(int width, int height, std::string mapData);
    char GetTile(CLGEngine::CORE::Vector2<float> coords);
}; 