/*
 * 51. N-Queens
 * https://leetcode.com/problems/n-queens/
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <memory>

using namespace std;


class Solution {
public:
    // MARK: 1. Brute force (unfinished).
//    vector<vector<string>> solveNQueens1(int n) {
//        if (n <= 0) {
//            return {};
//        } else if (n == 1) {
//            return {{"Q"}};
//        }
//
//        vector<vector<string>> returnValue;
//
//        vector<pair<int, int>> queenPositions;
//        queenPositions.push_back(make_pair(0, 0));
//
//        while (true) {
//            // Tries to find next possible queen position. Start searching from the next row of last queen position.
//            pair<int, int> lastQueenPosition = queenPositions.back();
//
//            bool potentialQueenPositionFound = false;
//            for (int i = (lastQueenPosition.first + 1); i < n; i += 1) {
//                for (int j = 0; j < n; j += 1) {
//                    // Same column
//                    if (j == lastQueenPosition.second) {
//                        continue;
//                    }
//                    // Diagonal
//                    if ((lastQueenPosition.first - i) == (lastQueenPosition.second - j)) {
//                        continue;
//                    }
//
//                    queenPositions.push_back(make_pair(i, j));
//                    break;
//                }
//
//                if (potentialQueenPositionFound) {
//                    break;
//                }
//            }
//
//            if (queenPositions.size() == n) {
//                // This is a solution.
//                vector<string> currentSolution (4, "....");
//                for (const auto& aQueenPosition: queenPositions) {
//                    currentSolution.at(aQueenPosition.first).at(aQueenPosition.second) = 'Q';
//                }
//            }
//        }
//
//        return returnValue;
//    }
    
    
    // MARK: 2. Recursion (how could this be so slow).
    // Runtime: 1736 ms, faster than 5.11% of C++ online submissions for N-Queens.
    // Memory Usage: 441.9 MB, less than 6.25% of C++ online submissions for N-Queens.
    vector<vector<string>> solveNQueens2(int n) {
        if (n <= 0) {
            return {};
        } else if (n == 1) {
            return {{"Q"}};
        }
        
        vector<vector<string>> returnValues;
        auto unprocessedReturnValues = solveNQueensRecursively({}, n, 0);
        
        for (const auto& aSetOfQueenPositions: unprocessedReturnValues) {
            vector<string> currentValue (n, string(n, '.'));
            
            for (const auto& aQueenPosition: aSetOfQueenPositions) {
                currentValue.at(aQueenPosition.first).at(aQueenPosition.second) = 'Q';
            }
            
            returnValues.push_back(currentValue);
        }
        
        return returnValues;
    }
    
    /**
     * `targetQueensCount` is guaranteed to be larger than 1.
     */
    vector<vector<pair<int, int>>> solveNQueensRecursively(const vector<pair<int, int>> existingQueens, const int targetQueensCount, const int existingQueensCount) {
        vector<pair<int, int>> possibleNextQueenCoordinates;
        
        if (existingQueensCount > 0) {
            // Start from the next row of `lastQueenCoordinate`.
            pair<int, int> lastQueenCoordinate = existingQueens.back();
            if (lastQueenCoordinate.first > (targetQueensCount - 2)) {
                // This is the final row.
                return {};
            }
            
            for (int i = (lastQueenCoordinate.first + 1); i < targetQueensCount; i += 1) {
                for (int j = 0; j < targetQueensCount; j += 1) {
                    possibleNextQueenCoordinates.push_back(make_pair(i, j));
                }
            }
        } else {
            // Try every coordinate.
            for (int i = 0; i < targetQueensCount; i += 1) {
                for (int j = 0; j < targetQueensCount; j += 1) {
                    possibleNextQueenCoordinates.push_back(make_pair(i, j));
                }
            }
        }
        
        vector<vector<pair<int, int>>> returnValue = {};
        
        int nextQueensCount = existingQueensCount + 1;
        for (const auto& aCoordinate: possibleNextQueenCoordinates) {
            // See if this coordinate can be a queen.
            bool isCoordinateEligible = true;
            for (const auto& anExistingQueen: existingQueens) {
                if (aCoordinate.second == anExistingQueen.second) {
                    isCoordinateEligible = false;
                    break;
                }
                
                if (abs(aCoordinate.first - anExistingQueen.first) == abs(aCoordinate.second - anExistingQueen.second)) {
                    isCoordinateEligible = false;
                    break;
                }
            }
            if (!isCoordinateEligible) {
                continue;
            }
            
            if (existingQueensCount < (targetQueensCount - 1)) {
                // There are more queens to be found.
                vector<pair<int, int>> nextQueens = existingQueens;
                nextQueens.push_back(aCoordinate);
                auto aResult = solveNQueensRecursively(nextQueens, targetQueensCount, nextQueensCount);
                if (aResult.size() > 0) {
                    // At least one result is found.
                    returnValue.insert(returnValue.end(), aResult.begin(), aResult.end());
                }
            } else {
                // This is the final queen.
                auto aResult = existingQueens;
                aResult.push_back(aCoordinate);
                returnValue.push_back(aResult);
            }
        }
        
        return returnValue;
    }
    
    
    // MARK: 3. Recursion with depth first search.
    /* 
     * OJ stats without the reference in the `isPositionValid` function parameters:
     * Runtime: 36 ms, faster than 16.81% of C++ online submissions for N-Queens.
     * Memory Usage: 48.4 MB, less than 6.25% of C++ online submissions for N-Queens.
     */
    /*
     * OJ stats with the reference in the `isPositionValid` function paremeters.
     * Runtime: 4 ms, faster than 97.28% of C++ online submissions for N-Queens.
     * Memory Usage: 9.8 MB, less than 100.00% of C++ online submissions for N-Queens.
     */
    vector<vector<string>> solveNQueens(int n) {
        if (n <= 0) {
            return {};
        } else if (n == 1) {
            return {{"Q"}};
        }
        
        vector<vector<string>> returnValues;
        vector<string> currentBoard (n, string(n, '.'));
        
        solveNQueensRecursively(returnValues, currentBoard, 0, n);
        
        return returnValues;
    }
    
    void solveNQueensRecursively(vector<vector<string>>& returnValues, vector<string>& currentBoard, int row, const int targetQueensCount) {
        if (row >= targetQueensCount) {
            returnValues.push_back(currentBoard);
            return;
        }
        
        // An important thing to notice is that there must be exactly one queen in each row.
        for (int j = 0; j < targetQueensCount; j += 1) {
            // `j` is the column.
            if (isPositionValid(currentBoard, row, j, targetQueensCount)) {
                currentBoard.at(row).at(j) = 'Q';
                solveNQueensRecursively(returnValues, currentBoard, row + 1, targetQueensCount);
                currentBoard.at(row).at(j) = '.';
            }
        }
    }
    
    /**
     * Changing `const vector<string> currentBoard` to `const vector<string>& currentBoard` improves LeetCode OJ run speed from 36ms to 4ms!
     */
    bool isPositionValid(const vector<string>& currentBoard, const int row, const int column, const int targetQueensCount) {
        for (int i = 0; i < row; i += 1) {    // Only compare the rows above.
            if (currentBoard.at(i).at(column) == 'Q') {
                // A queen on the same column.
                return false;
            }
            
            int distance = row - i;
            int diagonalColumn1 = column + distance;
            int diagonalColumn2 = column - distance;
            
            if ((diagonalColumn1 < targetQueensCount) && (currentBoard.at(i).at(diagonalColumn1) == 'Q')) {
                // A queen on diagonals.
                return false;
            }
            if ((diagonalColumn2 >= 0) && (currentBoard.at(i).at(diagonalColumn2) == 'Q')) {
                // A queen on diagonals.
                return false;
            }
        }
                        
        return true;
    }
};


void printNQueensSolution(int n) {
    static Solution* solutionInstance = new Solution();
    auto results = solutionInstance->solveNQueens(n);
    
    cout << n << "-Queen(s) problem: Results count: " << results.size() << endl;
    for (const auto& aResult: results) {
        cout << "Current result:\n";
        for (const auto& aRow: aResult) {
            cout << aRow << "\n";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    printNQueensSolution(6);
    return 0;
}
