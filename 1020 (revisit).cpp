/*
 * 1020. Number of Enclaves
 * https://leetcode.com/problems/number-of-enclaves/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Start from edges
// Runtime: 81 ms, faster than 28.32% of C++ online submissions for Number of Enclaves.
// Memory Usage: 21.8 MB, less than 38.60% of C++ online submissions for Number of Enclaves.
class Solution {
private:
    int dfsRecursion(std::vector<std::vector<int>>& grid, const int x, const int y) {
        if (grid[y][x] == 0) {
            // Water.
            return 0;
        }
        if (grid[y][x] == 2) {
            // Visited.
            return 0;
        }

        // Mark as visited.
        grid[y][x] = 2;

        int returnValue = 1;

        if (x > 0) {
            returnValue += dfsRecursion(grid, x - 1, y);
        }
        if (x < (grid.front().size() - 1)) {
            returnValue += dfsRecursion(grid, x + 1, y);
        }
        if (y > 0) {
            returnValue += dfsRecursion(grid, x, y - 1);
        }
        if (y < (grid.size() - 1)) {
            returnValue += dfsRecursion(grid, x, y + 1);
        }

        return returnValue;
    }

public:
    int numEnclaves(std::vector<std::vector<int>>& grid) {
        // Edge case: 1 high or 1 wide.
        if ((grid.size() == 1) || (grid.front().size() == 1)) {
            return 0;
        }

        // Calculate the total 1s.
        int returnValue = 0;
        for (const auto& row: grid) {
            for (const int& num: row) {
                returnValue += num;
            }
        }

        // Top and bottom edges.
        for (int x = 0; x < grid.front().size(); x += 1) {
            const int y0 = 0;
            const int result0 = dfsRecursion(grid, x, y0);
            returnValue -= result0;

            const int y1 = static_cast<int>(grid.size()) - 1;
            const int result1 = dfsRecursion(grid, x, y1);
            returnValue -= result1;
        }

        // Left and right edges.
        for (int y = 1; y < (grid.size() - 1); y += 1) {
            const int x0 = 0;
            const int result0 = dfsRecursion(grid, x0, y);
            returnValue -= result0;

            const int x1 = static_cast<int>(grid.front().size()) - 1;
            const int result1 = dfsRecursion(grid, x1, y);
            returnValue -= result1;
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1 (revisit)
/*
 * 1. Use DFS to replace all boundary land blocks with 0
 * 2. Calculate the remaining sum of land blocks
 *
 * Much simpler :)
 */


void test(const std::vector<std::vector<int>>& grid, const int expectedResult) {
    auto solutionInstance = Solution();

    auto gridCopy = grid;
    auto result = solutionInstance.numEnclaves(gridCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << grid << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << grid << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}}, 3);
    test({{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}}, 0);

    return 0;
}
