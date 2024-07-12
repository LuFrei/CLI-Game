#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity(float x, float y, float width,float height)
		   : rend(nullptr)
		   , col(nullptr)
		   , rect({x, y, width, height})
		{
		EntityManager::AddEntity(this);
	}

	Entity::~Entity() {
		if(rend != nullptr){
			delete rend;
		}
		if(col != nullptr){
			delete col;
		}
		// delete componentMan;		
		EntityManager::RemoveEntity(this);
	}

	void Entity::Translate(float x, float y) {
		//Check if we can translate first
		//project new location
		float newX = rect.position.x + x;
		float newY = rect.position.y + y;
		if(col != nullptr){
			col->SetColliderPosition(newX, newY);
			Collider* hit = NULL;
			if(col->CheckCollision(&hit)){
				// if new movement hits something, snap position to hug collided object..
				if(x > 0){
					newX = hit->bounds.left - rect.size.x;
				}
				if(x < 0){
					newX = hit->bounds.right;
				}
				if(y > 0){
					newY = hit->bounds.top - rect.size.y;
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
		rect.position.x = newX;
		rect.position.y = newY;
	}

	void Entity::Translate(CORE::Vector2<float> direction) {
		Translate(direction.x, direction.y);
	}

	void Entity::Scale(float x, float y) {
		this->rect.size.x *= x;
		this->rect.size.y *= y;
	}

	void Entity::AddRenderer(CHAR_INFO material){
		// Replace existing
		if(rend != nullptr){
			delete rend;
		}
		rend = new Graphics::Renderer(&this->rect, material);
	}

	void Entity::AddCollider(){
		if(col != nullptr){
			// remove from component
			delete col;
		}
		col = new Collider(&this->rect);
	}
}