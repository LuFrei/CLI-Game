#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

namespace CLGEngine {

	Entity::Entity(float x, float y, float width,float height)
		   : rect({x, y, width, height})
	{
		EntityManager::AddEntity(this);
	}

	Entity::~Entity() {
		EntityManager::RemoveEntity(this);
	}

#pragma region Transform
	void Entity::Translate(CORE::Vector2<float> direction) {
		rect.position.x += direction.x;
		rect.position.y += direction.y;
		Notify();
	}

	void Entity::SetPosition(CORE::Vector2<float> newPos){
		rect.position = newPos;
		Notify();
	}

	void Entity::Scale(float x, float y) {
		this->rect.size.x *= x;
		this->rect.size.y *= y;
	}
#pragma endregion

#pragma region Event
// TODO: Will it make more ense to send this to ISubject itself?
	void Entity::AddSubscriber(IObserver* o) {
		_observers.emplace_front(o);
	}

	void Entity::RemoveSubscriber(IObserver* o) {
		_observers.remove(o);
	}
	


	void Entity::Notify(Event e) {
		for(IObserver* o : _observers){
			o->OnNotify();
		}
	}


#pragma endregion
}
