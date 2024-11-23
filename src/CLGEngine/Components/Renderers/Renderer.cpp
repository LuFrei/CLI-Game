#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <wincon.h>

#include "Renderer.h"
#include "../../Graphics/ASCII.h"

namespace CLGEngine {

Renderer::Renderer(CLGEngine::Entity* ent)
: Component(ent) 
, _screen(Game::GetGameInstance()->mainWindow.screen) 
, block(Block(ent->rect)){
	_screen->AddToRenderQueue(&block);
}

Renderer::~Renderer() {
	_screen->RemoveFromRenderQueue(&block);
}

void Renderer::OnNotify() {
	block.rect = entity->rect;
}
}