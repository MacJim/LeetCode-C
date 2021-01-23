/*
 * 1673. Find the Most Competitive Subsequence
 * https://leetcode.com/problems/find-the-most-competitive-subsequence/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Stack (unused)
class Solution1 {
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k) {
        if (nums.size() == k) {
            return nums;
        }

        auto returnValue = std::vector<int>();

        for (size_t i = 0; i < nums.size(); i += 1) {
            const auto cacheStackRemainingSize = k - returnValue.size();
            const auto remainingNumsCount = nums.size() - i;

            const auto popLimit = remainingNumsCount - cacheStackRemainingSize;

            if (popLimit == 0) {
                // Just enough remaining numbers.
                // Do not pop elements from the return value.
                returnValue.push_back(nums[i]);
                continue;
            }

            // Choose to pop.

        }

        return returnValue;
    }
};


#pragma mark - 2. Unused
class Solution2 {
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k) {
        if (nums.size() == k) {
            return nums;
        }

        auto returnValue = std::vector<int>();

        for (size_t i = 0; i < nums.size(); i += 1) {
            const auto returnValueRemainingSize = k - returnValue.size();
            const auto remainingNumsCount = nums.size() - i;

            const auto popLimit = remainingNumsCount - returnValueRemainingSize;

            if (popLimit == 0) {
                // Just enough remaining numbers.
                // Do not pop elements from the return value.
                returnValue.insert(returnValue.end(), nums.begin() + i, nums.end());
                break;
            }

            // Choose to insert to return value.
        }

        return returnValue;
    }
};


#pragma mark - 3. Select one smallest number at a time
// Time Limit Exceeded.
// 83 / 86 test cases passed.
class Solution3 {
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k) {
        if (nums.size() == k) {
            return nums;
        }

        auto returnValue = std::vector<int>();

        size_t startIndex = 0;
        size_t endIndex = nums.size() - k;

        while (returnValue.size() < k) {
            const auto remainingReturnValueCount = k - returnValue.size();
            const auto remainingNumsCount = nums.size() - startIndex;
            if (remainingNumsCount == remainingReturnValueCount) {
                for (size_t i = startIndex; i < nums.size(); i += 1) {
                    const auto& num = nums[i];
                    returnValue.push_back(num);
                }
                break;
            }

            int smallestNum = INT_MAX;
            size_t smallestIndex = 0;

            for (size_t i = startIndex; i <= endIndex; i += 1) {
                const auto& num = nums[i];
                if (num < smallestNum) {
                    smallestNum = num;
                    smallestIndex = i;
                }
            }

            returnValue.push_back(smallestNum);
            startIndex = smallestIndex + 1;

            endIndex += 1;
        }

        return returnValue;
    }
};


#pragma mark - 4. Fixed 1
// Runtime: 188 ms, faster than 98.27% of C++ online submissions for Find the Most Competitive Subsequence.
// Memory Usage: 109.7 MB, less than 44.65% of C++ online submissions for Find the Most Competitive Subsequence.
class Solution {
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k) {
        if (nums.size() == k) {
            return nums;
        }

        auto returnValue = std::vector<int>();

        for (size_t i = 0; i < nums.size(); i += 1) {
            const auto& num = nums[i];

            const auto remainingNumsCount = nums.size() - i - 1;    // Note the -1 here. We cannot count the current number in.
            while ((!returnValue.empty()) && (returnValue.back() > num) && ((k - returnValue.size()) <= remainingNumsCount)) {
                returnValue.pop_back();
            }

            if (returnValue.size() < k) {
                returnValue.push_back(num);
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int k, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.mostCompetitive(numsCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << " " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << " " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,5,2,6}, 2, {2,6});
    test({2,4,3,3,5,4,9,6}, 4, {2,3,3,4});
    test({9,4,2,5,1,3}, 3, {2,1,3});
    test({9,4,2,5,1,3}, 2, {1,3});
    test(std::vector<int>(100000, 0), 50000, std::vector<int>(50000, 0));

    return 0;
}
