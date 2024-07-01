#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {
	Entity::Entity(float x, float y, float width,float height)
		: rend(nullptr)
		, col(nullptr) {
		position = {x, y};
		size = {width, height};
		EntityManager::AddEntity(this);
	}

	Entity::~Entity() {
		if(rend != nullptr){
			delete rend;
		}
		if(col != nullptr){
			delete col;
		}		
		EntityManager::RemoveEntity(this);
	}

	void Entity::Translate(float x, float y) {
		//Check if we can translate first
		//project new location
		float newX = position.x + x;
		float newY = position.y + y;
		if(col != nullptr){
			col->SetColliderPosition(newX, newY);
			Collider* hit = NULL;
			if(col->CheckCollision(&hit)){
				// if new movement hits something, snap position to hug collided object..
				if(x > 0){
					newX = hit->bounds.left - size.x;
				}
				if(x < 0){
					newX = hit->bounds.right;
				}
				if(y > 0){
					newY = hit->bounds.top - size.y;
				}
				if(y < 0){
					newY = hit->bounds.bottom;
				}
				col->SetColliderPosition(newX, newY);
			}
		}
		if(rend != nullptr){
			rend->SetBlockPosition(newX, newY);
		}
		position.x = newX;
		position.y = newY;
	}

	void Entity::Translate(CORE::Vector2<float> direction) {
		Translate(direction.x, direction.y);
	}

	void Entity::Scale(float x, float y) {
		this->size.x *= x;
		this->size.y *= y;
	}

	void Entity::AddRenderer(CHAR_INFO material){
		if(rend != nullptr){
			// remove from component
			delete rend;
		}
		rend = new Graphics::Renderer(position.x, position.y, size.x, size.y, material);
	}

	void Entity::AddCollider(){
		if(col != nullptr){
			// remove from component
			delete col;
		}
		col = new Collider(position.x, position.y, size.x, size.y);
	}
}