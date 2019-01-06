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

        void printMove() {
            std::cout << std::dec << origin << "," << std::dec << destination;
            switch (specialMove) {
                case PROMOTE_TO_QUEEN:
                    std::cout << " (Q)";
                    break;
                case PROMOTE_TO_ROOK:
                    std::cout << " (R)";
                    break;
                case PROMOTE_TO_BISHOP:
                    std::cout << " (B)";
                    break;
                case PROMOTE_TO_KNIGHT:
                    std::cout << " (N)";
                    break;
            }
            std::cout << std::endl;
        }

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
