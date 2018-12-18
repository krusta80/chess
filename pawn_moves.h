#ifndef PAWN_MOVES_H
#define PAWN_MOVES_H

#include "magic-bits/src/common.h"

#include <vector>

// Comprises methods to generate pawn moves
// from a square, for a given piece occupancy bitboard.
// Note that en passant is NOT covered in this class.
// Initialize() method must be called before using other methods.
class PawnMoves
{
    public:
        void Initialize();

        U64 Moves(const U64 bitboard, const int index, const int side) const {
            return Advances(bitboard, index, side)|Attacks(bitboard, index, side);
        }

        U64 Attacks(const U64 bitboard, const int index, const int side) const {
            return attack_table_[side][index]&~bitboard;
        }

        U64 Advances(const U64 bitboard, const int index, const int side) const {
            return advance_table_[side][index]&~bitboard;
        }

    private:
        U64 generateAttackBitboard(const int index, const int side);
        U64 generateAdvanceBitboard(const int index, const int side);

        std::vector<U64> attack_table_[2];
        std::vector<U64> advance_table_[2];
};

#endif // PAWN_MOVES_H
