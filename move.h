#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move(const int origin, const int destination, const int pieceTypeIndex) {
            this->origin = origin;
            this->destination = destination;
            this->piece = pieceTypeIndex;
        }

        int origin;
        int destination;
        int piece;
};

#endif // MOVE_H
