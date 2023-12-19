#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "Render.h"

namespace Graphics {
	std::vector<Block*> Renderer::blocks;

	/// <summary>
	/// Counter to assign new Rets unique Ids.
	/// </summary>
	unsigned int blockIdCounter = 0;

	const int screenWidth = 120;
	const int screenHeight = 60;
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];

	DWORD charsWritten = 0;

	HANDLE cScreenHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);



	void InitGraphics() {
		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(cScreenHandle, &cursorInfo);
		cursorInfo.bVisible = 0;
		SetConsoleCursorInfo(cScreenHandle, &cursorInfo);

		SetConsoleActiveScreenBuffer(cScreenHandle);
	}
	

	Renderer::Renderer(int x, int y, int width, int height, char material) {
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

	void Renderer::DrawBlocks() {


		for (int i = 0; i < screenWidth * screenHeight; i++) {
			wchar_t texture = ' ';
			if (i < screenWidth) {
				texture = 'v';
			}
			if (i % screenWidth == 0) {
				texture = '>';
			}
			if (i % screenWidth == (screenWidth - 1)) {
				texture = '<';
			}
			screen[i] = texture;
		}

		// Paint the border


		for (Block* block : blocks) {
			// is this block going to show up in the screen?
			if (block->x >= screenWidth
				|| block->y >= screenHeight
				|| block->x + block->width < 0
				|| block->y + block->height < 0)
			{ continue; }


			for (int w = 0; w < block->width; w++) {
				for (int h = 0; h < block->height; h++) {
					int cellX = block->x + w;
					int cellY = block->y + h;

					// is this part of the block within screen's bounds?
					if(cellX < 0 
					   || cellX >= screenWidth
					   || cellY < 0
					   || cellY >= screenHeight)
					{ continue; }

					screen[screenWidth * (block->y + h) + (block->x + w)] = block->material;
				}
			}
		}
			WriteConsoleOutputCharacter(cScreenHandle, screen, screenWidth * screenHeight, { 0, 0 }, &charsWritten);
	}
}