#ifndef MOVE_H
#define MOVE_H

#include <iostream>

class Move
{
    public:
        Move(const int origin, const int destination, const int pieceTypeIndex, int specialMove) {
            this->origin = origin;
            this->destination = destination;
            this->piece = pieceTypeIndex;
            this->specialMove = specialMove;
        }

        char* getMoveNotation();
        void printMove();

        int origin;
        int destination;
        int piece;
        int specialMove;

        constexpr static int STANDARD = 0;
        constexpr static int CASTLE_KINGSIDE = 1;
        constexpr static int CASTLE_QUEENSIDE = 2;
        constexpr static int EN_PASSANT = 3;
        constexpr static int PROMOTE_TO_BISHOP = 4;
        constexpr static int PROMOTE_TO_KNIGHT = 5;
        constexpr static int PROMOTE_TO_QUEEN = 6;
        constexpr static int PROMOTE_TO_ROOK = 7;
};

#endif // MOVE_H
