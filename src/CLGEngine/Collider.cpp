#include "Collider.h"

#include <vector>

namespace CLGEngine{

struct ColliderUpdateMeta {
    Collider* col;
    CORE::Vector2<float> movementVec;
};

std::vector<Collider*> activeColliders;
std::vector<Collider*> updateQueue;
int counter = 0;

Collider* GetCollision(Collider* movedCol){
    Collider* hit = nullptr;
    for(Collider* col : activeColliders){
        if(movedCol->bounds.left > col->bounds.right
          || movedCol->bounds.right < col->bounds.left
          || movedCol->bounds.bottom < col->bounds.top
          || movedCol->bounds.top > col->bounds.bottom
          || col == movedCol)
        {
            continue;
        }
        hit = col;
        break;
    }
    return hit;
}

/// @brief 
/// @param id 
/// @return -1 if not found.
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


Collider::Collider(float x, float y, float width, float height):
    position({x, y}),
    size({width, height}),
    bounds({x, y, x+width, y+height}),
    id(counter++)
{
    activeColliders.push_back(this);
}

Collider::~Collider(){
    int idx = FindColliderIdx(this);
    activeColliders.erase(activeColliders.begin() + idx);
}

void Collider::UpdateColliderPosition(float newX, float newY){
    position = {newX, newY};
    bounds = {position.x, position.y, position.x+size.x, position.y+size.y};
    updateQueue.push_back(this);
}

void Collider::UpdateColliderSize(float newWidth, float newHeight){
    size = {newWidth, newHeight};
    bounds = {position.x, position.y, position.x+size.x, position.y+size.y};
    updateQueue.push_back(this);
}

void Collider::UpdateCollider(float newX, float newY, float newWidth, float newHeight){
    CORE::Vector2<float> deltaVec = {newX - position.x, newY - position.y};
    position = {newX, newY};
    size = {newWidth, newHeight};
    bounds = {position.x, position.y, position.x+size.x, position.y+size.y};
    updateQueue.push_back(this); // Should we put some meta data? Like what direction we moved?
}

/// @brief 
/// @return collided entity. Returns Nullptr if no collision.
/// Note, order of checks are not fixed. When colliding with multiple, no guarentee one collider will be returned over the other
void Collider::CheckCollisions(){
    Collider* hit = nullptr;
    for(Collider* movedCol : updateQueue){
        Collider* hit = GetCollision(movedCol);
    }
    updateQueue.erase(updateQueue.begin(), updateQueue.end());
}


}