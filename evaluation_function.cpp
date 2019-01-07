#include "evaluation_function.h"

int EvaluationFunction::evaluate(Board& board, MoveGenerator& moveGenerator, const int side) {
    // need to make this smarter
    moveGenerator.generateAllMoves(board, side);
    if (isCheckmate(board, moveGenerator, side)) {
        return side == 0 ?
                  -1 * Board::PIECE_VALUES[Board::KING_INDEX]
                :      Board::PIECE_VALUES[Board::KING_INDEX];
        }
    if (isStalemate(board, moveGenerator, side)) {
            return 0;
    }
    return getMaterialBalance(board);
}

bool EvaluationFunction::isCheckmate(Board& board, MoveGenerator& moveGenerator, const int side) {
    //  Assumes move list already generated for given board and side
    return moveGenerator.moveList.size() == 0 && moveGenerator.isInCheck(board, side);
}

bool EvaluationFunction::isStalemate(Board& board, MoveGenerator& moveGenerator, const int side) {
    //  Assumes move list already generated for given board and side
    return moveGenerator.moveList.size() == 0 && !moveGenerator.isInCheck(board, side);
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
