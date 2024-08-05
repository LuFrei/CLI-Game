#include "TileMap.h"
#include <cmath>

// class TileMap{
//     int width, height;
//     const CHAR_INFO map[];
//     /// @brief Whether the contents of map should be displayed literal.
//     bool coded;
//     std::map<std::string, CHAR_INFO> codeMapping;
// };


TileMap::TileMap(int width, int height, std::string mapData) : 
    width(width),
    height(height),
    coded(false)
{
    for(char& c : mapData){
        CHAR_INFO cInfo = {c, 0};
        map.push_back(cInfo);
    }
}

char TileMap::GetTile(CLGEngine::CORE::Vector2<float> coords){
    try {
        if (coords.x < 0 || coords.x > width){
            throw "X is out of bounds";
        }
        if (coords.y < 0 || coords.y > height){
            throw "Y is out of bounds";
        }
        return map[std::floor(coords.x) * std::floor(coords.y)].Char.AsciiChar;
    } catch (std::string err) {

    }
}