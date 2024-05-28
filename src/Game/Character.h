#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"
#include "../CLGEngine/Collider.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	float speed;
public:
	Graphics::Renderer* rend;
	Collider* col;
	Character(float speed);
	~Character();
	void Move(float x, float y);
	void Update();
};