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

void Collider::UpdateBounds(){
    bounds = {position.x, position.y, position.x+size.x, position.y+size.y};
}

Collider::Collider(float x, float y, float width, float height):
    position({x, y}),
    size({width, height}),
    bounds({x, y, x+width, y+height}),
    solid(true)
{
    activeColliders.push_back(this);
}

Collider::~Collider(){
    int idx = FindColliderIdx(this); //TODO : Handle if idx = -1
    activeColliders.erase(activeColliders.begin() + idx);
}

void Collider::SetColliderPosition(float newX, float newY){
    position = {newX, newY};
    UpdateBounds();
}

void Collider::SetColliderSize(float newWidth, float newHeight){
    size = {newWidth, newHeight};
    UpdateBounds();
}

void Collider::UpdateCollider(float newX, float newY, float newWidth, float newHeight){
    CORE::Vector2<float> deltaVec = {newX - position.x, newY - position.y};
    position = {newX, newY};
    size = {newWidth, newHeight};
    UpdateBounds();
}

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