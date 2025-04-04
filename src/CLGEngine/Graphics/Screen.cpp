#include "Screen.h"

#include "ASCII.h" 
#include "../CORE/Vector2.h"

namespace CLGEngine {
SMALL_RECT bounds;
HANDLE cOutBuffer;

// TODO: This should be the same save as the window.
//		There's a bug right now that locks the maximum size to the default window size no matter what 
Screen::Screen(int width, int height) {
	this->_width = width;
	this->_height = height;

	_data = new CHAR_INFO[width * height];
	bounds = { 0, 0, (short)width, (short)height };

	// TODO: May need to create a new buffer everytime the screen resizes.
	// Note: This is specific to console. worth renaming.
	cOutBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
	);

	SetConsoleActiveScreenBuffer(cOutBuffer);

	// Set cursor invisible
	// TODO(Stretch): Lets make this an option later.
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(cOutBuffer, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(cOutBuffer, &cursorInfo);
}

void Screen::AddToRenderQueue(Block* block){
	_renderQueue[block->z()].push_back(block);
}

void Screen::RemoveFromRenderQueue(Block* block){
	std::vector<Block*> blockList = _renderQueue[block->z()];
	blockList.erase(
		std::find(
			blockList.begin(),
			blockList.end(),
			block
	));
}

void Screen::ClearScreenData() {
	// Paint the border
	for (int i = 0; i < _width * _height; i++) {
		unsigned char asciiSymbol = ' ';


		CHAR_INFO texture;
		texture.Char.AsciiChar = asciiSymbol;
		texture.Attributes = 0 
							 | FOREGROUND_RED 
							 | FOREGROUND_BLUE 
							 | FOREGROUND_GREEN 
							 | FOREGROUND_INTENSITY;

		_data[i] = texture;
	}
}

void Screen::Draw() {
	ClearScreenData();
	for(std::pair<int, std::vector<Block*>> queue : _renderQueue){
		for (Block* block : queue.second) {
			// is this block ever going going to show up in the screen?
			if (block->rect.position.x >= _width
				|| block->rect.position.y >= _height
				|| block->rect.position.x + block->rect.size.x < 0
				|| block->rect.position.y + block->rect.size.y < 0)
			{ continue; }

			for (int h = 0; h < block->rect.size.y; h++) {
				for (int w = 0; w < block->rect.size.x; w++) {
					int cellX = block->rect.position.x + w;
					int cellY = block->rect.position.y + h;

					// Skip if this PART of the block is outside screen's bounds.
					if (cellX < 0
						|| cellX >= _width
						|| cellY < 0
						|| cellY >= _height)
					{
						continue;
					}


					int cellIdx = _width * cellY + cellX;
					int dataIdx = block->rect.size.x * h + w;
					_data[cellIdx] = block->dataArr[dataIdx];
				}
			}
		}
	}

	WriteConsoleOutputA(
		cOutBuffer, 
		_data, 
		{ (short)_width , (short)_height },
		{ 0, 0 },
		&bounds
	);
}

void Screen::Resize(int nW, int nH){
	this->_width = nW;
	this->_height = nH;

	_data = new CHAR_INFO[nW * nH];
	bounds = { 0, 0, (short)nW, (short)nH };
}
}