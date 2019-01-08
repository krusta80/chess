#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "move_generator.h"

#include <vector>

class Game
{
    public:
        Game(const int whitePlayerType, const int blackPlayerType, MoveGenerator& moveGenerator);
        void inputMove();
        void play();
        void printEvaluation();
        void printMoveList();

        int sideToMove;
        bool GAME_OVER;

    private:
        // Moves
        bool isValidMove(char* candidate);
        void makeMove(Move move);
        void undoMove();

        Move *currentMove;
        std::vector<Move*> moveHistory;
        std::vector<Board*> boardHistory;
        MoveGenerator *moveGenerator;

        // Players
        int playerTypes[2];

        constexpr static int COMPUTER = 0;
        constexpr static int HUMAN = 1;

        // Board
        Board board;
};

#endif // GAME_H
