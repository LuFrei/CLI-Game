#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"
#include "CLGEngine/TileMap.h"

#include "Game/Entities/Character.h"
#include "Game/Entities/ScreenText.h"
#include "Game/Entities/Wall.h"
#include "Game/Entities/Door.h"
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

    Character* player = new Character({25, 21});
    player->gm = gm;
    player->AddTileMap(gm->GetLevelTileMap()); // MAke this internal. No need if we reference gm in Player.

    ScreenText* instructionalText = new ScreenText({0, 29});
    ScreenText* mapNameText = new ScreenText({20, 0});
    instructionalText->SetText("[SpaceBar]  [<][>]");

    Door* door = new Door(
        {
            {29, 19}, // pos
            {1, 4}  // size
        },
        DoorCode::Blue
    );
    Door* door1 = new Door(
        {
            {31, 19}, // pos
            {1, 4}  // size
        },
        DoorCode::Blue,
        true
    );
    Door* door2 = new Door(
        {
            {33, 19}, // pos
            {1, 4}  // size
        },
        DoorCode::Red,
        false
    );
    Door* door3 = new Door(
        {
            {35, 19}, // pos
            {1, 4}  // size
        },
        DoorCode::Red,
        true
    );


    game.mainWindow.screen->SetTileMap(gm->GetLevelTileMap()); // TODO: TileMap Renderer

    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete door;
    delete door1;
    delete door2;
    delete door3;
    delete player;
    delete instructionalText;
    delete mapNameText;
    delete gm;
}


// Need to know "what" to instantiate and the positions.