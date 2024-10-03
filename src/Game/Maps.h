#pragma once

#include <map>
#include <string>
#include "../CLGEngine/MapData.h"

const int MAX_LEVELS = 5; 

class Maps{
private:
    static Maps* _instance;
public:
    static const MapData list[MAX_LEVELS];
    Maps();
};
