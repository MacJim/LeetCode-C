/*
 * 516. Longest Palindromic Subsequence
 * https://leetcode.com/problems/longest-palindromic-subsequence/
 */

#include <iostream>
#include <string>
#include <vector>

#include "helpers/terminal_format.h"


#pragma mark - 1. For each middle element (unfinished)
class Solution1 {
public:
    int longestPalindromeSubseq(const std::string& s) {
        if (s.size() == 1) {
            return 1;
        }

        int returnValue = 1;

        // Calculate the occurrences of each character.
        auto occurrences = std::vector<int>(26, 0);
        for (const char& c: s) {
            const auto index = c - 'a';
            occurrences[index] += 1;
        }

        // Odd length.


        return returnValue;
    }
};


#pragma mark - 2. DP (not intuitive)
/*
 * Source: https://leetcode.com/problems/longest-palindromic-subsequence/discuss/99101/Straight-forward-Java-DP-solution
 *
 * This solution is not intuitive.
 * Check solution 3 instead.
 */
// Runtime: 112 ms, faster than 24.62% of C++ online submissions for Longest Palindromic Subsequence.
// Memory Usage: 72.8 MB, less than 34.17% of C++ online submissions for Longest Palindromic Subsequence.
class Solution2 {
public:
    int longestPalindromeSubseq(const std::string& s) {
        if (s.size() == 1) {
            return 1;
        }

        auto dp = std::vector<std::vector<int>>(s.size(), std::vector<int>(s.size(), 0));
        for (int right = 0; right < s.size(); right += 1) {
            dp[right][right] = 1;
            for (int left = right - 1; left >= 0; left -= 1) {
                if (s[right] == s[left]) {
                    dp[left][right] = dp[left + 1][right - 1] + 2;
                } else {
                    dp[left][right] = std::max(dp[left][right - 1], dp[left + 1][right]);
                }
            }
        }

        return dp.front().back();
    }
};


#pragma mark - 3. Alternative of 2 (revisit)
// Runtime: 100 ms, faster than 34.24% of C++ online submissions for Longest Palindromic Subsequence.
// Memory Usage: 72.8 MB, less than 43.79% of C++ online submissions for Longest Palindromic Subsequence.
class Solution {
public:
    int longestPalindromeSubseq(const std::string& s) {
        if (s.size() == 1) {
            return 1;
        }

        auto dp = std::vector<std::vector<int>>(s.size(), std::vector<int>(s.size(), 0));

        // Length 1.
        for (int i = 0; i < s.size(); i += 1) {
            dp[i][i] = 1;
        }

        // Longer lengths.
        for (int length = 2; length <= s.size(); length += 1) {
            for (int left = 0; left <= (s.size() - length); left += 1) {
                const int right = left + length - 1;
                if (s[left] == s[right]) {
                    dp[left][right] = 2 + dp[left + 1][right - 1];
                } else {
                    dp[left][right] = std::max(dp[left + 1][right], dp[left][right - 1]);
                }
            }
        }

        return dp.front().back();
    }
};


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.longestPalindromeSubseq(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("bbbab", 4);
    test("cbbd", 2);
    test("babcb", 3);
    test("bbbabbb", 7);
    test("bbabbabb", 8);
    test("bbabbcbb", 6);
    test("bbabbbcbbb", 8);
    test("abbbcbbb", 7);
    test("bcbabb", 5);

    return 0;
}
