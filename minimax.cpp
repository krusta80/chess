#include "minimax.h"

#include <iostream>

Move Minimax::minimax(Board board, Move* moveMade, const int side, MoveGenerator& moveGenerator, const int level) {
    Board *newBoard = new Board(board);
    Move* candidateMove = new Move(-1, -1, -1, -1);
    bool topLevel = moveMade->piece == -1;
    moveGenerator.generateAllMoves(board, side);
    std::vector<Move*> moveList = moveGenerator.moveList;

    moveMade->minimaxValue = SIDE_VALUE_COEFFICIENT[1-side] * INT_MAX;
//    std::cout << "Level " << level << std::endl;
//    if (!topLevel) {
//        std::cout << "Against Move " << moveMade->getMoveNotation();
//    }
//    std::cout << "(" << moveMade->minimaxValue << ")" << std::endl;
    for (std::vector<Move*>::iterator i = moveList.begin(); i != moveList.end(); ++i) {
        newBoard->makeMove(*i, side, /* tryOnly */ false);

        candidateMove = *i;
        candidateMove->minimaxValue = EvaluationFunction::evaluate(*newBoard, moveGenerator, 1-side);
        if (level > 0 && moveGenerator.moveList.size() > 0) {
            *candidateMove = minimax(*newBoard, *i, 1-side, moveGenerator, level-1);
        }
//        std::cout << "Level " << level << std::endl;
//        std::cout << "    Candidate Move ";
//        candidateMove->printMove();
//        std::cout << "(" << candidateMove->minimaxValue << ")" << std::endl;
//        std::cout << "candidate: " << SIDE_VALUE_COEFFICIENT[side]*candidateMove->minimaxValue << std::endl;
//        std::cout << "old: " << SIDE_VALUE_COEFFICIENT[side]*moveMade->minimaxValue << std::endl;
        if (SIDE_VALUE_COEFFICIENT[side]*candidateMove->minimaxValue >
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
//    moveMade->printMove();
    return *moveMade;
}

int Minimax::SIDE_VALUE_COEFFICIENT[2] = {1, -1};
