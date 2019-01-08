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
      CASTLE_KINGSIDE_.push_back(new Move(4, 6, 1, Move::CASTLE_KINGSIDE));
      CASTLE_KINGSIDE_.push_back(new Move(60, 62, 1, Move::CASTLE_KINGSIDE));
      CASTLE_QUEENSIDE_.push_back(new Move(4, 2, 1, Move::CASTLE_QUEENSIDE));
      CASTLE_QUEENSIDE_.push_back(new Move(60, 58, 1, Move::CASTLE_QUEENSIDE));
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

    bool isInCheck(Board& board, const int side) {
        return isAttacked(board, board.getKingBitboard(side), side);
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

        addMovesFromAttackBitboard(kingAttacks, kingIndex, Board::KING_INDEX, Move::STANDARD);
    }

    void addCastlingIfLegal(Board& board, const int side) {
        addKingsideCastlingIfLegal(board, side);
        addQueensideCastlingIfLegal(board, side);
    }

    void addKingsideCastlingIfLegal(Board& board, const int side) {
        if (board.never_castle_kingside[side]) {
            return;
        }
        if ((board.occupancyBitboard() & Board::BACK_RANK_FG[side]) > 0) {
            return;
        }
        if (isAttacked(board, Board::BACK_RANK_E[side], side) ||
                isAttacked(board, Board::BACK_RANK_F[side], side) ||
                isAttacked(board, Board::BACK_RANK_G[side], side)) {
            return;
        }
        moveList.push_back(CASTLE_KINGSIDE_.at(side));
    }

    void addQueensideCastlingIfLegal(Board& board, const int side) {
        if (board.never_castle_queenside[side]) {
            return;
        }
        if ((board.occupancyBitboard() & Board::BACK_RANK_BCD[side]) > 0) {
            return;
        }
        if (isAttacked(board, Board::BACK_RANK_C[side], side) ||
                isAttacked(board, Board::BACK_RANK_D[side], side) ||
                isAttacked(board, Board::BACK_RANK_E[side], side)) {
            return;
        }
        moveList.push_back(CASTLE_QUEENSIDE_.at(side));
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
             addEnPassantMoves(board, __builtin_ffsll(bitboard)-1, side);
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
        untryMove(board, side);
        return isIllegal;
    }

    void tryMove(Move* move, Board& board, const int side) {
        for (int i = 0; i < 6; i++) {
            previousBoard.pieces[i][side] = board.pieces[i][side];
            previousBoard.pieces[i][1-side] = board.pieces[i][1-side];
        }
        board.makeMove(move, side, /* tryOnly */ true);
    }

    void untryMove(Board& board, const int side) {
        for (int i = 0; i < 6; i++) {
            board.pieces[i][side] = previousBoard.pieces[i][side];
            board.pieces[i][1-side] = previousBoard.pieces[i][1-side];
        }
        board.updateOccupancyBitboard();
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
        U64 king_checks = king_attacks_.Attacks(board.getKingBitboard(side), index);

        bishop_checks &= (board.getBishopBitboard(1-side) | board.getQueenBitboard(1-side));
        king_checks &= (board.getKingBitboard(1-side));
        knight_checks &= (board.getKnightBitboard(1-side));
        rook_checks &= (board.getRookBitboard(1-side) | board.getQueenBitboard(1-side));
        return (bishop_checks | rook_checks | knight_checks | pawn_checks | king_checks) > 0;
    }

    void addBishopMoves(U64 allPieces, U64 friendlyPieces, const int bishopIndex) {
        U64 bishopAttacks = slider_attacks_.BishopAttacks(allPieces, bishopIndex);

        bishopAttacks &= ~friendlyPieces;
        addMovesFromAttackBitboard(bishopAttacks, bishopIndex, Board::BISHOP_INDEX, Move::STANDARD);
    }

    void addKnightMoves(Board& board, const int knight_index, const int side) {
        U64 knight_attacks = knight_attacks_.Attacks(1L<<knight_index);

        knight_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(knight_attacks, knight_index, Board::KNIGHT_INDEX, Move::STANDARD);
    }

    void addPawnMoves(Board& board, const int pawn_index, const int side) {
        U64 pawn_moves = 0;

        switch (side) {
            case WHITE_:
              pawn_moves = pawn_moves_.WhiteMoves(
                            1L<<pawn_index,
                            ~board.sideBitboard(1-side));
              break;
            case BLACK_:
              pawn_moves = pawn_moves_.BlackMoves(
                            1L<<pawn_index,
                            ~board.sideBitboard(1-side));
        }
        addMovesFromAttackBitboard(pawn_moves, pawn_index, Board::PAWN_INDEX, Move::STANDARD);
    }

    void addEnPassantMoves(Board& board, const int pawn_index, const int side) {
        U64 pawn_moves = 0;

        switch (side) {
            case WHITE_:
              pawn_moves = pawn_moves_.WhiteAttacks(
                            1L<<pawn_index,
                            ~board.enPassantDestination);
              break;
            case BLACK_:
              pawn_moves = pawn_moves_.BlackAttacks(
                            1L<<pawn_index,
                            ~board.enPassantDestination);
        }
        addMovesFromAttackBitboard(pawn_moves, pawn_index, Board::PAWN_INDEX, Move::EN_PASSANT);
    }

    void addQueenMoves(Board& board, const int queen_index, const int side) {
        U64 queen_attacks = slider_attacks_.QueenAttacks(board.occupancyBitboard(),
                                                       queen_index);
        queen_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(queen_attacks, queen_index, Board::QUEEN_INDEX, Move::STANDARD);
    }

    void addRookMoves(Board& board, const int rook_index, const int side) {
        U64 rook_attacks = slider_attacks_.RookAttacks(board.occupancyBitboard(),
                                                       rook_index);
        rook_attacks &= ~board.sideBitboard(side);
        addMovesFromAttackBitboard(rook_attacks, rook_index, Board::ROOK_INDEX, Move::STANDARD);
    }

    void addMovesFromAttackBitboard(U64 bitboard,
                                    const int pieceIndex,
                                    const int pieceType,
                                    const int moveType) {
        int destinationIndex;
        while (bitboard > 0) {
            destinationIndex = Bit().Pop(bitboard);
            if (pieceType == Board::PAWN_INDEX &&
                    (destinationIndex < 8 || destinationIndex > 55)) {
                addPromotionsToMoveList(pieceIndex, destinationIndex);
            } else {
                moveList.push_back(new Move(pieceIndex, destinationIndex, pieceType, moveType));
            }
        }
    }

    void addPromotionsToMoveList(const int origin, const int dest) {
        moveList.push_back(new Move(origin, dest, Board::PAWN_INDEX, Move::PROMOTE_TO_QUEEN));
        moveList.push_back(new Move(origin, dest, Board::PAWN_INDEX, Move::PROMOTE_TO_ROOK));
        moveList.push_back(new Move(origin, dest, Board::PAWN_INDEX, Move::PROMOTE_TO_BISHOP));
        moveList.push_back(new Move(origin, dest, Board::PAWN_INDEX, Move::PROMOTE_TO_KNIGHT));
    }

    constexpr static int WHITE_ = 0;
    constexpr static int BLACK_ = 1;

    std::vector<Move*> CASTLE_KINGSIDE_;
    std::vector<Move*> CASTLE_QUEENSIDE_;

    Board previousBoard;

    KingAttacks king_attacks_;
    KnightAttacks knight_attacks_;
    PawnMoves pawn_moves_;
    SliderAttacks slider_attacks_;
};

#endif // MOVE_GENERATOR_H
