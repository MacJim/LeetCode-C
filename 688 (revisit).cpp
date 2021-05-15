/*
 * 688. Knight Probability in Chessboard
 * https://leetcode.com/problems/knight-probability-in-chessboard/
 */

#include <iostream>
#include <vector>

//#include "helpers/Operators.hpp"
#include "helpers/float_helper.h"


/*
 * - The knight is disqualified if it moves out of the board at any move
 */


#pragma mark - 1. Recursion
// Time Limit Exceeded
class Solution1 {
public:
    double knightProbability(const int boardSideLength, const int moves, const int row, const int column) {
        // Out of the board.
        if ((row < 0) || (row >= boardSideLength)) {
            return 0.0;
        }
        if ((column < 0) || (column >= boardSideLength)) {
            return 0.0;
        }

        if (moves == 0) {
            // The knight doesn't move.
            return 1.0;
        }

        double returnValue = 0.0;

        std::vector<std::pair<int, int>> positions = {{row + 1, column + 2}, {row + 1, column - 2}, {row - 1, column + 2}, {row - 1, column - 2}, {row + 2, column + 1}, {row + 2, column - 1}, {row - 2, column + 1}, {row - 2, column - 1}};
        for (const auto& [newRow, newCol]: positions) {
            double newProbability = knightProbability(boardSideLength, moves - 1, newRow, newCol);
            newProbability *= (1.0 / 8.0);
            returnValue += newProbability;
        }

        return returnValue;
    }
};


#pragma mark - 2. DP (revisit)
/*
 * Cache results step by step.
 *
 * Well I was initially worried about the space consumption and wanted to use a hash map instead.
 */
// Runtime: 32 ms, faster than 26.69% of C++ online submissions for Knight Probability in Chessboard.
// Memory Usage: 18 MB, less than 19.19% of C++ online submissions for Knight Probability in Chessboard.
class Solution {
public:
    double knightProbability(const int boardSideLength, int moves, const int initialRow, const int initialColumn) {
        if (moves == 0) {
            // The knight doesn't move.
            return 1.0;
        }

        auto previousStep = std::vector<std::vector<double>>(boardSideLength, std::vector<double>(boardSideLength, 0.0));
        auto currentStep = std::vector<std::vector<double>>(boardSideLength, std::vector<double>(boardSideLength, 0.0));

        previousStep[initialColumn][initialRow] = 1.0;
        for (; moves > 0; moves -= 1) {
            for (int column = 0; column < boardSideLength; column += 1) {
                for (int row = 0; row < boardSideLength; row += 1) {
                    auto& previousChance = previousStep[column][row];
                    if (isClose(0.0, previousChance)) {
                        continue;
                    }

                    std::vector<std::pair<int, int>> positions = {{row + 1, column + 2}, {row + 1, column - 2}, {row - 1, column + 2}, {row - 1, column - 2}, {row + 2, column + 1}, {row + 2, column - 1}, {row - 2, column + 1}, {row - 2, column - 1}};
                    for (const auto& [newRow, newCol]: positions) {
                        if ((newRow >= 0) && (newRow < boardSideLength) && (newCol >= 0) && (newCol < boardSideLength)) {
                            currentStep[newCol][newRow] += previousChance / 8.0;
                        }
                    }
                }
            }

            previousStep = std::move(currentStep);
            currentStep = std::vector<std::vector<double>>(boardSideLength, std::vector<double>(boardSideLength, 0));
        }

        double returnValue = 0.0;
        for (const auto& row: previousStep) {
            for (const auto& chance: row) {
                returnValue += chance;
            }
        }

        return returnValue;
    }
};


void test(const int boardSideLength, const int moves, const int row, const int column, const double expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.knightProbability(boardSideLength, moves, row, column);

    if (isClose(result, expectedResult)) {
        std::cout << "[Correct] (" << boardSideLength << ", " << moves << ", " << row << ", " << column << "): " << result << std::endl;
    } else {
        std::cout << "[Wrong] (" << boardSideLength << ", " << moves << ", " << row << ", " << column << "): " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(3, 2, 0, 0, 0.06250);
    test(1, 0, 0, 0, 1.0);
    test(8, 30, 6, 4, 0.000190526);

    return 0;
}
