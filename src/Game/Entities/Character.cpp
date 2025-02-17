#include "Character.h"

#include <iostream>
#include <cmath>
#include "../../CLGEngine/Graphics/ASCII.h"
#include "../../CLGEngine/Time.h"
#include "../../CLGEngine/Input.h"
#include "../Maps.h"

const int jumpHeight = 4;
const int jumpSpeed = 10;
int vertMomentum = 0;

CHAR_INFO charMat = {
    ' ', BACKGROUND_BLUE
};

Character::Character(CLGEngine::Vector2<float> startPosition)
            : Entity(startPosition.x, startPosition.y, 1, 1)
            , _speed(10)
            , _position({startPosition.x + 0.5f, startPosition.y + 0.5f})
{
    name = "player";
    _col = new CLGEngine::Collider(this);
    _rend = new CLGEngine::BlockRenderer(this, charMat, true);
    _rend->z(1);
}

Character::~Character(){
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
#pragma region Jump/Gravity Logic
    CLGEngine::Vector2<float> belowCell = {_position.x, _position.y + 0.5f};
    CLGEngine::Collider* hit = _col->CheckCollisionPoint(belowCell);
    bool solidGround = 
        (hit == nullptr) ? 
        false : hit->isSolid;  
    _grounded = _tileMap->GetTile((CLGEngine::Vector2<int>)belowCell) == '#' || solidGround;
    
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
    SnapRectToGrid();
#pragma endregion

    int direction = 0;
    if (CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Left) || CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Comma)) {
        direction += -1;
    }
    if (CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Right) || CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Period)) {
        direction += 1;
    }
    if (CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Space) && _grounded){
        jumping = 1;
    }
    if(jumping){
        Jump();
    }
    if(direction != 0 || momentum != 0){
        AdjustMomentum(direction);
        Move(momentum);
    }

    char tileValue = _tileMap->GetTile({(int)std::floor(_position.x), (int)std::floor(_position.y)});

    if(tileValue == '*' || tileValue == 'e'){
        gm->SetLevel(gm->GetCurrentLevelIdx()+1);
    }

    //!! Level Swap test 
    if(CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Alpha1)) {
        _tileMap->SetMap(Maps::list[0]);
    }
    if(CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Alpha2)) {
        _tileMap->SetMap(Maps::list[1]);
    }
    if(CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Alpha3)) {
        _tileMap->SetMap(Maps::list[2]);
    }
    if(CLGEngine::Input::Input::GetKeyPressed(CLGEngine::Input::KeyCode::Alpha4)) {
        _tileMap->SetMap(Maps::list[3]);
    }
}

void Character::Move(float momentum) {

    float nextXPosition = _position.x + momentum; 

    // TODO: Collisison should be universal. maybe on a Physics Engine update.
    CLGEngine::Vector2<float> nextCell = {nextXPosition, _position.y};
    CLGEngine::Collider* hit = _col->CheckCollisionPoint(nextCell);
    if(_tileMap->GetTile((CLGEngine::Vector2<int>)nextCell) != '#' && hit == nullptr){
        _position += {momentum * _speed * CLGEngine::Time::deltaTime, 0};
        SnapRectToGrid();
    }
}

void Character::Jump(){
    if(vertMomentum == 0){
        vertMomentum = 1;
    }

    CLGEngine::Vector2<float> offSet = {0, -vertMomentum * jumpSpeed * CLGEngine::Time::deltaTime};
    CLGEngine::Vector2<float> nextPos = _position + offSet;

    CLGEngine::Vector2<float> nextCell = {nextPos.x, nextPos.y};
    CLGEngine::Collider* hit = _col->CheckCollisionPoint(nextCell);
    if((_tileMap->GetTile((CLGEngine::Vector2<int>)nextCell) == '#'
        || hit != nullptr
        || _position.y <= _groundLevel - jumpHeight
        ) 
        && vertMomentum == 1)
    {
        vertMomentum = -1;
        jumping = 0;
        return;
    }
    _position = nextPos;
    SetPosition({std::floor(_position.x), std::floor(_position.y)});
}

void Character::SnapRectToGrid() {
    CLGEngine::Vector2<float> posFloored = {std::floor(_position.x), std::floor(_position.y)};
    if(posFloored == rect().position){
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