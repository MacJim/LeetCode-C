/*
 * 474. Ones and Zeroes
 * https://leetcode.com/problems/ones-and-zeroes/
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


#pragma mark - 1. 3D DP: 0 ~ maxM, 0 ~ maxN, first 0 ~ k strings -> 2 choices: either use or not use the current string
// Runtime: 480 ms, faster than 25.12% of C++ online submissions for Ones and Zeroes.
// Memory Usage: 88.8 MB, less than 11.60% of C++ online submissions for Ones and Zeroes.
class Solution {
public:
    int findMaxForm(std::vector<std::string>& strs, int maxM, int maxN) {
        // Count 0s (m) and 1s (n).
        auto zeroCounts = std::vector<int>(strs.size(), 0);
        auto oneCounts = std::vector<int>(strs.size(), 0);

        for (size_t i = 0; i < strs.size(); i += 1) {
            const auto& str = strs[i];

            for (const auto& c: str) {
                // `str` may only contain '0's and '1's.
                if (c == '0') {
                    zeroCounts[i] += 1;
                } else {
                    oneCounts[i] += 1;
                }
            }
        }

        // DP
        /// (m value, n value, string count)
        auto dp = std::vector<std::vector<std::vector<int>>>(maxM + 1, std::vector<std::vector<int>>(maxN + 1, std::vector<int>(strs.size(), 0)));

        for (int m = 0; m <= maxM; m += 1) {
            for (int n = 0; n <= maxN; n += 1) {
                // k = 0 (use this string, must have large enough `m` and `n` values)
                if ((m >= zeroCounts[0]) && (n >= oneCounts[0])) {
                    dp[m][n][0] = 1;
                }

                for (int k = 1; k < strs.size(); k += 1) {
                    // Don't use this string.
                    const int countWithoutCurrentStr = dp[m][n][k - 1];

                    // Use this string.
                    const int previousM = m - zeroCounts[k];
                    const int previousN = n - oneCounts[k];

                    if ((previousM < 0) || (previousN < 0)) {
                        // Current m or n counts are not enough for the current string.
                        dp[m][n][k] = countWithoutCurrentStr;
                    } else {
                        const int countWithCurrentStr = dp[previousM][previousN][k - 1] + 1;
                        dp[m][n][k] = std::max(countWithoutCurrentStr, countWithCurrentStr);
                    }
                }
            }
        }

        return dp.back().back().back();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::string> strs1 = {"10","0001","111001","1","0"};
    int m1 = 5;
    int n1 = 3;
    std::cout << solutionInstance.findMaxForm(strs1, m1, n1) << std::endl;    // 4

    std::vector<std::string> strs2 = {"10","0","1"};
    int m2 = 1;
    int n2 = 1;
    std::cout << solutionInstance.findMaxForm(strs2, m2, n2) << std::endl;    // 2
}
