#pragma once

#include <vector>
#include <Windows.h>
#include "../CORE/Component.h"
#include "../CORE/Utility.h"

// We can store all created instances to update every cycle
namespace Graphics {

	/// <summary>
	/// Almalgomation of Entity position nd RendOffset.
	/// </summary>
	struct Block {
		int x, y, z,
			width, height, 
			id;
		CHAR_INFO material;
	};

	class Renderer : public Component {
	private:
		static std::vector<Block*> blocks;
	public:
		Block block;
		CHAR_INFO material;

		Renderer(Rect* entityRect);
		Renderer(Rect* entityRect, int x, int y, int width, int height);
		Renderer(Rect* entityRect, CHAR_INFO& material);
		~Renderer();

		// ! Do we want to create a new new Vector to pass on?
		//   Do we want to give access to the OG Vector that may be modifiable?
		//   Maybe we will have a middle-
		static std::vector<Block*> GetBlocks() {
			return blocks;
		}
		/// <summary>
		/// Up date data to be displayed for this block.
		/// </summary>
		void SetBlockPosition(CLGEngine::CORE::Vector2<float> newPosition);
		void SetBlockSize(float newWidth, float newHeight);
		void UpdateBlock(float newX, float newY, float newWidth, float newHeight);

		// CHAR_INFO CreateColoredMaterial(Color color);
		// CHAR_INFO CreateColoredMaterial(char, Color bgColor, Color fgColor);
	};
}