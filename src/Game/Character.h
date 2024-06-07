#pragma once
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/Render.h"
#include "../CLGEngine/Collider.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	int speed;
public:
	Character(int speed);
	~Character();
	void Move(int x, int y);
	void Update();
};