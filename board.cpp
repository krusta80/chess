#include "board.h"
#include "magic-bits/src/common.h";

#include <iostream>>

void Board::initialize() {
    bishop_bitboard[0] = 0ULL;
    bishop_bitboard[1] = 0ULL;
    king_bitboard[0] = 0ULL;
    king_bitboard[1] = 0ULL;
    knight_bitboard[0] = 0ULL;
    knight_bitboard[1] = 0ULL;
    pawn_bitboard[0] = 0ULL;
    pawn_bitboard[1] = 0ULL;
    queen_bitboard[0] = 0ULL;
    queen_bitboard[1] = 0ULL;
    rook_bitboard[0] = 0ULL;
    rook_bitboard[1] = 0ULL;
}

U64 Board::movingSideBitboard(const int side) {
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
    occupancy_bitboard_[0] |= bishop_bitboard[0];
    occupancy_bitboard_[0] |= king_bitboard[0];
    occupancy_bitboard_[0] |= knight_bitboard[0];
    occupancy_bitboard_[0] |= pawn_bitboard[0];
    occupancy_bitboard_[0] |= queen_bitboard[0];
    occupancy_bitboard_[0] |= rook_bitboard[0];

    occupancy_bitboard_[1] = 0ULL;
    occupancy_bitboard_[1] |= bishop_bitboard[1];
    occupancy_bitboard_[1] |= king_bitboard[1];
    occupancy_bitboard_[1] |= knight_bitboard[1];
    occupancy_bitboard_[1] |= pawn_bitboard[1];
    occupancy_bitboard_[1] |= queen_bitboard[1];
    occupancy_bitboard_[1] |= rook_bitboard[1];
}
