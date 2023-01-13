# Geese-Spotter-Game-CPlusPlus

What is this program about?
- This is a simplified version of the classic minesweeper game.
- The program asks user the dimension of the "field" (game board of minesweeper) and the number of geese (landmines in minesweeper).
- The program then creates a 1-D array storing char. Using the bitwise operators:
    - The 4 least significant bits represent the number of geese around the coresponding block in the field; 
    - The 5th bit tells whether the block is marked. 1 - marked, 0 - not marked.
    - The 6th bit tells whether the block is hidden. 1- hidden, 0 - revealed.
- Once the user marked all the blocks that contains a geese, or reveal all the blocks that don't contain a geese, the user wins the game.
- Otherwise, the user loses the game and the program will start a new game.


My contribution to this project:
- I am responsible of writing the functions including: createBoard, hideBoard, cleanBoard, printBoard, mark, isGameWon, computeNeighbors, reveal.
- The parts that I am responsible for are in the file geesespotter.cpp
- The other functions are provided by the class instructor.
