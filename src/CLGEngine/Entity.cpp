#include <iostream>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity() {
		position = {0, 0};
		size = {0, 0};
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
		this->size.x += x;
		this->size.y += y;
	}

	void Entity::Update() {
		// TODO: Throw an error here. 
		//		Update() should only ever be called from derived classes.
		// 		Base impl is needed (Point 8): https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2001?view=msvc-170#coding-issues
	}
}