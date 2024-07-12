#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity(float x, float y, float width,float height)
		   : rend(nullptr)
		   , col(nullptr)
		   , rect_({x, y, width, height})
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

	void Entity::Translate(CORE::Vector2<float> direction) {
		//Check if we can translate first
		//project new location
		float newX = rect_.position.x + direction.x;
		float newY = rect_.position.y + direction.y;
		if(col != nullptr){
			col->SetColliderPosition({newX, newY});
			Collider* hit = NULL;
			if(col->CheckCollision(&hit)){
				// if new movement hits something, snap position to hug collided object..
				if(direction.x > 0){
					newX = hit->bounds.left - rect_.size.x;
				}
				if(direction.x < 0){
					newX = hit->bounds.right;
				}
				if(direction.y > 0){
					newY = hit->bounds.top - rect_.size.y;
				}
				if(direction.y < 0){
					newY = hit->bounds.bottom;
				}
				col->SetColliderPosition({newX, newY});
			}
		}
		if(rend != nullptr){
			rend->SetBlockPosition({newX, newY});
		}
		rect_.position.x = newX;
		rect_.position.y = newY;
	}

	void Entity::SetPosition(CORE::Vector2<float> newPos){
		//Tell Components I moved.
		col->SetColliderPosition(newPos);
		rend->SetBlockPosition(newPos);
	}

	void Entity::Scale(float x, float y) {
		this->rect_.size.x *= x;
		this->rect_.size.y *= y;
	}

	void Entity::AddRenderer(CHAR_INFO material){
		// Replace existing
		if(rend != nullptr){
			delete rend;
		}
		rend = new Graphics::Renderer(&this->rect_, material);
	}

	void Entity::AddCollider(){
		if(col != nullptr){
			// remove from component
			delete col;
		}
		col = new Collider(&this->rect_);
	}
}