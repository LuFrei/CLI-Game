#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Maps.h"
#include "Game/Entities/LevelTrigger.h"
#include "Game/GameManager.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();
//TODO: REMINDER! Lets write everything in main 
// - as simple as posisble. THEN, we move into modularization
    GameManager* gm = new GameManager();

    Character* player = new Character({17, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // MAke this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({20, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");

    
    
    game.mainWindow.screen->SetTileMap(gm->GetLevelTileMap()); // TODO: TileMap Renderer

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;
}


// Need to know "what" to instantiate and the positions.