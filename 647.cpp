/*
 * 647. Palindromic Substrings
 * https://leetcode.com/problems/palindromic-substrings/
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"


#pragma mark - 1. DP
// Runtime: 28 ms, faster than 34.67% of C++ online submissions for Palindromic Substrings.
// Memory Usage: 7.6 MB, less than 57.20% of C++ online submissions for Palindromic Substrings.
class Solution {
public:
    int countSubstrings(std::string& s) {
        if (s.size() < 2) {
            return true;
        }

        int returnValue = 0;
        auto dp = std::vector<std::vector<bool>>(s.size(), std::vector<bool>(s.size(), false));

        // Length 0 and 1 substrings.
        for (size_t i = 0; i < s.size(); i += 1) {
            dp[i][i] = true;
        }
        returnValue += s.size();
        for (size_t i = 0; i < (s.size() - 1); i += 1) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                returnValue += 1;
            }
        }

        // Longer substrings.
        for (int delta = 2; delta < s.size(); delta += 1) {
            for (int start = 0; start < (s.size() - delta); start += 1) {
                const int end = start + delta;
                if (dp[start + 1][end - 1]) {
                    if (s[start] == s[end]) {
                        dp[start][end] = true;
                        returnValue += 1;
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Expand around centers
// I think this one will run faster than my DP solution.
// But anyway, the DP solution looks much fancier :)


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.countSubstrings(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("aaa", 6);
    test("abc", 3);
    test("abcba", 7);
    test("aaaa", 10);

    return 0;
}
