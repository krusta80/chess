#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"
#include "magic-bits/src/common.h"
#include "magic-bits/src/slider_attacks.h"
#include "bit.h"
#include "king_attacks.h"
#include "knight_attacks.h"
#include "move.h"
#include "pawn_moves.h"

#include <vector>

class MoveGenerator {
  public:
    MoveGenerator() {
      king_attacks_.Initialize();
      slider_attacks_.Initialize();
    }

    std::vector<Move> GenerateQueenMoves(const Board& board, const int queen_index) {
      U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancy_bitboard,
                                                       queen_index);
      queen_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(queen_attacks, queen_index);
    }

    std::vector<Move> GenerateRookMoves(const Board& board, const int rook_index) {
      U64 rook_attacks = slider_attacks_.RookAttacks(board.occupancy_bitboard,
                                                       rook_index);
      rook_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(rook_attacks, rook_index);
    }

    std::vector<Move> GenerateBishopMoves(const Board& board, const int bishop_index) {
      U64 bishop_attacks = slider_attacks_.BishopAttacks(board.occupancy_bitboard,
                                                       bishop_index);
      bishop_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(bishop_attacks, bishop_index);
    }

    std::vector<Move> GenerateKingMoves(const Board& board, const int king_index) {
      U64 king_attacks = king_attacks_.Attacks(board.occupancy_bitboard,
                                                       king_index);
      king_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(king_attacks, king_index);
    }

    std::vector<Move> GenerateKnightMoves(const Board& board, const int side, const int knight_index) {
      U64 knight_attacks = knight_attacks_.Attacks(board.knight_bitboard[side]);

      knight_attacks &= ~board.moving_side_bitboard();  // discard self-piece captures
      return GenerateMovesFromAttackBitBoard(knight_attacks, knight_index);
    }

    std::vector<Move> GeneratePawnMoves(const Board& board, const int side, const int pawn_index) {
      U64 pawn_moves = -1;

      if (side == 0) {
          pawn_moves = pawn_moves_.WhiteMoves(board.pawn_bitboard[side], ~board.occupancy_bitboard);
      } else if (side == 1) {
          pawn_moves = pawn_moves_.BlackMoves(board.pawn_bitboard[side], ~board.occupancy_bitboard);
      }
      return GenerateMovesFromAttackBitBoard(pawn_moves, pawn_index);
    }

  private:
    std::vector<Move> GenerateMovesFromAttackBitBoard(const U64 queen_attacks, const int queen_index) {
        std::vector<Move> moves;
        while (queen_attacks > 0) {
             moves.push_back(new Move(queen_index, Bit().Pop(queen_attacks)));
        }
    }

    KingAttacks king_attacks_;
    KnightAttacks knight_attacks_;
    PawnMoves pawn_moves_;
    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
