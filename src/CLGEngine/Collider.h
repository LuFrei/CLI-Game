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
public:
    Bounds bounds;
    Collider(float x, float y, float width, float height);
    ~Collider();
    static void CheckCollisions();
    void UpdateColliderPosition(float newX, float newY);
    void UpdateColliderSize(float newWidth, float newHeight);
    void UpdateCollider(float newX, float newY, float newWidth, float newHeight); // Dejavu... Maybe we should reduce this somehow.
};
}