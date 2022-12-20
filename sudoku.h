#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class SudokuGame {
    private:
        
    public: 
        std::vector<std::vector<int>> board_;
        //constructors
        SudokuGame();
        SudokuGame(std::vector<std::vector<int>> b) : board_(b){};

        std::vector<std::vector<int>>& GetBoard();//returns a reference of the board vector

        bool IsBoardValid();//returns true if sudoku is properly solved
        bool IsSetValid(const std::vector<int> &);//takes a vector and returns true if it only contains 1-9 once
        bool IsUpdateValid(int, int , int);//takes row, col, and num and sees if you can place num there
        bool IsNumUnique(std::vector<int>, int);//takes a vector and num and returns true if no repeats of num

        void FillGrid(int fill = 0);//fills the grid with whatever integer you want
        void FillGrid(bool);//fills with increasing increments from one, left to right first, top bottom

        std::vector<std::vector<int>> GetSubGroups();//returns all the subgroups as vectors
        std::vector<int> GetSubGroup(int, int);//returns the subgroup if given a top left index of one

        bool SolveNaive(int, int);//solve teh sudoku game recursively
        bool SolveBacktracking(int, int);//solves recursively using a backtracking algorithm
};
