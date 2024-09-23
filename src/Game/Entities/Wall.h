#pragma once
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Component/Render.h"
#include "../../CLGEngine/Component/Collider.h"

using namespace CLGEngine;

class Wall : public Entity {
private:
    CLGEngine::Renderer* _rend;
    Collider* _col;
public:
    Wall(int x, int y, int width, int height);
    ~Wall();
    void Update();
};