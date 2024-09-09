#pragma once

#include <map>
#include <string>
#include "MapData.h"

class Maps{
private:
    static Maps* _instance;
    static std::map<std::string, MapData> _mapList;
public:
    Maps();
    static MapData GetMap(std::string mapName);
};

