#include "TileMap.h"
#include <cmath>

TileMap::TileMap(MapData data) 
: size({data.width, data.height})
{
    for(char& c : data.data){
        CHAR_INFO cInfo = {c, 0};
        _map.push_back(cInfo);
    }

    for(int i = 0; i < data.data.size(); i++){
        char c = data.data[i];
        CHAR_INFO cInfo = {c, 0};
        _map.push_back(cInfo);

        if(c == 's'){
            int y = std::floor(i / size.x);
            int x = i % size.x;
            startPos = {x, y};
        }
        if(c == 'e'){
            int y = std::floor(i / size.x);
            int x = i % size.x;
            endPos = {x, y};
        }


    }
}

wchar_t TileMap::GetTile(CLGEngine::CORE::Vector2<float> coords){
    int x = std::floor(coords.x - offset.x);
    int y = std::floor(coords.y - offset.y);
    if (x < 0 || x >= size.x || y < 0 || y >= size.y){
        return ' ';
    }

    return _map[size.x * y + x].Char.AsciiChar;
}

void TileMap::SetMap(MapData data){
    _map.clear();
    for(char& c : data.data){
        CHAR_INFO cInfo = {c, 0};
        _map.push_back(cInfo);
    }
    size.x = data.width;
    size.y = data.height;
}