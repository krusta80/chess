#include <iostream>

#include "bit.h"
#include "king_attacks.h"

using namespace std;

int main()
{
    KingAttacks kingAttacks;
    U64 board;

    kingAttacks.Initialize();
//    board = pawnMoves.Attacks(1L<<3|1L<<5, 12, 1);
//        while (board > 0) {
//            cout << Bit().Pop(board) << endl;
//        }
//        cout << endl;

    board = kingAttacks.Attacks(1L<<48, 43);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;
}
