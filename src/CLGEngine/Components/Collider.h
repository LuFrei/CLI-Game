#pragma once

#include "Component.h"
#include "../CORE/Vector2.h"
#include "../CORE/ISubject.h"
#include "../CORE/IObserver.h"

namespace CLGEngine{

struct Bounds
{
    float left,
        top,
        right,
        bottom;
};

// TODO: Make collision checks engine-level intiation.
//      Look into making a playloop that checks Collisions, similar
//      to how we are doing Draw().

/// @brief Adds a collision box to entity.
// ->!! Right now: Entity must initiate collisison check.
class Collider : 
    public Component,
    public IObserver
{
private:
    int _id;
    void UpdateBounds();
    void BroadcastHit(bool wasHit, Collider* hit);
    bool _isActive;
    
    /// @brief The last and current collider this collider collided with.
    std::vector<Collider*> _hitColliders;
public:
    /// @brief Determines if the object is solid. 
    /// Non-solid objects still emit hit events, but don't effect physical interactions.
    bool isSolid;
    Bounds bounds;

    Collider(CLGEngine::Entity* ent);
    ~Collider();

    //IObserver
    void OnNotify(Event e);
    
    void SetActive(bool isActive);

    // Main Logic
    Collider* CheckCollisionPoint(Vector2<float> point);
    void CheckCollision();
    bool CastCollider(Rect rect, Collider** hit);
};
}