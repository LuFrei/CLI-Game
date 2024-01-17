#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"

using namespace CLGEngine;

class Character : public Entity {
public:
	Graphics::Renderer* rend;
	Character();
	void Move(int x, int y);
};