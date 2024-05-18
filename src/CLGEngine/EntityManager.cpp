#include <algorithm>
#include "EntityManager.h"

namespace CLGEngine {

    std::vector<Entity*> entities;

    void EntityManager::AddEntity(Entity* ent){
        entities.push_back(ent);
    }

    void EntityManager::RemoveEntity(Entity* ent){
        entities.erase(
            std::find(
                entities.begin(),
                entities.end(),
                ent
        ));
    }

    void EntityManager::UpdateEntities(){
        for(Entity* ent : entities){
            ent->Update();
        }
    }
}