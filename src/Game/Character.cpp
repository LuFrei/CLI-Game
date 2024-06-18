#include "Character.h"

#include <iostream>
#include <cmath>
#include "../CLGEngine/Graphics/ASCII.h"
#include "../CLGEngine/Time.h"
#include "../CLGEngine/Input.h"

CHAR_INFO charMat = {
    ' ', BACKGROUND_BLUE
};

Character::Character(int speed):
	Entity(0, 0, 1, 1),
	speed(speed) {
		AddRenderer(charMat);
		AddCollider();
}

void Character::Update(){
	    if (Input::Input::GetKeyPressed(Input::KeyCode::Up)) {
            Move(0, -1);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Down)) {
            Move(0, 1);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
            Move(-1, 0);
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
            Move(1, 0);
        }
}

Character::~Character(){
}

void Character::Move(int x, int y) {
	Translate(
		(x * speed) * CLGEngine::Time::deltaTime, 
		(y * speed) * CLGEngine::Time::deltaTime
	);
}
