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

    std::vector<Move*> GenerateAllMoves(Board& board, const int side) {

    }

    std::vector<Move*> getBishopsMoves(Board& board, const int const int side) {
        std::vector<Move*> moves;


        return moves;
    }

  private:
    std::vector<Move*> getBishopMoves(U64 allPieces, U64 friendlyPieces, const int bishopIndex) {
      U64 bishopAttacks = slider_attacks_.BishopAttacks(allPieces, bishopIndex);

      bishopAttacks &= ~friendlyPieces;
      return generateMovesFromAttackBitBoard(bishopAttacks, bishopIndex);
    }

    std::vector<Move*> getKingMoves(U64 allPieces, U64 friendlyPieces, const int kingIndex) {
      U64 kingAttacks = king_attacks_.Attacks(allPieces, kingIndex);

      kingAttacks &= ~friendlyPieces;
      return generateMovesFromAttackBitBoard(kingAttacks, kingIndex);
    }

    std::vector<Move*> getKnightMoves(U64 , const int knight_index, const int side) {
      U64 knight_attacks = knight_attacks_.Attacks(board.knight_bitboard[side]);

      knight_attacks &= ~board.movingSideBitboard(side);
      return GenerateMovesFromAttackBitBoard(knight_attacks, knight_index);
    }

    std::vector<Move*> GeneratePawnMoves(Board& board, const int pawn_index, const int side) {
      U64 pawn_moves = 0;

      switch (side) {
        case WHITE_:
          pawn_moves = pawn_moves_.WhiteMoves(board.pawn_bitboard[side], ~board.occupancyBitboard());
          break;
        case BLACK_:
          pawn_moves = pawn_moves_.BlackMoves(board.pawn_bitboard[side], ~board.occupancyBitboard());
      }
      return GenerateMovesFromAttackBitBoard(pawn_moves, pawn_index);
    }

    std::vector<Move*> GenerateQueenMoves(Board& board, const int queen_index, const int side) {
      U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancyBitboard(),
                                                       queen_index);
      queen_attacks &= ~board.movingSideBitboard(side);
      return GenerateMovesFromAttackBitBoard(queen_attacks, queen_index);
    }

    std::vector<Move*> GenerateRookMoves(Board& board, const int rook_index, const int side) {
      U64 rook_attacks = slider_attacks_.RookAttacks(board.occupancyBitboard(),
                                                       rook_index);
      rook_attacks &= ~board.movingSideBitboard(side);
      return GenerateMovesFromAttackBitBoard(rook_attacks, rook_index);
    }

    std::vector<Move*> generateMovesFromAttackBitBoard(U64 bitboard, const int piece_index) {
        std::vector<Move*> moves;

        while (bitboard > 0) {
             moves.push_back(new Move(piece_index, Bit().Pop(bitboard)));
        }
        return moves;
    }

    constexpr static int WHITE_ = 0;
    constexpr static int BLACK_ = 1;

    KingAttacks king_attacks_;
    KnightAttacks knight_attacks_;
    PawnMoves pawn_moves_;
    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
