 #include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Entities/Door.h"
#include "Game/Entities/Button.h"
#include "Game/Maps.h"
#include "Game/Entities/LevelTrigger.h"
#include "Game/GameManager.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    /*Level Setup
    * Have levels in a folder.
    * Load levels from directory into Level queue
    
    LevelManager.AddLevelToQueue(<path/to/levels>);

    * LevelManager should have direct access to entity manager to create and destroy
    
    * TileMap will be 1 value in each level.
    */

    GameManager* gm = new GameManager();

    Character* player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // MAke this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({20, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;
}


// Need to know "what" to instantiate and the positions.