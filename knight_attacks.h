#ifndef KNIGHT_ATTACKS_H
#define KNIGHT_ATTACKS_H

#include "magic-bits/src/common.h"

class KnightAttacks
{
    public:
        U64 Attacks(U64 knights) {
           U64 l1 = (knights >> 1) & 0x7f7f7f7f7f7f7f7f;
           U64 l2 = (knights >> 2) & 0x3f3f3f3f3f3f3f3f;
           U64 r1 = (knights << 1) & 0xfefefefefefefefe;
           U64 r2 = (knights << 2) & 0xfcfcfcfcfcfcfcfc;
           U64 h1 = l1 | r1;
           U64 h2 = l2 | r2;
           return (h1<<16) | (h1>>16) | (h2<<8) | (h2>>8);
        }
};

#endif // KNIGHT_ATTACKS_H
