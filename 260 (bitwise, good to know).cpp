/*
 * 260. Single Number III
 * https://leetcode.com/problems/single-number-iii/
 */

/*
 * Like problem 136.
 */

#include <iostream>
#include <vector>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Bitwise operations, 2 passes (good to know)
// Source: https://leetcode.com/problems/single-number-iii/discuss/68900/Accepted-C%2B%2BJava-O(n)-time-O(1)-space-Easy-Solution-with-Detail-Explanations
class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
        if (nums.size() == 2) {
            return nums;
        }

        // 1. Calculate XOR
        int diff = 0;
        for (const auto& num: nums) {
            diff ^= num;
        }

        // At least one bit in `diff` must be 1.
        /*
         * This finds out the right-most 1 bit.
         *
         * Example:
         *
         * 6: 0b0110
         * -6: 0b1010 (reverse all bits and plus 1)
         * 6 & -6: 0b0010
         */
        diff &= -diff;

        // 2. Divide numbers into 2 groups
        auto returnValue = std::vector<int>(2, 0);

        for (const auto& num: nums) {
            if (num & diff) {
                // Group 1: The bit is set.
                returnValue[0] ^= num;
            } else {
                // Group 2: The bit is not set.
                returnValue[1] ^= num;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::set<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.singleNumber(numsCopy);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,1,3,2,5}, {3,5});
    test({0,1}, {0,1});

    return 0;
}
