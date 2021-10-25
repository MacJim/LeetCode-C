/*
 * 304. Range Sum Query 2D - Immutable
 * https://leetcode.com/problems/range-sum-query-2d-immutable/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. 2D prefix sum
// Runtime: 599 ms, faster than 32.67% of C++ online submissions for Range Sum Query 2D - Immutable.
// Memory Usage: 148.1 MB, less than 49.93% of C++ online submissions for Range Sum Query 2D - Immutable.
class NumMatrix {
    std::vector<std::vector<int>> prefixSum;

public:
    explicit NumMatrix(const std::vector<std::vector<int>>& matrix) {
        const auto yLen = matrix.size();
        const auto xLen = matrix[0].size();

        prefixSum = std::vector<std::vector<int>>(yLen + 1, std::vector<int>(xLen + 1, 0));

        // Calculate x prefix sums.
        for (size_t y = 0; y < yLen; y += 1) {
            const auto& currentNums = matrix[y];
            auto& currentSums = prefixSum[y + 1];    // Note `y + 1` here because `y == 0` row is always 0.
            for (size_t x = 0; x < xLen; x += 1) {
                currentSums[x + 1] = currentSums[x] + currentNums[x];
            }
        }

        // Calculate y prefix sums.
        for (size_t x = 1; x <= xLen; x += 1) {    // Note: `x <= xLen` here because prefix sum is longer.
            for (size_t y = 1; y < yLen; y += 1) {
                prefixSum[y + 1][x] += prefixSum[y][x];
            }
        }
    }

    int sumRegion(const int y0, const int x0, int y1, int x1) {
        y1 += 1;
        x1 += 1;

        return prefixSum[y1][x1] - prefixSum[y0][x1] - prefixSum[y1][x0] + prefixSum[y0][x0];
    }
};


#pragma mark - Helpers
/**
 * Used for verification only.
 */
class NumMatrixBruteForce {
private:
    std::vector<std::vector<int>> matrix;

public:
    explicit NumMatrixBruteForce(const std::vector<std::vector<int>>& matrix) {
        // Do a copy in the brute force approach.
        this->matrix = matrix;
    }

    int sumRegion(const int y0, const int x0, const int y1, const int x1) {
        int returnValue = 0;

        for (int y = y0; y <= y1; y += 1) {
            for (int x = x0; x <= x1; x += 1) {
                returnValue += matrix[y][x];
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& matrix) {
    const auto yLen = matrix.size();
    const auto xLen = matrix[0].size();

    auto solutionInstance = NumMatrix(matrix);
    auto referenceSolutionInstance = NumMatrixBruteForce(matrix);

    bool isCorrect = true;

    // Test all index combinations.
    for (int y0 = 0; y0 < yLen; y0 += 1) {
        for (int y1 = y0; y1 < yLen; y1 += 1) {
            for (int x0 = 0; x0 < xLen; x0 += 1) {
                for (int x1 = x0; x1 < xLen; x1 += 1) {
                    const int result = solutionInstance.sumRegion(y0, x0, y1, x1);
                    const int expectedResult = referenceSolutionInstance.sumRegion(y0, x0, y1, x1);

                    if (result != expectedResult) {
                        isCorrect = false;
                        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << matrix << ", " << "(" << y0 << ", " << x0 << ", " << y1 << ", " << x1 << ")" << ": " << result << " (should be " << expectedResult << ")" << std::endl;
                    }
                }
            }
        }
    }

    if (isCorrect) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << matrix << std::endl;
    }
}


int main() {
    test({{{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}}});

    return 0;
}
