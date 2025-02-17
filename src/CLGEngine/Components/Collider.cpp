#include "Collider.h"

#include <cmath>
#include <vector>
#include <map>

namespace CLGEngine{

std::map<int, Collider*> activeColliders; // TODO: Replace with Quad Tree.
int counter = 0;

// Should be the best 
void Collider::BroadcastHit(bool wasHit, Collider* hit){
    auto colIt = std::find(_hitColliders.begin(), _hitColliders.end(), hit);
    bool inList = colIt != _hitColliders.end();
    if(!inList && wasHit){
        hit->entity->OnCollisionStart(this->entity);
        this->entity->OnCollisionStart(hit->entity);
        _hitColliders.push_back(hit);
    }
    // constant braodcast
    if(inList && wasHit){
        hit->entity->OnCollision(this->entity);
        this->entity->OnCollision(hit->entity);
    }
    // End broadcast 
    if(inList && !wasHit){
        hit->entity->OnCollisionEnd(this->entity);
        this->entity->OnCollisionEnd(hit->entity);
        _hitColliders.erase(colIt);
    }
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
    _id(counter),
    bounds({
        GetBoundsFromRect(ent->rect())
    }),
    isSolid(true),
    _isActive(true)
{
    ent->AddSubscriber(this); // TODO: see if i can move this to Component
    activeColliders.insert({_id, this});
    counter++;
}

Collider::~Collider(){
    entity->RemoveSubscriber(this);
    activeColliders.erase(_id);
}

void Collider::UpdateBounds() {
    bounds = {
        entity->rect().position.x,
        entity->rect().position.y,
        entity->rect().position.x + entity->rect().size.x,
        entity->rect().position.y + entity->rect().size.y
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

void Collider::CheckCollision(){
    for(std::pair<int, Collider*> pair : activeColliders){
        bool collision = true;
        Collider* col = pair.second;
        if(bounds.left >= col->bounds.right
          || bounds.right <= col->bounds.left 
          || bounds.bottom <= col->bounds.top
          || bounds.top >= col->bounds.bottom
          || col == this)
        {
            collision = false;
        }

        BroadcastHit(collision, col);
    }
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

        BroadcastHit(true, col);
        return col;
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

        BroadcastHit(true, col);
        return true;
    }
    return false;
}

#pragma region IObserver
void Collider::OnNotify(Event e){
    UpdateBounds();
    CheckCollision();
}
#pragma endregion
}
