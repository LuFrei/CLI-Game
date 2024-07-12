#pragma once
#include "CORE/Utility.h"
#include <vector>
#include "Collider.h"
#include "Graphics/Render.h"
#include <string>
#include <map>
#include "CORE/Rect.h"
 
namespace CLGEngine {

	/// <summary>
	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>	
	class Entity {
	private:
		Entity* parent;
		Graphics::Renderer* rend;
		Collider* col;
		void UpdateCollider(float x, float y);
	public:
		Rect rect;
		Entity(float x, float y, float width,float height);
		~Entity();
		virtual void Update() = 0;
		void Translate(float x, float y);
		void Translate(CORE::Vector2<float> direction);
		void SetPosition(float x, float y);
		void SetPosition(CORE::Vector2<float> newPosition);
		void Scale(float x, float y);
		void AddRenderer(CHAR_INFO material);
		void AddCollider();
	};
}