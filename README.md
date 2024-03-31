# SuperTicTacToe

```txt
 ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____
/ ___)/ )( \(  _ \(  __)(  _ \  (_  _)(  )/ __)___(_  _)/  \  / __)___(_  _)/  \(  __)
\___ \) \/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \( (__(___) )( (    )) _)
(____/\____/(__)  (____)(__\_)   (__) (__)\___)    (__)\_/\_/ \___)    (__) \__/(____)
```

> By @powan5(Discord)

### We all know the classic game of Tic-Tac-Toe we all play when bored in class, or just to have a little fun. But what if we made it a little more interesting ?

- #### Initial Placement:
The game begins with an empty larger 3x3 grid. The smaller grids within the larger grid are also empty.

- #### First Move:
The first player can make their move in any of the smaller 3x3 grids. The position they choose determines the smaller grid in which the second player must make their next move.

- #### Subsequent Moves:
After the initial move, each subsequent move must be made in the smaller grid corresponding to the cell of the previous move. For example, if a move is made in the top-right cell of a smaller grid, the next move must be made in the top-right smaller grid.

- #### Forced Grid:
If a player is directed to a smaller grid that has already been won they can choose any open cell on the board.

- #### Drawn grid:
If a player plays in a cell, filling the last cell of the smaller grid in a draw, the smaller grid will be reset to empty and the next player's move can be made in any of the smaller grids. This is made to prevent a maximum draws in the bigger grid and was overwhole a better experience when testing.

- #### Winning a Smaller Grid:
To win a smaller grid, a player must get three in a row (horizontally, vertically, or diagonally) within that specific smaller grid. Once a smaller grid is won by a player, that player's symbol is placed in the corresponding cell of the larger grid.

- #### Winning the Game:
To win the overall game, a player must win three smaller grids in a row (horizontally, vertically, or diagonally) on the larger 3x3 grid. The game ends when one player achieves this or if the entire larger grid is filled without a winner, resulting in a draw.

Players need to think strategically, not only focusing on winning individual smaller grids but also considering the overall larger grid. A move in one smaller grid not only affects the outcome of that grid but also influences the next forced move for the opponent.

```
The grid's presentation:
+-------------------+-------------------+-------------------+
| A   1   2   3   A | B   1   2   3   B | C   1   2   3   C |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 1 | . | . | . | 1 | 1 | . | . | . | 1 | 1 | . | . | . | 1 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 2 | . | . | . | 2 | 2 | . | . | . | 2 | 2 | . | . | . | 2 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 3 | . | . | . | 3 | 3 | . | . | . | 3 | 3 | . | . | . | 3 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| A   1   2   3   A | B   1   2   3   B | C   1   2   3   C |
+-------------------+-------------------+-------------------+
| D   1   2   3   D | E   1   2   3   E | F   1   2   3   F |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 1 | . | . | . | 1 | 1 | . | . | . | 1 | 1 | . | . | . | 1 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 2 | . | . | . | 2 | 2 | . | . | . | 2 | 2 | . | . | . | 2 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 3 | . | . | . | 3 | 3 | . | . | . | 3 | 3 | . | . | . | 3 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| D   1   2   3   D | E   1   2   3   E | F   1   2   3   F |
+-------------------+-------------------+-------------------+
| G   1   2   3   G | H   1   2   3   H | I   1   2   3   I |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 1 | . | . | . | 1 | 1 | . | . | . | 1 | 1 | . | . | . | 1 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 2 | . | . | . | 2 | 2 | . | . | . | 2 | 2 | . | . | . | 2 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| 3 | . | . | . | 3 | 3 | . | . | . | 3 | 3 | . | . | . | 3 |
|   +---+---+---+   |   +---+---+---+   |   +---+---+---+   |
| G   1   2   3   G | H   1   2   3   H | I   1   2   3   I |
+-------------------+-------------------+-------------------+
```