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
    Collider* _hit;
    void UpdateBounds();
    bool _isActive;
public:

    // TODO: Second part is a lie, we don't have an auto-phsycial interaciton system.
    //          But we should, Make it.
    
    /// @brief Determines if the object is solid. 
    /// Non-solid objects still emit hit events, but don't effect physical interactions.
    bool isSolid;
    Bounds bounds;

    Collider(CLGEngine::Entity* ent);
    ~Collider();

    //IObserver
    void OnNotify();
    
    void SetActive(bool isActive);

    // Main Logic
    Collider* CheckCollisionPoint(Vector2<float> point);
    bool CheckCollision();
    bool CastCollider(Rect rect, Collider** hit);
    Collider* hit(){return _hit;};
    // Temp func for current refactor. call inthe end of caller's Update()
    void ClearHit();
};
}