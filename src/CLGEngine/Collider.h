#pragma once

#include "CORE/Utility.h"

namespace CLGEngine{

struct Bounds{
    float left,
        top, 
        right, 
        bottom;
};

class Collider{
private:
    CORE::Vector2<float> position;
    CORE::Vector2<float> size;

    int id;
    void UpdateBounds();
public:
    bool solid;
    Bounds bounds;
    Collider(float x, float y, float width, float height);
    ~Collider();
    /// @brief 
    /// @return collided entity. Returns Nullptr if no collision.
    /// Note, order of checks are not fixed. When colliding with multiple, no guarentee one collider will be returned over the other
    bool CheckCollision();
    bool CheckCollision(Collider** hit);
    void SetColliderPosition(float newX, float newY);
    void SetColliderSize(float newWidth, float newHeight);
    void UpdateCollider(float newX, float newY, float newWidth, float newHeight); // Dejavu... Maybe we should reduce this somehow.
};
}