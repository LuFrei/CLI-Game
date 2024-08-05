#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity(float x, float y, float width,float height)
		   : _rect({x, y, width, height})
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

#pragma region Transform
	void Entity::Translate(CORE::Vector2<float> direction) {
		_rect.position.x += direction.x;
		_rect.position.y += direction.y;
		// TODO: We need to move this out of here. Idealy with a Message/Event Call.
		if(col != nullptr){
			Collider* hit = NULL;
			col->ProjectPath(direction, &hit);
		}
	}

	void Entity::SetPosition(CORE::Vector2<float> newPos){
		_rect.position = newPos;	
		// TODO: Should be an event, collider shouldn't be explicitly called here.
		col->SetColliderPosition(newPos);
	}

	void Entity::Scale(float x, float y) {
		this->_rect.size.x *= x;
		this->_rect.size.y *= y;
	}
#pragma endregion

#pragma region Components
	void Entity::AddRenderer(CHAR_INFO material){
		// Replace existing
		if(rend != nullptr){
			delete rend;
		}
		rend = new Graphics::Renderer(&this->_rect, material);
	}

	void Entity::AddCollider(){
		// Replace existing
		if(col != nullptr){
			delete col;
		}
		col = new Collider(&this->_rect);
	}
#pragma endregion

#pragma region Event
// TODO: Will it make more ense to send this to ISubject itself?
	void Entity::Subscribe(int event, IObserver* o){
		_observers[event].emplace_front(o);
	}

	void Entity::Unsubscribe(int event, IObserver* o){
		_observers[event].remove(o);
	}
	
	void Entity::Notify(int Event){
		for(IObserver* o : _observers[Event]){
			o->OnNotify();
		}
	}


#pragma endregion
}
