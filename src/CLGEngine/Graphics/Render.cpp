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
	
	
	CHAR_INFO defaultMaterial = {
		ASCII_SHADE1,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED
	};


	Renderer::Renderer(Rect* entityRect, CHAR_INFO& material)
		: Component(entityRect) {
		block.id = blockIdCounter;
		blockIdCounter++;

		block.x = entityRect->position.x;
		block.y = entityRect->position.y;
		block.width = entityRect->size.x;
		block.height = entityRect->size.y;
		block.material = material;

		blocks.push_back(&block);
	}
	 
	Renderer::~Renderer() {
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

	void Renderer::SetBlockPosition(CLGEngine::CORE::Vector2<float> newPosition) {
		block.x = newPosition.x;
		block.y = newPosition.y;
	}
	void Renderer::SetBlockSize(float newWidth, float newHeight) {
		block.width = newWidth;
		block.height = newHeight;
	}
	void Renderer::UpdateBlock(float newX, float newY, float newWidth, float newHeight) {
		SetBlockPosition({newX, newY});
		SetBlockSize(newWidth, newHeight);
	}

}