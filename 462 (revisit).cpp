/*
 * 462. Minimum Moves to Equal Array Elements II
 * https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
 */

#include <iostream>
#include <vector>
#include <climits>
#include <numeric>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Binary search on the target number
/*
 * Problem: equal cases caused by over-shooting.
 * Example: (1, 20, 1) with 0 and 4 both yield 22.
 *
 * So binary search is only applicable when the data is sorted.
 */
class Solution1 {
private:
    inline int calculateReturnValue(const std::vector<int>& nums, const int target) {
        int returnValue = 0;

        for (const auto& num: nums) {
            returnValue += std::abs(num - target);
        }

        return returnValue;
    }

public:
    int minMoves2(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        // Initial boundaries
        int minNum = INT_MAX;
        int maxNum = INT_MIN;
        for (const auto& num: nums) {
            minNum = std::min(minNum, num);
            maxNum = std::max(maxNum, num);
        }

        if (minNum == maxNum) {
            // Edge case: All numbers equal.
            return 0;
        }

        int returnValue = 0;
        int bestTarget = -1;

        // Binary search.
        while (minNum <= maxNum) {    // Terminates when `(minNum + 1) == maxNum`
            const int mid = (minNum + maxNum) / 2;

            const int currentValue = calculateReturnValue(nums, mid);
            if (currentValue == returnValue) {
                // The optimal return value should be between [bestTarget, mid].
                if (bestTarget == mid) {
                    return returnValue;
                } else if (bestTarget < mid) {
                    minNum = bestTarget;
                    maxNum = mid;
                } else {
                    minNum = mid;
                    maxNum = bestTarget;
                }
            } else if (currentValue < returnValue) {
                returnValue = currentValue;
                bestTarget = mid;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Separate into left and right parts, and update each part's required moves in a rolling fashion (somewhat like rolling hash) to reduce the amount of calculations needed
/*
 * Well, I devised this solution in an hour.
 *
 * It may be more convenient to just calculate left and right sums respectively, and add them up.
 */
// Runtime: 8 ms, faster than 94.44% of C++ online submissions for Minimum Moves to Equal Array Elements II.
// Memory Usage: 11.2 MB, less than 14.09% of C++ online submissions for Minimum Moves to Equal Array Elements II.
class Solution2 {
public:
    int minMoves2(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        // Calculate deltas between adjacent nums.
        auto delta = std::vector<int>(nums.size(), 0);    // The last element is left unused. It is there to prevent overflows in the main loop.
        for (size_t i = 1; i < nums.size(); i += 1) {
            delta[i - 1] = nums[i] - nums[i - 1];
        }

        // Initially, the right segment contains all numbers other than the first one.
        long long leftSum = 0;    // Have to use 64-bit int to prevent addition overflow (this is a cumulative sorting solution after all).
        long long rightSum = 0;
        for (int i = 1; i < (nums.size() - 1); i += 1) {
            rightSum += delta[delta.size() - i - 1] * i;    // Note that the last element of `delta` is unused.
        }

        long long returnValue = LONG_LONG_MAX;

        // Main loop: rolling fashion.
        // [0, separationPoint], (separationPoint, nums.size() - 1]
        for (int separationPoint = 0; separationPoint < (nums.size() - 1); separationPoint += 1) {
            const int leftLength = separationPoint + 1;
            const int rightLength = nums.size() - leftLength;

            const long long currentValue = leftSum + rightSum + std::min(leftLength, rightLength) * delta[separationPoint];
            if (currentValue > returnValue) {
                // If it's increasing, abort because it'll just continue to increase in later loops.
                break;
            }

            returnValue = currentValue;

            // Update sums in a rolling fashion.
            leftSum += leftLength * delta[separationPoint];
            rightSum -= (rightLength - 1) * delta[separationPoint + 1];
        }

        return static_cast<int>(returnValue);
    }
};


#pragma mark - 3. Math solution: make all elements equal to the median
// Runtime: 18 ms, faster than 7.86% of C++ online submissions for Minimum Moves to Equal Array Elements II.
// Memory Usage: 10.8 MB, less than 91.85% of C++ online submissions for Minimum Moves to Equal Array Elements II.
class Solution {
public:
    int minMoves2(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int median = nums[nums.size() / 2];

        int returnValue = 0;
        for (const int& num: nums) {
            returnValue += std::abs(num - median);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.minMoves2(numsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({203125577,-349566234,230332704,48321315,66379082,386516853,50986744,-250908656,-425653504,-212123143}, 2127271182);
    test({1,10,2,9}, 16);
    test({1,2,3}, 2);
    test({1,20,1}, 19);

    return 0;
}
