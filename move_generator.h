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
      previousBoard.initialize();
    }

    void generateAllMoves(Board& board, const int side) {
        moveList = std::vector<Move*>();

        addAllBishopMoves(board, side);
        addKingAttacks(
                    board.sideBitboard(side),
                    __builtin_ffsll(board.getKingBitboard(side))-1);
        addCastlingIfLegal(board, side);
        addAllKnightMoves(board, side);
        addAllPawnMoves(board, side);
        addAllQueenMoves(board, side);
        addAllRookMoves(board, side);

        removeIllegalMoves(board, side);
    }

  private:
    void addAllBishopMoves(Board& board, const int side) {
        U64 bitboard = board.getBishopBitboard(side);

        while (bitboard > 0) {
             addBishopMoves(
                         board.occupancyBitboard(),
                         board.sideBitboard(side),
                         Bit().Pop(bitboard));
        }
    }

    void addKingAttacks(U64 friendlyPieces, const int kingIndex) {
        U64 kingAttacks = king_attacks_.Attacks(friendlyPieces, kingIndex);

        addMovesFromAttackBitboard(kingAttacks, kingIndex, Board::KING_INDEX);
    }

    void addCastlingIfLegal(Board& board, const int side) {
        addKingsideCastlingIfLegal(board, side);
        addQueensideCastlingIfLegal(board, side);
    }

    void addKingsideCastlingIfLegal(Board& board, const int side) {
        if (board.never_castle_kingside[side]) {
            return;
        }
        if ((board.occupancyBitboard() & 0x60) > 0) {
            return;
        }
        if (isAttacked(board, 0x20, side) ||
                isAttacked(board, 0x40, side) ||
                isAttacked(board, 0x10, side)) {
            return;
        }
        moveList.push_back(new Move(4, 6, Board::KING_INDEX));
    }

    void addQueensideCastlingIfLegal(Board& board, const int side) {
        if (board.never_castle_queenside[side]) {
            return;
        }
        if ((board.occupancyBitboard() & 0xE) > 0) {
            return;
        }
        if (isAttacked(board, 0x8, side) ||
                isAttacked(board, 0x4, side) ||
                isAttacked(board, 0x10, side)) {
            return;
        }
        moveList.push_back(new Move(4, 2, Board::KING_INDEX));
    }

    void addAllKnightMoves(Board& board, const int side) {
        U64 bitboard = board.getKnightBitboard(side);

        while (bitboard > 0) {
             addKnightMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllPawnMoves(Board& board, const int side) {
        U64 bitboard = board.getPawnBitboard(side);

        while (bitboard > 0) {
             addPawnMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllQueenMoves(Board& board, const int side) {
        U64 bitboard = board.getQueenBitboard(side);

        while (bitboard > 0) {
             addQueenMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void addAllRookMoves(Board& board, const int side) {
        U64 bitboard = board.getRookBitboard(side);

        while (bitboard > 0) {
             addRookMoves(board, Bit().Pop(bitboard), side);
        }
    }

    void removeIllegalMoves(Board& board, const int side) {
        int moveCount = moveList.size();

        for (int i = 0; i < moveCount; i++) {
            if (isIllegal(moveList.at(i), board, side)) {
                std::iter_swap(moveList.begin() + i, moveList.end() - 1);
                moveList.pop_back();
                moveCount--;
                i--;
            }
        }
    }

    bool isIllegal(Move* move, Board& board, const int side) {
        // TODO(jgruska): Predetermine xray blockers to speed this up.
        bool isIllegal = false;

        tryMove(move, board, side);
        if (isInCheck(board, side)) {
            isIllegal = true;
        }
        untryMove(move, board, side);
        return isIllegal;
    }

    void tryMove(Move* move, Board& board, const int side) {
        U64 originMask = (0ULL | 1L<<move->origin);
        U64 destinationMask = (0ULL | 1L<<move->destination);

        board.pieces[move->piece][side] ^= (originMask | destinationMask);
        for (int i = 0; i < 6; i++) {
            previousBoard.pieces[i][1-side] = board.pieces[i][1-side];
            board.pieces[i][1-side] &= ~destinationMask;
        }
        board.updateOccupancyBitboard();
    }

    void untryMove(Move* move, Board& board, const int side) {
        U64 originMask = 1L<<move->origin;
        U64 destinationMask = 1L<<move->destination;

        board.pieces[move->piece][side] ^= (originMask | destinationMask);
        for (int i = 0; i < 6; i++) {
            board.pieces[i][1-side] = previousBoard.pieces[i][1-side];
        }
        board.updateOccupancyBitboard();
    }

    bool isInCheck(Board& board, const int side) {
        return isAttacked(board, board.getKingBitboard(side), side);
    }

    bool isAttacked(Board& board, U64 square_bitboard, int side) {
        // TODO(jgruska): Speed this up.
        const int index =  __builtin_ffsll(square_bitboard)-1;
        U64 bishop_checks = slider_attacks_.BishopAttacks(board.occupancyBitboard(),
                                                       index);
        U64 rook_checks = slider_attacks_.RookAttacks(board.occupancyBitboard(),
                                                       index);
        U64 knight_checks = knight_attacks_.Attacks(square_bitboard);
        U64 pawn_checks = pawn_moves_.Attacks(square_bitboard,
                                              ~board.getPawnBitboard(1-side), side);
        U64 king_checks = king_attacks_.Attacks(board.getKingBitboard(1-side), index);

        bishop_checks &= (board.getBishopBitboard(1-side) | board.getQueenBitboard(1-side));
        king_checks &= (board.getKingBitboard(1-side));
        knight_checks &= (board.getKnightBitboard(1-side));
        rook_checks &= (board.getRookBitboard(1-side) | board.getQueenBitboard(1-side));
        return (bishop_checks | rook_checks | knight_checks | pawn_checks | king_checks) > 0;
    }

    void addBishopMoves(U64 allPieces, U64 friendlyPieces, const int bishopIndex) {
        U64 bishopAttacks = slider_attacks_.BishopAttacks(allPieces, bishopIndex);

        bishopAttacks &= ~friendlyPieces;
        addMovesFromAttackBitboard(bishopAttacks, bishopIndex, Board::BISHOP_INDEX);
    }

    void addKnightMoves(Board& board, const int knight_index, const int side) {
        U64 knight_attacks = knight_attacks_.Attacks(1<<knight_index);

        knight_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(knight_attacks, knight_index, Board::KNIGHT_INDEX);
    }

    void addPawnMoves(Board& board, const int pawn_index, const int side) {
        U64 pawn_moves = 0;

        switch (side) {
            case WHITE_:
              pawn_moves = pawn_moves_.WhiteMoves(
                            1L<<pawn_index,
                            ~board.occupancyBitboard());
              break;
            case BLACK_:
              pawn_moves = pawn_moves_.BlackMoves(
                            1L<<pawn_index,
                           ~board.occupancyBitboard());
        }
        addMovesFromAttackBitboard(pawn_moves, pawn_index, Board::PAWN_INDEX);
    }

    void addQueenMoves(Board& board, const int queen_index, const int side) {
        U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancyBitboard(),
                                                       queen_index);
        queen_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(queen_attacks, queen_index, Board::QUEEN_INDEX);
    }

    void addRookMoves(Board& board, const int rook_index, const int side) {
        U64 rook_attacks = slider_attacks_.RookAttacks(board.occupancyBitboard(),
                                                       rook_index);
        rook_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(rook_attacks, rook_index, Board::ROOK_INDEX);
    }

    void addMovesFromAttackBitboard(U64 bitboard, const int piece_index, const int piece_type) {
        while (bitboard > 0) {
            moveList.push_back(new Move(piece_index, Bit().Pop(bitboard), piece_type));
        }
    }

    constexpr static int WHITE_ = 0;
    constexpr static int BLACK_ = 1;

    Board previousBoard;

    KingAttacks king_attacks_;
    KnightAttacks knight_attacks_;
    PawnMoves pawn_moves_;
    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
