/*
 * 1686. Stone Game VI
 * https://leetcode.com/problems/stone-game-vi/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sum and greedy (revisit)
/*
 * When A takes valueA, B loses valueB.
 */
// Runtime: 436 ms, faster than 36.57% of C++ online submissions for Stone Game VI.
// Memory Usage: 107.6 MB, less than 86.07% of C++ online submissions for Stone Game VI.
class Solution {
public:
    int stoneGameVI(const std::vector<int>& aliceValues, const std::vector<int>& bobValues) {
        auto totalValues = aliceValues;
        for (int i = 0; i < aliceValues.size(); i += 1) {
            totalValues[i] += bobValues[i];
        }

        auto indices = std::vector<int>(aliceValues.size(), 0);
        for (int i = 1; i < aliceValues.size(); i += 1) {
            indices[i] = i;
        }

        auto cmp = [&totalValues] (const int& lhs, const int& rhs) -> bool {
            return totalValues[lhs] > totalValues[rhs];
        };
        std::sort(indices.begin(), indices.end(), cmp);

        int delta = 0;
        // Alice.
        for (int i = 0; i < aliceValues.size(); i += 2) {
            delta += aliceValues[indices[i]];
        }
        // Bob.
        for (int i = 1; i < aliceValues.size(); i += 2) {
            delta -= bobValues[indices[i]];
        }

        if (delta > 0) {
            return 1;
        } else if (delta == 0) {
            return 0;
        } else {
            return -1;
        }
    }
};


void test(const std::vector<int>& aliceValues, const std::vector<int>& bobValues, const int expectedResult) {
    auto solutionInstance = Solution();

    const int result = solutionInstance.stoneGameVI(aliceValues, bobValues);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << aliceValues << ", " << bobValues << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << aliceValues << ", " << bobValues << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3}, {2,1}, 1);
    test({1,2}, {3,1}, 0);
    test({2,4,3}, {1,6,7}, -1);

    return 0;
}
