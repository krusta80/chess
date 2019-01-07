#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "move_generator.h"

#include <vector>

class Game
{
    public:
        Game(const int whitePlayerType, const int blackPlayerType, MoveGenerator& moveGenerator);
        void printEvaluation();
        void printMoveList();
        int sideToMove;

    private:
        // Moves
        std::vector<Move*> moveList;
        MoveGenerator *moveGenerator;

        // Players
        int playerTypes[2];

        constexpr static int COMPUTER = 0;
        constexpr static int HUMAN = 1;

        // Board
        Board board;
};

#endif // GAME_H
