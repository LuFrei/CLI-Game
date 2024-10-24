#pragma once

#include <Windows.h>
#include <vector>
#include "../TileMap.h"
#include "../CORE/Rect.h"

namespace CLGEngine {
struct Block {
	Rect* rect;
	int z;
	CHAR_INFO material;
};


/// @brief that represents the viewport into the virttual world; i.e. 
/// the client's screen that renders the game.
class Screen
{
private:
	int _width;
	int _height;

	CHAR_INFO* _data;

	bool _squareCells;
	
	// TODO: Remove this
	TileMap* tileMap;

	void ClearScreenData();
public:
	std::vector<Block*> renderQueue; //RenderCache?


	Screen(int width, int height);

	void SetSquareCells(bool isSquare);

	void Draw();

	void RemoveFromRenderQueue(Block* block);

	// TODO: This needs to be out of here.
	// 	     TileMap should be the one providing data to screen.
	void SetTileMap(TileMap* map) {tileMap = map;};
};
}