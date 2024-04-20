#include <iostream>
#include "Entity.h"

namespace CLGEngine {

	void Entity::Move(float x, float y) {
		this->position.x += x;
		this->position.y += y;
	}

	Entity::Entity() {
		position.x = 0;
		position.y = 0;
		size.x = 1;
		size.y = 1;
	}

	Entity::Entity(float x, float y, float width, float height) {
		this->position.x = x;
		this->position.y = y;
		this->size.x = width;
		this->size.y = height;
	}
}