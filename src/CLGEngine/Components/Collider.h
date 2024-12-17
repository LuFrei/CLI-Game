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
    bool CastCollider(Rect rect, Collider** hit);
    Collider* GetHit(){return _hit;};
    // Temp func for current refactor. call inthe end of caller's Update()
    void ClearHit();
};
}