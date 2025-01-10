#pragma once

#include <Windows.h>
#include <vector>
#include <map>
#include "Block.h"
#include "../CORE/Rect.h"

namespace CLGEngine {

/// @brief that represents the viewport into the virttual world; i.e. 
/// the client's screen that renders the game.
class Screen
{
private:
	int _width;
	int _height;

	CHAR_INFO* _data;

	void ClearScreenData();
	std::vector<Block*> _renderQueue; //RenderCache? We are less going through a queue and more storing a cache of blocks...
public:

	Screen(int width, int height);

	void Draw();

	void AddToRenderQueue(Block* block);
	void RemoveFromRenderQueue(Block* block);
};
}