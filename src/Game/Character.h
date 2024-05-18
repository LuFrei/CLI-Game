#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	float speed;
public:
	Graphics::Renderer* rend;
	Character(float speed);
	void Move(float x, float y);
	void Update();
};