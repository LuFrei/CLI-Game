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
	/// Counter to assign new Rets unique Ids.
	/// </summary>
	unsigned int blockIdCounter = 0;

	const int screenWidth = 120;
	const int screenHeight = 60;
	CHAR_INFO* screen = new CHAR_INFO[screenWidth * screenHeight];

	SMALL_RECT screenBounds = { 0, 0, screenWidth, screenHeight};

	HANDLE cScreenHandle = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);
	
	void InitGraphics() {
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(cScreenHandle, &cursorInfo);
		cursorInfo.bVisible = 0;
		SetConsoleCursorInfo(cScreenHandle, &cursorInfo);

		CONSOLE_FONT_INFOEX fontInfo;
		GetCurrentConsoleFontEx(cScreenHandle, 0, &fontInfo);
		/*fontInfo.dwFontSize = { 4, 4 };*/
		SetCurrentConsoleFontEx(cScreenHandle, 0, &fontInfo);

		SetConsoleActiveScreenBuffer(cScreenHandle);

		std::cout << "Testing new font info" << std::endl;
	}
	

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

	void Renderer::DrawBlocks() {


		// Paint the border
		for (int i = 0; i < screenWidth * screenHeight; i++) {
			unsigned char asciiSymbol = ' ';
			unsigned short backgroundColor = 0;
			unsigned short foreGroundColor = FOREGROUND_RED;
			if (i < screenWidth 
			|| i >= screenWidth * (screenHeight - 1)){
				asciiSymbol = ASCII_HORIZONTAL_BAR;
			}
			if (i % screenWidth == 0 
			|| (i % screenWidth == (screenWidth - 1))) {
				asciiSymbol = ASCII_VERTICAL_BAR;
			}
			CHAR_INFO texture;
			texture.Char.AsciiChar = asciiSymbol;
			texture.Attributes = 0 | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

			screen[i] = texture;
		}


		for (Block* block : blocks) {
			// is this block ever going going to show up in the screen?
			if (block->x >= screenWidth
				|| block->y >= screenHeight
				|| block->x + block->width < 0
				|| block->y + block->height < 0)
			{ continue; }


			for (unsigned int w = 0; w < block->width; w++) {
				for (unsigned int h = 0; h < block->height; h++) {
					int cellX = block->x + w;
					int cellY = block->y + h;

					// is this PART of the block within screen's bounds?
					if(cellX < 0 
					   || cellX >= screenWidth
					   || cellY < 0
					   || cellY >= screenHeight)
					{ continue; }


					switch(w % 4) {
					case(0):
						block->material.Char.AsciiChar = ASCII_SHADE1;
						break;
					case(1):
						block->material.Char.AsciiChar = ASCII_SHADE2;
						break;
					case(2):
						block->material.Char.AsciiChar = ASCII_SHADE3;
						break;
					case(3):
						block->material.Char.AsciiChar = ASCII_SHADE4;
						break;
					}

					screen[screenWidth * (block->y + h) + (block->x + w)] = block->material;
				}
			}
		}
		WriteConsoleOutputA(cScreenHandle, screen, { screenWidth , screenHeight }, { 0, 0 }, &screenBounds);
	}
}