#include <iostream>

#include "bit.h"
#include "move_generator.h"

int main()
{
    MoveGenerator* moveGenerator = new MoveGenerator();
    Board board;

    board.initialize();
    board.bishop_bitboard[0] = 1L<<0;
    board.bishop_bitboard[1] = 1L<<1;

    board.king_bitboard[0] = 1L<<7;
    board.king_bitboard[1] = 1L<<56;

    board.knight_bitboard[0] = 1L<<11;
    board.knight_bitboard[1] = 1L<<46;

    board.pawn_bitboard[0] = ((1L<<10)|(1L<<8));
    board.pawn_bitboard[1] = ((1L<<19)|(1L<<17));

    board.updateOccupancyBitboard();
    Bit::printBoard(board.occupancyBitboard());
    moveGenerator->generateAllMoves(board, 0);

    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin(); i != moveGenerator->moveList.end(); ++i) {
        std::cout << std::dec << (*i)->origin << "," << std::dec << (*i)->destination << std::endl;
    }
}
