#include "Collider.h"

#include <cmath>
#include <vector>

namespace CLGEngine{

std::vector<Collider*> activeColliders; // TODO: Replace with Quad Tree.
int counter = 0;

int FindColliderIdx(Collider* col){
    int min = 0;
    int max = activeColliders.size();
    int diff = max-min;

    while(diff > 2) {
        int idx = min+(diff/2);
        if(activeColliders[idx] == col){
            return idx;
        }
    }

    // Doing a simple loop cuz i cant be bothered right now.
    while(min <= max){
        if(activeColliders[min] == col){
            return min;
        }
        min++;
    }

    return -1;
}

// TODO: Maybe a good funciton to put INSIDE of Rect?
Bounds GetBoundsFromRect(Rect rect){
    return {
        rect.position.x, 
        rect.position.y, 
        rect.position.x + rect.size.x,
        rect.position.y + rect.size.y
    };
}

Collider::Collider(Rect* entityRect):
    Component(entityRect),
    bounds({
        entityRect->position.x, 
        entityRect->position.y, 
        entityRect->position.x + entityRect->size.x,
        entityRect->position.y + entityRect->size.y
    }),
    centerPoint({
        entityRect->position.x + (entityRect->size.x/2),
        entityRect->position.y + (entityRect->size.y/2)
    }),
    isSolid(true)
{
    activeColliders.push_back(this);
}

Collider::Collider(Rect* entityRect, Rect offset):
    Component(entityRect, offset),
    bounds({
        entityRect->position.x, 
        entityRect->position.y, 
        entityRect->position.x + entityRect->size.x,
        entityRect->position.y + entityRect->size.y
    }),
    isSolid(true)
{
    activeColliders.push_back(this);
}

Collider::~Collider(){
    int idx = FindColliderIdx(this); //TODO : Handle if idx = -1
    activeColliders.erase(activeColliders.begin() + idx);


}

void Collider::UpdateBounds(){
    bounds = {
        entityRect->position.x, 
        entityRect->position.y, 
        entityRect->position.x + entityRect->size.x,
        entityRect->position.y + entityRect->size.y
    };
}

// TODO: Remove this.
//      Right now it's used to update Bound when Entity calls SetPosition().
//      UpdateBounds() should be called automatically when a move event comes from Entity.
void Collider::SetColliderPosition(CORE::Vector2<float> newPosition){
    UpdateBounds();
}

bool Collider::CheckCollision(Collider** hit){
    UpdateBounds();
    for(Collider* col : activeColliders){
        if(bounds.left >= col->bounds.right
          || bounds.right <= col->bounds.left 
          || bounds.bottom <= col->bounds.top
          || bounds.top >= col->bounds.bottom
          || col == this)
        {
            continue;
        }
        *hit = col;
        return true;
    }
    return false;
}

// bool Collider::CheckTileMapCollision(Rect rect){
//     // Well have to check for whole numbers
//     //  we are getting some bleed into neighboring cells when checking collisison.
//     int wholePosX = std::floor(rect.position.x);
//     int wholePosY = std::floor(rect.position.y);
//     CORE::Vector2<float> midPoint;
//     // "Locked" into the same cell as position.[x|y]
//     bool lockedX = false;
//     bool lockedY = false;
//     if(wholePosX == rect.position.x)
//         { lockedX = true; }
//     if(wholePosY == rect.position.y)
//         { lockedY = true; }

//     // Get vertices
//     CORE::Vector2<float> TL = rect.position;
//     CORE::Vector2<float> TR = {rect.position.x + rect.size.x, rect.position.y};
//     CORE::Vector2<float> BR = {rect.position.x + rect.size.x, rect.position.y + rect.size.y};
//     CORE::Vector2<float> BL = {rect.position.x              , rect.position.y + rect.size.y};

//     //Check if it's in a tile zone
//     if(tileMap->GetTile(TL) == '#'){
//         return true;
//     } 
//     if(!lockedX && tileMap->GetTile(TR) == '#'){
//         return true;
//     } 
//     if(!lockedY && tileMap->GetTile(BL) == '#'){
//         return true;
//     } 
//     if(!lockedX && !lockedY &&tileMap->GetTile(BR) == '#'){
//         return true;
//     } 
//     return false;  
// }

// TODO: make data flow work to check collision and reposition the entity to not overlap
//      Idea right now is to use a center point and compare x, y to know where to snap the entity.
void Collider::ProjectPath(CORE::Vector2<float> direction, Collider** hit){
    CORE::Vector2 newPos = entityRect->position;
    //Check against other Entities
    if(CheckCollision(hit)){
        if(direction.x > 0){
            entityRect->position.x = (*hit)->bounds.left - entityRect->size.x;
        } else if (direction.x < 0) {
            entityRect->position.x = (*hit)->bounds.right;
        }
        if(direction.y > 0){
            entityRect->position.y = (*hit)->bounds.top - entityRect->size.y;
        } else if(direction.y < 0){
            entityRect->position.y = (*hit)->bounds.bottom;
        }
    }

    //Check Against Map
    // if(CheckTileMapCollision(*entityRect)){
    //     if(direction.x > 0){
    //         entityRect->position.x = std::floor(entityRect->position.x);
    //     } else if (direction.x < 0) {
    //         entityRect->position.x = std::floor(entityRect->position.x) + 1;
    //     }
    //     if(direction.y > 0){
    //         entityRect->position.y = std::floor(entityRect->position.y);
    //     } else if(direction.y < 0){
    //         entityRect->position.y = std::floor(entityRect->position.y) + 1;
    //     }
    // }
}

// What if Collider is like RigidBody. And evberything has a collider. but you only check for interaction with a collider on.

bool Collider::CastCollider(Rect rect, Collider** hit){
    // TODO(?): Make bounds a part of Rect? We seem to be using them a lot together...
    // Create bounds for Rect
    Bounds rectBounds = GetBoundsFromRect(rect);
    for(Collider* col : activeColliders){
        // Check other Entities
        if(rectBounds.left >= col->bounds.right
          || rectBounds.right <= col->bounds.left 
          || rectBounds.bottom <= col->bounds.top
          || rectBounds.top >= col->bounds.bottom
          || col == this)
        {
            continue;
        }
        *hit = col;
        return true;
    }
    // return CheckTileMapCollision(rect);
    return false;
}


#pragma region ISubject
void Collider::Subscribe(int event, IObserver* o){
    _observers[event].emplace_front(o);
}

void Collider::Unsubscribe(int event, IObserver* o){
    _observers[event].remove(o);
}

void Collider::Notify(int Event){
    for(IObserver* o : _observers[Event]){
        o->OnNotify();
    }
}
#pragma endregion

#pragma region IObserver
void Collider::OnNotify(){
    
}
#pragma endregion
}
