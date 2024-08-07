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
{
    AddRenderer(charMat);
    AddCollider();
}

Character::~Character(){ }

#pragma region TileMap-Interaction
void Character::AddTileMap(TileMap* map){
    _tileMap = map;
    col->SetTileMap(map);
}

bool Character::CheckTileMapCollision(){
    // Get vertices
    CORE::Vector2<float> vertices[4] = {
         rect().position                  ,                                        //TopLeft
        {rect().position.x + rect().size.x, rect().position.y},                    //TopRight
        {rect().position.x + rect().size.x, rect().position.y + rect().size.y},    //BottomRight
        {rect().position.x                , rect().position.y + rect().size.y}     //BottomLeft
    };
    //Check if it's in a tile zone
    for(CORE::Vector2<float> vertex : vertices){
        if(_tileMap->GetTile(vertex) == '#'){
            return true;
        }
    }
    return false;  
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
    Collider* hitGround = NULL;
    _grounded = col->CastCollider(groundChecker, &hitGround);
    
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
    Translate({momentum * _speed * CLGEngine::Time::deltaTime, 0});
}

void Character::Jump(){
    if(vertMomentum == 0){
        vertMomentum = 1;
    }

    Translate({0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime});

    // -- Check Ceiling
    Rect ceilingChecker = {
        _rect.position.x,
        _rect.position.y - 0.01f,
        _rect.size.x,
        _rect.size.y
    };
    Collider* hit = NULL; // only need to fill the func.
    bool ceilingHit = col->CastCollider(ceilingChecker, &hit);
    if(ceilingHit){
        int num = 10;
    }

    if((ceilingHit || rect().position.y <= _groundLevel - jumpHeight) && vertMomentum == 1){
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