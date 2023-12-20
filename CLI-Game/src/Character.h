#pragma once
#include "Entity.h"
#include "Graphics/Render.h"

class Character : public Entity {
public:
	Graphics::Renderer* rend;
	Character();
	void Move(int x, int y);
};

