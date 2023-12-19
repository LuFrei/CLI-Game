#include "Character.h"

Character::Character() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
	rend = new Graphics::Renderer(0, 0, 1, 1, 'P');
}

void Character::Move(int x, int y) {
	Entity::Move(x, y);
	rend->updateBlockPosition(this->x, this->y);
}