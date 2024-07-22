#pragma once
#include "../CLGEngine/Entity.h"
// #include "../CLGEngine/Graphics/Render.h"
// #include "../CLGEngine/Collider.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	int speed;
	bool grounded;
public:
	Character(int speed);
	~Character();
	void Move(float direction);
	void Jump();
	void Update();
};