## Sudoku-Solver
Provides algorithm and tools to solve any sudoku game

---
The header and implementation file for the class SudokuGame is provided. An object of this class can perform the heavy-lifting of solving any given game, using a backtracking algorithm. <br>
### Constructors
---
There are two provided constructors, <code>SudokuGame()</code> and <code> SudokuGame(std::vector<std::vector<int>>)</code> <br>
The first generates a default sudoku board, filled with zeros to denote a blank number<br>
The second takes in an already existing 2d vector to represent the board. Each row is the inner vector.
Examples are as follows<br>
~~~
  SudokuGame sg;//invokes default constructor, board is filled with 0.
  std::vector<std::vector<int>> board = sg.GetBoard();
  for (const auto & row : board) {
    for (const auto & item : row) {
      std::cout << item;
    }
    std::cout << std::endl;
  }
~~~
<br>
The output is:<br>
~~~
000000000
000000000
000000000
000000000
000000000
000000000
000000000
000000000
000000000
~~~



