#include "kingattacks.h"

void KingAttacks::Initialize() {
    for (int i = 0; i < 64; i++) {
        attack_table_.push_back(generateAttackBitboard(i));
    }
}

U64 KingAttacks::generateAttackBitboard(const int index) {
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
