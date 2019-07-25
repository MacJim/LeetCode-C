/**
 * 37. Sudoku Solver
 * https://leetcode.com/problems/sudoku-solver/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <bitset>
#include <memory>

using namespace std;


//struct Cell {
//    char value;
//};

class Solution {
public:
    void solveSudoku1(vector<vector<char>>& board) {
        //1. Calculate constraints.
        vector<unordered_set<char>> existingNumbersInRows (9, unordered_set<char>({}));
        vector<unordered_set<char>> existingNumbersInColumns (9, unordered_set<char>({}));
        vector<unordered_set<char>> existingNumbersInSubBoxes (9, unordered_set<char>({}));
        
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentNumber = board.at(rowIndex).at(columnIndex);
                if (currentNumber == '.') {
                    continue;
                }
                
                existingNumbersInRows.at(rowIndex).insert(currentNumber);
                existingNumbersInColumns.at(columnIndex).insert(currentNumber);
                
                //1st quadrant coordinates.
                int currentSubBoxIndex = (rowIndex / 3) * 3 + (columnIndex / 3);
                existingNumbersInSubBoxes.at(currentSubBoxIndex).insert(currentNumber);
            }
        }
        
        //2. Brute force.
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentNumber = board.at(rowIndex).at(columnIndex);
                if (currentNumber == '.') {
                    for (int testNumber = 0; testNumber < 9; testNumber += 1) {
                        
                    }
                }
            }
        }
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentNumber = board.at(rowIndex).at(columnIndex);
                if (currentNumber == '.') {
                    
                }
            }
        }
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<vector<char>> testCase1 = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    solutionInstance->solveSudoku(testCase1);
    for (auto aRow: testCase1) {
        for (char aCharacter: aRow) {
            cout << aCharacter << " ";
        }
        cout << endl;
    }
    
    return 0;
}
