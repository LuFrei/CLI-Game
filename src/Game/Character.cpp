#include "Character.h"

#include <iostream>
#include <cmath>
#include "../CLGEngine/Graphics/ASCII.h"
#include "../CLGEngine/Time.h"
#include "../CLGEngine/Input.h"

Character::Character(float speed):
	Entity(0, 0, 4, 4),
	speed(speed) {
		rend = new Graphics::Renderer(position.x, position.y, size.x, size.y);
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

Character::~Character(){
	delete rend;
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