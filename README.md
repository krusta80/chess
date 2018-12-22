# chess

As an avid chess enthusiast, I've always wanted to create my own chess engine.  I can think of no better way of motivating myself to diving into C++ than finally getting around to it.

This README will double as a sort of blog of my progress for now:

<b>12/16/18</b><br>
I just finished watching Home Alone with Julie, and I have to say that it still holds up as an all-time great Christmas movie.  While some of the humor doesn't quite still get the same belly laughs it did when I was a child, the heart-warming parts still deliver the goosebumps every time.  :)

That all said, let's dive into things, shall we?  I spent an hour or so looking into various methods of maintaining state for a chess game's components, and it seems as though using bitboards is the way to go.  For sliding pieces, I'll be leveraging magic bitboards (https://github.com/goutham/magic-bits) to generate moves and attack lists as quickly as possible.

I suppose that makes my first order of business handling similar logic for non-sliding pieces.

<b>12/17/18</b><br>
It's almost 1am, and I'm ready for bed.  That said, I'm going to bed pretty satisfied, since I've found a way to rapidly generate a move list from an attack bitboard.  (https://www.chessprogramming.org/BitScan#DeBruijnMultiplation)

<b>12/21/18</b><br>
It's been a busy week, but I've managed to spend some time here and there digging a bit more deeply into bitboards and how to best leverage them.  I'm finding myself striving for the "perfect" approach and making little to no tangible progress, however.

I think it's important to take an iterative approach at this point and accept that improvements will be inevitable regardless.  I think my knowledge base is also at the point now where following my own design and ideas will prove the most rewarding course of action.  After all, if I were truly obsessed with creating the world's best chess engine, I'd simply use Stockfish (or Lc0) as my starting point.  ;)
