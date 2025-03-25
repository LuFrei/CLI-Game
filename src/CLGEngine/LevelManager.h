#include <vector>

#include "Level.h"

/* LevelManager is a projet-wide utility for changing, adding and removing levels
Purpose:
- Provide an easy, global system with minimal setup levels and interact with level data at runtime.
  - NO instantiation; all static.
  - Tools setting up level heirarchy.
  - Tools for changing levels at runtime.

- Add levels to game-wide level-pool
- Remove levels from game-wide level-pool (admitedly can't think of a use case for this, other than maybe mod support?)
- Set level to dynamically change level data during play.
  - Currently we only do ONE level, but it would nifty to 
    add a multi-level system for seemless loading & 
*/

class LevelManager {
private:
    std::vector<Level*> _levels;
public:
    static void SetLevel(Level* lvl);
    static void AddLevel(Level* lvl);
    static void AddLevels(std::vector<Level*> lvls);
    static void RemoveLevel(Level* lvl);
};