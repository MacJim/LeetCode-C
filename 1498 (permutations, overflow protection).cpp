/*
 * 1498. Number of Subsequences That Satisfy the Given Sum Condition
 * https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 */

#include <iostream>
#include <vector>
#include <cmath>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. 2 pointers
// WRONG ANSWER: See MARK in solution 2
class Solution1 {
private:
    static constexpr int MOD = 1000000007;

public:
    int numSubseq(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end());

        int returnValue = 0;
        for (int i1 = 0; i1 < nums.size(); i1 += 1) {
            const int target2 = target - nums[i1];
            if (target2 < 0) {
                break;
            }

            int i2 = i1;
            for (; i2 < nums.size(); i2 += 1) {
                if (nums[i2] > target2) {
                    // The 2nd number is too large.
                    break;
                }
            }

            const int numsCount = i2 - 1 - i1;
            if (numsCount >= 0) {
                int currentCount = static_cast<int>(lround(pow(2, numsCount)));
                currentCount %= MOD;
                returnValue += currentCount;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Fixed 1 (overflow protection, revisit)
/*
 * Overflow happens during:
 *
 * - Power
 * - Addition
 */
// Runtime: 104 ms, faster than 95.12% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
// Memory Usage: 49.8 MB, less than 50.55% of C++ online submissions for Number of Subsequences That Satisfy the Given Sum Condition.
class Solution {
private:
    static constexpr int MOD = 1000000007;

public:
    int numSubseq(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end());

        // Cache powers.
        auto powerCache = std::vector<int>(nums.size() + 1, 0);
        powerCache[0] = 1;
        for (int i = 1; i <= nums.size(); i += 1) {
            powerCache[i] = powerCache[i - 1] * 2;
            powerCache[i] %= MOD;    // MARK: This is the key piece. Some powers are so big that they overflow.
        }

        // 2 pointers.
        int returnValue = 0;

        int i2 = nums.size() - 1;
        for (int i1 = 0; i1 < nums.size(); i1 += 1) {
            const int target2 = target - nums[i1];
            if (target2 < 0) {
                break;
            }

            while ((i2 >= i1) && (nums[i2] > target2)) {
                // The 2nd number is too large.
                i2 -= 1;
            }

            const int numsCount = i2 - i1;
            if (numsCount >= 0) {
                int currentCount = powerCache[numsCount];
                returnValue += currentCount;
                returnValue %= MOD;
            } else {
                // i1 is too large.
                break;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int target, const int expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.numSubseq(numsCopy, target);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({14,4,6,6,20,8,5,6,8,12,6,10,14,9,17,16,9,7,14,11,14,15,13,11,10,18,13,17,17,14,17,7,9,5,10,13,8,5,18,20,7,5,5,15,19,14}, 22, 272187084);
    test({3,5,6,7}, 9, 4);
    test({3,3,6,8}, 10, 6);
    test({2,3,3,4,6,7}, 12, 61);
    test({5,2,4,1,7,6,8}, 16, 127);

    return 0;
}
