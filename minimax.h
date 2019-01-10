#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "evaluation_function.h"
#include "move.h"
#include "move_generator.h"

#include <vector>

class Minimax
{
    public:
        static Move minimax(Board board, Move* moveMade, const int side, MoveGenerator& moveGenerator, const int level);

    private:
        static int SIDE_VALUE_COEFFICIENT[2];
        static int SIDE_IMPOSSIBLE_MOVE_THRESHOLD[2];
};

#endif // MINIMAX_H
