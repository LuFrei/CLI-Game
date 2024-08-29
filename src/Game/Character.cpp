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

Character::Character(CORE::Vector2<float> startPosition)
            : Entity(startPosition.x, startPosition.y, 1, 1)
            , _speed(10)
            , _position({startPosition.x + 0.5f, startPosition.y + 0.5f})
{
    _col = new Collider(this);
    _rend = new Graphics::Renderer(this, charMat);
    AddSubscriber(_col);
}

Character::~Character(){
    RemoveSubscriber(_col);
    delete _col;
    delete _rend;
}

#pragma region TileMap-Interaction
void Character::AddTileMap(TileMap* map){
    _tileMap = map;
}

#pragma endregion

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

    CORE::Vector2<float> belowCell = {std::floor(_position.x), std::floor(_position.y + 0.5f)};
    _grounded = _tileMap->GetTile(belowCell) == '#';
    
    if(_grounded){ 
        _groundLevel = belowCell.y;
        _position.y = _groundLevel - 0.5;
        jumping = 0;
        vertMomentum = 0;
    } else {
        if(vertMomentum != 1){
            _position += {0, jumpSpeed * CLGEngine::Time::deltaTime};
        }
    }
    AdjustRectAsNeeded();


    int direction = 0; //1 = right; -1 = left
    if (Input::Input::GetKeyPressed(Input::KeyCode::Left)) {
        direction += -1;
    }
    if (Input::Input::GetKeyPressed(Input::KeyCode::Right)) {
        direction += 1;
    }
    if (Input::Input::GetKeyPressed(Input::KeyCode::Space) && _grounded){
        jumping = 1;
    }
    if(jumping){
        Jump();
    }
    if(direction != 0 || momentum != 0){
        AdjustMomentum(direction);
        Move(momentum);
    }
    _col->ClearHit();
}

void Character::Move(float momentum) {

    int nextX = momentum > 0 
          ? std::floor(_position.x) + 1
          : std::floor(_position.x) - 1;

    if(_position.x < 0 
    || _position.x > _tileMap->width 
    || _position.y < 0 
    || _position.y > _tileMap->height) {
        _position += {momentum * _speed * CLGEngine::Time::deltaTime, 0};
        AdjustRectAsNeeded();
        return;
    }
    CORE::Vector2<float> nextCell = {(float)nextX , std::floor(_position.y)};
    if(_tileMap->GetTile(nextCell) != '#'){
        _position += {momentum * _speed * CLGEngine::Time::deltaTime, 0};
        AdjustRectAsNeeded();
    }
}

void Character::Jump(){
    if(vertMomentum == 0){
        vertMomentum = 1;
    }

    CORE::Vector2<float> offSet = {0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime};
    CORE::Vector2<float> nextPos = _position + offSet;

    CORE::Vector2<float> nextCell = {std::floor(nextPos.x), std::floor(nextPos.y)};
    if((_tileMap->GetTile(nextCell) == '#' || _position.y <= _groundLevel - jumpHeight) 
        && vertMomentum == 1)
    {
        vertMomentum = -1;
        jumping = 0;
        return;
    }
    _position = nextPos;
    SetPosition({std::floor(_position.x), std::floor(_position.y)});
}

void Character::AdjustRectAsNeeded() {
    CORE::Vector2<float> posFloored = {std::floor(_position.x), std::floor(_position.y)};
    if(posFloored == rect.position){
        return;    
    }
    SetPosition(posFloored);
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