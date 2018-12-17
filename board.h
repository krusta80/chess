#ifndef BOARD_H
#define BOARD_H

#include "magic-bits/src/common.h"

class Board
{
    public:
        Board();

        U64 moving_side_bitboard() const;

        U64 occupancy_bitboard;
        U64 white_bitboard;
        U64 black_bitboard;

    private:
};

#endif // BOARD_H
