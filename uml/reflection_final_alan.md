# Introduction

This project builds on a previous chess game I created in C++. That earlier version lacked interaction, menus, and sophisticated AI. For this project, I aimed to enhance the user interface and implement a robust AI using minimax.

# Game concept

Since creating a board game was suggested, our team decided to design an entirely new concept. The board game bears some resemblance to chess. However, players select their pieces before the game begins, each with unique properties such as nobility and different movement abilities. With a limited budget, players must strategically choose their pieces and place them on their side of the board. The game lasts for a set number of turns, and the winner is the player with the most valuable pieces remaining. It’s an interesting concept, simple to explain yet potentially deep in strategy, and we were successful in making a prototype and even had a tournament in class where people tried the game and played it. It was engaging to observe.

The most innovative aspects of our game is that the player gets to choose their hand of pieces, place them on the board, and try to make their most noble pieces survive. There is a trade off, where noble pieces are expensive but often a little helpless, while pieces with less nobility are more capable put worth less in the long run.

# Data Structures and their Application

I was responsible for implementing Dijkstra's algorithm for legal moves, A-star for animation, and Minimax for AI behavior. My teammates worked on menus, legal moves, game pieces, settings, and the replay system.

We have implemented Linked List, Dynamic Array, Stack and Queue, and a Tree for the game.

The Linked List is used to hold the cards and player pieces, which move from the shop to the players hand, and then to the game board. The game board is constructed with a linked list too, where the tiles can hold pieces.

We used a dynamic array to hold all the legal moves available to a player during the player's turn. The AI uses this to figure out what move to make, and we use it to visualise the possible moves on the game board.

We use a stack in the menus and in the shop. The menu system is based on a stack to allow the user to go backwards in the menus, without us coding a complicated system for it. In the shop, the cards available to the player are put into a stack before they are put into the store. The wildcard gamble card takes from the stack, and it is also used to refill the shop when the users have chosen all the cards available, or presses the restock shop button.

We use a queue to implement Dijkstra's algorithm for calculating legal moves. This algorithm is employed by most game pieces to determine their movement range while accounting for obstacles. However, special cases such as flying pieces (e.g., the Stallion, Prince, Princess, Queen, and Rogue) utilize simpler movement patterns, bypassing this calculation.

- **Linked List**: Manages game cards, player pieces, and the board.  
- **Dynamic Array**: Tracks all legal moves available during a player's turn.  
- **Stack**: Powers the menu system and card shop mechanics.  
- **Queue**: Implements Dijkstra’s algorithm to calculate legal moves.  
- **Tree**: Used for A-star and minimax algorithms.  

# Algorithms and Their Justifications

Unlike its typical application for finding the shortest path, we use Dijkstra to identify all reachable tiles within a range. This was ideal for game pieces that navigate around obstacles, such as the Monster and Deserter

We use a tree for A-star and for the Minimax algorithm. Minimax simulates several future turns, evaluating each move based on the difference in total nobility points. It chooses the move leading to the most advantageous outcome for the current player. One of the biggest challenges was ensuring the minimax algorithm performed efficiently within the constraints of the game. Debugging and iterating on the algorithm taught me a great deal about performance optimization and strategic problem-solving. Performance hindered the depth of the tree, when working correctly minimax is a good fit for discrete games such as board games. I want to work more on it in the future.

We originally had an AI which chose random moves, or captures if possible. We wanted to make the AI more fun to play against, and had read about minimax from Ron Penton's book Data Structures for Games Programmers. Since it works well for turn based games, and it uses a tree, it seemed like an opportunity we could not turn down. Also, the website chessengines.org had a guide for writing strong chess AI, which we wanted to implement.

It seems the minimax tree grows really big really fast. It is possible improving finding legal moves, making that process faster, could help the algorithm. Alternatively, debugging the tree and finding ways to optimize growing it could help make the game have better performance, deeper AI and more interesting gameplay. It is also possible to put the AI on its own thread, and utilize multithreading to have the computer calculate moves in the background without freezing the game.

The implementations for Stack, Queue and Linked List can be found in solid/source/core/containers. The tree can be found in app/source/tree.h. The exe file for the game can be found in Windows/Kings.exe

# Contributions and Reflections

I worked on Dijkstra (find legal moves), A-Star (Animation for the pieces) and Minimax (AI). My teammates used a stack and linked list to implement menus, helped make the legal moves code, designed and implemented several of the game pieces (including special logic specific to the pieces), settings menus, and the replay system.

Minimax should result in really interesting and fun AI. Games become fun when they are a challenge. AI is an important, if not the most important component to make a game fun.

A-Star shines when the start and end locations are known, such as during animation. That is why we used A-Star first when the user has made a move, which involves moving a piece from one tile to another.

# Summary

This project not only improved gameplay mechanics but also deepened my understanding of algorithms and their practical applications.

Overall, our project achieved its goals of enhancing interactivity and AI. The implementation of data structures and algorithms like Dijkstra, A-star, and Minimax provided a strong foundation for gameplay. In future iterations, we could implement multithreading to compute AI moves in parallel, reducing gameplay interruptions. We aim to further optimize performance and experiment with even more advanced AI strategies to make games more engaging and challenging.

# Sources

We have used monocraft font from IdreesInc: https://github.com/IdreesInc/Monocraft

We used Suno to generate some music for the game. The music is an experimental feature which was not fully implemented in the final build.

We used Dalle-E to generate the background for the game.

For solid, read solid/NOTICE for the third party libraries used in the engine.
