/*
 * 1510. Stone Game IV
 * https://leetcode.com/problems/stone-game-iv/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP
/*
 * For each number, try subtracting all squared numbers that's smaller than it.
 *
 * Very similar to other "Stone Game" series questions (this might be the DP series).
 */
// Runtime: 24 ms, faster than 92.06% of C++ online submissions for Stone Game IV.
// Memory Usage: 6 MB, less than 97.62% of C++ online submissions for Stone Game IV.
class Solution {
private:
    static constexpr int UPPER_LIMIT = 100000;

public:
    static std::vector<bool> results;

public:
    bool winnerSquareGame(int n) {
        if (!results[1]) {
            // Calculate all square numbers.
            /**
             * Square numbers from [1, 317^2].
             * 0 is excluded.
             */
            auto squareNumbers = std::vector<int>();
            /*
             * 10^5 is between 316^2 and 317^2
             * 317 * 317 = 100,489
             * We need to include 317 for the following comparison `squareNum > num` to work.
             */
            squareNumbers.reserve(317);
            for (int i = 1; i <= 317; i += 1) {
                const int currentSquareNumber = i * i;
                squareNumbers.push_back(currentSquareNumber);
            }

            // Calculate all results up to 10^5 right away (we'll likely need all of them anyway).
            for (int num = 1; num <= UPPER_LIMIT; num += 1) {
                // Subtract all squared numbers that's smaller than `num`.
                for (size_t squareIndex = 0; ; squareIndex += 1) {
                    const int squareNum = squareNumbers[squareIndex];
                    if (squareNum > num) {
                        break;
                    }

                    int previousNum = num - squareNum;
                    if (!results[previousNum]) {
                        // Previous player loses; current player wins.
                        results[num] = true;
                        break;
                    }
                }
            }
        }

        return results[n];
    }
};

std::vector<bool> Solution::results = std::vector<bool>(100000 + 1, false);


void test(const int n, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.winnerSquareGame(n);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << n << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, true);
    test(2, false);
    test(4, true);
    test(7, false);
    test(17, false);
    test(100000, true);

    return 0;
}
