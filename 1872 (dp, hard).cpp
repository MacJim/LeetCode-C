/*
 * 1872. Stone Game VIII
 * https://leetcode.com/problems/stone-game-viii/
 */

/*
 * - Stone sum never change
 * - Last move gets the total sum
 *
 * dp[i]: first mover's score advantage when choosing from [i, end].
 * That is: stones [0, i - 1] are merged into a single stone.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP
// Runtime: 148 ms, faster than 71.19% of C++ online submissions for Stone Game VIII.
// Memory Usage: 90.9 MB, less than 30.85% of C++ online submissions for Stone Game VIII.
class Solution1 {
private:
    std::vector<int> prefixSum = std::vector<int>();

    inline void initializePrefixSum(const std::vector<int>& stones) {
        prefixSum.reserve(stones.size() + 1);
        prefixSum.push_back(0);
        for (const int& value: stones) {
            const int currentSum = prefixSum.back() + value;
            prefixSum.push_back(currentSum);
        }
    }

    inline int getSum(const int start, int end) {    // Optimize: `start` always equals 0
        end += 1;
        return prefixSum[end] - prefixSum[start];
    }

public:
    int stoneGameVIII(std::vector<int>& stones) {
        if (stones.size() == 2) {
            // Edge case.
            return stones[0] + stones[1];
        }

        initializePrefixSum(stones);

        /**
         * [i, stones.size()) First picker's advantage.
         *
         * The front element is unused (as we cannot pick a single leading number).
         */
        auto dp = std::vector<int>(stones.size(), INT_MIN);
        dp.back() = prefixSum.back();    // Sum all elements together.

        const int end = stones.size() - 1;

        for (int start = (end - 1); start > 0; start -= 1) {    // Index 0 is unused.
            /*
             * - Candidate 1: sum[0, start] - dp[start + 1]
             * - Candidate 2: dp[start + 1]
             *   - We know that `dp[start + 1]` must contain all previous numbers
             */
            const int candidate1 = getSum(0, start) - dp[start + 1];
            dp[start] = std::max(candidate1, dp[start + 1]);
        }

        return dp[1];
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 136 ms, faster than 91.86% of C++ online submissions for Stone Game VIII.
// Memory Usage: 90.9 MB, less than 30.85% of C++ online submissions for Stone Game VIII.
class Solution {
private:
    std::vector<int> prefixSum = std::vector<int>();

    inline void initializePrefixSum(const std::vector<int>& stones) {
        prefixSum.reserve(stones.size());    // Just use the same size as `stone` as we always calculate from `start == 0`.
        prefixSum.push_back(stones[0]);
        for (int i = 1; i < stones.size(); i += 1) {
            const int currentSum = prefixSum.back() + stones[i];
            prefixSum.push_back(currentSum);
        }
    }

    inline int getSumFromStart(int end) {
        return prefixSum[end];
    }

public:
    int stoneGameVIII(std::vector<int>& stones) {
        if (stones.size() == 2) {
            // Edge case.
            return stones[0] + stones[1];
        }

        initializePrefixSum(stones);

        /**
         * [i, stones.size()) First picker's advantage.
         *
         * The front element is unused (as we must pick at least 2 numbers, and cannot pick a single leading number).
         */
        auto dp = std::vector<int>(stones.size(), INT_MIN);
        dp.back() = prefixSum.back();    // Sum all elements together.

        const int end = stones.size() - 1;
        for (int start = (end - 1); start > 0; start -= 1) {    // Index 0 is unused (as we must pick at least 2 numbers, and cannot pick a single leading number).
            /*
             * - Candidate 1: sum[0, start] - dp[start + 1]
             * - Candidate 2: dp[start + 1]
             *   - We know that `dp[start + 1]` must contain all previous numbers
             */
            const int candidate1 = getSumFromStart(start) - dp[start + 1];
            dp[start] = std::max(candidate1, dp[start + 1]);
        }

        return dp[1];
    }
};


void test(const std::vector<int>& stones, const int expectedResult) {
    auto solutionInstance = Solution();

    auto stonesCopy = stones;
    auto result = solutionInstance.stoneGameVIII(stonesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << stones << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << stones << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({-3,-5,3}, -3);
    test({-10,-12}, -22);
    test({-1,2,-3,4,-5}, 5);
    test({7,-6,5,10,5,-2,-6}, 13);

    return 0;
}
