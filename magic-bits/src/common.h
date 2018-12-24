#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

typedef uint64_t U64;

static const int kSquares = 64;

static const char kRookMagics[] = "magic-bits/magics/rook_magics.magic";
static const char kRookMasks[] = "magic-bits/magics/rook_masks.magic";
static const char kRookShifts[] = "magic-bits/magics/rook_shifts.magic";
static const char kRookOffsets[] = "magic-bits/magics/rook_offsets.magic";
static const char kRookAttackTable[] = "magic-bits/magics/rook_attack_table.magic";

static const char kBishopMagics[] = "magic-bits/magics/bishop_magics.magic";
static const char kBishopMasks[] = "magic-bits/magics/bishop_masks.magic";
static const char kBishopShifts[] = "magic-bits/magics/bishop_shifts.magic";
static const char kBishopOffsets[] = "magic-bits/magics/bishop_offsets.magic";
static const char kBishopAttackTable[] = "magic-bits/magics/bishop_attack_table.magic";

#endif
