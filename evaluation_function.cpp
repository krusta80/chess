#include "evaluation_function.h"

int EvaluationFunction::evaluate(Board& board, MoveGenerator& moveGenerator, const int side) {
    return getMaterialBalance(board);
}

int EvaluationFunction::getMaterialBalance(Board& board) {
    int materialBalance = 0;
    U64 whiteBB;
    U64 blackBB;

    for (int p = 0; p < 6; p++) {
        whiteBB = board.pieces[p][0];
        blackBB = board.pieces[p][1];
        materialBalance +=
                Board::PIECE_VALUES[p] *
                (Bit::countBits(whiteBB) - Bit::countBits(blackBB));
    }
    return materialBalance;
}
