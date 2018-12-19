#include <iostream>

#include "bit.h"
#include "king_attacks.h"
#include "magic-bits/src/slider_attacks.h"
#include "pawn_moves.h"

using namespace std;

int main()
{
    PawnMoves pawnMoves;
    U64 board;
//    board = pawnMoves.Attacks(1L<<3|1L<<5, 12, 1);
//        while (board > 0) {
//            cout << Bit().Pop(board) << endl;
//        }
//        cout << endl;

    board = pawnMoves.WhiteAdvances(1L<<8, (1L<<16) | (1L<<24));
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = pawnMoves.BlackAdvances(1L<<48, (1L<<40) | (1L<<32));
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = pawnMoves.BlackMoves((1L<<48) | (1L<<43), (1L<<36) | (1L<<40));
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;
}
