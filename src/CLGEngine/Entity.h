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
	virtual void Update() { };

// Transform
private:
	Rect _rect;
public:
	// Returning a pointer here defeats the purpose of a getter.
	// TODO: Return VALUE
	Rect rect(){return _rect;}
	
	void Translate(Vector2<float> direction);
	void SetPosition(Vector2<float> newPosition);
	void Scale(float x, float y);

// Component helpers
public:
	virtual void OnCollision(Entity* hit) { } // We can't reference Collider because we'd ahve a include loop.

// ISubject
public:
	void AddSubscriber(IObserver* o) override;
	void RemoveSubscriber(IObserver* o) override;
private:
	void Notify(Event e);
	std::forward_list<IObserver*> _observers;
};
}