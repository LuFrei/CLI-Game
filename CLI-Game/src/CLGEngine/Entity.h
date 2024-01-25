 #pragma once
namespace CLGEngine {
	/// <summary>
	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>
	class Entity {
	public:
		float x, y;
		int width, height;
		Entity();
		Entity(float x, float y, int width, int height);
		virtual void Move(float x, float y);
	};
}