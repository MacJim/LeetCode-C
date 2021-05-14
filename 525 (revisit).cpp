/*
 * 525. Contiguous Array
 * https://leetcode.com/problems/contiguous-array/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"


/*
 * At first glance, doesn't seem like a 2 pointer problem because we don't want to increase `left`.
 */


#pragma mark - 1. Binary search (wrong)
class Solution1 {
public:
    int findMaxLength(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }

        /// Initial value is always 0.
        auto zeroSums = std::vector<int>(nums.size() + 1, 0);
        auto oneSums = std::vector<int>(nums.size() + 1, 0);

        for (size_t i = 0; i < nums.size(); i += 1) {
            if (nums[i] == 0) {
                zeroSums[i + 1] = zeroSums[i] + 1;
                oneSums[i + 1] = oneSums[i];
            } else {
                zeroSums[i + 1] = zeroSums[i];
                oneSums[i + 1] = oneSums[i] + 1;
            }
        }

        if (zeroSums.back() == oneSums.back()) {
            return nums.size();
        } else if (zeroSums.back() < oneSums.back()) {
            // More 0 than 1.

        } else {
            // More 1 than 0.
        }

        int returnValue = 0;

//        int left = 0;
//        int right = 0;
//
//        int zeroCount = 0;
//        int oneCount = 0;
//
//        while (right < nums.size()) {
//            if (zeroCount == oneCount) {
//            }
//        }

        return returnValue;
    }
};


#pragma mark - 2. DP
// WRONG ANSWER because all 1/0 sequences are ignored in earlier iterations.
class Solution2 {
public:
    int findMaxLength(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }

        int returnValue = 0;
        auto dp = std::vector<std::vector<bool>>(nums.size(), std::vector<bool>(nums.size(), false));

        // Distance = 2
        for (int start = 0; start < (nums.size() - 1); start += 1) {
            const auto end = start + 1;
            if (nums[start] != nums[end]) {
                dp[start][end] = true;
                returnValue = 2;
            }
        }

        // Bigger distances.
        for (int distance = 4; distance <= (nums.size()); distance += 2) {
            for (int start = 0; start < (nums.size() - distance + 1); start += 1) {
                const auto end = start + distance - 1;

                for (int mid = start + 2; mid < end; mid += 2) {
                    if (dp[start][mid - 1] && dp[mid][end]) {
                        dp[start][end] = true;
                        returnValue = distance;
                        break;
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 4. Convert to zero-sum (revisit)
// Source: https://leetcode.ca/2017-05-08-525-Contiguous-Array/
// Runtime: 96 ms, faster than 93.98% of C++ online submissions for Contiguous Array.
// Memory Usage: 83.5 MB, less than 48.98% of C++ online submissions for Contiguous Array.
class Solution {
public:
    int findMaxLength(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }

        int returnValue = 0;

        int currentSum = 0;
        /// (value, first occurrence)
        auto sumsCache = std::unordered_map<int, int>({{0, -1}});
        for (int i = 0; i < nums.size(); i += 1) {
            if (nums[i] == 1) {
                currentSum += 1;
            } else {
                currentSum -= 1;
            }

            // Don't use the exception approach: It's slower and uses more memory.
//            try {
//                // This element exists in the sums cache.
//                auto& previousOccurrence = sumsCache.at(currentSum);
//                const auto distance = i - previousOccurrence;
//                returnValue = std::max(returnValue, distance);
//            } catch (std::out_of_range& e) {
//                // This element does not exist in the sums cache.
//                sumsCache[currentSum] = i;
//            }

            auto it = sumsCache.find(currentSum);
            if (it == sumsCache.end()) {
                // This element does not exist in the sums cache.
                sumsCache[currentSum] = i;
            } else {
                // This element exists in the sums cache.
                const auto distance = i - it->second;
                returnValue = std::max(returnValue, distance);
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findMaxLength(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,0,1,1,0,1,1,1,1,1,1,1,1,1}, 6);
    test({0,0,0,1,1,1}, 6);
    test({0,0,1,1,0,1}, 6);

    test({0,1}, 2);
    test({0,1,0}, 2);
    test({0,1,0,1}, 4);
    test({0,1,1,0}, 4);

    test({0,0,0}, 0);
    test({0,0,0,0}, 0);
    test({1,1,1}, 0);
    test({1,1,1,1}, 0);

    test({0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0}, 4);

    return 0;
}
