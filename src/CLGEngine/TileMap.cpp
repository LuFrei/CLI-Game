#include "TileMap.h"
#include <cmath>

TileMap::TileMap(MapData data) 
    : width(data.width)
    , height(data.height)
    , _offset({data.xOffset, data.yOffset})
{
    for(char& c : data.data){
        CHAR_INFO cInfo = {c, 0};
        _map.push_back(cInfo);
    }
}

wchar_t TileMap::GetTile(CLGEngine::CORE::Vector2<float> coords){
    int x = std::floor(coords.x - _offset.x);
    int y = std::floor(coords.y - _offset.y);
    if (x < 0 || x > width || y < 0 || y > height){
        return ' ';
    }

    return _map[width * y + x].Char.AsciiChar;
}

void TileMap::SetMap(MapData data){
    _map.clear();
    for(char& c : data.data){
        CHAR_INFO cInfo = {c, 0};
        _map.push_back(cInfo);
    }
    width = data.width;
    height = data.height;
    _offset = {data.xOffset, data.yOffset};
}