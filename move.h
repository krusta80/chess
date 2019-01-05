#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move(const int origin, const int destination, const int pieceTypeIndex, int specialMove) {
            this->origin = origin;
            this->destination = destination;
            this->piece = pieceTypeIndex;
            this->specialMove = specialMove;
        }

        int origin;
        int destination;
        int piece;
        int specialMove;

        constexpr static int STANDARD_MOVE = 0;
        constexpr static int CASTLE_KINGSIDE = 1;
        constexpr static int CASTLE_QUEENSIDE = 2;
        constexpr static int EN_PASSANT = 3;
};

#endif // MOVE_H
