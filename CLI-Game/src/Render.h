#pragma once

#include <vector>

// We can store all created instances to update every cycle
namespace Graphics {

	/// <summary>
	/// 
	/// </summary>
	struct Block {
		int x, y, z;
		unsigned int width, height, 
			id;
		wchar_t material;
	};

	void InitGraphics();

	class Renderer{
	private:
		static std::vector<Block*> blocks;
	public:
		Block block;
		Renderer(int x, int y, int width, int height, char material);
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