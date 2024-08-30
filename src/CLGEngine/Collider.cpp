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

Collider::Collider(CLGEngine::Entity* ent):
    Component(ent),
    _hit(nullptr),
    bounds({
        GetBoundsFromRect(ent->rect)
    }),
    isSolid(true)
{
    activeColliders.push_back(this);
}

Collider::~Collider(){
    int idx = FindColliderIdx(this); //TODO : Handle if idx = -1
    activeColliders.erase(activeColliders.begin() + idx);
}

void Collider::UpdateBounds() {
    bounds = {
        _ent->rect.position.x,
        _ent->rect.position.y,
        _ent->rect.position.x + _ent->rect.size.x,
        _ent->rect.position.y + _ent->rect.size.y
    };
}

bool Collider::CheckCollision(){
    for(Collider* col : activeColliders){
        if(bounds.left >= col->bounds.right
          || bounds.right <= col->bounds.left 
          || bounds.bottom <= col->bounds.top
          || bounds.top >= col->bounds.bottom
          || col == this)
        {
            continue;
        }
        _hit = col;
        return true;
    }
    return false;
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
        _hit = col;
        return true;
    }
    return false;
}

void Collider::ClearHit(){
    _hit = nullptr;
}

#pragma region IObserver
void Collider::OnNotify(){
    UpdateBounds();
    CheckCollision();
}
#pragma endregion
}
