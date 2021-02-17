/*
 * 200. Number of Islands
 * https://leetcode.com/problems/number-of-islands/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. DP
// Wrong Answer
class Solution1 {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.empty() || grid.front().empty()) {
            return 0;
        }

//        int returnValue = 0;

        int nextIslandIndex = 1;
        auto duplicateIndices = std::unordered_set<int>();

        auto previousIndices = std::vector<int>(grid.front().size(), 0);

        // First row.
        size_t y = 0;
        size_t x = 0;
        if (grid[y][x] == '1') {
            previousIndices[x] = nextIslandIndex;
            nextIslandIndex += 1;
//            returnValue += 1;
        }

        for (x = 1; x < grid[y].size(); x += 1) {
            const auto& c = grid[y][x];
            if (c == '1') {
                const auto& leftIndex = previousIndices[x - 1];
                if (leftIndex == 0) {
                    previousIndices[x] = nextIslandIndex;
                    nextIslandIndex += 1;
//                    returnValue += 1;
                } else {
                    previousIndices[x] = leftIndex;
                }
            }
        }

        // Upcoming rows.
        auto currentIndices = std::vector<int>(grid.front().size(), 0);
        for (y = 1; y < grid.size(); y += 1) {
            for (x = 0; x < grid[y].size(); x += 1) {
                const auto& c = grid[y][x];
                if (c == '1') {
                    const auto& upIndex = previousIndices[x];

                    if (x == 0) {
                        // First element in row.
                        if (upIndex > 0) {
                            currentIndices[x] = upIndex;
                        } else {
                            currentIndices[x] = nextIslandIndex;
                            nextIslandIndex += 1;
//                            returnValue += 1;
                        }
                    } else {
                        // Upcoming elements in row.
                        const int leftIndex = currentIndices[x - 1];
                        if (leftIndex > 0) {
                            currentIndices[x] = leftIndex;

                            if ((upIndex > 0) && (upIndex != leftIndex)) {
                                // Connects left and top.
//                                returnValue -= 1;
                                if (upIndex < leftIndex) {
                                    duplicateIndices.insert(leftIndex);
                                    currentIndices[x] = upIndex;
                                } else {
                                    duplicateIndices.insert(upIndex);
                                }
                            }
                        } else if (upIndex > 0) {
                            currentIndices[x] = upIndex;
                        } else {
                            currentIndices[x] = nextIslandIndex;
                            nextIslandIndex += 1;
//                            returnValue += 1;
                        }
                    }
                } else {
                    currentIndices[x] = 0;
                }
            }

            std::swap(previousIndices, currentIndices);    // Moves `currentIndices` to `previousIndices`.
        }

        return nextIslandIndex - duplicateIndices.size() - 1;
    }
};


#pragma mark - 2. DP (fixed 1, adds a chunk of mitigation code)
// Runtime: 12 ms, faster than 97.34% of C++ online submissions for Number of Islands.
// Memory Usage: 9.5 MB, less than 87.57% of C++ online submissions for Number of Islands.
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.empty() || grid.front().empty()) {
            return 0;
        }

//        int returnValue = 0;

        int nextIslandIndex = 1;
        auto duplicateIndices = std::unordered_set<int>();

        auto previousIndices = std::vector<int>(grid.front().size(), 0);

        // First row.
        size_t y = 0;
        size_t x = 0;
        if (grid[y][x] == '1') {
            previousIndices[x] = nextIslandIndex;
            nextIslandIndex += 1;
//            returnValue += 1;
        }

        for (x = 1; x < grid[y].size(); x += 1) {
            const auto& c = grid[y][x];
            if (c == '1') {
                const auto& leftIndex = previousIndices[x - 1];
                if (leftIndex == 0) {
                    previousIndices[x] = nextIslandIndex;
                    nextIslandIndex += 1;
//                    returnValue += 1;
                } else {
                    previousIndices[x] = leftIndex;
                }
            }
        }

        // Upcoming rows.
        auto currentIndices = std::vector<int>(grid.front().size(), 0);
        for (y = 1; y < grid.size(); y += 1) {
            for (x = 0; x < grid[y].size(); x += 1) {
                const auto& c = grid[y][x];
                if (c == '1') {
                    const auto& upIndex = previousIndices[x];

                    if (x == 0) {
                        // First element in row.
                        if (upIndex > 0) {
                            currentIndices[x] = upIndex;
                        } else {
                            currentIndices[x] = nextIslandIndex;
                            nextIslandIndex += 1;
//                            returnValue += 1;
                        }
                    } else {
                        // Upcoming elements in row.
                        const int leftIndex = currentIndices[x - 1];
                        if (leftIndex > 0) {
                            currentIndices[x] = leftIndex;

                            if ((upIndex > 0) && (upIndex != leftIndex)) {
                                // Connects left and top.
//                                returnValue -= 1;
                                if (upIndex < leftIndex) {
                                    duplicateIndices.insert(leftIndex);
                                    currentIndices[x] = upIndex;

                                    // Updates the left values if they're larger than the top value.
                                    // This mitigates the longest test case below, where both the up and left values are new and connected to a previous value in later iterations.
                                    for (int x2 = x; x2 >= 0; x2 -= 1) {
                                        if (currentIndices[x2] == 0) {
                                            break;
                                        }
                                        currentIndices[x2] = upIndex;
                                    }
                                } else {
                                    duplicateIndices.insert(upIndex);
                                }
                            }
                        } else if (upIndex > 0) {
                            currentIndices[x] = upIndex;
                        } else {
                            currentIndices[x] = nextIslandIndex;
                            nextIslandIndex += 1;
//                            returnValue += 1;
                        }
                    }
                } else {
                    currentIndices[x] = 0;
                }
            }

            std::swap(previousIndices, currentIndices);    // Moves `currentIndices` to `previousIndices`.
        }

        return nextIslandIndex - duplicateIndices.size() - 1;
    }
};


void test(const std::vector<std::vector<char>>& grid, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto gridCopy = grid;
    auto result = solutionInstance.numIslands(gridCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << grid << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << grid << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({
        {'1','0','1','1','0','0','1','0','1','1','1','1','0','1','0','1','1','1','1','0'},
        {'0','1','0','0','1','0','1','0','1','1','1','1','1','1','0','1','1','0','1','1'},
        {'1','0','0','1','0','1','0','1','0','1','1','0','1','1','1','0','0','1','1','0'},
        {'0','1','1','0','0','1','1','0','1','1','1','1','0','0','1','0','0','0','1','1'},
        {'1','1','0','1','0','0','1','0','0','0','1','0','1','0','1','1','1','0','1','1'},
        {'0','0','0','0','1','0','1','1','0','0','1','0','0','1','0','1','1','1','1','0'},
        {'1','0','1','1','1','1','0','1','1','0','1','1','0','1','1','1','0','0','1','0'},
        {'0','1','1','0','0','0','1','0','0','1','0','1','1','1','0','0','1','1','0','1'},
        {'0','0','0','0','1','1','0','1','0','0','1','1','0','1','0','0','1','0','1','0'},
        {'0','0','1','1','1','0','1','0','1','0','1','1','1','0','1','1','1','1','1','0'},
        {'1','0','1','0','1','1','1','0','1','1','1','0','1','0','1','0','1','0','1','1'},
        {'0','0','1','1','1','1','0','1','1','1','0','1','0','0','0','1','1','1','0','1'},
        {'1','1','1','0','0','0','0','0','1','1','0','1','1','1','0','1','1','1','1','0'},
        {'0','0','1','1','1','0','0','1','0','0','1','1','1','1','1','1','0','1','1','0'},
        {'0','0','0','1','1','0','0','0','0','1','1','0','1','0','0','1','1','1','1','1'},
        {'0','1','1','1','0','1','0','0','1','1','1','1','1','0','1','1','1','0','0','1'},
        {'0','0','0','0','1','1','1','1','0','0','0','0','1','0','0','0','0','1','1','0'},
        {'1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','1','1'},
        {'0','1','0','0','1','0','0','1','1','1','1','1','1','0','1','0','1','1','1','1'},
        {'0','0','1','1','1','1','1','0','0','0','1','1','1','1','1','1','0','1','1','0'},
    }, 23);
    test({
        {'1','1','1','1','1','0','1','1','1','1'},
        {'1','0','1','0','1','1','1','1','1','1'},
        {'0','1','1','1','0','1','1','1','1','1'},
        {'1','1','0','1','1','0','0','0','0','1'},
        {'1','0','1','0','1','0','0','1','0','1'},
        {'1','0','0','1','1','1','0','1','0','0'},
        {'0','0','1','0','0','1','1','1','1','0'},
        {'1','0','1','1','1','0','0','1','1','1'},
        {'1','1','1','1','1','1','1','1','0','1'},
        {'1','0','1','1','1','1','1','1','1','0'}
    }, 2);
    test({
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    }, 1);
    test({
        {'1','0','0','0','1'},
        {'1','0','1','0','0'},
        {'1','0','1','0','1'},
        {'1','1','1','1','1'}
    }, 2);
    test({
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    }, 3);
    test({
        {'0','0','0','0','0'},
        {'0','0','0','0','0'},
        {'0','0','0','0','0'},
        {'0','0','0','0','0'}
    }, 0);

    return 0;
}
