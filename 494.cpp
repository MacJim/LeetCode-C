/*
 * 494. Target Sum
 * https://leetcode.com/problems/target-sum/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
//#include <algorithm>
#include <numeric>

#include "helpers/Operators.hpp"


#pragma mark - 1. Hash map
// Runtime: 168 ms, faster than 39.95% of C++ online submissions for Target Sum.
// Memory Usage: 46.9 MB, less than 18.98% of C++ online submissions for Target Sum.
class Solution1 {
public:
    int findTargetSumWays(std::vector<int>& nums, const int S) {
        /// (sum, count)
        auto prevSums = std::unordered_map<int, int>({{0, 1}});

        for (const auto& n: nums) {
            auto currSums = std::unordered_map<int, int>();

            for (const auto& [sum, count]: prevSums) {
                const int newSum1 = sum + n;
                const int newSum2 = sum - n;

                currSums[newSum1] += count;    // Zero-initialized if the key does not exist.
                currSums[newSum2] += count;
            }

            prevSums = std::move(currSums);
        }

        return prevSums[S];    // Zero-initialized if the key does not exist.
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 124 ms, faster than 43.08% of C++ online submissions for Target Sum.
// Memory Usage: 38.8 MB, less than 21.23% of C++ online submissions for Target Sum.
class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, const int S) {
        const auto sum = std::accumulate(nums.begin(), nums.end(), 0);
        if ((sum < S) || ((sum + S) % 2)) {
            // Smaller sum, or ever vs odd.
            return 0;
        }

        /// (sum, count)
        auto prevSums = std::unordered_map<int, int>({{0, 1}});

        for (const auto& n: nums) {
            auto currSums = std::unordered_map<int, int>();

            for (const auto& [sum, count]: prevSums) {
                const int newSum1 = sum + n;
                const int newSum2 = sum - n;

                currSums[newSum1] += count;    // Zero-initialized if the key does not exist.
                currSums[newSum2] += count;
            }

            prevSums = std::move(currSums);
        }

        return prevSums[S];    // Zero-initialized if the key does not exist.
    }
};


#pragma mark - 3. Replace hash map with a vector of size 2001
/*
 * We know that the sum of elements in the given array will not exceed 1000.
 * So just record values from [-1000, 1000]
 */


void test(const std::vector<int>& nums, const int S, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findTargetSumWays(numsCopy, S);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << " " << S << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << " " << S << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1, 1, 1, 1, 1}, 3, 5);
    test({2, 2, 2, 2, 2}, 3, 0);
    test({1, 2}, 3, 1);

    return 0;
}
