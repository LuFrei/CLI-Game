#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "Render.h"

namespace Render {
	std::vector<Block> Renderer::blocks;


	/// <summary>
	/// Counter to assign new Rets unique Ids.
	/// </summary>
	unsigned int blockIdCounter = 0;

	Renderer::Renderer(int x, int y, int width, int height, char material) {
		block.id = blockIdCounter;
		blockIdCounter++;

		block.x = x;
		block.y = y;
		block.width = width;
		block.height = height;
		block.material = material;

		//std::cout << "Created Renderer with Block id: " << block.id << std::endl;

		blocks.push_back(block);
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
			constexpr bool operator()(Block const& b) const {
				return b.id == id;
			}
		};

		auto it = std::find_if(blocks.begin(), blocks.end(), find_id(block.id));

		std::cout << "*it is the same as this->block? " << ((*it).id == block.id) << std::endl;

		if ((*it).id != block.id) {
			std::cout << "ERROR: Wrong block was deleted." << std::endl;
		}

	}

	void Renderer::updateBlock(int newX, int newY) {
		block.x = newX;
		block.y = newY;
	}
	void Renderer::updateBlock(unsigned int newWidth, unsigned int newHeight) {
		block.width = newWidth;
		block.height = newHeight;
	}
	void Renderer::updateBlock(int newX, int newY, int newWidth, int newHeight) {
		updateBlock(newX, newY);
		updateBlock(newWidth, newHeight);
	}

	void Renderer::DrawBlocks() {
		//std::cout << "Drawing blocks" << std::endl;
		for (const Block& block : blocks) {
			std::cout << "Drawing block " << block.id << "." << std::endl;
			for (unsigned short i = 0; i < block.height; i++) {
				SetConsoleCursorPosition(
					GetStdHandle(STD_OUTPUT_HANDLE),
					{ (short)block.x, (short)(block.y + i) }
				);
				for (unsigned int j = 0; j < block.width; j++) {
					std::cout << "drawing material" << std::endl;
					std::cout << block.material;
				}
			}
		}
	}

	void Renderer::EraseBlocks() {
		for (const Block& block : blocks) {
			for (unsigned short i = 0; i < block.height; i++) {
				SetConsoleCursorPosition(
					GetStdHandle(STD_OUTPUT_HANDLE),
					{ (short)block.x, (short)(block.y + i) }
				);
				for (unsigned int j = 0; j < block.width; j++) {
					std::cout << " ";
				}
			}
		}
	}

}