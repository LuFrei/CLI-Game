#pragma once
#include "CORE/Utility.h"
#include "Entity.h"
#include "CORE/Component.h"
#include <vector>
#include "Graphics/Render.h"
#include "Collider.h"


namespace CLGEngine {
	/// <summary>
	/// Any "physical" thing that can be represented in "world-space". 
	/// Such as a playable or non-playable character, floors, walls, props
	/// </summary>	
	class Entity {
	private:
		Entity* parent;
		std::vector<Component*> components;
		Graphics::Renderer* rend;
		Collider* col;
	public:
		CORE::Vector2<float> position;
		CORE::Vector2<float> size;
		Entity(float x, float y, float width,float height);
		~Entity();
		virtual void Update() = 0;
		virtual void Translate(float x, float y);
		virtual void Scale(float x, float y);
		void AddRenderer(CHAR_INFO material);
		/// @brief Add Renderer with offset
		void AddCollider();
	};
}