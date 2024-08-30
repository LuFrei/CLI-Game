#pragma once

#include "Utility.h"
#include "../Entity.h"

class Component{
protected:
    CLGEngine::Entity* const _ent;
public:
    Component();
    Component(CLGEngine::Entity* ent)
        : _ent(ent)
    {};
};