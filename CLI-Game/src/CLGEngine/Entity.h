 #pragma once
#include "CORE/Utility.h"

namespace CLGEngine {
	/// <summary>
	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>	
	class Entity {
	public:
		CORE::Vector2<float> position;
		CORE::Vector2<float> size;
		Entity();
		Entity(float x, float y, int width, int height);
		virtual void Move(float x, float y);
	};
}