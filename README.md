# chess

As an avid chess enthusiast, I've always wanted to create my own chess engine.  I can think of no better way of motivating myself to diving into C++ than finally getting around to it.

This README will double as a sort of blog of my progress for now:

<b>12/16/18</b><br>
I just finished watching Home Alone with Julie, and I have to say that it still holds up as an all-time great Christmas movie.  While some of the humor doesn't quite still get the same belly laughs it did when I was a child, the heart-warming parts still deliver the goosebumps every time.  :)

That all said, let's dive into things, shall we?  I spent an hour or so looking into various methods of maintaining state for a chess game's components, and it seems as though using bitboards is the way to go.  For sliding pieces, I'll be leveraging magic bitboards (https://github.com/goutham/magic-bits) to generate moves and attack lists as quickly as possible.

I suppose that makes my first order of business handling similar logic for non-sliding pieces.

<b>8:31 PM</b><br>
After a bit of browsing, I think I'll try out Qt Creator as my C++ IDE of choice on Mac OS.  I'm currently waiting for the kits to download/install (almost 20GB worth!), so I'll spend this time thinking about knight, king, and pawn move generation.
