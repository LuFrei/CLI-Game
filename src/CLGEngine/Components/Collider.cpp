#include "Collider.h"

#include <cmath>
#include <vector>
#include <map>

namespace CLGEngine{

std::map<int, Collider*> activeColliders; // TODO: Replace with Quad Tree.
int counter = 0;

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
    _id(counter),
    _hit(nullptr),
    bounds({
        GetBoundsFromRect(ent->rect)
    }),
    isSolid(true),
    _isActive(true)
{
    activeColliders.insert({_id, this});
    counter++;
}

Collider::~Collider(){
    activeColliders.erase(_id);
}

void Collider::UpdateBounds() {
    bounds = {
        entity->rect.position.x,
        entity->rect.position.y,
        entity->rect.position.x + entity->rect.size.x,
        entity->rect.position.y + entity->rect.size.y
    };
}

void Collider::SetActive(bool isActive){
    if(_isActive == isActive){
        return;
    }
    _isActive = isActive;
    if(!isActive){
        activeColliders.erase(_id);
    } else {
        activeColliders.insert({_id, this});
    }
}

bool Collider::CheckCollision(){
    for(std::pair<int, Collider*> pair : activeColliders){
        Collider* col = pair.second;
        if(bounds.left >= col->bounds.right
          || bounds.right <= col->bounds.left 
          || bounds.bottom <= col->bounds.top
          || bounds.top >= col->bounds.bottom
          || col == this)
        {
            continue;
        }
        _hit = col;
        col->_hit = this;
        return true;
    }
    return false;
}

// TODO: split this into PointCollider when polishing physics.

Collider* Collider::CheckCollisionPoint(Vector2<float> point){
    for(std::pair<int, Collider*> pair : activeColliders){
        Collider* col = pair.second;
        if(point.x >= col->bounds.right
          || point.x <= col->bounds.left 
          || point.y <= col->bounds.top
          || point.y >= col->bounds.bottom
          || col == this)
        {
            continue;
        }
        _hit = col;
        col->_hit = this;
        // TODO: If this works better than bool above,
        //       Copy this in CheckCollision() for consistency.
        return _hit;
    }
    return nullptr;
}

// What if Collider is like RigidBody. And evberything has a collider. but you only check for interaction with a collider on.

bool Collider::CastCollider(Rect rect, Collider** hit){
    // TODO(?): Make bounds a part of Rect? We seem to be using them a lot together...
    // Create bounds for Rect
    Bounds rectBounds = GetBoundsFromRect(rect);
    for(std::pair<int, Collider*> pair : activeColliders){
        Collider* col = pair.second;
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
