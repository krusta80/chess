#include "game.h"
#include "evaluation_function.h"
#include "move_generator.h"

#include <vector>

Game::Game(const int whitePlayerType, const int blackPlayerType, MoveGenerator& moveGenerator) {
    // Moves
    this->moveGenerator = &moveGenerator;
    moveList = std::vector<Move*>();

    // Players
    playerTypes[0] = whitePlayerType;
    playerTypes[1] = blackPlayerType;
    sideToMove = 0;

    // Board
    board.initialize();
    board.printBoard();
    std::cout << std::endl;
}

void Game::printMoveList() {
    moveGenerator->generateAllMoves(board, sideToMove);

    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin(); i != moveGenerator->moveList.end(); ++i) {
        (*i)->printMove();
    }
}

void Game::printEvaluation() {
    std::cout << EvaluationFunction::evaluate(board, *moveGenerator, sideToMove) << std::endl;
}
