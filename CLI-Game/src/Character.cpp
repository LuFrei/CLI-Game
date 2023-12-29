
#include "Character.h"

Character::Character() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;

	CHAR_INFO defaultMaterial;
	defaultMaterial.Char.AsciiChar = 178;
	defaultMaterial.Attributes = BACKGROUND_BLUE | FOREGROUND_GREEN;

	rend = new Graphics::Renderer(0, 0, 8, 4, defaultMaterial);
}

void Character::Move(int x, int y) {
	Entity::Move(x, y);
	rend->updateBlockPosition(this->x, this->y);
}