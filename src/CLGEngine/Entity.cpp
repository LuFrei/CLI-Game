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
		EntityManager::RemoveEntity(this);
	}

#pragma region Transform
	void Entity::Translate(Vector2<float> direction) {
		_rect.position += direction;
		Notify(Event::Moved);
	}

	void Entity::SetPosition(Vector2<float> newPos){
		_rect.position = newPos;
		Notify(Event::Moved);
	}

	void Entity::Scale(float x, float y) {
		this->_rect.size.x *= x;
		this->_rect.size.y *= y;
	}
#pragma endregion

#pragma region Event
// TODO: Will it make more ense to send `this` to ISubject itself?
	void Entity::AddSubscriber(IObserver* o) {
		_observers.emplace_front(o);
	}

	void Entity::RemoveSubscriber(IObserver* o) {
		_observers.remove(o);
	}

	void Entity::Notify(Event e) {
		for(IObserver* o : _observers){
			o->OnNotify(e);
		}
	}


#pragma endregion
}
