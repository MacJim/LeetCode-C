/*
 * 1690. Stone Game VII
 * https://leetcode.com/problems/stone-game-vii/
 */

/*
 * Calculate the sum, and subtract.
 * Err. No, just use prefix sum.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Bottom-up DP and prefix sum
// Runtime: 240 ms, faster than 49.28% of C++ online submissions for Stone Game VII.
// Memory Usage: 84.5 MB, less than 19.68% of C++ online submissions for Stone Game VII.
using DP = std::vector<std::vector<int>>;

class Solution {
private:
    std::vector<int> prefixSum = std::vector<int>();

    inline void initializePrefixSum(const std::vector<int>& stones) {
        prefixSum.reserve(stones.size() + 1);
        prefixSum.push_back(0);
        for (const int& value: stones) {
            const int newValue = prefixSum.back() + value;
            prefixSum.push_back(newValue);
        }
    }

    inline int getSum(int start, int end) {
        end += 1;
        return prefixSum[end] - prefixSum[start];
    }

public:
    int stoneGameVII(const std::vector<int>& stones) {
        // 1. Calculate prefix sum
        initializePrefixSum(stones);

        // 2. DP
        auto dp = DP(stones.size(), std::vector<int>(stones.size(), 0));

        // Length = 2
        for (int end = 1; end < stones.size(); end += 1) {
            const int start = end - 1;
            dp[start][end] = std::max(stones[start], stones[end]);
        }

        // Longer lengths.
        for (int length = 3; length <= stones.size(); length += 1) {
            for (int end = length - 1; end < stones.size(); end += 1) {
                const int start = end - length + 1;

                const int sum1 = getSum(start + 1, end) - dp[start + 1][end];
                const int sum2 = getSum(start, end - 1) - dp[start][end - 1];

                dp[start][end] = std::max(sum1, sum2);
            }
        }

        return dp.front().back();
    }
};


void test(const std::vector<int>& stones, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.stoneGameVII(stones);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << stones << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << stones << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({5,3,1,4,2}, 6);
    test({7,90,5,1,100,10,10,2}, 122);

    return 0;
}
