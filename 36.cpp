/**
 * 36. Valid Sudoku
 * https://leetcode.com/problems/valid-sudoku/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>

using namespace std;


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>> temporaryRowsSet (9, unordered_set<char>({}));
        vector<unordered_set<char>> temporaryColumnsSet (9, unordered_set<char>({}));
        vector<unordered_set<char>> temporarySubBoxesSet (9, unordered_set<char>({}));
        
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentNumber = board.at(rowIndex).at(columnIndex);
                if (currentNumber == '.') {
                    continue;
                }
                
                //1. Rows.
                if (temporaryRowsSet.at(rowIndex).find(currentNumber) == temporaryRowsSet.at(rowIndex).end()) {
                    //Not found in row.
                    temporaryRowsSet.at(rowIndex).insert(currentNumber);
                } else {
                    return false;
                }
                
                //2. Columns.
                if (temporaryColumnsSet.at(columnIndex).find(currentNumber) == temporaryColumnsSet.at(columnIndex).end()) {
                    //Not found in column.
                    temporaryColumnsSet.at(columnIndex).insert(currentNumber);
                } else {
                    return false;
                }
                
                //3. Sub-boxes.
                //1st quadrant coordinates.
                int currentSubBoxIndex = (rowIndex / 3) * 3 + (columnIndex / 3);
                if (temporarySubBoxesSet.at(currentSubBoxIndex).find(currentNumber) == temporarySubBoxesSet.at(currentSubBoxIndex).end()) {
                    //Not found in sub box.
                    temporarySubBoxesSet.at(currentSubBoxIndex).insert(currentNumber);
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    vector<vector<char>> testInput = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << solutionInstance->isValidSudoku(testInput) << endl;
    
    return 0;
}
