#include "Character.h"

#include <iostream>
#include <cmath>
#include "../CLGEngine/Graphics/ASCII.h"
#include "../CLGEngine/Time.h"
#include "../CLGEngine/Input.h"

const int jumpHeight = 4;
const int jumpSpeed = 10;
int vertMomentum = 0;

CHAR_INFO charMat = {
    ' ', BACKGROUND_BLUE
};

Character::Character(CORE::Vector2<float> startPosition):
	Entity(startPosition.x, startPosition.y, 1, 1),
	speed(10) {
		AddRenderer(charMat);
		AddCollider();
}


float momentum = 0;
float const acceleration = 2;
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

bool jumping = 0;
void Character::Update(){
    // //Check Ground
    //TODO: This is expensive we build the checker EVERY FRAME.
    //      Seriously need a way to have entity/component heirarchy 
    //      and build up a coordinate position like that..
    Rect groundChecker = {
        rect_.position.x,
        rect_.position.y + 0.01f,
        rect_.size.x,
        rect_.size.y
    };
    Collider* hitGround = NULL;
    grounded = col->CastCollider(groundChecker, &hitGround);
    
    
    if(grounded){
        SetPosition({rect().position.x, hitGround->bounds.top - rect_.size.y});
        groundLevel = hitGround->bounds.top - rect_.size.y;
        jumping = 0;
        vertMomentum = 0;
    } else {
        if(vertMomentum != 1){
            Translate({0, jumpSpeed * CLGEngine::Time::deltaTime});
        }
    }

    int direction = 0; //1 = right; -1 = left
    if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
        direction += -1;
    }
    if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
        direction += 1;
    }
    if (Input::Input::GetKeyPressed(Input::KeyCode::Space) && grounded){
        jumping = 1;
    }
    if(jumping){
        Jump();
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
    Translate({momentum * speed * CLGEngine::Time::deltaTime, 0});
}

void Character::Jump(){
    if(vertMomentum == 0){
        vertMomentum = 1;
    }

    // rect.position.y += -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime;

    Translate({0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime});

    if(rect().position.y <= groundLevel - jumpHeight && vertMomentum == 1){
        SetPosition({rect().position.x, groundLevel - jumpHeight});
        vertMomentum = -1;
        jumping = 0;
    }
}

#pragma region  !/ / / QUARANTINE ZONE / / /! 
// The following is an early prototype for Gravity.
// TODO: MOVE THIS TO A COMPONENT!
// Will stop working on this as it may bring unpredictability to the crisp experience I'm looking to make.
// Determines if we are going up or down, and by how much.
float verticalVelocity;

// Maximum rate of descent.
float terminalVelocity;

// How hard to pull down
// !! NOT ACTUAL GRAVITY VALUE (yet)
float gravityScale;

void SimulateGravity(){
    if(verticalVelocity == -(terminalVelocity)){
        return;
    }

    verticalVelocity -= gravityScale;
    
    if(verticalVelocity < -(terminalVelocity)){
        verticalVelocity = terminalVelocity;
    }
}
#pragma endregion