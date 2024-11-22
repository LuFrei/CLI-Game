#pragma once
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Component/BlockRenderer.h"
#include "../../CLGEngine/Component/Collider.h"

class Wall : public CLGEngine::Entity {
private:
    CLGEngine::BlockRenderer* _rend;
    CLGEngine::Collider* _col;
public:
    Wall(int x, int y, int width, int height);
    ~Wall();
    void Update();
};