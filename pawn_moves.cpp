#include "pawn_moves.h"

void PawnMoves::Initialize() {
    for (int i = 0; i < 64; i++) {
        attack_table_[0].push_back(generateAttackBitboard(i, 0)); // white
        attack_table_[1].push_back(generateAttackBitboard(i, 1)); // black
        advance_table_[0].push_back(generateAdvanceBitboard(i, 0)); // white
        advance_table_[1].push_back(generateAdvanceBitboard(i, 1)); // black
    }
}

U64 PawnMoves::generateAttackBitboard(const int index, const int side) {
    U64 attack = 0;

    if (side == 0 && index < 56 && index%8 > 0) attack |= 1L<<(index+7);    // upperleft
    if (side == 0 && index < 56 && index%8 < 7) attack |= 1L<<(index+9);    // upperright

    if (side == 1 && index > 7 && index%8 > 0) attack |= 1L<<(index-9);     // lowerleft
    if (side == 1 && index > 7 && index%8 < 7) attack |= 1L<<(index-7);     // lowerright
    return attack;
}

U64 PawnMoves::generateAdvanceBitboard(const int index, const int side) {
    U64 attack = 0;

    if (index < 56) attack |= 1L<<(index+8);                   // up
    if (index%8 > 0) attack |= 1L<<(index-1);                  // left
    if (index < 56 && index%8 > 0) attack |= 1L<<(index+7);    // upperleft
    if (index%8 < 7) attack |= 1L<<(index+1);                  // right
    if (index < 56 && index%8 < 7) attack |= 1L<<(index+9);    // upperright
    if (index > 7) attack |= 1L<<(index-8);                    // down
    if (index > 7 && index%8 > 0) attack |= 1L<<(index-9);     // lowerleft
    if (index > 7 && index%8 < 7) attack |= 1L<<(index-7);     // lowerright
    return attack;
}
