#ifndef BOARD_H
#define BOARD_H

#include "magic-bits/src/common.h"

class Board
{
    public:
        // Occupancy
        U64 movingSideBitboard(const int side);
        U64 whiteBitboard();
        U64 blackBitboard();
        U64 occupancyBitboard();

        // Pieces
        U64 bishop_bitboard[2];
        U64 king_bitboard[2];
        U64 knight_bitboard[2];
        U64 pawn_bitboard[2];
        U64 queen_bitboard[2];
        U64 rook_bitboard[2];

    private:
        U64 occupancy_bitboard_[2];
};

#endif // BOARD_H
