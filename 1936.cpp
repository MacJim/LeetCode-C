/*
 * 1936. Add Minimum Number of Rungs
 * https://leetcode.com/problems/add-minimum-number-of-rungs/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Try to use all existing rungs
// Runtime: 92 ms, faster than 94.89% of C++ online submissions for Add Minimum Number of Rungs.
// Memory Usage: 54.2 MB, less than 28.02% of C++ online submissions for Add Minimum Number of Rungs.
class Solution {
public:
    int addRungs(const std::vector<int>& rungs, const int dist) {
        int returnValue = 0;

        const int distance0 = rungs[0] - 1;    // Remember to minus 1.
        returnValue += (distance0 / dist);

        for (int i = 1; i < rungs.size(); i += 1) {
            const int distance = rungs[i] - rungs[i - 1] - 1;    // Remember to minus 1.
            returnValue += (distance / dist);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& rungs, const int dist, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.addRungs(rungs, dist);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << rungs << ", " << dist << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << rungs << ", " << dist << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,5,10}, 2, 2);
    test({3,6,8,10}, 3, 0);
    test({3,4,6,7}, 2, 1);
    test({5}, 10, 0);
    test({5}, 5, 0);
    test({1,3,8,13}, 2, 4);
    test({1,2,7,12}, 2, 4);
    test({1,2,7,12,17}, 2, 6);

    return 0;
}
