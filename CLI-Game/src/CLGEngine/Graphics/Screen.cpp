#include "Screen.h"

// TODO: Temp, we should not use ASCII_SHADE or Block here.
#include "ASCII.h" 
#include "Render.h"

namespace CLGEngine {
  	SMALL_RECT bounds;
	HANDLE cOutBuffer;

	// TODO: This should be the same save as the window.
	//		There's a bug right now that locks the maximum size to the default window size no matter what 
	Screen::Screen(int width, int height) {
		this->width = width;
		this->height = height;
		this->squareCells = false;

		data = new CHAR_INFO[width * height];
		bounds = { 0, 0, (short)width, (short)height };

		// TODO: May need to create a new buffer everytime the screen resizes.
		cOutBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
		);

		SetConsoleActiveScreenBuffer(cOutBuffer);

		// Set curose invisible
		// TODO(Stretch): Lets make this an option later.
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(cOutBuffer, &cursorInfo);
		cursorInfo.bVisible = 0;
		SetConsoleCursorInfo(cOutBuffer, &cursorInfo);
	}

	void Screen::ClearScreenData() {
		// Paint the border
		for (int i = 0; i < width * height; i++) {
			unsigned char asciiSymbol = ' ';
			unsigned short backgroundColor = 0;
			unsigned short foreGroundColor = FOREGROUND_RED;

			if (i < width
				|| (i > width * (height - 1))) {
				asciiSymbol = ASCII_HORIZONTAL_BAR;
			}
			if (i % width == 0
				|| (i % width == (width - 1))) {
				asciiSymbol = ASCII_VERTICAL_BAR;
			}
			if (i == 0) {
				asciiSymbol = ASCII_CORNER_NW;
			}
			if (i == (width * height) - 1) {
				asciiSymbol = ASCII_CORNER_SE;
			}
			if (i == width - 1) {
				asciiSymbol = ASCII_CORNER_NE;
			}
			if (i == width * (height - 1)) {
				asciiSymbol = ASCII_CORNER_SW;
			}

			CHAR_INFO texture;
			texture.Char.AsciiChar = asciiSymbol;
			texture.Attributes = 0 | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

			data[i] = texture;
		}
	}

	void Screen::Draw() {

		// TODO: Loading data into the screen buffer should be a middle-ground function
		// Take the data that the screen is over in the level data set, and apply it to the buffer.
		
		std::vector<Graphics::Block*> blocks = Graphics::Renderer::GetBlocks();

		ClearScreenData();


		for (Graphics::Block* block : blocks) {
			// is this block ever going going to show up in the screen?
			if (block->x >= width
				|| block->y >= height
				|| block->x + block->width < 0
				|| block->y + block->height < 0)
			{ continue; }

			for (int h = 0; h < block->height; h++) {
				for (int w = 0; w < block->width; w++) {
					int cellX = block->x + w;
					int cellY = block->y + h;

					// Find if this PART of the block is within screen's bounds.
					if (cellX < 0
						|| cellX >= width
						|| cellY < 0
						|| cellY >= height)
					{
						continue;
					}

					// TODO: Move this out of here and into Character; May need to add renderer definition for shaders.
					// ... As part of the renderer, we may be able to have a shader property we can add algos into to 
					// make effects like this one below, or the screen border one...
					switch (w % 4) {
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

					if (this->squareCells) {
						cellX *= 2;
						data[width * cellY + cellX] = block->material;
						data[width * cellY + cellX +1] = block->material;
					} else {
						data[width * cellY + cellX] = block->material;
					}
				}
			}
		}
		WriteConsoleOutputA(cOutBuffer, data, { (short)width , (short)height }, { 0, 0 }, &bounds);
	}

	void Screen::SetSquareCells(bool isSquare) {
		this->squareCells = isSquare;
	}
}