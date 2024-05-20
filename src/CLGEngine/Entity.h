#pragma once
#include "CORE/Utility.h"


namespace CLGEngine {
	/// <summary>
	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>	
	class Entity {
	public:
		CORE::Vector2<float> position; // Due to float math inacurracy, should we make these int, and turn them into int??
		CORE::Vector2<float> size;
		Entity();
		~Entity();
		virtual void Update();
		virtual void Translate(float x, float y);
		virtual void Scale(float x, float y);
	};
}