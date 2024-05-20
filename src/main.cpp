#include "CLGEngine/Game.h"

#include "Game/Character.h"

using namespace CLGEngine;

int main()
{
    Game game = Game();

    Character* player = new Character(4);

    game.Play();
}
