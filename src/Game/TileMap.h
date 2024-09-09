#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include "../CLGEngine/CORE/Vector2.h"
#include "MapData.h"

class TileMap {
private:
    std::vector<CHAR_INFO> map;
    const bool coded;
    std::map<std::string, CHAR_INFO> codeMapping;
public:
    const int width, height;
    TileMap(MapData data);
    wchar_t GetTile(CLGEngine::CORE::Vector2<float> coords);
    void ChangeMap(MapData);
};