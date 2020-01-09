/*
 * 73. Set Matrix Zeroes
 * https://leetcode.com/problems/set-matrix-zeroes/
 */

#include <iostream>
#include <vector>
#include <unordered_set>


// MARK: - 1. Save the row and column numbers that should be purged.
// Runtime: 72 ms, faster than 7.95% of C++ online submissions for Set Matrix Zeroes.
// Memory Usage: 11.6 MB, less than 37.04% of C++ online submissions for Set Matrix Zeroes.
class Solution {
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        // We assume matrix.at(y).at(x), that is (row, column).
        auto rowsCount = matrix.size();
        auto columnsCount = matrix.at(0).size();
        
        auto rowsToPurge = std::unordered_set<int>();
        auto columnsToPurge = std::unordered_set<int>();
        
        for (int y = 0; y < rowsCount; y += 1) {
            for (int x = 0; x < columnsCount; x += 1) {
                auto currentValue = matrix.at(y).at(x);
                if (currentValue == 0) {
                    rowsToPurge.insert(y);
                    columnsToPurge.insert(x);
                }
            }
        }
        
        for (const auto& y: rowsToPurge) {
            for (int x = 0; x < columnsCount; x += 1) {
                matrix.at(y).at(x) = 0;
            }
        }
        for (const auto& x: columnsToPurge) {
            for (int y = 0; y < rowsCount; y += 1) {
                matrix.at(y).at(x) = 0;
            }
        }
    }
};


void test(std::vector<std::vector<int>> testCase) {
    static auto solutionInstance = Solution();
    solutionInstance.setZeroes(testCase);
    for (const auto& aColumn: testCase) {
        for (const auto& aValue: aColumn) {
            std::cout << aValue << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    std::vector<std::vector<int>> testCase1 = {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };
    test(testCase1);
    
    std::vector<std::vector<int>> testCase2 = {
        {0,1,2,0},
        {3,4,5,2},
        {1,3,1,5}
    };
    test(testCase2);
    
    return 0;
}
