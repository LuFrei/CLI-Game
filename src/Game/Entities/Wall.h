#pragma once
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Components/Renderers/BlockRenderer.h"
#include "../../CLGEngine/Components/Collider.h"

class Wall : public CLGEngine::Entity {
private:
    CLGEngine::BlockRenderer* _rend;
    CLGEngine::Collider* _col;
public:
    Wall(int x, int y, int width, int height);
    ~Wall();
    void Update();
};