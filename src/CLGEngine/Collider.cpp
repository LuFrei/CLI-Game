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

Collider::Collider(Rect* entityRect):
    Component(entityRect),
    bounds({
        entityRect->position.x, 
        entityRect->position.y, 
        entityRect->position.x + entityRect->size.x,
        entityRect->position.y + entityRect->size.y
    }),
    solid(true)
{
    activeColliders.push_back(this);
}

Collider::Collider(Rect* entityRect, Rect offset):
    Component(entityRect, offset),
    bounds({
        entityRect->position.x + offset.position.x, 
        entityRect->position.y + offset.position.y, 
        (entityRect->position.x + offset.position.x) + (entityRect->size.x + offset.size.x),
        (entityRect->position.y + offset.position.y) + (entityRect->size.y + offset.size.y)
    }),
    solid(true)
{
    activeColliders.push_back(this);
}

Collider::~Collider(){
    int idx = FindColliderIdx(this); //TODO : Handle if idx = -1
    activeColliders.erase(activeColliders.begin() + idx);


}

void Collider::UpdateBounds(){
    bounds = {
        entityRect->position.x + offset.position.x, 
        entityRect->position.y + offset.position.y, 
        (entityRect->position.x + offset.position.x) + (entityRect->size.x + offset.size.x),
        (entityRect->position.y + offset.position.y) + (entityRect->size.y + offset.size.y)
    };
}

// TODO(start): The following functions are using offset as a local rect, and updating it to match Entity's Rect.
//            We'll have to change this later to directly use Entity's Rect
void Collider::SetColliderPosition(float newX, float newY){
    offset.position = {newX, newY};
    UpdateBounds();
}

void Collider::SetColliderSize(float newWidth, float newHeight){
    offset.size = {newWidth, newHeight};
    UpdateBounds();
}

void Collider::UpdateCollider(float newX, float newY, float newWidth, float newHeight){
    CORE::Vector2<float> deltaVec = {newX - offset.position.x, newY - offset.position.y};
    offset.position = {newX, newY};
    offset.size = {newWidth, newHeight};
    UpdateBounds();
}

// TODO(end)
bool Collider::CheckCollision(){
    Collider* hit = nullptr;
    return CheckCollision(&hit);
}

bool Collider::CheckCollision(Collider** hit){
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
}