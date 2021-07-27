/*
 * 1074. Number of Submatrices That Sum to Target
 * https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Prefix sums
// Runtime: 1948 ms, faster than 5.01% of C++ online submissions for Number of Submatrices That Sum to Target.
// Memory Usage: 9.2 MB, less than 95.66% of C++ online submissions for Number of Submatrices That Sum to Target.
class Solution1 {
public:
    int numSubmatrixSumTarget(std::vector<std::vector<int>>& matrix, const int target) {
        // Create prefix sums.
        for (auto& row: matrix) {
            for (size_t x = 1; x < row.size(); x += 1) {
                row[x] += row[x - 1];
            }
        }

        for (size_t y = 1; y < matrix.size(); y += 1) {
            auto& currentRow = matrix[y];
            auto& previousRow = matrix[y - 1];

            for (size_t x = 0; x < currentRow.size(); x += 1) {
                currentRow[x] += previousRow[x];
            }
        }

        // Insert 0s at the beginning of each row and column to form prefix sums.
        for (auto& row: matrix) {
            row.insert(row.begin(), 0);
        }
        matrix.insert(matrix.begin(), std::vector<int>(matrix[0].size(), 0));

        // Minus.
        int returnValue = 0;

        // (y0, y1].
        for (size_t y0 = 0; y0 < matrix.size(); y0 += 1) {
            for (size_t x0 = 0; x0 < matrix[0].size(); x0 += 1) {
                for (size_t y1 = y0 + 1; y1 < matrix.size(); y1 += 1) {
                    for (size_t x1 = x0 + 1; x1 < matrix[0].size(); x1 += 1) {
                        auto result = matrix[y1][x1] - matrix[y0][x1] - matrix[y1][x0] + matrix[y0][x0];
                        if (result == target) {
                            returnValue += 1;
                        }
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimize 1 using hash tables
// Runtime: 988 ms, faster than 25.52% of C++ online submissions for Number of Submatrices That Sum to Target.
// Memory Usage: 275.8 MB, less than 12.85% of C++ online submissions for Number of Submatrices That Sum to Target.
class Solution {
public:
    int numSubmatrixSumTarget(std::vector<std::vector<int>>& matrix, const int target) {
        // Create prefix sums.
        for (auto& row: matrix) {
            for (size_t x = 1; x < row.size(); x += 1) {
                row[x] += row[x - 1];
            }
        }

        for (size_t y = 1; y < matrix.size(); y += 1) {
            auto& currentRow = matrix[y];
            auto& previousRow = matrix[y - 1];

            for (size_t x = 0; x < currentRow.size(); x += 1) {
                currentRow[x] += previousRow[x];
            }
        }

        // No need to insert 0 into row begin thanks to the hash tables.
//        for (auto& row: matrix) {
//            row.insert(row.begin(), 0);
//        }
        matrix.insert(matrix.begin(), std::vector<int>(matrix[0].size(), 0));

        int returnValue = 0;

        // Create hash tables for each (y0, y1] pair.
        for (size_t y0 = 0; y0 < matrix.size(); y0 += 1) {
            for (size_t y1 = y0 + 1; y1 < matrix.size(); y1 += 1) {
                auto previousValues = std::unordered_map<int, int>({{0, 1}});
                for (size_t x = 0; x < matrix[0].size(); x += 1) {
                    const auto result = matrix[y1][x] - matrix[y0][x];
                    const auto expectedValue = result - target;

                    returnValue += previousValues[expectedValue];

                    previousValues[result] += 1;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& matrix, const int target, const int expectedResult) {
    auto solutionInstance = Solution();

    auto matrixCopy = matrix;
    auto result = solutionInstance.numSubmatrixSumTarget(matrixCopy, target);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << matrix << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << matrix << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,-1},{-1,1}}, 0, 5);
    test({{0,1,1,1,0,1},{0,0,0,0,0,1},{0,0,1,0,0,1},{1,1,0,1,1,0},{1,0,0,1,0,0}}, 0, 43);
    test({{0,1,0},{1,1,1},{0,1,0}}, 0, 4);
    test({{900}}, 0, 0);

    return 0;
}
