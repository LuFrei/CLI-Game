#include <iostream>
#include "Entity.h"


void Entity::Move(int x, int y) {
	this->x += x;
	this->y += y;
}

Entity::Entity() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

Entity::Entity(int x, int y, unsigned int width, unsigned int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}