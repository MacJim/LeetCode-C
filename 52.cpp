/*
 * 52. N-Queens II
 * https://leetcode.com/problems/n-queens-ii/
 */

#include <iostream>
#include <vector>
#include <utility>

#include "helpers/terminal_format.h"


#pragma mark - 1. Recursion
// Runtime: 3 ms, faster than 88.70% of C++ online submissions for N-Queens II.
// Memory Usage: 6 MB, less than 81.81% of C++ online submissions for N-Queens II.
class Solution {
private:
    int _recursion(const int n, const int y, std::vector<std::pair<int, int>>& queenLocations) {
        if (y == n) {
            // Reached the end: Found a valid solution.
            return 1;
        }

        int returnValue = 0;
        for (int x = 0; x < n; x += 1) {
            bool valid = true;
            for (const auto& [y1, x1]: queenLocations) {
                if ((x1 == x) || (std::abs(x1 - x) == std::abs(y1 - y))) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                queenLocations.emplace_back(y, x);
                returnValue += _recursion(n, y + 1, queenLocations);
                queenLocations.pop_back();
            }
        }

        return returnValue;
    }

public:
    int totalNQueens(const int n) {
        // Trivial solutions
        switch (n) {
            case 1:
                return 1;
            case 2:
            case 3:
                return 0;
        }

        auto queenLocations = std::vector<std::pair<int, int>>();

        int returnValue = _recursion(n, 0, queenLocations);
        return returnValue;
    }
};


void test(const int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.totalNQueens(n);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << n << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
//    test(1, 1);
    test(4, 2);
    test(9, 352);

    return 0;
}
