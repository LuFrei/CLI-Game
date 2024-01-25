#include <iostream>
#include "Entity.h"

namespace CLGEngine {

	void Entity::Move(float x, float y) {
		this->x += x;
		this->y += y;
	}

	Entity::Entity() {
		x = 0;
		y = 0;
		width = 1;
		height = 1;
	}

	Entity::Entity(float x, float y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
}