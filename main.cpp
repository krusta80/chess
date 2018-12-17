#include <iostream>
#include "magic-bits/src/slider_attacks.h"
#include "bit.h"

using namespace std;

int main()
{
    U64 board = (7<<20) | 15;
    while (board > 0) {
        cout << Bit().Pop(board) << endl;
    }
    return 0;
}
