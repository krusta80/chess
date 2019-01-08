#include "board.h"
#include "move.h"

void Move::printMove(){
   std::cout << getMoveNotation() << std::endl;
}

char* Move::getMoveNotation() {
    char* move = new char[5];

    move[0] = Board::PIECE_NOTATION[piece];
    strcat(move, Board::SQUARE_LABELS[destination]);

    switch (specialMove) {
        case PROMOTE_TO_QUEEN:
            strcat(move, "=Q");
            break;
        case PROMOTE_TO_ROOK:
            strcat(move, "=R");
            break;
        case PROMOTE_TO_BISHOP:
            strcat(move, "=B");
            break;
        case PROMOTE_TO_KNIGHT:
            strcat(move, "=N");
            break;
    }
    return move;
}
