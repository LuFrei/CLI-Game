#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <wincon.h>

#include "Render.h"
#include "../Graphics/ASCII.h"

namespace CLGEngine {
	CHAR_INFO defaultMaterial = {
		ASCII_SHADE1,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED
	};


	Renderer::Renderer(CLGEngine::Entity* ent, CHAR_INFO& material)
		: Component(ent) 
		, _screen(Game::GetGameInstance()->mainWindow.screen) {
		block.rect = &ent->rect;
		block.material = material;

		_screen->renderQueue.push_back(&block);
	}
	
	Renderer::~Renderer() {
		_screen->RemoveFromRenderQueue(&block);
	}

}