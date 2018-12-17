# chess

As an avid chess enthusiast, I've always wanted to create my own chess engine.  I can think of no better way of motivating myself to diving into C++ than finally getting around to it.

This README will double as a sort of blog of my progress for now:

<b>12/16/18</b><br>
I just finished watching Home Alone with Julie, and I have to say that it still holds up as an all-time great Christmas movie.  While some of the humor doesn't quite still get the same belly laughs it did when I was a child, the heart-warming parts still deliver the goosebumps every time.  :)

That all said, let's dive into things, shall we?  I spent an hour or so looking into various methods of maintaining state for a chess game's components, and it seems as though using bitboards is the way to go.  For sliding pieces, I'll be leveraging magic bitboards (https://github.com/goutham/magic-bits) to generate moves and attack lists as quickly as possible.

I suppose that makes my first order of business handling similar logic for non-sliding pieces.

<b>12/17/18</b><br>
It's almost 1am, and I'm ready for bed.  That said, I'm going to bed pretty satisfied, since I've found a way to rapidly generate a move list from an attack bitboard.  (https://www.chessprogramming.org/BitScan#DeBruijnMultiplation)
