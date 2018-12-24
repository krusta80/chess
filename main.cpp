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

    board.updateOccupancyBitboard();
    moveGenerator->generateAllMoves(board, 0);

    for (std::vector<Move*>::iterator i = moveGenerator->moveList.begin(); i != moveGenerator->moveList.end(); ++i) {
        std::cout << (*i)->origin << "," << (*i)->destination << std::endl;
    }
}
