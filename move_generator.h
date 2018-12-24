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

#include <iostream>
#include <vector>

class MoveGenerator {
  public:
    std::vector<Move*> moveList;

    MoveGenerator() {
      king_attacks_.Initialize();
      slider_attacks_.Initialize();
    }

    void generateAllMoves(Board& board, const int side) {
        moveList = std::vector<Move*>();

        addAllBishopMoves(board, side);
        addKingMoves(
                    board.occupancyBitboard(),
                    board.movingSideBitboard(side),
                    __builtin_ffsll(board.king_bitboard[side])-1);
        addAllKnightMoves(board, side);
        addAllPawnMoves(board, side);
        addAllQueenMoves(board, side);
        addAllRookMoves(board, side);

        removeIllegalMoves(board);
    }

  private:
    void addAllBishopMoves(Board& board, const int side) {
        U64 bitboard = board.bishop_bitboard[side];

        while (bitboard > 0) {
             addBishopMoves(
                         board.occupancyBitboard(),
                         board.movingSideBitboard(side),
                         Bit().Pop(bitboard));
        }
    }

    void addKingMoves(U64 allPieces, U64 friendlyPieces, const int kingIndex) {
        U64 kingAttacks = king_attacks_.Attacks(allPieces, kingIndex);

        kingAttacks &= ~friendlyPieces;
        addMovesFromAttackBitboard(kingAttacks, kingIndex);
    }

    void addAllKnightMoves(Board& board, const int side) {
        U64 bitboard = board.knight_bitboard[side];

        while (bitboard > 0) {
             addKnightMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllPawnMoves(Board& board, const int side) {
        U64 bitboard = board.pawn_bitboard[side];

        while (bitboard > 0) {
             addPawnMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllQueenMoves(Board& board, const int side) {
        U64 bitboard = board.queen_bitboard[side];

        while (bitboard > 0) {
             addQueenMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllRookMoves(Board& board, const int side) {
        U64 bitboard = board.rook_bitboard[side];

        while (bitboard > 0) {
             addRookMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void removeIllegalMoves(Board& board) {
        int moveCount = moveList.size();

        for (int i = 0; i < moveCount; i++) {
            if (isIllegal(moveList.at(i), board)) {
                std::iter_swap(moveList.begin() + i, moveList.end() - 1);
                moveList.pop_back();
                moveCount--;
                i--;
            }
        }
    }

    bool isIllegal(Move* move, Board& board) {
        // TODO(jgruska): Add legality check.
        return false;
    }

    void addBishopMoves(U64 allPieces, U64 friendlyPieces, const int bishopIndex) {
        U64 bishopAttacks = slider_attacks_.BishopAttacks(allPieces, bishopIndex);
        std::cout << "bishop attacks is " << std::hex << bishopAttacks << std::endl;
        std::cout << "friendly pieces is " << std::hex << friendlyPieces << std::endl;
        std::cout << "bishop index is " << bishopIndex << std::endl;

        bishopAttacks &= ~friendlyPieces;
        addMovesFromAttackBitboard(bishopAttacks, bishopIndex);
    }

    void addKnightMoves(Board& board, const int knight_index, const int side) {
        U64 knight_attacks = knight_attacks_.Attacks(1<<knight_index);

        knight_attacks &= ~board.movingSideBitboard(side);
        addMovesFromAttackBitboard(knight_attacks, knight_index);
    }

    void addPawnMoves(Board& board, const int pawn_index, const int side) {
        U64 pawn_moves = 0;

        switch (side) {
            case WHITE_:
              pawn_moves = pawn_moves_.WhiteMoves(
                            board.pawn_bitboard[side],
                            ~board.occupancyBitboard());
              break;
            case BLACK_:
              pawn_moves = pawn_moves_.BlackMoves(
                            board.pawn_bitboard[side],
                          ~board.occupancyBitboard());
        }
        addMovesFromAttackBitboard(pawn_moves, pawn_index);
    }

    void addQueenMoves(Board& board, const int queen_index, const int side) {
        U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancyBitboard(),
                                                       queen_index);
        queen_attacks &= ~board.movingSideBitboard(side);
        addMovesFromAttackBitboard(queen_attacks, queen_index);
    }

    void addRookMoves(Board& board, const int rook_index, const int side) {
        U64 rook_attacks = slider_attacks_.RookAttacks(board.occupancyBitboard(),
                                                       rook_index);
        rook_attacks &= ~board.movingSideBitboard(side);
        addMovesFromAttackBitboard(rook_attacks, rook_index);
    }

    void addMovesFromAttackBitboard(U64 bitboard, const int piece_index) {
        while (bitboard > 0) {
            moveList.push_back(new Move(piece_index, Bit().Pop(bitboard)));
        }
    }

    constexpr static int WHITE_ = 0;
    constexpr static int BLACK_ = 1;

    KingAttacks king_attacks_;
    KnightAttacks knight_attacks_;
    PawnMoves pawn_moves_;
    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
