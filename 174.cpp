/*
 * 174. Dungeon Game
 * https://leetcode.com/problems/dungeon-game/
 */

#include <iostream>
#include <vector>
#include <algorithm>


#pragma mark - 1. WRONG. I forgot that the knight cannot die midway.
class Solution1 {
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
        const auto iLen = dungeon.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = dungeon.front().size();
        if (jLen == 0) {
            return 0;
        }

        auto currentRow = std::vector<int>(jLen, 0);

        // First row.
        currentRow.at(0) = dungeon.front().front();
        for (int j = 1; j < jLen; j += 1) {
            currentRow.at(j) = dungeon.at(0).at(j) + currentRow.at(j - 1);
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            // First column.
            currentRow.at(0) = currentRow.at(0) + dungeon.at(i).at(0);

            // Upcoming columns.
            for (int j = 1; j < jLen; j += 1) {
                currentRow.at(j) = std::max(currentRow.at(j), currentRow.at(j - 1)) + dungeon.at(i).at(j);
            }
        }

        return 0;
    }
};


#pragma mark - 2. WRONG. A low damage may not result in an optimal path.
class Solution3 {
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
        const auto iLen = dungeon.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = dungeon.front().size();
        if (jLen == 0) {
            return 0;
        }

        auto currentRow = std::vector<int>(jLen, 0);
        auto currentDamage = std::vector<int>(jLen, 0);    // Should be negative.

        // First row.
        currentRow.at(0) = dungeon.front().front();
        currentDamage.at(0) = currentRow.at(0);

        for (int j = 1; j < jLen; j += 1) {
            currentRow.at(j) = dungeon.at(0).at(j) + currentRow.at(j - 1);
            currentDamage.at(j) = std::min(currentDamage.at(j - 1), currentRow.at(j));
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            // First column.
            currentRow.at(0) = currentRow.at(0) + dungeon.at(i).at(0);

            currentDamage.at(0) = std::min(currentDamage.at(0), currentRow.at(0));

            // Upcoming columns.
            for (int j = 1; j < jLen; j += 1) {
                if (currentDamage.at(j) > currentDamage.at(j - 1)) {
                    currentRow.at(j) = currentRow.at(j) + dungeon.at(i).at(j);
                    // Use minimum value since this depends on the previous min damage.
                    currentDamage.at(j) = std::min(currentDamage.at(j), currentRow.at(j));
                } else {
                    currentRow.at(j) = currentRow.at(j - 1) + dungeon.at(i).at(j);
                    currentDamage.at(j) = std::min(currentDamage.at(j - 1), currentRow.at(j));
                }
            }
        }

        if (currentDamage.back() > 0)  {
            return 1;
        } else {
            return 1 - currentDamage.back();    // I add 1 to the solution because I forgot that the min health is 1 instead of 0.
        }
    }
};


#pragma mark - 3. Differenciate between positive and negative results & start from back.
/*
 * Start from the bottom right instead of top left.
 *
 * Whenever we encounter a positive result, we reset it to 0.
 * Such occasions are only achieved when health gain from potions are equal to or larger than the upcoming damage.
 */
// Runtime: 12 ms, faster than 62.59% of C++ online submissions for Dungeon Game.
// Memory Usage: 8.7 MB, less than 67.52% of C++ online submissions for Dungeon Game.
class Solution {
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) {
        const int iLen = dungeon.size();
        if (iLen == 0) {
            return 0;
        }

        const int jLen = dungeon.front().size();
        if (jLen == 0) {
            return 0;
        }

        auto currentRow = std::vector<int>(jLen, 0);
        auto currentDamage = std::vector<int>(jLen, 0);    // Should be negative.

        // Final row.
        currentRow.back() = std::min(0, dungeon.back().back());
        for (int j = (jLen - 2); j >= 0; j -= 1) {
            // Values are capped at 0.
            currentRow.at(j) = std::min(0, currentRow.at(j + 1) + dungeon.back().at(j));
        }

        // Upcoming rows.
        for (int i = (iLen - 2); i >= 0; i -= 1) {
            // Last column.
            currentRow.back() = std::min(0, currentRow.back() + dungeon.at(i).back());

            for (int j = (jLen - 2); j >= 0; j -= 1) {
                if (currentRow.at(j + 1) > currentRow.at(j)) {
                    currentRow.at(j) = std::min(0, currentRow.at(j + 1) + dungeon.at(i).at(j));
                } else {
                    currentRow.at(j) = std::min(0, currentRow.at(j) + dungeon.at(i).at(j));
                }
            }
        }

        return 1 - currentRow.front();
    }
};


int main() {
    auto solutionInstance = Solution();
    
    std::vector<std::vector<int>> testCase1 = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    std::cout << solutionInstance.calculateMinimumHP(testCase1) << std::endl;    // 7

    std::vector<std::vector<int>> testCase2 = {{100}};
    std::cout << solutionInstance.calculateMinimumHP(testCase2) << std::endl;    // 1

    std::vector<std::vector<int>> testCase3 = {{0,-5},{0,0}};
    std::cout << solutionInstance.calculateMinimumHP(testCase3) << std::endl;    // 1

    std::vector<std::vector<int>> testCase4 = {{1,-3,3},{0,-2,0},{-3,-3,-3}};
    std::cout << solutionInstance.calculateMinimumHP(testCase4) << std::endl;    // 3

    return 0;
}
