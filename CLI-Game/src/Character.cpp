
#include "Character.h"
#include "Graphics/ASCII.h"

Character::Character() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;

	CHAR_INFO defaultMaterial = {
		ASCII_SHADE1,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE
	};


	rend = new Graphics::Renderer(0, 0, 8, 4, defaultMaterial);
}

void Character::Move(int x, int y) {
	Entity::Move(x, y);
	rend->updateBlockPosition(this->x, this->y);
}