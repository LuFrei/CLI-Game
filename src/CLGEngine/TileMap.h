#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include "CORE/Vector2.h"
#include "MapData.h"

class TileMap {
private:
    std::vector<CHAR_INFO> _map;
public:
    CLGEngine::CORE::Vector2<int> size;
    CLGEngine::CORE::Vector2<int> endPos;
    CLGEngine::CORE::Vector2<int> startPos;
    
    CLGEngine::CORE::Vector2<int> offset = {0, 0}; // We currently need this to grab global Tile location. Will have to set from GameManager for now.

    TileMap(MapData data);
    wchar_t GetTile(CLGEngine::CORE::Vector2<float> coords);
    void SetMap(MapData map);
};