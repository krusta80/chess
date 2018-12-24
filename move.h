#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move(const int origin, const int destination) {
            this->origin = origin;
            this->destination = destination;
        }

        int origin;
        int destination;
};

#endif // MOVE_H
