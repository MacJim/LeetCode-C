/*
 * 312. Burst Balloons
 * https://leetcode.com/problems/burst-balloons/
 */

/*
 * This is fundamentally a subdivision problem.
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Official solution: DP: divide (revisit)
/*
 * Most important thought: instead of choosing which number to eliminate first, we choose which number to eliminate **last**.
 */
// Runtime: 52 ms, faster than 18.28% of C++ online submissions for Burst Balloons.
// Memory Usage: 9.2 MB, less than 14.36% of C++ online submissions for Burst Balloons.
class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        } else if (nums.size() == 1) {
            return nums.front();
        }

        // Virtual 1s at the front and back.
        auto extendedNums = nums;
        extendedNums.insert(extendedNums.begin(), 1);
        extendedNums.push_back(1);

        /**
         * (begin, end) rather than [begin, end].
         *
         * Thus, there are 2 additional elements at the front and back.
         */
        auto dp = std::vector<std::vector<int>>(extendedNums.size(), std::vector<int>(extendedNums.size(), 0));

        /// The 3 numbers have a product when `end == begin + 2`.
        const int minInterval = 2;
        const int maxInterval = extendedNums.size() - 1;

        for (int interval = minInterval; interval <= maxInterval; interval += 1) {
            for (size_t begin = 0; begin < extendedNums.size(); begin += 1) {    // (begin - 1) in the original array.
                const size_t end = begin + interval;    // (end - 1) in the original array.
                if (end >= extendedNums.size()) {
                    break;
                }

                for (size_t mid = begin + 1; mid < end; mid += 1) {    // (mid - 1) in the original array.
                    const int& product = extendedNums[begin] * extendedNums[mid] * extendedNums[end];    // Discard `mid` **last**.
                    const int sum = product + dp[begin][mid] + dp[mid][end];
                    dp[begin][end] = std::max(dp[begin][end], sum);
                }
            }
        }

        return dp[0].back();
    }
};


int main() {
    auto solutionInstance = Solution();
    std::vector<std::vector<int>> testCases = {
        {3,1,5,8},    // 167
    };

    for (auto& testCase: testCases) {
        auto testCaseCopy = testCase;
        auto result = solutionInstance.maxCoins(testCaseCopy);
        std::cout << testCase << ": " << result << std::endl;
    }

    return 0;
}
