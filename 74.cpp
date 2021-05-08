/*
 * 74. Search a 2D Matrix
 * https://leetcode.com/problems/search-a-2d-matrix/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Search a 2D Matrix.
// Memory Usage: 9.6 MB, less than 42.46% of C++ online submissions for Search a 2D Matrix.
class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, const int target) {
        // Search row.
        int rowStart = 0;
        int rowEnd = matrix.size() - 1;

        while (rowEnd >= rowStart) {
            const int rowMid = (rowStart + rowEnd) / 2;
            if (matrix[rowMid][0] == target) {
                return true;
            } else if (matrix[rowMid][0] < target) {
                rowStart = rowMid + 1;
            } else {
                rowEnd = rowMid - 1;
            }
        }

        const int& row = rowStart - 1;
        if ((row < 0) || (row >= matrix.size())) {
            return false;
        }

        // Search column.
        int columnStart = 0;
        int columnEnd = matrix[0].size() - 1;

        while (columnEnd >= columnStart) {
            const int columnMid = (columnStart + columnEnd) / 2;
            if (matrix[row][columnMid] == target) {
                return true;
            } else if (matrix[row][columnMid] < target) {
                columnStart = columnMid + 1;
            } else {
                columnEnd = columnMid - 1;
            }
        }

        return false;
    }
};


void test(const std::vector<std::vector<int>>& matrix, const int target, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto matrixCopy = matrix;
    auto result = solutionInstance.searchMatrix(matrixCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << matrix << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << matrix << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{4,5}}, 1, true);
    test({{1,2},{4,5}}, 3, false);
    test({{1,2},{4,5}}, 4, true);

    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 0, false);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 3, true);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 6, false);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 13, false);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 16, true);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 23, true);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 34, true);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 50, false);
    test({{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 100, false);

    return 0;
}
