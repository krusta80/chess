#ifndef EVALUATION_FUNCTION_H
#define EVALUATION_FUNCTION_H

#include "board.h"
#include "move_generator.h"

class EvaluationFunction
{
    public:
        static int evaluate(Board& board, MoveGenerator& moveGenerator, const int side);

    private:
        static int getMaterialBalance(Board& board);
};

#endif // EVALUATION_FUNCTION_H
