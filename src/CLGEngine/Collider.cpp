#include "Collider.h"

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


// TODO: make data flow work to check collision and reposition the entity to not overlap
//      Idea right now is to use a center point and compare x, y to know where to snap the entity.
void Collider::ProjectPath(CORE::Vector2<float> direction, Collider** hit){
    if(CheckCollision(hit)){
        CORE::Vector2<float> newPos = entityRect->position;
        if(direction.x > 0){
            newPos.x = (*hit)->bounds.left - entityRect->size.x;
        }
        if (direction.x < 0) {
            newPos.x = (*hit)->bounds.right;
        }
        if(direction.y > 0){
            newPos.y = (*hit)->bounds.top - entityRect->size.y;
        }
        if(direction.y < 0){
            newPos.y = (*hit)->bounds.bottom;
        }
        entityRect->position = newPos;
    }
}
}