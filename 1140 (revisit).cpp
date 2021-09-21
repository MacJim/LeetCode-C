/*
 * 1140. Stone Game II
 * https://leetcode.com/problems/stone-game-ii/
 */

#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DFS/recursion DP (revisit, see the "MARK: Difficult" part)
// Runtime: 180 ms, faster than 13.35% of C++ online submissions for Stone Game II.
// Memory Usage: 14.9 MB, less than 13.04% of C++ online submissions for Stone Game II.
/*
 * dp[start index][M]
 *
 * Cache results of a specific M and indices [i, inf).
 *
 * Each pair: (first picker/1P, second picker/2P).
 */
using DP = std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>>;


class Solution {
private:
    std::pair<int, int> recursion(const std::vector<int>& piles, DP& dp, const int startIndex, const int M) {
        if (startIndex >= piles.size()) {
            return std::make_pair(0, 0);
        }

        if (dp[startIndex].count(M)) {
            return dp[startIndex][M];
        }

        /// The max amount of piles for the current player to pick.
        const int upperLimit = std::min(static_cast<int>(piles.size()) - startIndex, 2 * M);

        // 1 <= x <= upperLimit
        for (int x = 1; x <= upperLimit; x += 1) {
            const int nextIndex = startIndex + x;

            auto currentResult = recursion(piles, dp, nextIndex, std::max(M, x));
            // Swap the positions because current `first` is calculated from the previous `second`.
            std::swap(currentResult.first, currentResult.second);

            // Take the stones within [startIndex, nextIndex).
            // MARK: Can use prefix sum to optimize this part.
            for (int i = startIndex; i < nextIndex; i += 1) {
                currentResult.first += piles[i];
            }

            /*
             * MARK: Difficult
             *
             * We assume that players want to maximize their profit in every scenario.
             *
             * The current player is represented by `currentResult.first`.
             * Thus, we only compare `first` with our `dp` cache.
             */
            if (currentResult.first > dp[startIndex][M].first) {
                dp[startIndex][M] = std::move(currentResult);
            }
        }

        return dp[startIndex][M];
    }

public:
    int stoneGameII(const std::vector<int>& piles) {
        if (piles.size() <= 2) {
            // Edge case: Player 1 takes all.
            return std::accumulate(piles.begin(), piles.end(), 0);
        }

        auto dp = DP();

        recursion(piles, dp, 0, 1);

        int returnValue = 0;
        for (const auto& [_, pair]: dp[0]) {
            returnValue = std::max(returnValue, pair.first);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& piles, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.stoneGameII(piles);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << piles << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << piles << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,7,9,4,4}, 10);
    test({1,2,3,4,5,100}, 104);

    return 0;
}
