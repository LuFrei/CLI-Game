#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include "CORE/Vector2.h"
#include "MapData.h"


// !TODO: REFINE THIS CLASS!!
//          This class is a mess. We call it TileMap, 
//          but it's built more like a specialized 2D Mapping classs.

class TileMap {
private:
    std::vector<CHAR_INFO> _map;
public:
    std::map<char, CHAR_INFO> definitions;

    // TODO: It's time I start thinking about moving 
    //      all of this into a game-specific script...
    CLGEngine::Vector2<int> size;
    CLGEngine::Vector2<int> endPos;
    CLGEngine::Vector2<int> startPos;
    
    // TODO: offset should be handled by the LevelManager
    CLGEngine::Vector2<int> offset = {0, 0}; 

    TileMap(MapData data);
    wchar_t GetTile(CLGEngine::Vector2<int> coords);
    void SetMap(MapData map);
    void SetDefinitions(std::map<char, CHAR_INFO> newDefs); // definitions is public, this is a bit redundant.
};