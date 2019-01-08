#include <iostream>

#include "bit.h"
#include "board.h"
#include "evaluation_function.h"
#include "game.h"
#include "move_generator.h"

int main()
{
    MoveGenerator* moveGenerator = new MoveGenerator();
    Game* game = new Game(1, 1, *moveGenerator);

    game->play();
}
