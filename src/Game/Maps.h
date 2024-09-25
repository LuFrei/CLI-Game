#pragma once

#include <map>
#include <string>
#include "../CLGEngine/MapData.h"

class Maps{
private:
    static Maps* _instance;
public:
    static const MapData list[4];
    Maps();
};

