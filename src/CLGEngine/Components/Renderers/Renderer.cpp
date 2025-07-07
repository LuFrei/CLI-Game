#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <wincon.h>

#include "Renderer.h"


namespace CLGEngine {
CHAR_INFO defaultMaterial = {
	ASCII_SHADE1,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED
};

Renderer::Renderer(CLGEngine::Entity* ent)
: Component(ent) 
, _screen(Game::GetGameInstance()->mainWindow->screen)
, block (clr::Block({
	(int)ent->rect().position.x, 
	(int)ent->rect().position.y, 
	(int)ent->rect().size.x, 
	(int)ent->rect().size.y
	})							// Kind of messy, TODO: need to sort out CLIG Rect and CLR Rect
) {
	ent->AddSubscriber(this); // TODO: see if i can move this to Component
	_screen->AddToRenderQueue(&block);
}

Renderer::~Renderer() {
	entity->RemoveSubscriber(this);
	_screen->RemoveFromRenderQueue(&block);
}

void Renderer::z(int z){
	_screen->RemoveFromRenderQueue(&block);
	// The way we do it now we use the block.z 
	//	to identify what layer to add in in the queue.
	//	We need to fix this up later.
	block.z(z);
	_z = z;
	_screen->AddToRenderQueue(&block);
}

void Renderer:: CreateNewBlock(Rect rect){
	block = clr::Block(rect.position.x, rect.position.y, rect.size.x, rect.size.y);
}

// Warn: if we - for whatever reason - need to change this at runtime,
//		 there may be some issues.
void Renderer::SetSquareCells(bool isSquare){
	_squareCells = true;
	block.Resize(block.width() * 2, block.height());
	block.x *= 2;
}

void Renderer::OnNotify(Event e) {
	switch(e){
		case Event::Moved:
			block.x = entity->rect().position.x;
			block.y = entity->rect().position.y;
			if(_squareCells) {
				block.x *= 2;
			}
			break;
	}

}
}

/* TODO Notes for when i get back on:

We are having an issue with coordinate-point consistency when it comes to `isSquare`
Things I learned:
- The player logic is still in the "squished" world.
    - Player & Level xCoord are actually half way to the left of actual visual representation
- We'll have to do special movement logic for `isSquare` so that we don't have "half-steps" 
- Some items like Text will NOT follow these rules.
    - We can possibly make a "UI" layer that doesn't follow the "world" rules
- We still want some DS that can fill individual poixels INSIDE the Block, but the Coordinate works
  `isSquare`; Doubled.

So Simple terms:
- "World" item x coordinates should be doubled.
    - This should be UNIVERSAL so that everything is consistent
    - How will we do this? In Screen? In Renderer?
- "World" x size MAYBE needs doubling?
    - Depending implementation this may not be necessary..
    -> Let's NOT do it and see if there's issues.
*/