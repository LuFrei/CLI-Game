#pragma once

#include "CORE/Utility.h"
#include "CORE/Component.h"

namespace CLGEngine{

struct Bounds{
    float left,
        top,
        right,
        bottom;
};

class Collider : public Component{
private:
    int id;
    void UpdateBounds();
    CORE::Vector2<float> centerPoint;
public:
    bool isSolid;
    Bounds bounds;
    Collider(Rect* entRect);
    Collider(Rect* entRect, Rect offset);
    ~Collider();
    /// @brief 
    /// @return collided entity. Returns Nullptr if no collision.
    /// Note, order of checks are not fixed. When colliding with multiple, no guarentee one collider will be returned over the other
    void SetColliderPosition(CORE::Vector2<float> newPosition);
    void SetColliderSize(float newWidth, float newHeight);
    void UpdateCollider(float newX, float newY, float newWidth, float newHeight); // Dejavu... Maybe we should reduce this somehow.
    bool CheckCollision(Collider** hit);
    void ProjectPath(CORE::Vector2<float> direction, Collider** hit);
    bool CastCollider(Rect rect, Collider** hit);
};
}