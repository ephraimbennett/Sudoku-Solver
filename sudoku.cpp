
#include "sudoku.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

void print(std::vector<std::vector<int>> v) {
    for (auto x : v) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << endl;
    }
}

SudokuGame::SudokuGame() {
    this->FillGrid();
}


std::vector<std::vector<int>>& SudokuGame::GetBoard() {
    return this->board_;
}

std::vector<int> SudokuGame::GetSubGroup(int row, int col) {
    vector<int> res;
    int hold;
    for (int i = 0; i < 9; i++) {
        hold = board_.at(row + i / 3).at(col + i % 3);
        res.push_back(hold);
    }
    return res;
}

std::vector<std::vector<int>> SudokuGame::GetSubGroups() {
    std::vector<std::vector<int>> res;
    for (int i = 0; i < 9; i++) {
        std::vector<int> sub = GetSubGroup(3 * (i / 3), (3 * i) % 9);
        res.push_back(sub);
    }
    return res;
}

bool SudokuGame::IsBoardValid() {
    //first, check each column
    vector<int> col;
    for (int i = 0; i < 9; i++) {
        for (auto & r : board_) {//fill each column with i at each row  
            col.push_back(r.at(i));
        }
        if (!IsSetValid(col)) {
            return false;
        }
        vector<int>().swap(col);
    }
    
    //next, check each row
    for (auto & row : board_) {
        if (!IsSetValid(row)) {
            return false;
        }
    }


    //next, check each subgroup
    vector<vector<int>> subs = GetSubGroups();
    for (const auto & subgroup : subs) {
        if (!IsSetValid(subgroup)) {
            return false;
        }
    }
    return true;
}

bool SudokuGame::IsSetValid(const vector<int> & v) {
    int nums[10] = {0};
    for (int x : v) {
        nums[x]++;
    }
    for (int x : nums) {
        if (x > 1) return false;
    }
    return true;
}

void SudokuGame::FillGrid(int fill) {
    //swap old memory with a blank vector
    vector<vector<int>>().swap(board_);

    //fill with all zeros
    for (int i = 0; i < 9; i++) {
        vector<int> v;
        for(int j = 0; j < 9; j++) {
            v.push_back(fill);
        }
        board_.push_back(v);
    }
}

void SudokuGame::FillGrid(bool step) {
    //swap old memory with a blank vector
    vector<vector<int>>().swap(board_);

    //fill with numbers counting up from one
    for (int i = 0; i < 9; i++) {
        vector<int> v;
        for(int j = 0; j < 9; j++) {
            v.push_back(j + (i * 9) + 1);
        }
        board_.push_back(v);
    }
}

bool SudokuGame::IsNumUnique(vector<int> v, int n) {
    cout << "Checking: ";
    for (auto x : v) {
        cout << x;
    }
    cout << ". For: " << n << endl;
    int nums[10] = {0};
    for (int x : v) {
        if(x == 0) continue;
        nums[x]++;
    }
    if (nums[n] > 0) return false;
    return true;
}

bool SudokuGame::IsUpdateValid(int row, int col, int num) {
    //first check subgroup
    int subRow = (row / 3) * 3;
    int subCol = (col / 3) * 3;
    if (!IsNumUnique(GetSubGroup(subRow, subCol), num)) return false;

    //next, check row
    if (!IsNumUnique(board_.at(row), num)) return false;

    //finally, check column
    vector<int> column;
    for (const auto & r : board_) {
        column.push_back(r.at(col));
    }
    if(!IsNumUnique(column, num)) return false;

    return true;
}

bool SudokuGame::SolveNaive(int row, int col) {
    if (row == 8 && col == 9) {//if last case return true
        return true;
    }

    if (col == 9) {//if column has grown past actual column size, reset and pass to next row
        cout << "PASS" << endl;
        row++;
        col = 0;
    }

    //skip the indices where there is already a number placed
    if (board_.at(row).at(col) != 0) {
        return SolveNaive(row, col + 1);
    }

    //loop through and test each potential number
    for (int i = 1; i < 10; i++) {
        if (IsUpdateValid(row, col, i)) {//if this combo does work, now check the next
            board_.at(row).at(col) = i;
            if (SolveNaive(row, col + 1)) {//if the next one also work, return true
                return true;
            }
            board_.at(row).at(col) = 0;//if i is not the answer, then reset number to empty(zero) value to re-try with
            //a new value for i.
        }
    }
    
    //if none of the test cases worked, return false
    return false;
}

bool SudokuGame::SolveBacktracking(int row, int col) {
    if (row == 8 && col == 9) return true;

    if (col >= 9) {
        row++;
        col = 0;
    }

    if (board_.at(row).at(col) == 0) {
        for (int i = 1; i < 10; i++) {
            if (IsUpdateValid(row, col, i)) {
                board_.at(row).at(col) = i;
                if (SolveBacktracking(row, col + 1)) {
                    return true;
                }
                board_.at(row).at(col) = 0;
            }
        }
        return false;
    } else {
        return SolveBacktracking(row, col + 1);
    }
}