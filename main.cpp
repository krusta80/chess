#include <iostream>

#include "bit.h"
#include "board.h"
#include "move_generator.h"

int main()
{
    MoveGenerator* moveGenerator = new MoveGenerator();
    Board board;

    board.initialize();
    board.pieces[Board::BISHOP_INDEX][0] = 1L<<0;
    board.pieces[Board::BISHOP_INDEX][1] = 1L<<37;

    board.pieces[Board::KING_INDEX][0] = 1L<<4;
    board.pieces[Board::KING_INDEX][1] = 1L<<24; // a4

    board.pieces[Board::KNIGHT_INDEX][0] = 1L<<11;
    board.pieces[Board::KNIGHT_INDEX][1] = 1L<<46;

    board.pieces[Board::PAWN_INDEX][0] = ((1L<<25)|(1L<<28));
    board.pieces[Board::PAWN_INDEX][1] = (1L<<26);
    board.enPassantTarget = 1L<<25;
    board.enPassantDestination = 1L<<17;

    board.pieces[Board::ROOK_INDEX][0] = 1L<<27;  // d4

    board.updateOccupancyBitboard();
    Bit::printBoard(board.sideBitboard(0));
    std::cout << std::endl;
    Bit::printBoard(board.sideBitboard(1));
    std::cout << std::endl;
    moveGenerator->generateAllMoves(board, 1);

    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin(); i != moveGenerator->moveList.end(); ++i) {
        std::cout << std::dec << (*i)->origin << "," << std::dec << (*i)->destination << std::endl;
    }
}
