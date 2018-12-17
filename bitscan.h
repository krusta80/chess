#ifndef BITSCAN_H
#define BITSCAN_H


class BitScan
{

    const int index64[64] = {
        0, 47,  1, 56, 48, 27,  2, 60,
       57, 49, 41, 37, 28, 16,  3, 61,
       54, 58, 35, 52, 50, 42, 21, 44,
       38, 32, 29, 23, 17, 11,  4, 62,
       46, 55, 26, 59, 40, 36, 15, 53,
       34, 51, 20, 43, 31, 22, 10, 45,
       25, 39, 14, 33, 19, 30,  9, 24,
       13, 18,  8, 12,  7,  6,  5, 63
    };

    /**
     * bitScanForward
     * @author Kim Walisch (2012)
     * @param bb bitboard to scan
     * @precondition bb != 0
     * @return index (0..63) of least significant one bit
     */
    int bitScanForward(U64 bb) {
       const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
       assert (bb != 0);
       return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
    }
    public:
        Bit();
};

#endif // BITSCAN_H
