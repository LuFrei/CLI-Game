#include "Level.h"


Level::Level(){
    _levels.push_back(this);
}

Level::~Level(){
    _levels.erase(
        std::find(
            _levels.begin(),
            _levels.end(),
            this
    ));
}

void Level::Load(int levelIdx){
    for(CLGEngine::Entity* ent :_levels[levelIdx]->entities){
        //TODO: Exception for entitiesr we want to keep between levels? (like player)
        
    }
}

void Level::Unload(int levelIdx){
    for(CLGEngine::Entity* ent :_levels[levelIdx]->entities){
        //TODO: Exception for entitiesr we want to keep between levels? (like player)
        if(ent != nullptr){
            delete ent;
        }
    }
}

/* NOTES
Need to instantiate proper entities
Need to assign proper positions
Need to set correct properties PER LEVEL
    ?This part is so complex and may not need to be implemented geenricly
    Important Properties:
    - Text
    - Level the portal leads to // ! forward one backward?????!!

*/