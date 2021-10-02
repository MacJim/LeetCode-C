/*
 * 1411. Number of Ways to Paint N × 3 Grid
 * https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/
 */

#include <iostream>
#include <vector>
#include <utility>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Math/DP
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Ways to Paint N × 3 Grid.
// Memory Usage: 6.1 MB, less than 49.30% of C++ online submissions for Number of Ways to Paint N × 3 Grid.

/*
 * 3 colors: 3! = 6 permutations.
 */

/*
 * Each row may contain 2 or 3 colors. (Check scratch paper for details)
 *
 * - Current row has 2 colors: next row may have 2 colors (3 scenarios) or 3 colors (2 scenarios)
 * - Current row has 3 colors: next row may have 2 colors (2 scenarios) or 3 colors (2 scenarios)
 *
 * Let `f(n, 2)` refer to a row with 2 colors, `f(n, 3)` refer to a row with 3 colors.
 * State machine:
 *
 * - f(n + 1, 2) = f(n, 2) * 3 + f(n, 3) * 2
 * - f(n + 1, 3) = f(n, 2) * 2 + f(n, 3) * 2
 */

class Solution {
private:
    static constexpr long long MOD = 1000000007;

private:
    static constexpr int MAX_N = 5000;
    static std::vector<std::pair<int, int>> solutions;

public:
    int numOfWays(int n) {
        if (solutions.empty()) {
            // Calculate to 5000 right away.
            solutions.reserve(MAX_N);
            solutions.emplace_back(1 * 6, 1 * 6);
            solutions.emplace_back(5 * 6, 4 * 6);
            solutions.emplace_back(23 * 6, 18 * 6);

            for (int i = 3; i < MAX_N; i += 1) {
                // Must use `long long` here to prevent overflows :(
                long long previous2 = solutions.back().first;
                long long previous3 = solutions.back().second;

                long long current2 = previous2 * 3 + previous3 * 2;
                long long current3 = previous2 * 2 + previous3 * 2;

                current2 %= MOD;
                current3 %= MOD;

                solutions.emplace_back(current2, current3);
            }
        }

        int returnValue = solutions[n - 1].first + solutions[n - 1].second;
        returnValue %= MOD;

        return returnValue;
    }
};

std::vector<std::pair<int, int>> Solution::solutions = std::vector<std::pair<int, int>>();


void test(const int n, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.numOfWays(n);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << n << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 12);
    test(2, 54);
    test(3, 246);
    test(7, 106494);
    test(5000, 30228214);

    return 0;
}
