#include "Screen.h"

#include "ASCII.h" 
#include "../Component/Render.h" //TODO: This shouldn't be here.
#include "TextRenderer.h"
#include "../CORE/Vector2.h"

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

		/* Border...
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
		*/

		CHAR_INFO texture;
		texture.Char.AsciiChar = asciiSymbol;
		texture.Attributes = 0 | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

		data[i] = texture;
	}
}

void Screen::Draw() {

	// TODO: All of this logic should idealy be taken out and each component shoul take care of it;
	//		Renderer should add the blocks to the screen. TileMapRenderer should interpret Chars to CHAR_INFO. TextREnderer as well. 
	std::vector<Block*> blocks = Renderer::GetBlocks();
	std::vector<TextRenderer*> textElems = TextRenderer::GetTextPool();

	ClearScreenData();

	//Add TileMap render
	// TODO improve this when we mov it to a renderer.
	for(int y = 0; y < tileMap->height; y++){
		for(int x = 0; x < tileMap->width; x++){
			int xCell = x;
			if (this->squareCells) {
				xCell *= 2;
			}
			wchar_t character = tileMap->GetTile({(float)x, (float)y});
			int idx = width * y + xCell;
			if(character == '#'){
				unsigned short whiteBG = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
				if (this->squareCells) {
					data[idx] = {' ', whiteBG};
					data[idx +1] = {' ', whiteBG};
				} else {
					data[idx] = {' ', whiteBG};
				}
			} else if (character == '*'){
				unsigned short yellowBG = BACKGROUND_GREEN | BACKGROUND_RED;
				if (this->squareCells) {
					data[idx] = {' ', yellowBG};
					data[idx +1] = {' ', yellowBG};
				} else {
					data[idx] = {' ', yellowBG};
				}
			}
		}
	}

	for (Block* block : blocks) {
		// is this block ever going going to show up in the screen?
		if (block->rect->position.x >= width
			|| block->rect->position.y >= height
			|| block->rect->position.x + block->rect->size.x < 0
			|| block->rect->position.y + block->rect->size.y < 0)
		{ continue; }

		for (int h = 0; h < block->rect->size.y; h++) {
			for (int w = 0; w < block->rect->size.x; w++) {
				int cellX = block->rect->position.x + w;
				int cellY = block->rect->position.y + h;

				if (this->squareCells) {
					cellX *= 2;
				}

				// Skip if this PART of the block is outside screen's bounds.
				if (cellX < 0
					|| cellX >= width
					|| cellY < 0
					|| cellY >= height)
				{
					continue;
				}

				if (this->squareCells) {
					data[width * cellY + cellX] = block->material;
					data[width * cellY + cellX +1] = block->material;
				} else {
					data[width * cellY + cellX] = block->material;
				}
			}
		}
	}

	// Text Render pseudo
	for(TextRenderer* textEl : textElems){
		CORE::Vector2<int> cursorPos = textEl->position;
		if (this->squareCells) {
			cursorPos.x *= 2;
		}
		for(int i = 0; i < textEl->string.length(); i++){
			data[width * cursorPos.y + cursorPos.x].Char.AsciiChar = textEl->string[i];

			cursorPos.x++;
			if(cursorPos.x >= (textEl->position.x * 2) + textEl->charPerLine){
				cursorPos.x = textEl->position.x * 2; //TODO: Mmodularize `*2`
				cursorPos.y++;
				if(textEl->lineLimit != 0 && cursorPos.y >= textEl->lineLimit){
					continue;
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