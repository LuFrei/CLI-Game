#pragma once

#include "Utility.h"

class Component{
public:
    CLGEngine::CORE::Vector2<float> offset;
    Component() 
        : offset({0,0}) {};
    Component(float offsetX, float offsetY)
        : offset({offsetX, offsetY}) {};
};