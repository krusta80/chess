#include <iostream>

#include "bit.h"
#include "king_attacks.h"
#include "magic-bits/src/slider_attacks.h"
#include "knight_attacks.h"

using namespace std;

int main()
{
    KnightAttacks knightAttacks;
    U64 board;
//    board = pawnMoves.Attacks(1L<<3|1L<<5, 12, 1);
//        while (board > 0) {
//            cout << Bit().Pop(board) << endl;
//        }
//        cout << endl;

    board = knightAttacks.Attacks((1L<<48) | (1L<<43));
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;
}
