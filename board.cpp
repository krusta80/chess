#include "board.h"
#include "magic-bits/src/common.h";

#include <iostream>>

void Board::initialize() {
    never_castle_kingside[0] = false;
    never_castle_kingside[1] = false;
    never_castle_queenside[0] = false;
    never_castle_queenside[1] = false;

    // Setup new board
    pieces[0][0] = (Board::BACK_RANK_C[0] | Board::BACK_RANK_F[0]);
    pieces[0][1] = (Board::BACK_RANK_C[1] | Board::BACK_RANK_F[1]);
    pieces[1][0] = Board::BACK_RANK_E[0];
    pieces[1][1] = Board::BACK_RANK_E[1];
    pieces[2][0] = (Board::BACK_RANK_B[0] | Board::BACK_RANK_G[0]);
    pieces[2][1] = (Board::BACK_RANK_B[1] | Board::BACK_RANK_G[1]);
    pieces[3][0] = 0x000000000000FF00;
    pieces[3][1] = 0x00FF000000000000;
    pieces[4][0] = Board::BACK_RANK_D[0];
    pieces[4][1] = Board::BACK_RANK_D[1];
    pieces[5][0] = (Board::BACK_RANK_A[0] | Board::BACK_RANK_H[0]);
    pieces[5][1] = (Board::BACK_RANK_A[1] | Board::BACK_RANK_H[1]);
    updateOccupancyBitboard();
}

void Board::printBoard() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            std::cout << getSquareNotation(i*8+j);
        }
        std::cout << std::endl;
    }
}

char Board::getSquareNotation(const int index) {
    U64 mask = 1L<<index;

    if ((occupancyBitboard() & mask) == 0) {
        return '.';
    }
    for (int p = 0; p < 6; p++) {
        if ((pieces[p][0] & mask) > 0) {
            if (p == Board::PAWN_INDEX) return 'P';
            return PIECE_NOTATION[p];
        } else if ((pieces[p][1] & mask) > 0) {
            if (p == Board::PAWN_INDEX) return 'p';
            return PIECE_NOTATION[p] + 32;
        }
    }
}

U64 Board::sideBitboard(const int side) {
    return occupancy_bitboard_[side];
}

U64 Board::whiteBitboard() {
    return occupancy_bitboard_[0];
}

U64 Board::blackBitboard() {
    return occupancy_bitboard_[1];
}

U64 Board::occupancyBitboard() {
    return (occupancy_bitboard_[0] | occupancy_bitboard_[1]);
}

void Board::updateOccupancyBitboard() {
    occupancy_bitboard_[0] = 0ULL;
    occupancy_bitboard_[1] = 0ULL;
    for (int i = 0; i < 6; i++) {
        occupancy_bitboard_[0] |= pieces[i][0];
        occupancy_bitboard_[1] |= pieces[i][1];
    }
}

void Board::makeMove(Move* move, const int side) {
    U64 originMask = 1L << move->origin;
    U64 destinationMask = 1L << move->destination;

    pieces[move->piece][side] ^= (originMask | destinationMask);
    for (int i = 0; i < 6; i++) {
        pieces[i][1-side] &= ~destinationMask;
    }
    switch (move->specialMove) {
        case Move::EN_PASSANT:
            pieces[PAWN_INDEX][1-side] &= ~enPassantTarget;
            break;
        case Move::PROMOTE_TO_QUEEN:
            pieces[PAWN_INDEX][side] ^= destinationMask;
            pieces[QUEEN_INDEX][side] |= destinationMask;
            break;
        case Move::PROMOTE_TO_ROOK:
            pieces[PAWN_INDEX][side] ^= destinationMask;
            pieces[ROOK_INDEX][side] |= destinationMask;
            break;
        case Move::PROMOTE_TO_BISHOP:
            pieces[PAWN_INDEX][side] ^= destinationMask;
            pieces[BISHOP_INDEX][side] |= destinationMask;
            break;
        case Move::PROMOTE_TO_KNIGHT:
            pieces[PAWN_INDEX][side] ^= destinationMask;
            pieces[KNIGHT_INDEX][side] |= destinationMask;
            break;
    }
    updateOccupancyBitboard();
}

U64 Board::getBishopBitboard(const int side) {
    return pieces[BISHOP_INDEX][side];
}

U64 Board::getKingBitboard(const int side) {
    return pieces[KING_INDEX][side];
}

U64 Board::getKnightBitboard(const int side) {
    return pieces[KNIGHT_INDEX][side];
}

U64 Board::getPawnBitboard(const int side) {
    return pieces[PAWN_INDEX][side];
}

U64 Board::getQueenBitboard(const int side) {
    return pieces[QUEEN_INDEX][side];
}

U64 Board::getRookBitboard(const int side) {
    return pieces[ROOK_INDEX][side];
}

const char Board::PIECE_NOTATION[] = {'B', 'K', 'N', '\0', 'Q', 'R'};

const U64 Board::BACK_RANK_BCD[] = {
    0x000000000000000E,
    0x0E00000000000000
};

const U64 Board::BACK_RANK_FG[]= {
    0x0000000000000060,
    0x6000000000000000
};

const U64 Board::BACK_RANK_A[] = {
    0x0000000000000001,
    0x0100000000000000
};

const U64 Board::BACK_RANK_B[] = {
    0x0000000000000002,
    0x0200000000000000
};

const U64 Board::BACK_RANK_C[] = {
    0x0000000000000004,
    0x0400000000000000
};

const U64 Board::BACK_RANK_D[] = {
    0x0000000000000008,
    0x0800000000000000
};

const U64 Board::BACK_RANK_E[] = {
    0x0000000000000010,
    0x1000000000000000
};

const U64 Board::BACK_RANK_F[] = {
    0x0000000000000020,
    0x2000000000000000
};

const U64 Board::BACK_RANK_G[] = {
    0x0000000000000040,
    0x4000000000000000
};

const U64 Board::BACK_RANK_H[] = {
    0x0000000000000080,
    0x8000000000000000
};

const char* Board::SQUARE_LABELS[] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
};

const int Board::PIECE_VALUES[] = {
   300,        // Bishop
   999999,     // King
   300,        // Knight
   100,        // Pawn
   900,        // Queen
   500         // Rook
};
