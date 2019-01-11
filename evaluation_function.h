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
        static int getPieceBalance(const int index, const U64 whiteBB, const U64 blackBB);

        static int PIECE_SQUARE_VALUES[6][64];
};

#endif // EVALUATION_FUNCTION_H
