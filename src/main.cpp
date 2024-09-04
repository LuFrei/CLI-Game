#include "CLGEngine/Entity.h"
#include "CLGEngine/Game.h"

#include "Game/Character.h"
#include "Game/Maps.h"
#include "Game/ScreenText.h"
#include "Game/TileMap.h"
#include "Game/Wall.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    TileMap* level = new TileMap(30, 30, map01);
    Character* player = new Character({20, 11});
    ScreenText* instructionalText = new ScreenText({35, 10});
    ScreenText* wrappingText = new ScreenText({35, 15});
    ScreenText* thinWrappingText = new ScreenText({47, 15});
    thinWrappingText->_text->charPerLine = 1; // TODO: expose _text a little bit better..
    instructionalText->SetText("[SpaceBar]  [<][>]");
    wrappingText->SetText("12345678901234567890The text should wrap around after 20 characters by default. But you can change this by changing maxCharsPerLine property!");
    thinWrappingText->SetText("Like this!");
    
    player->AddTileMap(level);
    game.mainWindow.screen->SetTileMap(level); 
    game.Play();
    
    // TODO: Make an auto Entitiy cleaner.
    delete level;
    delete player;
    delete instructionalText;
    delete wrappingText;
    delete thinWrappingText;
}
