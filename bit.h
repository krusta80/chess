#ifndef BIT_H
#define BIT_H

#include "magic-bits/src/common.h"

#include <cassert>
#include <iostream>

class Bit
{
    public:
        static int
        countBits(U64 &bb) {
            int count = 0;

            while (bb > 0) {
                Pop(bb);
                count++;
            }
            return count;
        }

        static int
        Pop(U64 &bb) { // also called dropForward
            int idx = __builtin_ffsll(bb)-1;
            bb &= bb - 1; // reset bit outside
            return idx;
        }

        /**
         * bitScanForward
         * @author Kim Walisch (2012)
         * @param bb bitboard to scan
         * @precondition bb != 0
         * @return index (0..63) of least significant one bit
         */
        static int bitScanForward(U64 bb) {
           const U64 debruijn64 = 0x03f79d71b4cb0a89;
           assert (bb != 0);
           return index64_[((bb ^ (bb-1)) * debruijn64) >> 58];
        }

        static void printBoard(U64 board) {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 8; j++) {
                    std::cout << ((board>>(i*8+j))&1);
                }
                std::cout << std::endl;
            }
        }

    private:
        static constexpr int index64_[64] = {
            0, 47,  1, 56, 48, 27,  2, 60,
           57, 49, 41, 37, 28, 16,  3, 61,
           54, 58, 35, 52, 50, 42, 21, 44,
           38, 32, 29, 23, 17, 11,  4, 62,
           46, 55, 26, 59, 40, 36, 15, 53,
           34, 51, 20, 43, 31, 22, 10, 45,
           25, 39, 14, 33, 19, 30,  9, 24,
           13, 18,  8, 12,  7,  6,  5, 63
        };
};

#endif // BIT_H
