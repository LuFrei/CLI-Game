#pragma once

#include <vector>
#include <Windows.h>
#include "../CORE/Component.h"
#include "../CORE/Vector2.h"

// We can store all created instances to update every cycle
namespace Graphics {

	/// <summary>
	/// Almalgomation of Entity position nd RendOffset.
	/// </summary>
	struct Block {
		Rect* rect;
		int z, id;
		CHAR_INFO material;
	};

	class Renderer : public Component {
	private:
		static std::vector<Block*> blocks;
	public:
		Block block;
		CHAR_INFO material;

		Renderer(CLGEngine::Entity* ent, CHAR_INFO& material);
		~Renderer();

		static std::vector<Block*> GetBlocks() {
			return blocks;
		}
		/// <summary>
		/// Up date data to be displayed for this block.
		/// </summary>
		void SetBlockPosition(CLGEngine::CORE::Vector2<float> newPosition);
		void SetBlockSize(float newWidth, float newHeight);
		void UpdateBlock(float newX, float newY, float newWidth, float newHeight);
	};
}