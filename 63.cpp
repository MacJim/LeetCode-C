/*
 * 63. Unique Paths II
 * https://leetcode.com/problems/unique-paths-ii/
 */

#include <iostream>
#include <vector>


#define DISTANCE_UNREACHABLE 0

#pragma mark - 1
// Runtime: 12 ms, faster than 6.82% of C++ online submissions for Unique Paths II.
// Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Unique Paths II.
class Solution1 {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        auto n = obstacleGrid.size();
        auto m = obstacleGrid.at(0).size();

        auto lastRow = std::vector<int>(m, DISTANCE_UNREACHABLE);
        auto currentRow = std::vector<int>(m, DISTANCE_UNREACHABLE);

        // First row.
        for (int j = 0; j < m; j += 1) {
            if (obstacleGrid.at(0).at(j) == 0) {
                // Can reach this tile.
                currentRow.at(j) = 1;
            } else {
                break;
            }
        }

        // Upcoming rows.
        for (int i = 1; i < n; i += 1) {
            std::swap(lastRow, currentRow);

            // j = 0
            if (obstacleGrid.at(i).at(0) == 0) {
                // Can reach this tile.
                currentRow.at(0) = lastRow.at(0);
            } else {
                // Can't reach this tile.
                currentRow.at(0) = DISTANCE_UNREACHABLE;
            }

            // j > 0
            for (int j = 1; j < m; j += 1) {
                if (obstacleGrid.at(i).at(j) == 1) {
                    // Can't reach this tile.
                    currentRow.at(j) = DISTANCE_UNREACHABLE;
                    continue;
                }

                // Can reach this tile.
                const auto& upValue = lastRow.at(j);
                const auto& leftValue = currentRow.at(j - 1);

                if (upValue == DISTANCE_UNREACHABLE) {
                    currentRow.at(j) = leftValue;
                } else if (leftValue == DISTANCE_UNREACHABLE) {
                    currentRow.at(j) = upValue;
                } else {
                    currentRow.at(j) = leftValue + upValue;
                }
            }
        }

        return currentRow.back();
    }
};


#pragma mark - 2. Optimized 1: Use only 1 vector.
// Runtime: 4 ms, faster than 74.67% of C++ online submissions for Unique Paths II.
// Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Unique Paths II.
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        auto n = obstacleGrid.size();
        auto m = obstacleGrid.at(0).size();

        auto currentRow = std::vector<int>(m, DISTANCE_UNREACHABLE);

        // First row.
        for (int j = 0; j < m; j += 1) {
            if (obstacleGrid.at(0).at(j) == 0) {
                // Can reach this tile.
                currentRow.at(j) = 1;
            } else {
                break;
            }
        }

        // Upcoming rows.
        for (int i = 1; i < n; i += 1) {
            // j = 0
            if (obstacleGrid.at(i).at(0) == 1) {
                // Can reach this tile.
                currentRow.at(0) = DISTANCE_UNREACHABLE;
            }

            // j > 0
            for (int j = 1; j < m; j += 1) {
                if (obstacleGrid.at(i).at(j) == 1) {
                    // Can't reach this tile.
                    currentRow.at(j) = DISTANCE_UNREACHABLE;
                    continue;
                }

                // Can reach this tile.
                const auto& upValue = currentRow.at(j);
                const auto& leftValue = currentRow.at(j - 1);

                if (upValue == DISTANCE_UNREACHABLE) {
                    currentRow.at(j) = leftValue;
                } else if (leftValue == DISTANCE_UNREACHABLE) {
                    currentRow.at(j) = upValue;
                } else {
                    currentRow.at(j) = leftValue + upValue;
                }
            }
        }

        return currentRow.back();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<int>> testCase1 = {
        {0,0,0},
        {0,1,0},
        {0,0,0}
    };
    std::cout << solutionInstance.uniquePathsWithObstacles(testCase1) << std::endl;    // 2

    std::vector<std::vector<int>> testCase2 = {
        {0, 0},
        {1, 0}
    };
    std::cout << solutionInstance.uniquePathsWithObstacles(testCase2) << std::endl;    // 1

    return 0;
}
