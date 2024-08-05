#pragma once

#include "CORE/Utility.h"
#include "CORE/Component.h"
#include "CORE/ISubject.h"
#include "CORE/IObserver.h"
#include "../Game/TileMap.h"

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
    public ISubject,
    public IObserver
    {
private:
    int id;
    CORE::Vector2<float> centerPoint;
    TileMap* tileMap = nullptr;
    void UpdateBounds();
public:
    bool isSolid;
    Bounds bounds;

    Collider(Rect* entRect);
    Collider(Rect* entRect, Rect offset);
    ~Collider();

    //ISubject
    void Subscribe(int Event, IObserver* o);
    void Unsubscribe(int Event, IObserver* o);
    void Notify(int Event);

    //IObserver
    void OnNotify();
    
    // Offsets
    void SetColliderPosition(CORE::Vector2<float> newPosition);
    void SetColliderSize(float newWidth, float newHeight);
    void UpdateCollider(float newX, float newY, float newWidth, float newHeight); // Dejavu... Maybe we should reduce this somehow.

    // Main Logic
    bool CheckCollision(Collider** hit);
    void ProjectPath(CORE::Vector2<float> direction, Collider** hit);
    bool CastCollider(Rect rect, Collider** hit);

    // TileMap
    void SetTileMap(TileMap* map) { tileMap = map; };
    bool CheckTileMapCollision();
};
}