/**
 * 37. Sudoku Solver
 * https://leetcode.com/problems/sudoku-solver/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <tuple>
#include <bitset>
#include <memory>

using namespace std;


#pragma mark - Helpers
void printBoard(const vector<vector<char>>& board) {
    cout << "-----------------------" << endl;
    
    for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
        auto currentRow = board.at(rowIndex);
        
        for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
            char currentCharacter = currentRow.at(columnIndex);
            cout << currentCharacter;
            
            if (columnIndex % 3 == 2) {
                cout << " | ";
            } else {
                cout << " ";
            }
        }
        
        if (rowIndex % 3 == 2) {
            cout << "\n-----------------------" << endl;
        } else {
            cout << endl;
        }
    }
}


#pragma mark - Solution class
class Solution {
public:
    //MARK: This is question 36 and is used to validate the Sudoku.
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
    
    
public:
    //MARK: 1. Brute force (not used).
    void solveSudoku1(vector<vector<char>>& board) {
        //Assume: board.at(row).at(column)
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
        
        //2. Backtrack.
        ///rowIndex, columnIndex, possible characters.
        stack<tuple<int, int, unordered_set<char>>> backtrackStack;

        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentNumber = board.at(rowIndex).at(columnIndex);
                
                if (currentNumber == '.') {
                    int currentSubBoxIndex = (rowIndex / 3) * 3 + (columnIndex / 3);

                    unordered_set<char> possibleCharacters = {};
                    for (char testNumber = '0'; testNumber < '9'; testNumber += 1) {
                        if ((existingNumbersInRows.at(rowIndex).find(testNumber) == existingNumbersInRows.at(rowIndex).end()) && (existingNumbersInColumns.at(columnIndex).find(testNumber) == existingNumbersInColumns.at(columnIndex).end()) && (existingNumbersInSubBoxes.at(currentSubBoxIndex).find(testNumber) == existingNumbersInSubBoxes.at(currentSubBoxIndex).end())) {
                            possibleCharacters.insert(testNumber);
                        }
                    }
                }
            }
        }
    }
    
    //MARK: 2. Brute force (not used).
    void solveSudoku2(vector<vector<char>>& board) {
        //Assume: board.at(row).at(column)
        //1. Calculate constraints.
        vector<vector<bool>> initiallyFreePositions (9, vector<bool>({}));
        
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentCharacter = board.at(rowIndex).at(columnIndex);
                if (currentCharacter == '.') {
                    initiallyFreePositions.at(rowIndex).push_back(true);
                } else {
                    initiallyFreePositions.at(rowIndex).push_back(false);
                }
            }
        }

        //2. Brute force.
        for (int rowIndex = 0; rowIndex < 9; rowIndex += 1) {
            for (int columnIndex = 0; columnIndex < 9; columnIndex += 1) {
                char currentCharacter = board.at(rowIndex).at(columnIndex);
            }
        }
    }


    //MARK: 3. Brute force.
    //Again, recursion wins...
    //Runtime: 12 ms, faster than 72.67% of C++ online submissions for Sudoku Solver.
    //Memory Usage: 8.6 MB, less than 92.47% of C++ online submissions for Sudoku Solver.
    /**
     * @param startCharacter '1' ~ '9'.
     * @return The smallest next candidate if one exists. '.' if none exists.
     */
    char findNextCandidateForCoordinate(const vector<vector<char>>& board, int currentRow, int currentColumn, char startCharacter) {
        //Current subbox pre-processing.
        int currentSubboxRowIndex = currentRow / 3;
        int currentSubboxRowStart = currentSubboxRowIndex * 3;
        int currentSubboxRowEnd = currentSubboxRowStart + 2;
        
        int currentSubboxColumnIndex = currentColumn / 3;
        int currentSubboxColumnStart = currentSubboxColumnIndex * 3;
        int currentSubboxColumnEnd = currentSubboxColumnStart + 2;

        //Compute duplicates.
        char aCandidate = startCharacter;
        for (; aCandidate <= '9'; aCandidate += 1) {
            bool duplicateFound = false;

            //1. Current row.
            for (int testColumn = 0; testColumn < 9; testColumn += 1) {
                if (board.at(currentRow).at(testColumn) == aCandidate) {
                    duplicateFound = true;
                    break;
                }
            }
            if (duplicateFound) {
                continue;
            }

            //2. Current column.
            for (int testRow = 0; testRow < 9; testRow += 1) {
                if (board.at(testRow).at(currentColumn) == aCandidate) {
                    duplicateFound = true;
                    break;
                }
            }
            if (duplicateFound) {
                continue;
            }

            //3. Current subbox.
            for (int testRow = currentSubboxRowStart; testRow <= currentSubboxRowEnd; testRow += 1) {
                for (int testColumn = currentSubboxColumnStart; testColumn <= currentSubboxColumnEnd; testColumn += 1) {
                    if (board.at(testRow).at(testColumn) == aCandidate) {
                        duplicateFound = true;
                        break;
                    }
                }

                if (duplicateFound) {
                    break;
                }
            }
            
            //4. Break out of this big for loop.
            if (!duplicateFound) {
                break;
            }
        }

        if (aCandidate <= '9') {
            return aCandidate;
        } else {
            return '.';
        }
    }

    bool solveSudokuRecursively(vector<vector<char>>& board, stack<pair<int, int>>& backtrackStack, int currentRow, int currentColumn) {
//        cout << currentRow << " " << currentColumn << endl;
        
        char currentCharacter = board.at(currentRow).at(currentColumn);

        //1. There is an existing number.
        if (currentCharacter != '.') {
            if ((currentRow == 8) && (currentColumn == 8)) {
                return true;
            }

            int nextRow = currentRow + 1;
            int nextColumn = currentColumn;
            if (nextRow > 8) {
                nextRow = 0;
                nextColumn += 1;
            }

            return solveSudokuRecursively(board, backtrackStack, nextRow, nextColumn);
        }

        //2. This position is vacant.
        //See if this position has any candidates.
        int currentStartCharacter = '1';
        while (currentStartCharacter <= '9') {
            char aCandidate = findNextCandidateForCoordinate(board, currentRow, currentColumn, currentStartCharacter);
            if (aCandidate != '.') {
                //2-1. If a candidate has been found.
                // backtrackStack.push(make_pair(currentRow, currentColumn));
                board.at(currentRow).at(currentColumn) = aCandidate;

                if ((currentRow == 8) && (currentColumn == 8)) {
                    //This is the final block. A solution has been found!
                    return true;
                } else {
                    //This is not the final block.
                    int nextRow = currentRow + 1;
                    int nextColumn = currentColumn;
                    if (nextRow > 8) {
                        nextRow = 0;
                        nextColumn += 1;
                    }

                    if (solveSudokuRecursively(board, backtrackStack, nextRow, nextColumn)) {
                        //A solution has been found in a future iteration.
                        return true;
                    } else {
                        //A solution was not found in all future iterations. Increase current number!
                        board.at(currentRow).at(currentColumn) = '.';
                        
                        if (aCandidate == '9') {    //MARK: Originally == '8'
                            //All candidates have been tried and none of them worked.
                            return false;
                        } else {
                            currentStartCharacter = aCandidate + 1;
                        }
                    }
                }
            } else {
                //2-2. If no candidate has been found.
                return false;
            }
        }
        
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        //Assume: board.at(row).at(column)

        ///rowIndex, columnIndex
        stack<pair<int, int>> backtrackStack;

        solveSudokuRecursively(board, backtrackStack, 0, 0);
    }
};


#pragma mark - Main
int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<vector<char>> testCase1 = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    solutionInstance->solveSudoku(testCase1);
    cout << "Is valid Sudoku: " << solutionInstance->isValidSudoku(testCase1) << endl;
    printBoard(testCase1);
    
    cout << endl;
    vector<vector<char>> testCase2 = {{'.','2','6','5','.','.','.','9','.'},{'5','.','.','.','7','9','.','.','4'},{'3','.','.','.','1','.','.','.','.'},{'6','.','.','.','.','.','8','.','7'},{'.','7','5','.','2','.','.','1','.'},{'.','1','.','.','.','.','4','.','.'},{'.','.','.','3','.','8','9','.','2'},{'7','.','.','.','6','.','.','4','.'},{'.','3','.','2','.','.','1','.','.'}};
    solutionInstance->solveSudoku(testCase2);
    cout << "Is valid Sudoku: " << solutionInstance->isValidSudoku(testCase2) << endl;
    printBoard(testCase2);
    
    return 0;
}
