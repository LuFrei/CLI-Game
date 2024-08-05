#pragma once

#include <vector>
#include <string>
#include <map>
#include "CORE/ISubject.h"
#include "CORE/Utility.h"
#include "CORE/Rect.h"
#include "Graphics/Render.h"
#include "Collider.h"
 
enum class Events {
	Translation
};

namespace CLGEngine {

	/// <summary>
	/// Any "physical" thing thato can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>	
	class Entity : public ISubject {
	protected:
		Entity* parent = nullptr;
		Graphics::Renderer* rend = nullptr;
		Collider* col = nullptr;
		Rect _rect = {}; //May have to set as protected later for COmponent Rework.
	public:
		friend class Component;
		Rect rect() const {return _rect;}
		Entity(float x, float y, float width, float height);
		~Entity();
		virtual void Update() = 0;

		// Transform
		void Translate(CORE::Vector2<float> direction);
		void SetPosition(CORE::Vector2<float> newPosition);
		void Scale(float x, float y);

		// Components
		void AddRenderer(CHAR_INFO material);
		void AddCollider();

		// ISubject
		void Subscribe(int Event, IObserver* o);
		void Unsubscribe(int Event, IObserver* o);
		void Notify(int Event);
	};
}