#pragma once

#include <vector>
#include <string>
#include <map>
#include <forward_list>
#include "CORE/ISubject.h"
#include "CORE/Vector2.h"
#include "CORE/Rect.h"

 

namespace CLGEngine {

enum class Event {
	Moved,
	Scaled,
};

/// Any "physical" thing that can be represented in "world-space". 
/// Such as a playable or non-playable character, floors, walls, props
class Entity : public ISubject {
// Core
public:
	/// @brief name that can be used to identify an instance.
	std::string name = "unnamed";
	Entity(float x, float y, float width, float height);
	~Entity();
	// TODO: Figure out do we NEED `virtual` here? 
	//		Update() MUST be callable,
	//		BUT is optional.
	virtual void Update() { };

// Transform
private:
	Rect _rect;
public:
	/// @brief returns a copy of the Entity's Rect.
	Rect rect(){return _rect;}
	/// @brief Adds to the "position" of the Entity's Rect.
	void Translate(Vector2<float> direction);
	/// @brief Sets the "position" parameter of the Entity's Rect.
	void SetPosition(Vector2<float> newPosition);
	void Scale(float x, float y);

// Component helpers
public:
	// TODO: See if Colldider can be referenced here.
	//		Can we use tempaltes???
	virtual void OnCollision(Entity* hit) { }
	virtual void OnCollisionStart(Entity* hit) { }
	virtual void OnCollisionEnd(Entity* hit) { }
	

// ISubject
public:
	void AddSubscriber(IObserver* o) override;
	void RemoveSubscriber(IObserver* o) override;
private:
	void Notify(Event e);
	std::forward_list<IObserver*> _observers;
};
}