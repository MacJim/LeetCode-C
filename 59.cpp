/*
 * 59. Spiral Matrix II
 * https://leetcode.com/problems/spiral-matrix-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Rim by rim
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Spiral Matrix II.
// Memory Usage: 6.9 MB, less than 67.22% of C++ online submissions for Spiral Matrix II.
class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n) {
        if (n == 1) {
            return {{1}};
        }

        auto returnValue = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

        int currentValue = 1;    // Start with 1

        int x0 = 0;
        int x1 = n - 1;
        int y0 = 0;
        int y1 = n - 1;

        while (x1 > x0) {
            for (int x = x0; x < x1; x += 1) {
                returnValue[y0][x] = currentValue;
                currentValue += 1;
            }
            for (int y = y0; y < y1; y += 1) {
                returnValue[y][x1] = currentValue;
                currentValue += 1;
            }
            for (int x = x1; x > x0; x -= 1) {
                returnValue[y1][x] = currentValue;
                currentValue += 1;
            }
            for (int y = y1; y > y0; y -= 1) {
                returnValue[y][x0] = currentValue;
                currentValue += 1;
            }

            x0 += 1;
            x1 -= 1;
            y0 += 1;
            y1 -= 1;
        }

        if (x1 == x0) {
            returnValue[x0][y0] = currentValue;
        }

        return returnValue;
    }
};


void test(int n, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.generateMatrix(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, {{1}});
    test(2, {{1, 2}, {4, 3}});
    test(3, {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}});

    return 0;
}
