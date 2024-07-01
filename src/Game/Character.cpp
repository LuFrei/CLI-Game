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
	Entity(0, 20, 1, 1),
	speed(speed) {
		AddRenderer(charMat);
		AddCollider();
}


float momentum = 0;
float const acceleration = 1;
void AdjustMomentum(int direction){
    if(direction == 0){
        momentum = (momentum > 0) 
            ? momentum - (acceleration * CLGEngine::Time::deltaTime)
            : momentum + (acceleration * CLGEngine::Time::deltaTime);

        // Prevent oscilation
        if(-0.01 < momentum || momentum < 0.01){
            momentum = 0;
        }
    } else {
        // Let's start going towards the maximum/minimum (-1)<->(1) based on direction.
        momentum += direction * CLGEngine::Time::deltaTime * acceleration;
        if(momentum > 1){
            momentum = 1;
        }
        if(momentum < -1){
            momentum = -1;
        }
    }
}


void Character::Update(){
    int direction = 0; //1 = right; -1 = left
    if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
        direction += -1;
    }
    if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
        direction += 1;
    }
    if(direction != 0){
        AdjustMomentum(direction);
        Move(momentum);
    } else if (momentum != 0){
        AdjustMomentum(direction);
        Move(momentum);
    }
}

Character::~Character(){ }

void Character::Move(float momentum) {
    Translate(momentum * speed * CLGEngine::Time::deltaTime, 0);
}
