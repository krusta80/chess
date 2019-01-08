#include "game.h"
#include "evaluation_function.h"
#include "move_generator.h"

#include <vector>

Game::Game(const int whitePlayerType, const int blackPlayerType, MoveGenerator& moveGenerator) {
    // Game state
    GAME_OVER = false;

    // Board
    board.initialize();

    // Moves
    this->moveGenerator = &moveGenerator;
    moveHistory = std::vector<Move*>();
    currentMove = new Move(-1, -1, -1, -1);
    moveGenerator.generateAllMoves(board, sideToMove);

    // Players
    playerTypes[0] = whitePlayerType;
    playerTypes[1] = blackPlayerType;
    sideToMove = 0;

    // Update console output
    board.printBoard();
    std::cout << std::endl;
    printMoveList();
    printEvaluation();
}

void Game::play() {
    while (!GAME_OVER) {
        switch (playerTypes[sideToMove]) {
            case HUMAN:
                inputMove();
                break;
            case COMPUTER:
                // TODO (jgruska): NOOP for now
                break;
        }
        makeMove(*currentMove);
    }
}

void Game::inputMove() {
    char* move = new char[5];

    do {
        std::cout << "Please enter move: ";
        std::cin >> move;
    } while (!isValidMove(move));
}

bool Game::isValidMove(char* candidate) {
    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin();
         i != moveGenerator->moveList.end(); ++i) {
        if (strcmp(candidate, (*i)->getMoveNotation()) == 0) {
            currentMove = *i;
            return true;
        }
    }
    return false;
}

void Game::printMoveList() {
    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin();
         i != moveGenerator->moveList.end(); ++i) {
        (*i)->printMove();
    }
}

void Game::printEvaluation() {
    std::cout << "Eval: ";
    std::cout << EvaluationFunction::evaluate(board, *moveGenerator, sideToMove) << std::endl;
}

void Game::makeMove(Move move) {
    // TODO(jgruska): Add validity check
    moveHistory.push_back(new Move(move));
    boardHistory.push_back(new Board(board));
    board.makeMove(&move, sideToMove);
    sideToMove = 1 - sideToMove;
    moveGenerator->generateAllMoves(board, sideToMove);

    board.printBoard();
    printMoveList();
    printEvaluation();
    std::cout << std::endl;
}

void Game::undoMove() {
    moveHistory.pop_back();
    board = *boardHistory.back();
    boardHistory.pop_back();
    sideToMove = 1 - sideToMove;

    board.printBoard();
    std::cout << std::endl;
}
