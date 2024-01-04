#pragma once

#include <vector>
#include <Windows.h>

// We can store all created instances to update every cycle
namespace Graphics {

	/// <summary>
	/// Data that define how something will be rendered on screen. 
	/// Position, Dimension, Material.
	/// </summary>
	struct Block {
		int x, y, z;
		unsigned int width, height, 
			id;
		CHAR_INFO material;
	};

	void InitGraphics();

	class Renderer{
	private:
		static std::vector<Block*> blocks;
	public:
		Block block;
		Renderer(int x, int y, int width, int height, CHAR_INFO& material);
		~Renderer();

		/// <summary>
		/// Visually display all active Blocks based on their position and dimensions.
		/// </summary>
		static void DrawBlocks();


		static std::vector<Block*> GetBlocks() {
			return blocks;
		}
		/// <summary>
		/// Up date data to be displayed for this block.
		/// </summary>
		void updateBlockPosition(int newX, int newY);
		void updateBlockSize(unsigned int newWidth, unsigned int newHeight);
		void updateBlock(int newX, int newY, int newWidth, int newHeight);

		 
		
	};
}