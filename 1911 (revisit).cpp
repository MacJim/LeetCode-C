/*
 * 1911. Maximum Alternating Subsequence Sum
 * https://leetcode.com/problems/maximum-alternating-subsequence-sum/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Backtracking/recursion
// Time Limit Exceeded
// Results should be correct, though.
class Solution1 {
private:
    long long recursion(const std::vector<int>& nums, const size_t currentIndex, const bool plusOrMinus, int currentValue) {
        if (currentIndex == nums.size()) {
            return currentValue;
        }

        // Do not use the current number.
        long long returnValueDoNotUse = recursion(nums, currentIndex + 1, plusOrMinus, currentValue);

        // Use the current number.
        if (plusOrMinus) {
            currentValue += nums[currentIndex];
        } else {
            currentValue -= nums[currentIndex];
        }
        long long returnValueUse = recursion(nums, currentIndex + 1, !plusOrMinus, currentValue);

        return std::max(returnValueDoNotUse, returnValueUse);
    }

public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        long long returnValue = recursion(nums, 0, true, 0);

        return returnValue;
    }
};


#pragma mark - 2. Dynamic Programming
// Time Limit Exceeded
class Solution2 {
public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        auto nextPlus = std::vector<std::vector<int>>(nums.size(), std::vector<int>(nums.size(), 0));
        for (int i = 0; i < nums.size(); i += 1) {
            // Don't use current number.
            nextPlus[i][i] = 0;
        }

        auto nextMinus = std::vector<std::vector<int>>(nums.size(), std::vector<int>(nums.size(), 0));
        for (int i = 0; i < nums.size(); i += 1) {
            // Use current number as the first number.
            nextMinus[i][i] = nums[i];
        }

        for (int len = 2; len <= nums.size(); len += 1) {
            for (int start = 0; ; start += 1) {
                const int end = start + len - 1;
                if (end >= nums.size()) {
                    break;
                }

                const auto& previousNextPlusValue = nextPlus[start][end - 1];
                const auto& previousNextMinusValue = nextMinus[start][end - 1];

                // Update next plus.
                nextPlus[start][end] = std::max(previousNextPlusValue, previousNextMinusValue - nums[end]);
                // Update next minus.
                nextMinus[start][end] = std::max(previousNextMinusValue, previousNextPlusValue + nums[end]);
            }
        }

        return std::max(nextPlus.front().back(), nextMinus.front().back());
    }
};


#pragma mark - 3. Optimized 2
// Time Limit Exceeded
class Solution3 {
public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        /// Don't use current number.
        auto nextPlus = std::vector<int>(nums.size(), 0);

        /// Use current number as the first number.
        auto nextMinus = nums;

        for (int len = 2; len <= nums.size(); len += 1) {
            const int end = nums.size() - len;
            for (int i = 0; i <= end; i += 1) {
                const int previousNextPlusValue = nextPlus[i];
                const int previousNextMinusValue = nextMinus[i];

                const int& currentNum = nums[i + len - 1];
                nextPlus[i] = std::max(previousNextPlusValue, previousNextMinusValue - currentNum);
                nextMinus[i] = std::max(previousNextMinusValue, previousNextPlusValue + currentNum);
            }
        }

        return std::max(nextPlus.front(), nextMinus.front());
    }
};


#pragma mark - 4. Optimized 3: State machine (revisit)
// Similar to "Best Time to Buy and Sell Stock".
// Runtime: 152 ms, faster than 89.09% of C++ online submissions for Maximum Alternating Subsequence Sum.
// Memory Usage: 91.1 MB, less than 84.33% of C++ online submissions for Maximum Alternating Subsequence Sum.
class Solution {
public:
    long long maxAlternatingSum(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        /// Don't use current number.
        long long nextPlus = 0;

        /// Use current number as the first number.
        long long nextMinus = 0;

        for (const auto& num: nums) {
            long long nextNextPlus = std::max(nextPlus, nextMinus - num);
            long long nextNextMinus = std::max(nextMinus, nextPlus + num);

            nextPlus = nextNextPlus;
            nextMinus = nextNextMinus;
        }

        return std::max(nextPlus, nextMinus);
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maxAlternatingSum(nums);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({4,2,5,3}, 7);
    test({5,6,7,8}, 8);
    test({6,2,1,2,4,5}, 10);
    test({4,2,3,7,2,1,4}, 12);
    test({374,126,84,237,195,139,328,353,286,113,351,167,394,398,29,118,17,162,206,138,34,109,291,368,162,109,336,256,203,330,235,74,136,72,127,382,288,276,135,383,300,220,299,205,186,113,71,261,253,47,387,25,57,79,322,82,349,217,306,33,198,196,306,240,271,129,284,6,349,370,59,350,275,385,137,394,329,175,58,151,223,81,233,2,370,369,135,257,391,92,260,55,321,153,328,260,312,102,79,192}, 7256);

    return 0;
}
