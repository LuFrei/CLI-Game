#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"
#include "../CLGEngine/Collider.h"

using namespace CLGEngine;

class Wall : public Entity {
private:
    Graphics::Renderer* _rend;
    Collider* _col;
public:
    Wall(int x, int y, int width, int height);
    ~Wall();
    void Update();
};