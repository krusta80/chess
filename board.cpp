#include "board.h"
#include "magic-bits/src/common.h";

#include <iostream>>

void Board::initialize() {
    bishop_bitboard[0] = 0x0000000000000000;
    bishop_bitboard[1] = 0x0000000000000000;
    king_bitboard[0] = 0x0000000000000000;
    king_bitboard[1] = 0x0000000000000000;
    knight_bitboard[0] = 0x0000000000000000;
    knight_bitboard[1] = 0x0000000000000000;
    pawn_bitboard[0] = 0x0000000000000000;
    pawn_bitboard[1] = 0x0000000000000000;
    queen_bitboard[0] = 0x0000000000000000;
    queen_bitboard[1] = 0x0000000000000000;
    rook_bitboard[0] = 0x0000000000000000;
    rook_bitboard[1] = 0x0000000000000000;
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
    occupancy_bitboard_[0] = 0x0000000000000000;
    occupancy_bitboard_[0] |= bishop_bitboard[0];
    occupancy_bitboard_[0] |= king_bitboard[0];
    occupancy_bitboard_[0] |= knight_bitboard[0];
    occupancy_bitboard_[0] |= pawn_bitboard[0];
    occupancy_bitboard_[0] |= queen_bitboard[0];
    occupancy_bitboard_[0] |= rook_bitboard[0];

    occupancy_bitboard_[1] =
            (bishop_bitboard[1] |
            king_bitboard[1] |
            knight_bitboard[1] |
            pawn_bitboard[1] |
            queen_bitboard[1] |
            rook_bitboard[1]);
    std::cout << "friendly pieces is " << std::hex << occupancy_bitboard_[0] << std::endl;
    std::cout << "friendly pieces is " << std::hex << occupancy_bitboard_[1] << std::endl;
}
