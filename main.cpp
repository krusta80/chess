#include <iostream>
#include "kingattacks.h"
#include "magic-bits/src/slider_attacks.h"
#include "bit.h"

using namespace std;

int main()
{
    KingAttacks kingAttacks;
    kingAttacks.Initialize();

    U64 board = kingAttacks.Attacks(0, 0);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = kingAttacks.Attacks(0, 4);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = kingAttacks.Attacks(0, 7);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = kingAttacks.Attacks(0, 56);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;

    board = kingAttacks.Attacks(0L, 63);
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    cout << endl;
    return 0;
}
