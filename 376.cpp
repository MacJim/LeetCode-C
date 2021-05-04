/*
 * 376. Wiggle Subsequence
 * https://leetcode.com/problems/wiggle-subsequence/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Log the changes from increasing to decreasing or from decreasing to increasing
// Runtime: 4 ms, faster than 39.61% of C++ online submissions for Wiggle Subsequence.
// Memory Usage: 7 MB, less than 64.01% of C++ online submissions for Wiggle Subsequence.
class Solution {
public:
    int wiggleMaxLength(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 1;
        } else if (nums.size() == 2) {
            if (nums[0] == nums[1]) {
                return 1;
            } else {
                return 2;
            }
        }

        int returnValue = 1;

        // We need to remove the initial duplicate numbers to assign a correct initial value of `increasing`.
        size_t nonDuplicateInitial = 0;
        while ((nonDuplicateInitial < (nums.size() - 1)) && (nums[nonDuplicateInitial] == nums[nonDuplicateInitial + 1])) {
            nonDuplicateInitial += 1;
        }

        if (nonDuplicateInitial == (nums.size() - 1)) {
            // All numbers are equal.
            return 1;
        }

        /*
         * Whether the previous 2 numbers are increasing or decreasing.
         *
         * The initial value is reverse to the actual value.
         */
        bool increasing = nums[nonDuplicateInitial + 1] <= nums[nonDuplicateInitial];

        // Main loop
        for (size_t i = nonDuplicateInitial + 1; i < nums.size(); i += 1) {
            const auto& previousNum = nums[i - 1];
            const auto& currentNum = nums[i];

            if (currentNum > previousNum) {
                if (!increasing) {
                    // From decreasing to increasing.
                    increasing = true;
                    returnValue += 1;
                }
            } else if (currentNum < previousNum) {
                if (increasing) {
                    // From increasing to decreasing.
                    increasing = false;
                    returnValue += 1;
                }
            } else {
                // Equal. Do nothing.
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.wiggleMaxLength(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
//    test({1}, 1);
    test({1,7,4,9,2,5}, 6);
    test({1,1,7,4,9,2,5}, 6);
    test({1,17,5,10,13,15,10,5,16,8}, 7);
    test({1,2,3,4,5,6,7,8,9}, 2);
    test({1,4,5,5,4}, 3);
    test({1,1,1,1,1,1,1}, 1);

    return 0;
}
