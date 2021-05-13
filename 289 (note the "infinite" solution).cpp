/*
 * 289. Game of Life
 * https://leetcode.com/problems/game-of-life/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1
/*
 * - Larger than 1: Currently alive, but dies in the next round
 * - 1: Currently alive and will be alive
 * - 0: Currently dead and will be dead
 * - Smaller than 0: Current dead, but will be alive
 */
// Runtime: 4 ms, faster than 14.82% of C++ online submissions for Game of Life.
// Memory Usage: 7.1 MB, less than 7.87% of C++ online submissions for Game of Life.
class Solution1 {
private:
    inline void updateStatus(std::vector<std::vector<int>>& board, size_t y, size_t x) {
        int& currentValue = board[y][x];

        auto neighborIndices = std::vector<std::pair<int, int>>();
        if (y > 0) {
            if (x > 0) {
                neighborIndices.emplace_back(y - 1, x - 1);
            }
            neighborIndices.emplace_back(y - 1, x);
            if (x < (board[0].size() - 1)) {
                neighborIndices.emplace_back(y - 1, x + 1);
            }
        }

        if (x > 0) {
            neighborIndices.emplace_back(y, x - 1);
        }
        if (x < (board[0].size() - 1)) {
            neighborIndices.emplace_back(y, x + 1);
        }

        if (y < (board.size() - 1)) {
            if (x > 0) {
                neighborIndices.emplace_back(y + 1, x - 1);
            }
            neighborIndices.emplace_back(y + 1, x);
            if (x < (board[0].size() - 1)) {
                neighborIndices.emplace_back(y + 1, x + 1);
            }
        }

        int neighbors = 0;
        for (const auto [y, x]: neighborIndices) {
            if (board[y][x] >= 1) {
                neighbors += 1;
            }
        }

        if (currentValue == 1) {
            // Must have exactly 2 or 3 neighbors to keep alive.
            if ((neighbors < 2) || (neighbors > 3)) {
                currentValue = 2;
            }
        } else {
            // Must have exactly 3 neighbors
            if (neighbors == 3) {
                currentValue = -1;
            }
        }
    }

public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        for (size_t y = 0; y < board.size(); y += 1) {
            for (size_t x = 0; x < board[0].size(); x += 1) {
                updateStatus(board, y, x);
            }
        }

        for (size_t y = 0; y < board.size(); y += 1) {
            for (size_t x = 0; x < board[0].size(); x += 1) {
                int& currentValue = board[y][x];
                if (currentValue < 0) {
                    currentValue = 1;
                } else if (currentValue > 1) {
                    currentValue = 0;
                }
            }
        }
    }
};


#pragma mark - 2. Use the next bit to store the next state
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Game of Life.
// Memory Usage: 6.9 MB, less than 81.10% of C++ online submissions for Game of Life.
class Solution {
private:
    inline void updateStatus(std::vector<std::vector<int>>& board, int currentY, int currentX) {
        int& currentValue = board[currentY][currentX];

        int neighbors = 0;
        for (int y = std::max(0, currentY - 1); y <= std::min(static_cast<int>(board.size()) - 1, currentY + 1); y += 1) {
            for (int x = std::max(0, currentX - 1); x <= std::min(static_cast<int>(board[0].size()) - 1, currentX + 1); x += 1) {
//                if (board[y][x] >= 1) {
//                    neighbors += 1;
//                }
                neighbors += (board[y][x] & 1);
            }
        }
        if (currentValue) {
            if ((neighbors == 3) || (neighbors == 4)) {
                currentValue |= 2;    // Mark the next bit as alive.
            }
        } else {
            if (neighbors == 3) {
                currentValue |= 2;    // Mark the next bit as alive.
            }
        }
    }

public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        for (int y = 0; y < board.size(); y += 1) {
            for (int x = 0; x < board[0].size(); x += 1) {
                updateStatus(board, y, x);
            }
        }

        for (size_t y = 0; y < board.size(); y += 1) {
            for (size_t x = 0; x < board[0].size(); x += 1) {
                board[y][x] >>= 1;    // Update to the next bit.
            }
        }
    }
};


#pragma mark - 3. "Infinite board" follow-up solution
/*
 * Source: https://leetcode.com/problems/game-of-life/discuss/73217/Infinite-board-solution
 *
 * Note that "alive" elements are rare in the board.
 *
 * Thus:
 * 1. collect all "alive" elements as an array or set
 * 2. Accumulate a counter for "number of neighbors alive"
 */


void test(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto boardCopy = board;
    solutionInstance.gameOfLife(boardCopy);

    if (boardCopy == expectedResult) {
        std::cout << "[Correct] " << board << ": " << expectedResult << std::endl;
    } else {
        std::cout << "[Wrong] " << board << ": " << boardCopy << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,1},{1,0}}, {{1,1},{1,1}});
    test({{0,1,0},{0,0,1},{1,1,1},{0,0,0}}, {{0,0,0},{1,0,1},{0,1,1},{0,1,0}});

    return 0;
}
