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


float timer = 0;

void Character::Update(){
        CORE::Vector2<int> direction = {0, 0};
        bool moved = 0;
	    if (Input::Input::GetKeyPressed(Input::KeyCode::Up)) {
            moved = 1;
            direction += {0, -1};
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Down)) {
            moved = 1;
            direction += {0, 1};
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
            moved = 1;
            direction += {-1, 0};
        }
        if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
            moved = 1;
            direction += {1, 0};
        }
        if(moved){
            Move(direction);
        } else {
            timer = 1; // Why 1 not 0? Feels better for the Char to move the frame the player intends to move the character.
        }
        
}

Character::~Character(){ }

void Character::Move(CORE::Vector2<int> dir) {
    timer += speed * CLGEngine::Time::deltaTime;
    if(timer > 1){
        Translate(dir.x, dir.y);
        timer = 0;
    }
}
