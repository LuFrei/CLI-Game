#pragma once

#include <vector>

// We can store all created instances to update every cycle
namespace Render {

	struct Block {
		int x, y;
		unsigned int width, height, 
			id;
	};

	class Renderer{
	private:
		static std::vector<Block> blocks;
	public:
		Block block;
		Renderer(int x, int y, int width, int height);
		~Renderer();

		/// <summary>
		/// Up date data to be displayed for this block.
		/// </summary>
		void updateBlock(int newX, int newY);
		void updateBlock(unsigned int newWidth, unsigned int newHeight);
		void updateBlock(int newX, int newY, int newWidth, int newHeight);

		/// <summary>
		/// Visually display all active Blocks based on their position and dimensions.
		/// </summary>
		static void DrawBlocks();

		/// <summary>
		/// Erase all active Blocks.
		/// </summary>
		static void EraseBlocks();

		// TODO: possibly seletively draw or erase a block?
	};
}