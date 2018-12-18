#ifndef KINGATTACKS_H
#define KINGATTACKS_H

#include "magic-bits/src/common.h"

#include <vector>

// Comprises methods to generate king attacks
// from a square, for a given piece occupancy bitboard.
// Initialize() method must be called before using other methods.
class KingAttacks
{
    public:
        void Initialize();

        U64 Attacks(const U64 bitboard, const int index) const {
            return attack_table_[index]&~bitboard;
        }

    private:
        U64 generateAttackBitboard(const int index);

        std::vector<U64> attack_table_;
};

#endif // KINGATTACKS_H
