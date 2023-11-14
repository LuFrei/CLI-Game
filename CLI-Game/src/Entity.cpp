#include "Entity.h"

void Entity::Move(Cardinal direction) {
	switch (direction) {
	case North:
		posY++;
		break;
	case East:
		posX++;
		break;
	case South:
		posY--;
		break;
	case West:
		posX--;
		break;
	}
}
