#pragma once

#include "CORE/Component.h"
#include "CORE/Utility.h"
#include "CORE/ISubject.h"
#include "CORE/IObserver.h"

namespace CLGEngine{

struct Bounds
{
    float left,
        top,
        right,
        bottom;
};

class Collider : 
    public Component,
    public IObserver
    {
private:
    int _id;
    Collider* _hit;
    void UpdateBounds();
public:
    bool isSolid;
    Bounds bounds;

    Collider(CLGEngine::Entity* ent);
    ~Collider();

    //IObserver
    void OnNotify();
    
    // Main Logic
    bool CheckCollision();
    // Temp func for current refactor. call inthe end of caller's Update()
    void ClearHit();
    bool CastCollider(Rect rect, Collider** hit);
};
}