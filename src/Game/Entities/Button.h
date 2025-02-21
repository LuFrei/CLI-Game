#pragma once

#include <vector>
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Components/Collider.h"
#include "../../CLGEngine/Components/Renderers/BlockRenderer.h"
#include "Door.h"

class Button
: public CLGEngine::Entity {
private:
    CLGEngine::Collider* _col;
    CLGEngine::BlockRenderer* _rend;
    std::vector<Door*> _doors;
    bool _active;
    short _color;
public:

    Button(std::vector<Door*> doors);
    ~Button();

    void OnCollisionStart(CLGEngine::Entity* hit);

    void Activate();
};