#include "Screen.h"

#include "ASCII.h" 
#include "TextRenderer.h"
#include "../CORE/Vector2.h"

namespace CLGEngine {
SMALL_RECT bounds;
HANDLE cOutBuffer;

// TODO: This should be the same save as the window.
//		There's a bug right now that locks the maximum size to the default window size no matter what 
Screen::Screen(int width, int height) {
	this->_width = width;
	this->_height = height;
	this->_squareCells = false;

	_data = new CHAR_INFO[width * height];
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

void Screen::AddToRenderQueue(Block* block){
	_renderQueue.push_back(block);
}

void Screen::RemoveFromRenderQueue(Block* block){
	_renderQueue.erase(
		std::find(
			_renderQueue.begin(),
			_renderQueue.end(),
			block
	));
}


void Screen::ClearScreenData() {
	// Paint the border
	for (int i = 0; i < _width * _height; i++) {
		unsigned char asciiSymbol = ' ';


		CHAR_INFO texture;
		texture.Char.AsciiChar = asciiSymbol;
		texture.Attributes = 0 | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

		_data[i] = texture;
	}
}



void Screen::Draw() {

	// TODO: All of this logic should idealy be taken out and each component shoul take care of it;
	//		Renderer should add the blocks to the screen. TileMapRenderer should interpret Chars to CHAR_INFO. TextREnderer as well. 
	std::vector<TextRenderer*> textElems = TextRenderer::GetTextPool();
 
	ClearScreenData();

	// TODO Move this to a tilemap renderer 
	// 		that sends results to renderQueue.
	for(int y = tileMap->offset.y; y < tileMap->size.y + tileMap->offset.y; y++){
		for(int x = tileMap->offset.x; x < tileMap->size.x + tileMap->offset.x; x++){
			int xCell = x;
			if (this->_squareCells) {
				xCell *= 2;
			}
			wchar_t character = tileMap->GetTile({(float)x, (float)y});
			int idx = _width * y + xCell;
			if(character == '#'){
				unsigned short whiteBG = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
				if (this->_squareCells) {
					_data[idx] = {' ', whiteBG};
					_data[idx +1] = {' ', whiteBG};
				} else {
					_data[idx] = {' ', whiteBG};
				}
			} else if (character == '*' || character == 'e'){
				unsigned short yellowBG = BACKGROUND_GREEN | BACKGROUND_RED;
				if (this->_squareCells) {
					_data[idx] = {' ', yellowBG};
					_data[idx +1] = {' ', yellowBG};
				} else {
					_data[idx] = {' ', yellowBG};
				}
			}
		}
	}

	for (Block* block : _renderQueue) {
		// is this block ever going going to show up in the screen?
		if (block->rect->position.x >= _width
			|| block->rect->position.y >= _height
			|| block->rect->position.x + block->rect->size.x < 0
			|| block->rect->position.y + block->rect->size.y < 0)
		{ continue; }

		for (int h = 0; h < block->rect->size.y; h++) {
			for (int w = 0; w < block->rect->size.x; w++) {
				int cellX = block->rect->position.x + w;
				int cellY = block->rect->position.y + h;

				if (this->_squareCells) {
					cellX *= 2;
				}

				// Skip if this PART of the block is outside screen's bounds.
				if (cellX < 0
					|| cellX >= _width
					|| cellY < 0
					|| cellY >= _height)
				{
					continue;
				}

				if (this->_squareCells) {
					_data[_width * cellY + cellX] = block->material;
					_data[_width * cellY + cellX +1] = block->material;
				} else {
					_data[_width * cellY + cellX] = block->material;
				}
			}
		}
	}

	// Text Render pseudo
	for(TextRenderer* textEl : textElems){
		CORE::Vector2<int> cursorPos = textEl->position;
		if (this->_squareCells) {
			cursorPos.x *= 2;
		}
		for(int i = 0; i < textEl->string.length(); i++){
			_data[_width * cursorPos.y + cursorPos.x].Char.AsciiChar = textEl->string[i];

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

	WriteConsoleOutputA(cOutBuffer, _data, { (short)_width , (short)_height }, { 0, 0 }, &bounds);
}

void Screen::SetSquareCells(bool isSquare) {
	this->_squareCells = isSquare;
}
}