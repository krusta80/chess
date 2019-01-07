#ifndef BOARD_H
#define BOARD_H

#include "magic-bits/src/common.h"

class Board
{
    public:
        void initialize();
        void printBoard();

        // Spaces (Notation, etc)
        const static char* SQUARE_LABELS[64];

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

        static const int PIECE_VALUES[6];

        constexpr static int BISHOP_INDEX = 0;
        constexpr static int KING_INDEX = 1;
        constexpr static int KNIGHT_INDEX = 2;
        constexpr static int PAWN_INDEX = 3;
        constexpr static int QUEEN_INDEX = 4;
        constexpr static int ROOK_INDEX = 5;

        const static char PIECE_NOTATION[6];

        // Castling
        bool never_castle_kingside[2];
        bool never_castle_queenside[2];

        const static U64 BACK_RANK_BCD[2];
        const static U64 BACK_RANK_FG[2];
        const static U64 BACK_RANK_A[2];
        const static U64 BACK_RANK_B[2];
        const static U64 BACK_RANK_C[2];
        const static U64 BACK_RANK_D[2];
        const static U64 BACK_RANK_E[2];
        const static U64 BACK_RANK_F[2];
        const static U64 BACK_RANK_G[2];
        const static U64 BACK_RANK_H[2];

        // En Passant
        U64 enPassantDestination;
        U64 enPassantTarget;

    private:
        char getSquareNotation(const int index);

        U64 occupancy_bitboard_[2];
};

#endif // BOARD_H
