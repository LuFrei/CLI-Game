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
    bool _active;
    short _color;
public:

    Switch(std::vector<Door*> doors);
    ~Switch();
    
    void Update();
    void OnCollisionStart(CLGEngine::Entity* hit);
    void OnCollisionEnd(CLGEngine::Entity* hit);

    void Activate();
};