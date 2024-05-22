#include <iostream>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity(float x, float y, float width,float height) {
		position = {x, y};
		size = {width, height};
		EntityManager::AddEntity(this);
	}

	Entity::~Entity() {
		EntityManager::RemoveEntity(this);
	}

	void Entity::Translate(float x, float y) {
		this->position.x += x;
		this->position.y += y;
	}

	void Entity::Scale(float x, float y) {
		this->size.x *= x;
		this->size.y *= y;
	}
}