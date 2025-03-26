#pragma once

#include <map>
#include <string>
#include <vector>
#include "../CLGEngine/MapData.h"

const int MAX_LEVELS = 9;

// This can literally just be a part of Game Manager...
class Maps{
private:
    static Maps* _instance;
public:
    static const std::vector<MapData> list;
    Maps();
};
