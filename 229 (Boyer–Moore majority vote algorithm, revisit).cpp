/*
 * 229. Majority Element II
 * https://leetcode.com/problems/majority-element-ii/
 */

#include <iostream>
#include <vector>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort
// Runtime: 8 ms, faster than 95.37% of C++ online submissions for Majority Element II.
// Memory Usage: 15.9 MB, less than 44.91% of C++ online submissions for Majority Element II.
class Solution1 {
public:
    std::vector<int> majorityElement(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums;
        }

        const auto threshold = nums.size() / 3;

        std::sort(nums.begin(), nums.end());

        auto returnValue = std::vector<int>();

        int currentNum = INT_MAX;
        int currentCount = 0;
        for (const auto& num: nums) {
            if (num == currentNum) {
                currentCount += 1;
            } else {
                if (currentCount > threshold) {
                    returnValue.push_back(currentNum);
                }

                currentNum = num;
                currentCount = 1;
            }
        }

        if (currentCount > threshold) {
            returnValue.push_back(currentNum);
        }

        return returnValue;
    }
};


#pragma mark - 2. Unordered map


#pragma mark - 3. Boyer-Moore Majority Vote algorithm (good to know)
/*
 * Source: https://leetcode.com/problems/majority-element-ii/discuss/63520/Boyer-Moore-Majority-Vote-algorithm-and-my-elaboration
 *
 * Hmm.
 * So this algorithm can be applied to more than 1 element.
 */
// Runtime: 20 ms, faster than 5.58% of C++ online submissions for Majority Element II.
// Memory Usage: 15.7 MB, less than 78.13% of C++ online submissions for Majority Element II.
class Solution {
public:
    std::vector<int> majorityElement(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums;
        }

        // Pass 1: Find the 2 candidates.
        int num1 = INT_MAX;
        int num2 = INT_MAX;
        int count1 = 0;
        int count2 = 0;

        for (const auto& num: nums) {
            if (num == num1) {
                count1 += 1;
            } else if (num == num2) {
                count2 += 1;
            } else if (count1 == 0) {    // `if (count == 0)` must appear after `num == num1` and `num == num2`. Otherwise, it may wrongly overwrite the other number with count 0.
                num1 = num;
                count1 = 1;
            } else if (count2 == 0) {
                num2 = num;
                count2 = 1;
            } else {
                count1 -= 1;
                count2 -= 1;
            }
        }

        // Pass 2: Verify the candidates.
        count1 = 0;
        count2 = 0;
        for (const auto& num: nums) {
            if (num == num1) {
                count1 += 1;
            } else if (num == num2) {
                count2 += 1;
            }
        }

        auto returnValue = std::vector<int>();
        const auto threshold = nums.size() / 3;
        if (count1 > threshold) {
            returnValue.push_back(num1);
        }
        if (count2 > threshold) {
            returnValue.push_back(num2);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::set<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.majorityElement(numsCopy);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,1,1,3,1,4,5,6}, {1});
    test({1,1}, {1});
    test({3,2,3}, {3});
    test({1,1,2,2,2,3,3,3}, {2,3});

    return 0;
}
