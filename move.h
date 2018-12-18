#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move(const int origin, const int destination) {
            this->origin_ = origin;
            this->destination_ = destination;
        }

    private:
        static int origin_;
        static int destination_;
};

#endif // MOVE_H
