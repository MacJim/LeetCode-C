/*
 * 1996. The Number of Weak Characters in the Game
 * https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort before "jumping" solution
/*
 * Challenge: Duplicate attack values.
 */
// Runtime: 812 ms, faster than 42.41% of C++ online submissions for The Number of Weak Characters in the Game.
// Memory Usage: 129 MB, less than 29.41% of C++ online submissions for The Number of Weak Characters in the Game.
class Solution1 {
public:
    int numberOfWeakCharacters(std::vector<std::vector<int>>& properties) {
        // Sort.
        auto cmp = [] (const std::vector<int>& lhs, std::vector<int>& rhs) -> bool {
            if (lhs[0] == rhs[0]) {
                return lhs[1] < rhs[1];
            } else {
                return lhs[0] < rhs[0];
            }
        };
        std::sort(properties.begin(), properties.end(), cmp);

        // Calculate next larger indices.
        auto nextLargerIndices0 = std::vector<int>(properties.size(), -1);
        auto nextLargerIndices1 = std::vector<int>(properties.size(), -1);

        for (int i = (properties.size() - 2); i >= 0; i -= 1) {
            const auto& previous = properties[i + 1];
            const auto& current = properties[i];

            // Index 0 ("attack").
            if (previous[0] > current[0]) {
                nextLargerIndices0[i] = i + 1;
            } else {
                nextLargerIndices0[i] = nextLargerIndices0[i + 1];
            }

            // Index 1 ("defense").
            if (previous[1] > current[1]) {
                nextLargerIndices1[i] = i + 1;
            } else {
                int largerIndex = nextLargerIndices1[i + 1];
                while ((largerIndex != -1) && (properties[largerIndex][1] <= current[1])) {
                    largerIndex = nextLargerIndices1[largerIndex];
                }

                nextLargerIndices1[i] = largerIndex;
            }
        }

        // For each index, jump and find.
        int returnValue = 0;
        for (int i = 0; i < (properties.size() - 1); i += 1) {    // Skip the last element.
            if ((nextLargerIndices0[i] == -1) || (nextLargerIndices1[i] == -1)) {
                continue;
            }

            int largerIndex = nextLargerIndices0[i];
            while ((largerIndex != -1) && (properties[largerIndex][1] <= properties[i][1])) {
                largerIndex = nextLargerIndices1[largerIndex];
            }

            if (largerIndex != -1) {
                returnValue += 1;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Log previous largest defense
// Runtime: 596 ms, faster than 89.58% of C++ online submissions for The Number of Weak Characters in the Game.
// Memory Usage: 125.1 MB, less than 94.16% of C++ online submissions for The Number of Weak Characters in the Game.
class Solution {
public:
    int numberOfWeakCharacters(std::vector<std::vector<int>>& properties) {
        // Sort.
        auto cmp = [] (const std::vector<int>& lhs, std::vector<int>& rhs) -> bool {
            if (lhs[0] == rhs[0]) {
                return lhs[1] < rhs[1];
            } else {
                return lhs[0] < rhs[0];
            }
        };
        std::sort(properties.begin(), properties.end(), cmp);

        /// Max defense value.
        int maxDefense = INT_MIN;

        int returnValue = 0;

        /// Current index.
        int i = properties.size() - 1;
        while (i >= 0) {
            const auto& current = properties[i];
            int currentAttack = current[0];
            int newMaxDefense = std::max(maxDefense, current[1]);

            /*
             * Find ineligible elements with:
             *
             * - Same attack value as `currentAttack`
             * - Bigger/equal defense value than `maxDefense`
             */
            while ((i >= 0) && (properties[i][0] == currentAttack) && (properties[i][1] >= maxDefense)) {
                i -= 1;
            }

            /*
             * Find eligible elements with:
             *
             * - Same attack value as `currentAttack`
             * - Smaller defense value than `maxDefense`
             */
            while ((i >= 0) && (properties[i][0] == currentAttack)) {
                i -= 1;
                returnValue += 1;
            }

            maxDefense = newMaxDefense;    // Update the max defense value for the next attack value.
        }

        return returnValue;
    }
};



void test(const std::vector<std::vector<int>>& properties, const int expectedResult) {
    auto solutionInstance = Solution();

    auto propertiesCopy = properties;
    auto result = solutionInstance.numberOfWeakCharacters(propertiesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << properties << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << properties << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{7,9},{10,7},{6,9},{10,4},{7,5},{7,10}}, 2);
    test({{2,5},{3,2},{3,4},{3,8},{4,7},{4,7},{5,6}}, 3);
    test({{5,5},{6,3},{3,7},{3,6}}, 0);
    test({{5,5},{6,3},{3,6}}, 0);
    test({{2,2},{3,3}}, 1);
    test({{1,5},{10,4},{4,3}}, 1);

    return 0;
}
