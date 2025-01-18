#pragma once

#include <vector>
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Components/Collider.h"
#include "../../CLGEngine/Components/Renderers/BlockRenderer.h"
#include "Door.h"

class Switch
: public CLGEngine::Entity {
private:
    CLGEngine::Collider* _col;
    CLGEngine::BlockRenderer* _rend;
    std::vector<Door*> _doors;
    short _color;
public:

    Switch(std::vector<Door*> doors);
    
    void Update();
    void OnCollision(CLGEngine::Entity* hit);

    void Activate();
};