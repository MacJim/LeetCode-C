/*
 * 1856. Maximum Subarray Min-Product
 * https://leetcode.com/problems/maximum-subarray-min-product/
 */

/*
 * I hate dealing with overflows.
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP-like but doing a lot of extra calculations
// Time Limit Exceeded
class Solution1 {
private:
    static constexpr int MOD = 1000000007;

public:
    int maxSumMinProduct(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            // Edge case.
            return nums[0] * nums[0];
        }

        long long returnValue = 0;

        // Len = 1.
        for (size_t i = 0; i < nums.size(); i += 1) {
            const long long newProduct = static_cast<long long>(nums[i]) * static_cast<long long>(nums[i]);
            returnValue = std::max(returnValue, newProduct);
        }

        // Len > 1
        auto mins = nums;
        auto sums = std::vector<long long>(nums.begin(), nums.end());

        for (size_t len = 2; len <= nums.size(); len += 1) {
            for (size_t i = 0; i <= (nums.size() - len); i += 1) {
                const int nextNum = nums[i + len - 1];

                mins[i] = std::min(mins[i], nextNum);
                sums[i] += nextNum;

                const long long newProduct = static_cast<long long>(mins[i]) * sums[i];

                returnValue = std::max(returnValue, newProduct);
            }
        }

        return returnValue % MOD;
    }
};


#pragma mark - 2. Jump (like problem 84)
/*
 * 2 basic principles:
 *
 * - Log and jump to previous and next non-smaller elements: like problem 84
 * - Use "cumulative sum" to calculate range sums quickly
 */
// Runtime: 180 ms, faster than 93.84% of C++ online submissions for Maximum Subarray Min-Product.
// Memory Usage: 89.4 MB, less than 58.08% of C++ online submissions for Maximum Subarray Min-Product.
class Solution2 {
private:
    static constexpr int MOD = 1000000007;

public:
    int maxSumMinProduct(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            // Edge case.
            return (static_cast<long long>(nums[0]) * static_cast<long long>(nums[0])) % MOD;
        }

        // Cumulative sum.
        /// 1-indexed. The 0-th element is always 0.
        auto cumulativeSum = std::vector<long long>(nums.size() + 1, 0);
        cumulativeSum[1] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            cumulativeSum[i + 1] = nums[i] + cumulativeSum[i];
        }

        // Previous and next non-smaller elements.
        auto previousSmallerIndices = std::vector<int>(nums.size(), -1);
        for (int i = 1; i < nums.size(); i += 1) {
            int previousIndex = i - 1;

            while ((previousIndex != -1) && (nums[i] <= nums[previousIndex])) {    // Jump
                previousIndex = previousSmallerIndices[previousIndex];
            }

            previousSmallerIndices[i] = previousIndex;
        }

        auto nextSmallerIndices = std::vector<int>(nums.size(), nums.size());
        for (int i = (nums.size() - 2); i >= 0; i -= 1) {
            int nextIndex = i + 1;

            while ((nextIndex != nums.size()) && (nums[i] <= nums[nextIndex])) {    // Jump
                nextIndex = nextSmallerIndices[nextIndex];
            }

            nextSmallerIndices[i] = nextIndex;
        }

        // Calculate products.
        long long returnValue = 0;

        for (size_t i = 0; i < nums.size(); i += 1) {
            const int rightIndex = nextSmallerIndices[i];    // Right index in `cumulativeSum`.
            const int leftIndex = previousSmallerIndices[i] + 1;
            const long long sum = cumulativeSum[rightIndex] - cumulativeSum[leftIndex];

            const long long product = sum * static_cast<long long>(nums[i]);    // `nums[i]` is always the smallest element in the streak.

            returnValue = std::max(returnValue, product);
        }

        return returnValue % MOD;
    }
};


#pragma mark - 3. Monotonic stack (revisit)
// Runtime: 172 ms, faster than 96.17% of C++ online submissions for Maximum Subarray Min-Product.
// Memory Usage: 84.1 MB, less than 71.62% of C++ online submissions for Maximum Subarray Min-Product.
/*
 * Very similar to solution 2, but harder to implement.
 *
 * Difficult part: need to find both left and right bounds (in previous similar questions only 1 bound was needed) with the stack.
 */
class Solution {
private:
    static constexpr int MOD = 1000000007;

public:
    int maxSumMinProduct(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            // Edge case.
            return (static_cast<long long>(nums[0]) * static_cast<long long>(nums[0])) % MOD;
        }

        // Cumulative sum.
        /// 1-indexed. The 0-th element is always 0.
        auto cumulativeSum = std::vector<long long>(nums.size() + 1, 0);
        cumulativeSum[1] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            cumulativeSum[i + 1] = nums[i] + cumulativeSum[i];
        }

        long long returnValue = 0;
        auto s = std::vector<size_t>();
        for (size_t i = 0; i < nums.size(); i += 1) {
            if (!s.empty()) {
                const int& currentNum = nums[i];

                while ((!s.empty()) && (nums[s.back()] >= currentNum)) {
                    // Need to pop the stack top.
                    const auto minNum = static_cast<long long>(nums[s.back()]);

                    size_t rightIndex = i;

                    s.pop_back();
                    size_t leftIndex = 0;
                    if (!s.empty()) {
                        // Left index is the previous number in the stack.
                        leftIndex = s.back() + 1;
                    }

                    const long long sum = cumulativeSum[rightIndex] - cumulativeSum[leftIndex];
                    const long long product = sum * minNum;

                    returnValue = std::max(returnValue, product);
                }
            }

            s.push_back(i);
        }

        // Check remaining elements in the stack.
        const size_t rightIndex = nums.size();
        while (!s.empty()) {
            const auto minNum = static_cast<long long>(nums[s.back()]);

            s.pop_back();
            size_t leftIndex = 0;
            if (!s.empty()) {
                leftIndex = s.back() + 1;
            }

            const long long sum = cumulativeSum[rightIndex] - cumulativeSum[leftIndex];
            const long long product = sum * minNum;

            returnValue = std::max(returnValue, product);
        }

        return returnValue % MOD;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

//    auto numsCopy = nums;
    auto result = solutionInstance.maxSumMinProduct(nums);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({46341}, 147488267);    // Larger than INT_MAX.
    test({1,2,3,2}, 14);
    test({2,3,3,1,2}, 18);
    test({3,1,5,6,4,2}, 60);
    test({4,10,6,4,8,7,8,3,5,3,4,9,9,5,10,7,10,7,6,4}, 387);

    return 0;
}
