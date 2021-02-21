/*
 * 79. Word Search
 * https://leetcode.com/problems/word-search/
 */

/*
 * Characters restricted to uppercase and lowercase alphabet. <- This is useful.
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"


#pragma mark - 1. DFS with recursion
// Runtime: 28 ms, faster than 90.27% of C++ online submissions for Word Search.
// Memory Usage: 11.3 MB, less than 77.96% of C++ online submissions for Word Search.
/*
 * Possible improvement
 *
 * Remove the `visited` array, and temporarily replace used characters with a non-alphabet character.
 * This way we don't need to check the `visited` array before running the next round of recursion.
 */
class Solution {
private:
    bool recursion(const std::vector<std::vector<char>>& board, std::vector<std::vector<bool>>& visited, std::string& word, int i, int y, int x) {
        if (i >= word.size()) {
            return true;
        }

        auto& c = word[i];

        // Up.
        if (y < (board.size() - 1)) {
            if (!visited[y + 1][x]) {
                auto& up = board[y + 1][x];
                if (up == c) {
                    visited[y + 1][x] = true;
                    auto result = recursion(board, visited, word, i + 1, y + 1, x);
                    if (result) {
                        return true;
                    }
                    visited[y + 1][x] = false;
                }
            }
        }

        // Down.
        if (y > 0) {
            if (!visited[y - 1][x]) {
                if (board[y - 1][x] == c) {
                    visited[y - 1][x] = true;
                    auto result = recursion(board, visited, word, i + 1, y - 1, x);
                    if (result) {
                        return true;
                    }
                    visited[y - 1][x] = false;
                }
            }
        }

        // Right.
        if (x < (board.front().size() - 1)) {
            if (!visited[y][x + 1]) {
                if (board[y][x + 1] == c) {
                    visited[y][x + 1] = true;
                    auto result = recursion(board, visited, word, i + 1, y, x + 1);
                    if (result) {
                        return true;
                    }
                    visited[y][x + 1] = false;
                }
            }
        }

        // Left.
        if (x > 0) {
            if (!visited[y][x - 1]) {
                if (board[y][x - 1] == c) {
                    visited[y][x - 1] = true;
                    auto result = recursion(board, visited, word, i + 1, y, x - 1);
                    if (result) {
                        return true;
                    }
                    visited[y][x - 1] = false;
                }
            }
        }

        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string& word) {
        auto visited = std::vector<std::vector<bool>>(board.size(), std::vector<bool>(board.front().size(), false));

        for (int y = 0; y < visited.size(); y += 1) {
            for (int x = 0; x < visited.front().size(); x += 1) {
                auto& c2 = board[y][x];
                if (c2 == word[0]) {
                    visited[y][x] = true;
                    auto result = recursion(board, visited, word, 1, y, x);
                    if (result) {
                        return true;
                    }
                    visited[y][x] = false;
                }
            }
        }

        return false;
    }
};


void test(const std::vector<std::vector<char>>& board, const std::string& word, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto boardCopy = board;
    auto wordCopy = word;
    auto result = solutionInstance.exist(boardCopy, wordCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << board << " " << word << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << board << " " << word << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "ABCCED", true);
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "SEE", true);
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "FCSEED", true);
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "ABCB", false);
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "ABCCC", false);
    test({{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "FCSEEDF", false);

    return 0;
}
