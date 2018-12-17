#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"
#include "magic-bits/src/common.h"
#include "magic-bits/src/slider_attacks.h"
#include "move.h"

#include <vector>

class MoveGenerator {
  public:
    MoveGenerator() {
      slider_attacks_.Initialize();
    }

    std::vector<Move> GenerateQueenMoves(const Board& board, const int queen_index) {
      U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancy_bitboard,
                                                       queen_index);
      queen_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(queen_attacks, queen_index);
    }

    // Methods to generate moves for other pieces
    // ...

  private:
    std::vector<Move> GenerateMovesFromAttackBitBoard(const U64 queen_attacks, const int queen_index) {
        std::vector<Move> moves;

    }

    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
