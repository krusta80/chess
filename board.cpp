#include "board.h"
#include "magic-bits/src/common.h";

#include <iostream>>

void Board::initialize() {
    for (int i = 0; i < 6; i++) {
        pieces[i][0] = 0ULL;
        pieces[i][1] = 0ULL;
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
