#ifndef BOARD_H
#define BOARD_H

#include "magic-bits/src/common.h"

class Board
{
    public:
        void initialize();

        // Occupancy
        U64 sideBitboard(const int side);
        U64 whiteBitboard();
        U64 blackBitboard();
        U64 occupancyBitboard();
        void updateOccupancyBitboard();

        // Attacks
        U64 attacked[2];

        // Pieces
        U64 pieces[6][2];
        U64 getBishopBitboard(const int side);
        U64 getKingBitboard(const int side);
        U64 getKnightBitboard(const int side);
        U64 getPawnBitboard(const int side);
        U64 getQueenBitboard(const int side);
        U64 getRookBitboard(const int side);

        constexpr static int BISHOP_INDEX = 0;
        constexpr static int KING_INDEX = 1;
        constexpr static int KNIGHT_INDEX = 2;
        constexpr static int PAWN_INDEX = 3;
        constexpr static int QUEEN_INDEX = 4;
        constexpr static int ROOK_INDEX = 5;

        // Castling
        bool never_castle_kingside[2];
        bool never_castle_queenside[2];

        constexpr static U64 C1 = 0x0000000000000020;
        constexpr static U64 D1 = 0x0000000000000010;
        constexpr static U64 E1 = 0x0000000000000008;
        constexpr static U64 F1 = 0x0000000000000004;
        constexpr static U64 G1 = 0x0000000000000002;
        constexpr static U64 C8 = 0x2000000000000000;
        constexpr static U64 D8 = 0x1000000000000000;
        constexpr static U64 E8 = 0x0800000000000000;
        constexpr static U64 F8 = 0x0400000000000000;
        constexpr static U64 G8 = 0x0200000000000000;

    private:
        U64 occupancy_bitboard_[2];
};

#endif // BOARD_H
