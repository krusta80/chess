#include "minimax.h"

#include <iostream>

Move Minimax::minimax(Board board, Move* moveMade, const int side, MoveGenerator& moveGenerator, const int level) {
    Board *newBoard = new Board(board);
    Move* candidateMove = new Move(-1, -1, -1, -1);
    bool topLevel = moveMade->piece == -1;
    moveGenerator.generateAllMoves(board, side);
    std::vector<Move*> moveList = moveGenerator.moveList;

    moveMade->minimaxValue = SIDE_IMPOSSIBLE_MOVE_THRESHOLD[1-side];
//    std::cout << "======================================" << std::endl;
//    std::cout << "Level " << level << std::endl;
//    if (!topLevel) {
//        std::cout << "Against Move " << moveMade->getMoveNotation();
//    }
//    std::cout << "(" << moveMade->minimaxValue << ")" << std::endl;
    for (std::vector<Move*>::iterator i = moveList.begin(); i != moveList.end(); ++i) {
        newBoard->makeMove(*i, side, /* tryOnly */ false);
        if (moveGenerator.isInCheck(*newBoard, side)) {
            delete newBoard;
            newBoard = new Board(board);
            continue;
        }

        candidateMove = *i;
        candidateMove->minimaxValue = EvaluationFunction::evaluate(*newBoard, moveGenerator, 1-side);
        if (level > 0) {
            *candidateMove = minimax(*newBoard, *i, 1-side, moveGenerator, level-1);
        }
//        std::cout << "Level " << level << std::endl;
//        std::cout << "    Candidate Move ";
//        candidateMove->printMove();
//        std::cout << "(" << candidateMove->minimaxValue << ")" << std::endl;
//        std::cout << "candidate: " << SIDE_VALUE_COEFFICIENT[side]*candidateMove->minimaxValue << std::endl;
//        std::cout << "old: " << SIDE_VALUE_COEFFICIENT[side]*moveMade->minimaxValue << std::endl;
        if (candidateMove->piece != -1 &&
                SIDE_VALUE_COEFFICIENT[side]*candidateMove->minimaxValue >
                SIDE_VALUE_COEFFICIENT[side]*moveMade->minimaxValue) {
            if (topLevel) {
                moveMade = new Move(*candidateMove);
            } else {
                moveMade->minimaxValue = candidateMove->minimaxValue;
            }
//            std::cout << "New best move is " << candidateMove->getMoveNotation();
//            std::cout << "(" << candidateMove->minimaxValue << ")" << std::endl;
        }
        delete newBoard;
        newBoard = new Board(board);
    }
//    if (moveMade->piece != -1) {
//        moveMade->printMove();
//        std::cout << "Level " << level << std::endl;
//    }
    return *moveMade;
}

int Minimax::SIDE_VALUE_COEFFICIENT[2] = {1, -1};
int Minimax::SIDE_IMPOSSIBLE_MOVE_THRESHOLD[2] = {
            Board::PIECE_VALUES[Board::KING_INDEX]>>1,
            -1*(Board::PIECE_VALUES[Board::KING_INDEX]>>1)
};
