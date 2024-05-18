#include "Character.h"

#include <cmath>
#include "../CLGEngine/Graphics/ASCII.h"
#include "../CLGEngine/Time.h"
#include "../CLGEngine/Input.h"

Character::Character(float speed) {
	this->speed = speed;

	CHAR_INFO defaultMaterial = {
		ASCII_SHADE1,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE
	};
	position = {0 , 0};
	size = {4 , 4};
	rend = new Graphics::Renderer(position.x, position.x, size.x, size.y, defaultMaterial);
}

void Character::Update(){
	    if (Input::Input::GetKeyPressed(Input::KeyCode::Up)) {
            Move(0, -10);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Down)) {
            Move(0, 10);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
            Move(-10, 0);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
            Move(10, 0);
        }
}

// We may want to do an event for Entity's move that ties with the Renderer
void Character::Move(float x, float y) {
	Translate(
		(x * speed) * CLGEngine::Time::deltaTime, 
		(y * speed) * CLGEngine::Time::deltaTime
	);
	rend->updateBlockPosition(
		(int)floor(this->position.x), 
		(int)floor(this->position.y)
	);
}