#pragma once

#include <map>
#include <string>
#include "../CLGEngine/MapData.h"

const int MAX_LEVELS = 5; 

// This can literally just be a part of Game Manager...
class Maps{
private:
    static Maps* _instance;
public:
    static const MapData list[MAX_LEVELS];
    Maps();
};
