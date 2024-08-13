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
            ,_position({startPosition.x + 0.5f, startPosition.y + 0.5f})
{
    AddRenderer(charMat);
    AddCollider();
}

Character::~Character(){}

#pragma region TileMap-Interaction
void Character::AddTileMap(TileMap* map){
    _tileMap = map;
    col->SetTileMap(map);
}

// bool Character::CheckTileMapCollision(){
//     // Get center-point
//     CORE::Vector2<float> center = {rect().position.x + 0.5, rect().position.y + 0.5};
//     //Check if it's in a tile zone
//     for(CORE::Vector2<float> vertex : vertices){
//         if(_tileMap->GetTile(vertex) == '#'){
//             return true;
//         }
//     }
//     return false;  
// }
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
    // -- Check Ground
    //TODO: This is expensive we build the checker EVERY FRAME.
    //      Seriously need a way to have entity/component heirarchy 
    //      and build up a coordinate position like that..
    Rect groundChecker = {
        _rect.position.x,
        _rect.position.y + 0.01f,
        _rect.size.x,
        _rect.size.y
    };
    CORE::Vector2<float> belowCell = {std::floor(_position.x), std::floor(_position.y) + 1};
    Collider* hitGround = NULL;
    _grounded = col->CastCollider(groundChecker, &hitGround)
                || _tileMap->GetTile(belowCell) == '#';
    
    if(_grounded){ 
        if(hitGround == NULL){
            _groundLevel = std::floor(groundChecker.position.y);
        } else {
            _groundLevel = hitGround->bounds.top - _rect.size.y;
        }
        SetPosition({rect().position.x, _groundLevel});
        jumping = 0;
        vertMomentum = 0;
    } else {
        if(vertMomentum != 1){
            _position += {0, jumpSpeed * CLGEngine::Time::deltaTime};
            SetPosition({std::floor(_position.x), std::floor(_position.y)});
        }
    }

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
    if(direction != 0){
        AdjustMomentum(direction);
        Move(momentum);
    } else if (momentum != 0){
        AdjustMomentum(direction);
        Move(momentum);
    }
}

void Character::Move(float momentum) {

    int x = momentum > 0 
        ? std::floor(_position.x) + 1
        : std::floor(_position.x) - 1;
    
    CORE::Vector2<float> nextCell = {(float)x , std::floor(_position.y)};

    if(_tileMap->GetTile(nextCell) != '#'){
        _position += {momentum * _speed * CLGEngine::Time::deltaTime, 0};
        CORE::Vector2<float> currCell = {std::floor(_position.x), std::floor(_position.y)};
        if(currCell.x == nextCell.x){
            SetPosition(currCell);
        }
    }
}

void Character::Jump(){
    if(vertMomentum == 0){
        vertMomentum = 1;
    }
    CORE::Vector2<float> lastPos = _position;
    _position += {0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime};

    Translate({0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime});

    CORE::Vector2<float> currCell = {std::floor(_position.x), std::floor(_position.y)};
    bool ceilingHit = false;
    if(_tileMap->GetTile(currCell) == '#'){
        ceilingHit = true;
        _position = lastPos;
    }

    if((ceilingHit || rect().position.y <= _groundLevel - jumpHeight) && vertMomentum == 1){
        vertMomentum = -1;
        jumping = 0;
    }
    SetPosition({std::floor(_position.x), std::floor(_position.y)});
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