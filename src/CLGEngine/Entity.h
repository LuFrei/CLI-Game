#pragma once

#include <vector>
#include <string>
#include <map>
#include <forward_list>
#include "CORE/ISubject.h"
#include "CORE/Vector2.h"
#include "CORE/Rect.h"

 

namespace CLGEngine {


	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	class Entity : public ISubject {
// ISubject
	public:
		enum Event {
			Moved
		};
		void AddSubscriber(IObserver* o) override;
		void RemoveSubscriber(IObserver* o) override;
	private:
		void Notify() override;
		std::forward_list<IObserver*> _observers;

// Core
	public:
		/// @brief name that can be used to identify an instance.
		std::string name = "unnamed";
		Rect rect; //May have to set as protected later for Component Rework.
		Entity(float x, float y, float width, float height);
		~Entity();
		virtual void Update() = 0;

		// Transform
		void Translate(CORE::Vector2<float> direction);
		void SetPosition(CORE::Vector2<float> newPosition);
		void Scale(float x, float y);

	};
}