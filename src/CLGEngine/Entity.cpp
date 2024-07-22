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
		rect_.position.x += direction.x;
		rect_.position.y += direction.y;
		// TODO: We need to move this out of here. Idealy with a Message/Event Call.
		if(col != nullptr){
			Collider* hit = NULL;
			col->ProjectPath(direction, &hit);
		}
	}

	void Entity::SetPosition(CORE::Vector2<float> newPos){
		rect_.position = newPos;	
		// TODO: Should be an event, collider shouldn't be explicitly called here.
		col->SetColliderPosition(newPos);
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
		// Replace existing
		if(col != nullptr){
			delete col;
		}
		col = new Collider(&this->rect_);
	}
}