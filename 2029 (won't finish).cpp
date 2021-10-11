/*
 * 2029. Stone Game IX
 * https://leetcode.com/problems/stone-game-ix/
 */

/*
 * Calculate mod/remainder on all numbers.
 */

/*
 * 0 remainder: (multiples of 3):
 *
 * - An even amount of 0 remainders don't affect the result
 * - An odd amount of 0 remainders reverses the winner
 *
 * Just ignore those numbers beyond the conclusions above.
 */

/*
 * Other than the first move, the current sum (mod 3) must be 1 or 2.
 *
 * - 1: The next move must be 1
 * - 2: The next move must be 2
 *
 * Thus: other than the first move, the players choices are alternating:
 *
 * - First move is 1: 1,1,2,1,2,1,2,1,2,...
 *   - Alice chooses 2 beyond the first move
 *   - Alice wants 1 to run out first
 * - First move is 2: 2,2,1,2,1,2,1,2,1,...
 *   - Alice chooses 1 beyond the first move
 *   - Alice wants 2 to run out first
 */

/*
 * Run out of numbers:
 *
 * - First move is 1: 1,1,2,1,2,1,2,1,2,...
 *   - Run out of numbers if `(count[1] - count[2]) <= 2` and `count[1] >= 2`
 * - First move is 2: 2,2,1,2,1,2,1,2,1,...
 *   - Run out of numbers if `(count[2] - count[1]) <= 2` and `count[2] >= 2`
 */

#include <iostream>
#include <vector>
#include <array>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Top-down recursion
// Time Limit Exceeded
/*
 * There are just too many cases to consider in the recursion.
 * Maybe adding a "current mover" parameter can fix this solution.
 */
enum class Result {
    moverLoses,
    moverWins,
    noMoreStones
};

class Solution1 {
private:
    Result recursion(std::array<int, 3>& counts, const int remainder) {
        if ((counts[0] == 0) && (counts[1] == 0) & (counts[2] == 0)) {
            return Result::noMoreStones;
        }

        bool nextMoverCanWin = false;

        if (remainder == 1) {
            if ((counts[0] == 0) && (counts[1] == 0) & (counts[2] != 0)) {
                return Result::moverLoses;
            }

            for (int i: {0, 1}) {
                if (counts[i]) {
                    counts[i] -= 1;
                    Result nextResult = recursion(counts, (remainder + i) % 3);
                    counts[i] += 1;
                    if (nextResult == Result::moverLoses) {
                        // If the next player always lose.
                        return Result::moverWins;
                    } else if (nextResult == Result::moverWins) {
                        nextMoverCanWin = true;
                    }
                }
            }
        } else {
            if ((counts[0] == 0) && (counts[1] != 0) & (counts[2] == 0)) {
                return Result::moverLoses;
            }

            for (int i: {0, 2}) {
                if (counts[i]) {
                    counts[i] -= 1;
                    Result nextResult = recursion(counts, (remainder + i) % 3);
                    counts[i] += 1;
                    if (nextResult == Result::moverLoses) {
                        // If the next player always lose.
                        return Result::moverWins;
                    } else if (nextResult == Result::moverWins) {
                        nextMoverCanWin = true;
                    }
                }
            }
        }

        if (nextMoverCanWin) {
            return Result::moverLoses;
        } else {
            return Result::noMoreStones;
        }
    }

public:
    bool stoneGameIX(const std::vector<int>& stones) {
        if (stones.size() == 1) {
            // Edge case: Bob always win if there are no remaining stones.
            return false;
        }

        std::array<int, 3> counts = {0, 0, 0};
        for (const int& value: stones) {
            counts[value % 3] += 1;
        }

        if ((counts[1] == 0) && (counts[2] == 0)) {
            return false;
        }

        for (int i: {1, 2}) {
            if (counts[i]) {
                counts[i] -= 1;
                const Result currentResult = recursion(counts, i);
                if (currentResult == Result::moverLoses) {
                    // If the next player always lose.
                    return true;
                }
                counts[i] += 1;
            }
        }

        return false;
    }
};


#pragma mark - 2. Fixed 1
// Time Limit Exceeded
/*
 * Maybe caching the results can help.
 * But that'll be too many results to cache :(
 */
class Solution {
private:
    bool recursion(std::array<int, 3>& counts, const int remainder, const bool isAlice) {
        // No more moves: Alice loses.
        if ((counts[0] == 0) && (counts[1] == 0) && (counts[2] == 0)) {
            return false;
        }

        // The only remaining number is invalid: Current player loses.
        if ((remainder == 1) && (counts[0] == 0) && (counts[1] == 0)) {
            return !isAlice;
        }
        if ((remainder == 2) && (counts[0] == 0) && (counts[2] == 0)) {
            return !isAlice;
        }

        // Pick the next number.
        /**
         * - Remainder 1: 0, 1
         * - Remainder 2: 0, 2
         */
        std::array<int, 2> nextPicks = {0, 1};
        if (remainder == 2) {
            nextPicks[1] = 2;
        }

        for (int i: nextPicks) {
            if (counts[i]) {
                counts[i] -= 1;

                const int newRemainder = (remainder + i) % 3;
                auto subResult = recursion(counts, newRemainder, !isAlice);

                counts[i] += 1;

                if (subResult) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    bool stoneGameIX(const std::vector<int>& stones) {
        // Edge case: Bob always win if there are no remaining stones.
        if (stones.size() == 1) {
            return false;
        }

        // Count remainders.
        std::array<int, 3> counts = {0, 0, 0};
        for (const int& value: stones) {
            counts[value % 3] += 1;
        }

        // Edge case: no valid first pick.
        if ((counts[1] == 0) && (counts[2] == 0)) {
            return false;
        }

        // Remove even amount of 0s.
        if (counts[0] > 2) {
            counts[0] = (counts[0] % 2) ? 1 : 2;
        }

        // Alice picks first. She picks 1 or 2.
        for (int i: {1, 2}) {
            if (counts[i]) {
                counts[i] -= 1;

                const bool currentResult = recursion(counts, i, false);
                if (currentResult) {
                    return true;
                }

                counts[i] += 1;
            }
        }

        return false;
    }
};


#pragma mark - 3. Observe the sequence pattern
// WRONG ANSWER
class Solution3 {
public:
    bool stoneGameIX(const std::vector<int>& stones) {
        if (stones.size() == 1) {
            // Edge case: Bob always win if there are no remaining stones.
            return false;
        }

        std::array<int, 3> counts = {0, 0, 0};
        for (const int& value: stones) {
            counts[value % 3] += 1;
        }

        // Edge case: Only 0-modded numbers.
        if ((counts[1] == 0) && (counts[2] == 0)) {
            // Alice always lose.
            return false;
        }

        // Reverse the end result if there are an even amount of 0s.
        const bool shouldReverseResult = ((counts[0] % 2) == 1);

        // Edge case: Run out of numbers: A always lose.
        if ((std::min(counts[1], counts[2]) == 0) && (std::max(counts[1], counts[2]) > 2)) {
            return shouldReverseResult;
        }

        return (std::abs(counts[1] - counts[2]) > 2) || (!shouldReverseResult);

        // Alice starts with 1.
//        bool result1 = false;
//        if (counts[1]) {
//            const int aliceRemaining1 = counts[2];
//            const int bobRemaining1 = counts[1] - 1;
//
//            result1 = aliceRemaining1 > bobRemaining1;
//
//            if (shouldReverseResult) {
//                result1 = !result1;
//            }
//        }

        // Alice starts with 2.
//        bool result2 = false;
//        if (counts[2]) {
//            const int aliceRemaining2 = counts[1];
//            const int bobRemaining2 = counts[2] - 1;
//            result2 = aliceRemaining2 > bobRemaining2;
//
//            if (shouldReverseResult) {
//                result2 = !result2;
//            }
//        }

//        return result1 || result2;
    }
};


void test(const std::vector<int>& stones, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.stoneGameIX(stones);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << stones << ": " << std::boolalpha << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << stones << ": " << std::boolalpha << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,3}, false);
    test({1,1,1,3}, true);
    test({1,1,2,2,2,3}, false);
    test({3,3,3,3,3}, false);
    test({1,2}, true);
    test({2,2,3}, false);
    test({5,1,2,4,3}, false);
    test({2}, false);
    test({1,3,3}, false);
    test({2,33,90,62,43,21,96,20,18,84,74,61,100,5,11,4,67,96,18,6,68,82,32,76,33,93,33,71,32,30,63,37,46,95,51,63,77,63,84,52,78,66,76,66,9,73,92,79,65,29,42,64,46,84,95,71,15,68,55,9,22,64,56,83,52,47,38,19,59,32,89,29,56,84,57,90,96,19,38,13,49,65,93,8,30,15,12,40,84,7,6,75,36,31,6,78,64,33,49},
         false);

    return 0;
}
