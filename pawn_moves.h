#ifndef PAWN_MOVES_H
#define PAWN_MOVES_H

#include "magic-bits/src/common.h"
#include <iostream>>
#include "bit.h"

// Comprises methods to generate pawn moves
// from a square, for a given piece occupancy bitboard.
// Note that en passant is NOT covered
// Initialize() method must be called before using other methods.
class PawnMoves
{
    public:
        U64 WhiteMoves(const U64 pawns, const U64 emptySpaces) const {
            return (WhiteAttacks(pawns, emptySpaces) | WhiteAdvances(pawns, emptySpaces));
        }

        U64 BlackMoves(const U64 pawns, const U64 emptySpaces) const {
            return (BlackAttacks(pawns, emptySpaces) | BlackAdvances(pawns, emptySpaces));
        }

        U64 Attacks(const U64 pawns, const U64 emptySpaces, const int side) const {
            switch (side) {
                case WHITE_:
                    return WhiteAttacks(pawns, emptySpaces);
                case BLACK_:
                    return BlackAttacks(pawns, emptySpaces);
            }
        }

        U64 WhiteAttacks(const U64 pawns, const U64 emptySpaces) const {
            U64 upperRight = (pawns & nonHFile_)<<9;
            U64 upperLeft = (pawns & nonAFile_)<<7;

            return (upperRight | upperLeft) & ~emptySpaces;
        }

        U64 BlackAttacks(const U64 pawns, const U64 emptySpaces) const {
            U64 lowerRight = (pawns & nonHFile_)>>7;
            U64 lowerLeft = (pawns & nonAFile_)>>9;

            return (lowerRight | lowerLeft) & ~emptySpaces;
        }

        U64 WhiteAdvances(const U64 pawns, const U64 emptySpaces) const {
            U64 singles = WhiteSingleAdvances_(pawns, emptySpaces);
            U64 doubles = (singles<<8) & emptySpaces & rank4_;

            return (singles | doubles);
        }

        U64 BlackAdvances(const U64 pawns, const U64 emptySpaces) const {
            U64 singles = BlackSingleAdvances_(pawns, emptySpaces);
            U64 doubles = (singles>>8) & emptySpaces & rank5_;

            return (singles | doubles);
        }

    private:
        U64 WhiteDoubleAdvances_(const U64 pawns, const U64 emptySpaces) const {
            return (WhiteSingleAdvances_(pawns, emptySpaces)<<8) & emptySpaces & rank4_;
        }

        U64 WhiteSingleAdvances_(const U64 pawns, const U64 emptySpaces) const {
            return emptySpaces & (pawns<<8);
        }

        U64 BlackDoubleAdvances_(const U64 pawns, const U64 emptySpaces) const {
            return (BlackSingleAdvances_(pawns, emptySpaces)>>8) & emptySpaces & rank5_;
        }

        U64 BlackSingleAdvances_(const U64 pawns, const U64 emptySpaces) const {
            return emptySpaces & (pawns>>8);
        }

        constexpr static int WHITE_ = 0;
        constexpr static int BLACK_ = 1;

        const U64 nonAFile_ = 0xFEFEFEFEFEFEFEFE;
        const U64 nonHFile_ = 0x7F7F7F7F7F7F7F7F;
        const U64 rank4_ = 255L<<24;
        const U64 rank5_ = 255L<<32;
};

#endif // PAWN_MOVES_H
