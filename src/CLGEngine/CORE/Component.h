#pragma once

#include "Utility.h"
#include "Rect.h"

class Component{
protected:
    const Rect* entityRect;
public:
    Rect offset;
    Component();
    Component(Rect* entRect)
        : entityRect(entRect)
    {};
    Component(Rect* entRect, Rect offset)
        : entityRect(entRect)
        , offset(offset)
    {};
};