/*
 * 877. Stone Game
 * https://leetcode.com/problems/stone-game/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP (revisit)
/*
 * Ignore the "`piles.length` is even" constraint when using this solution.
 * It's misleading to this specific solution.
 */
// Runtime: 31 ms, faster than 11.51% of C++ online submissions for Stone Game.
// Memory Usage: 16.4 MB, less than 17.09% of C++ online submissions for Stone Game.
class Solution {
public:
    bool stoneGame(const std::vector<int>& piles) {
        if (piles.size() == 2) {
            // Edge case: Can always choose the larger pile.
            return true;
        }

        /// Current turn winning delta.
        auto winningDelta = std::vector<std::vector<int>>(piles.size(), std::vector<int>(piles.size(), INT_MIN));

        // Length 1: always winnable.
        for (int start = 0; start < piles.size(); start += 1) {
            winningDelta[start][start] = piles[start];
        }

        // Longer lengths.
        for (int length = 2; length <= piles.size(); length += 1) {
            for (int start = 0; start < (piles.size() - length + 1); start += 1) {
                const int end = start + length - 1;

                const int result1 = piles[start] - winningDelta[start + 1][end];
                const int result2 = piles[end] - winningDelta[start][end - 1];

                winningDelta[start][end] = std::max(result1, result2);
            }
        }

        return (winningDelta.front().back() > 0);

        /*
         * Well, somehow I got carried away using step size 2 (because the total pile count is always even).
         * They shouldn't have given this condition in the description :(
         */
//        for (int start = 0; start < piles.size(); start += 2) {
//            const int end = start + 1;
//
//            const int delta = std::abs(piles[start] - piles[end]);
//            winningDelta[start][end] = delta;
//        }
//
//        // Longer lengths.
//        for (int length = 4; length <= piles.size(); length += 2) {
//            auto currentWinningMoves = std::vector<bool>();
//
//            // [0, length) segment.
//            // Only check [0, length - 2) and [2, length)
//            if (winningMoves[0][length - 3] && winningMoves[2][length - 1]) {
//                winningMoves[0][length - 1] = true;
//            }
//
//            // Upcoming segments.
//            for (int start = 2; start < (piles.size() - length); start += 2) {
//                const int end = start + length - 1;
//
//                if (winningMoves[start][end - 2] && winningMoves[start + 2][end] && winningMoves[])
//            }
//        }
    }
};


#pragma mark - 2. Even and odd indices (revisit)
/*
 * The length of `piles` is always even.
 *
 * Note that when player 1 chooses the even indices, player 2 must choose odd.
 * And vice versa.
 *
 * Player 1 can always pick the indices group with more stones.
 */
class Solution2 {
public:
    bool stoneGame(const std::vector<int>& piles) {
        return true;

//        if (piles.size() == 2) {
//            // Edge case: Can always choose the larger pile.
//            return true;
//        }

//        int evenSum = 0;
//        int oddSum = 0;
    }
};


void test(const std::vector<int>& piles, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.stoneGame(piles);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << piles << ": " << std::boolalpha << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << piles << ": " << std::boolalpha << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({5,3,4,5}, true);
    test({3,7,2,3}, true);
    test({1,3,4,1}, true);
    test({1,2}, true);
    test({3,5,3,2}, true);

    return 0;
}
