#pragma once
#include "Entity.h"
#include "Render.h"

class Character : public Entity {
public:
	Render::Renderer* rend;
	Character();
	void Move(int x, int y);
};

