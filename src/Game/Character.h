#pragma once
#include "../CLGEngine/Entity.h"
// #include "../CLGEngine/Graphics/Render.h"
// #include "../CLGEngine/Collider.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	int speed;
	bool grounded;
	float groundLevel;
public:
	Character(CORE::Vector2<float> startPosition);
	~Character();
	void Move(float direction);
	void Jump();
	void Update();
};