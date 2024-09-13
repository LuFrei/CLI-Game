#pragma once

#include "../Entity.h"

class Component{
protected:
public:
    CLGEngine::Entity* const entity;
    Component();
    Component(CLGEngine::Entity* ent)
        : entity(ent)
    {};
};