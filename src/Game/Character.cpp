
#include "Character.h"

#include <cmath>
#include "../CLGEngine/Graphics/ASCII.h"
#include "../CLGEngine/Time.h"

Character::Character(float speed) {
	this->speed = speed;

	CHAR_INFO defaultMaterial = {
		ASCII_SHADE1,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE
	};

	rend = new Graphics::Renderer(0, 0, 4, 4, defaultMaterial);
}

// We may want to do an event for Entity's move that ties with the Renderer
void Character::Move(float x, float y) {
	Entity::Move((x * speed) * CLGEngine::Time::deltaTime, (y * speed) * CLGEngine::Time::deltaTime);
	rend->updateBlockPosition(
		(int)floor(this->position.x), 
		(int)floor(this->position.y)
	);
}