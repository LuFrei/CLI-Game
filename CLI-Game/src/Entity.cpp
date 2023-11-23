#include "Entity.h"

void Entity::Move(int x, int y) {
	posX += x;
	posY += y;
}

Entity::Entity(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
}