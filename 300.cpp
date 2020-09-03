/*
 * 300. Longest Increasing Subsequence
 * https://leetcode.com/problems/longest-increasing-subsequence/
 */

#include <iostream>
#include <vector>
//#include <map>
#include <unordered_map>
#include <climits>
#include <algorithm>    // std::upper_bound

#include "helpers/Operators.hpp"


#pragma mark - 1. Wrong understanding of the problem
class Solution1 {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        if (nums.size() == 1) {
            return 1;
        }

        int returnValue = 0;
        int length = 0;
        int& previousNum = nums[0];
        for (const auto& num: nums) {
            if (num > previousNum) {
                length += 1;
            } else {
                if (length > returnValue) {
                    returnValue = length;
                }
            }
            previousNum = num;
        }

        if (length > returnValue) {
            return length;
        } else {
            return returnValue;
        }
    }
};


#pragma mark - 2. Use secondary array to store current optimal sequence
/*
 * Make sure to consider the equal case when doing comparisons (see "Equal case here" comments).
 * Ignoring the equal cases may result in duplicate numbers in the `minValues` array.
 */
// Runtime: 20 ms, faster than 70.35% of C++ online submissions for Longest Increasing Subsequence.
// Memory Usage: 7.8 MB, less than 63.00% of C++ online submissions for Longest Increasing Subsequence.
class Solution2 {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        if (nums.size() == 1) {
            return 1;
        }

        auto minValues = std::vector<int>();
        for (const auto& num: nums) {
            if (minValues.empty()) {
                // This is the first number.
                minValues.push_back(num);
            } else {
                if (minValues.size() > 1) {
                    // 0
                    if (num <= minValues[0]) {    // Equal case here. See comments above.
                        minValues[0] = num;
                        continue;
                    }

                    // 1 ~ (size - 2)
                    bool shouldContinue = false;
                    for (size_t i = 0; i < (minValues.size() - 1); i += 1) {
                        auto& currentMinVal = minValues[i];
                        if (num <= currentMinVal) {    // Equal case here. See comments above.
                            currentMinVal = num;
                            shouldContinue = true;
                            break;
                        }
                    }
                    if (shouldContinue) {
                        continue;
                    }
                }

                // Final number (size - 1)
                if (num <= minValues.back()) {    // Equal case here. See comments above.
                    minValues.back() = num;
                } else if (num > minValues.back()) {
                    // This number is larger than all numbers in the `minValues` array.
                    minValues.push_back(num);
                }
            }
        }

        return minValues.size();
    }
};


#pragma mark - 3. Optimized 2
// Runtime: 4 ms, faster than 98.42% of C++ online submissions for Longest Increasing Subsequence.
// Memory Usage: 7.9 MB, less than 52.89% of C++ online submissions for Longest Increasing Subsequence.
class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        if (nums.size() == 1) {
            return 1;
        }

        auto minValues = std::vector<int>();
        for (const auto& num: nums) {
            if (minValues.empty()) {
                minValues.push_back(num);
            } else if (num > minValues.back()) {
                /*
                 * We know that the last number is the largest since we either:
                 *
                 * - Replace an existing number with a smaller number
                 * - Push the largest number to the back of `minValues`
                 *
                 * Thus, comparing with the last number is enough.
                 */
                minValues.push_back(num);
            } else {
                /*
                 * Use `std::upper_bound` to get an iterator pointing to the first element which compares greater than `val`.
                 * Catch: If no element in the range compares greater than val, the function returns `last`.
                 *
                 * Strangely though, there doesn't seem to be a "greater or equal" function in C++.
                 * Thus, I used `num - 1` to count in the equal case.
                 */
                auto it = std::upper_bound(minValues.begin(), minValues.end(), num - 1);
                *it = num;
            }
        }

        return minValues.size();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<int>> testCases = {
        {10,9,2,5,3,7,101,18},    // 4
        {1},    // 1
        {1,1,1,1,1,1,1,1},    // 1
        {5,8,7,4,6,7,9},    // 4
        {0,3,1,4,5,0,7,8},    // 6
        {4,10,4,3,8,9},    // 3
    };
    for (auto& testCase: testCases) {
        std::cout << testCase << ": " << solutionInstance.lengthOfLIS(testCase) << std::endl;
    }

    return 0;
}
