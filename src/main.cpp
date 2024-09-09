#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/ScreenText.h"
#include "Game/TileMap.h"
#include "Game/Wall.h"
#include "Game/Maps.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    Maps* maps = new Maps();

    TileMap* level = new TileMap(Maps::GetMap("map01"));
    Character* player = new Character({20, 11});
    ScreenText* instructionalText = new ScreenText({35, 10});
    ScreenText* wrappingText = new ScreenText({35, 15});
    ScreenText* thinWrappingText = new ScreenText({47, 15});
    thinWrappingText->_text->charPerLine = 1; // TODO: expose _text a little bit better..
    instructionalText->SetText("[SpaceBar]  [<][>]");
    wrappingText->SetText("12345678901234567890The text should wrap around after 20 characters by default. But you can change this by changing maxCharsPerLine property!");
    thinWrappingText->SetText("Like this!");
    
    player->AddTileMap(level); 
    game.mainWindow.screen->SetTileMap(level); // TODO: TileMap Renderer
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete maps;
    delete level;
    delete player;
    delete instructionalText;
    delete wrappingText;
    delete thinWrappingText;
}
