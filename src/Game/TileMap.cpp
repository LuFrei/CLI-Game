#include "TileMap.h"
#include <cmath>

TileMap::TileMap(MapData data) 
    : width(data.width)
    , height(data.height)
    , coded(false)
{
    for(char& c : data.data){
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

void TileMap::SetMap(MapData data){
    map.clear();
    for(char& c : data.data){
        CHAR_INFO cInfo = {c, 0};
        map.push_back(cInfo);
    }
    width = data.width;
    height = data.height;
}