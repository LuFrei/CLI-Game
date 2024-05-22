#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"

using namespace CLGEngine;

class Wall : public Entity {
private:
public:
    Wall();
	Graphics::Renderer* rend;
    void Update();
};