#pragma once

#include <vector>
#include <Windows.h>
#include "../Component.h"
#include "../../CORE/IObserver.h"
#include "../../CORE/Vector2.h"
#include "../../Game.h"
#include "../../Graphics/Screen.h" // Game includes screen... slgihtly redudant

// We can store all created instances to update every cycle
namespace CLGEngine {

/// @brief Handles loading visual assets into the screenrender queue.
///		If a speciallize method of coverting data to Blocks are need, do so from a subclass.
class Renderer : 
	public Component, 
	public IObserver {
private:
	Screen* _screen;
protected:
	bool _squareCells;
public:
	Block block;
	CHAR_INFO material;

	Renderer(Entity* ent);
	~Renderer();

	void SetSquareCells(bool isSquare);

	void OnNotify() override;
};
}
