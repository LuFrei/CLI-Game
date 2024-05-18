#pragma once
#include <vector>
#include "Entity.h"

namespace CLGEngine {
class EntityManager{
public:
    static void AddEntity(Entity* ent);
    static void RemoveEntity(Entity* ent);
    static void UpdateEntities();
};
}