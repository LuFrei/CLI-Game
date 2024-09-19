#pragma once

#include <Windows.h>
#include "../TileMap.h"

namespace CLGEngine {
/// <summary>
/// Object that represents the viewport into the virttual world; i.e. 
/// the client's screen that renders the game.
/// </summary>
class Screen
{
private:
	int width;
	int height;

	CHAR_INFO* data;

	bool squareCells;
	TileMap* tileMap;
	void ClearScreenData();
public:

	Screen(int width, int height);

	/// <summary>
	/// Whether the renderer should display a cell as a square of standard rectangle?
	/// Effectively doubles the width of the rendered game-world objects, more accuratly displying a 2x2 block to look like a square.
	/// </summary>
	/// <param name="isSquare">Should objects be </param>
	void SetSquareCells(bool isSquare);
	/// <summary>
	/// Visually display all active Blocks based on their position and dimensions.
	/// </summary>
	void Draw();
	void SetTileMap(TileMap* map) {tileMap = map;};
};
}