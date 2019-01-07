#include "board.h"
#include "move.h"

void Move::printMove(){
   std::cout << Board::PIECE_NOTATION[piece] << Board::SQUARE_LABELS[destination];
   switch (specialMove) {
       case PROMOTE_TO_QUEEN:
           std::cout << " (Q)";
           break;
       case PROMOTE_TO_ROOK:
           std::cout << " (R)";
           break;
       case PROMOTE_TO_BISHOP:
           std::cout << " (B)";
           break;
       case PROMOTE_TO_KNIGHT:
           std::cout << " (N)";
           break;
   }
   std::cout << std::endl;
}
