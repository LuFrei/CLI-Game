#include "TileMap.h"
#include <cmath>

TileMap::TileMap(int width, int height, std::string mapData) 
    : width(width)
    , height(height)
    , coded(false)
{
    for(char& c : mapData){
        CHAR_INFO cInfo = {c, 0};
        map.push_back(cInfo);
    }
}

wchar_t TileMap::GetTile(CLGEngine::CORE::Vector2<float> coords){
    if (coords.x < 0 || coords.x > width || coords.y < 0 || coords.y > height){
        return ' ';
    }
    int xInt = std::floor(coords.x);
    int yInt = std::floor(coords.y);
    return map[width * yInt + xInt].Char.AsciiChar;
}