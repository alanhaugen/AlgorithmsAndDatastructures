# Journal

## December 1. 2024

Packaged the game. Fixed bugs in replay. Ready to hand it in.

## November 24. 2024

New graphics and bug fixes. Implemented minimax. Can only go to depth 2 before it gets too slow to run. Seems dumber than the AI which simply did random moves and captures, but it is more fun to play against. Will need to work more on it to make it more fun.

## November 17. 2024

This week was spent on making all the menu buttons work and refactoring the code base, particularly autochess.cpp We use a finite state machine to keep track of states. Playing, placing, shopping and done. I read one can use a graph as a fsm, and it is used often for AI. We started working on animation code and wrote a new game state, Animate. The animation interpolates the pieces from the start to the end position. We intend to use A-star here.

## November 15. 2024

A-star was implemented in a day. We had some really funny weird bugs, but in the evening they were found and fixed. The game is much more fun and easier to understand when the pieces animate and move along their path across the board.

## November 7. 2024

We have balanced the monster by making it only move perpendicularly. And then we added that deserter can only go diagonally. Both use Dijkstra to find legal moves, just on different planes. Added a back button. Fixed 2-player MoveTotal. Bendik play tested against Lisa during the presentation, and liked the game so much that he challenged me to a round afterwards. So it seems like other people like the game too.

## November 3. 2024

Today the entire team assembled together and worked in finishing the last moves for the final pieces in the game. The resolution of the game was changed this week to make fullscreen work better and to accommodate more information about the pieces in the ship and on the board during the shipping and playing phases. Work on improving the shop and getting replays working was done, the game has become easier to read by having more of the game information presented to the player.

## October 31. 2024

Coords were added to the game board. The banners on the game board now has the nobility numbers. The amount of turns left is now presented visually. Plans were made for the presentation next week. A list of previous moves was started on being implemented.

## October 30. 2024

Paul has joined the team. We worked together to get him up to speed on development.

## October 29. 2024

We made it so you can only place game pieces on your side of the game board. We also made it so the shop consists of a linkedlist of 52 cards which then are randomly picked from to fill up a stack. This way, the game will always have the same amount of kings, queens, princes, princesses etc. but they will be randomly available in the shop and the random cards deck.

## October 28. 2024

Improved performance by compiling shaders only when there is a unique program.

## October 27. 2024

Made game use linkedlist instead of array to keep track of drawables. Made game work on linux.

## October 24. 2024

Presented the game.

Started working on the replay scene and the user interface for selecting a replay.

## October 19. 2024

Added lots of new graphics and quality of life improvements. Very pleased with the additions. Also, the random card is added.

## October 16. 2024

Today some work on fullscreen support for the game was added. It still needs some more work but it is satisfying to have it. It does not contribute to having actual structures and algorithms but it is improving the overall game and the technology behind it.

## October 13. 2024

Player vs player has been implemented. A new typeface taken from an open source font has been added, it looks a lot better than the old one. The font is called monocraft. There is a lot of polish left, but an initial prototype is complete.

## October 9. 2024

We had a team meeting and met up at Alan`s home. The first iteration of the game is now complete. One can select to play from the main menu, select pieces from the shop, place them out on the board, and watch the computer duke it out. It is quite fun to look at. Pressing escape takes you back to the main menu. Next, we should add replays, animation, better sprites, music, fullscreen and window scale support. Then the rest of the time can be focused on AI, implementing the minimax algorithm and tree and make a smart AI. We can also make single-player scenarios, and the ability to take control of the game in the third playing phase. Great progress so far.

## October 6. 2024

This week, the game board was developed further. One can place out pieces on the board. The shop is partially implemented and work on moves for each piece has been started. Warnings from the OpenGL renderer were fixed. A crash bug on Windows was found for nvidia cards when the engine loads textures with a debugger attached to the program. Work has begun on fixing this bug. The book Game Coding Complete, fourth edition, has a section on bugs. Bugs go from AA, A, B to C (McShaffry and Graham p. 853). The nvidia bug is a class C bug, it will not affect the final product. Tomorrow marks the first month of development, the project started on September 7. The first week of development entailed making a detailed UML-schema for the game. This resulted in excellent feedback from the teacher. ``This is a very impressive UML diagram, not just for the game, but for the engine as well, excellent work!`` In the second week, work on the actual code and game started. The main menus were developed first, with the mouse controlling navigation. A mockup of the board was made and could be accessed by pressing play game through the menu system. In the third week, the menus were refined. The first datastructure application was implemented. The menus were redesigned to use a Stack, which allows for many levels of menus and an incredibly easy implementation. It is trivial to add new menu screens to the game, and to nest menus. The idea of using a Stack to let the player navigate menus (were the top of the stack is rendered, while pushing a button pushes a new menu to the Stack) was an example taken from a book called Data Structures for Games Programmers (Penton p. 199). This week, actual game mechanics were implemented with the board, shop, and ability to place pieces added. Next week, implementing legal moves and making a dead-simple AI is planned. The plan is to also implement all the game`s phases correctly, with the shopping phase, putting out pieces phase and battling phase implemented.

