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
    int id;
    CORE::Vector2<float> centerPoint;
    void UpdateBounds();
public:
    bool isSolid;
    Bounds bounds;

    Collider(CLGEngine::Entity* ent);
    ~Collider();

    //IObserver
    void OnNotify();
    
    // Main Logic
    bool CheckCollision(Collider** hit);
    void ProjectPath(CORE::Vector2<float> direction, Collider** hit);
    bool CastCollider(Rect rect, Collider** hit);
};
}