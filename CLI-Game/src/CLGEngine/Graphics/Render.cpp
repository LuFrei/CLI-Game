#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <wincon.h>

#include "Render.h"
#include "ASCII.h"

namespace Graphics {
	std::vector<Block*> Renderer::blocks;

	/// <summary>
	/// Counter to assign new Rects unique Ids.
	/// </summary>
	unsigned int blockIdCounter = 0;
	

	Renderer::Renderer(int x, int y, int width, int height, CHAR_INFO& material) {
		block.id = blockIdCounter;
		blockIdCounter++;

		block.x = x;
		block.y = y;
		block.width = width;
		block.height = height;
		block.material = material;

		blocks.push_back(&block);
	}
	 
	Renderer::~Renderer() {
		// Delete the Rects
		// Remove it from Rectangles list

		std::cout << "Deleting Renderer with Block id: " << block.id << std::endl;

		// find the index of the correct Block within the vector
		// Solution from: https://stackoverflow.com/questions/589985/vectors-structs-and-stdfind
		struct find_id  {
			unsigned int id;
			find_id(unsigned int id) :id(id) { }
			constexpr bool operator()(Block* b) const {
				return b->id == id;
			}
		};

		auto it = std::find_if(blocks.begin(), blocks.end(), find_id(block.id));

		std::cout << "*it is the same as this->block? " << ((*(*it)).id == block.id) << std::endl;

		if ((*(*it)).id != block.id) {
			std::cout << "ERROR: Wrong block was deleted." << std::endl;
		}

	}

	void Renderer::updateBlockPosition(int newX, int newY) {
		block.x = newX;
		block.y = newY;
	}
	void Renderer::updateBlockSize(unsigned int newWidth, unsigned int newHeight) {
		block.width = newWidth;
		block.height = newHeight;
	}
	void Renderer::updateBlock(int newX, int newY, int newWidth, int newHeight) {
		updateBlockPosition(newX, newY);
		updateBlockPosition(newWidth, newHeight);
	}

}