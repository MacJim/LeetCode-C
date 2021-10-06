/*
 * 2017. Grid Game
 * https://leetcode.com/problems/grid-game/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sum from 2 directions
/*
 * Note that robot 2's only options are top-right or bottom-left.
 */
// Runtime: 164 ms, faster than 55.59% of C++ online submissions for Grid Game.
// Memory Usage: 62.9 MB, less than 65.77% of C++ online submissions for Grid Game.
class Solution {
public:
    long long gridGame(const std::vector<std::vector<int>>& grid) {
        const size_t len = grid[0].size();

        long long bottomLeftSum = 0;
        long long topRightSum = 0;
        for (size_t i = 1; i < len; i += 1) {
            topRightSum += grid[0][i];
        }

        long long returnValue = topRightSum;

        for (size_t i = 1; i < len; i += 1) {
            topRightSum -= grid[0][i];
            bottomLeftSum += grid[1][i - 1];

            const long long biggerSum = std::max(topRightSum, bottomLeftSum);    // 2nd player choose the optimal solution.
            returnValue = std::min(returnValue, biggerSum);
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& grid, const long long expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.gridGame(grid);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << grid << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << grid << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{2,5,4},{1,5,1}}, 4);
    test({{3,3,1},{8,5,2}}, 4);
    test({{1,3,1,15},{1,3,3,1}}, 7);

    return 0;
}
