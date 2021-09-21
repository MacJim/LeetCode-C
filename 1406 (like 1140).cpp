/*
 * 1406. Stone Game III
 * https://leetcode.com/problems/stone-game-iii/
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DFS/recursion with DP, like 1140. Stone Game II
// Runtime: 268 ms, faster than 42.03% of C++ online submissions for Stone Game III.
// Memory Usage: 143.4 MB, less than 17.92% of C++ online submissions for Stone Game III.
class Solution {
private:
    std::pair<int, int> recursion(const std::vector<int>& stoneValues, std::vector<int>& player1Scores, std::vector<int>& player2Scores, const int startIndex) {
        if (startIndex > stoneValues.size()) {
            return std::make_pair(INT_MIN, INT_MIN);
        } else if (startIndex == stoneValues.size()) {
            return std::make_pair(0, 0);
        }

        if (player1Scores[startIndex] != INT_MIN) {
            return std::make_pair(player1Scores[startIndex], player2Scores[startIndex]);
        }

        for (int count = 1; count <= 3; count += 1) {
            auto currentScores = recursion(stoneValues, player1Scores, player2Scores, startIndex + count);
            if (currentScores.first == INT_MIN) {
                // Out of bounds.
                break;
            }

            // Calculate current sum.
            // MARK: Again, this part can be optimized using a prefix sum.
            for (int i = startIndex; i < (startIndex + count); i += 1) {
                currentScores.second += stoneValues[i];
            }

            /*
             * Note that both players play optimally.
             * Thus, the current player (player 1) chooses the max gain for all turns.
             *
             * See also: 1140. Stone Game II.
             */
            if (currentScores.second > player1Scores[startIndex]) {
                player1Scores[startIndex] = currentScores.second;
                player2Scores[startIndex] = currentScores.first;
            }
        }

        return std::make_pair(player1Scores[startIndex], player2Scores[startIndex]);
    }

public:
    std::string stoneGameIII(const std::vector<int>& stoneValues) {
        auto player1Scores = std::vector<int>(stoneValues.size(), INT_MIN);    // It's guaranteed that the total score is bigger than `INT_MIN`.
        auto player2Scores = player1Scores;

        recursion(stoneValues, player1Scores, player2Scores, 0);

        if (player1Scores[0] > player2Scores[0]) {
            return "Alice";
        } else if (player1Scores[0] == player2Scores[0]) {
            return "Tie";
        } else {
            return "Bob";
        }
    }
};


void test(const std::vector<int>& stoneValues, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.stoneGameIII(stoneValues);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << stoneValues << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << stoneValues << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,7}, "Bob");
    test({1,2,3,-9}, "Alice");
    test({1,2,3,6}, "Tie");
    test({1,2,3,-1,-2,-3,7}, "Alice");
    test({-1,-2,-3}, "Tie");

    return 0;
}
