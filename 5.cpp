/*
 * 5. Longest Palindromic Substring
 * https://leetcode.com/problems/longest-palindromic-substring/
 */

#include <iostream>
#include <string>

#include "helpers/terminal_format.h"


#pragma mark - 1. For each middle position
// Runtime: 24 ms, faster than 74.65% of C++ online submissions for Longest Palindromic Substring.
// Memory Usage: 6.9 MB, less than 94.29% of C++ online submissions for Longest Palindromic Substring.
class Solution {
public:
    std::string longestPalindrome(const std::string& s) {
        if (s.size() == 1) {
            return s;
        }

        int start = 0;
        int length = 1;

        // Odd lengths.
        for (int i = 0; i < s.size(); i += 1) {
            for (int sideLength = 1; ((i - sideLength) >= 0) && ((i + sideLength) < s.size()); sideLength += 1) {
                const auto currentStart = i - sideLength;
                const auto currentEnd = i + sideLength;
                if (s[currentStart] == s[currentEnd]) {
                    const int currentLength = currentEnd - currentStart + 1;
                    if (currentLength > length) {
                        start = currentStart;
                        length = currentLength;
                    }
                } else {
                    break;
                }
            }
        }

        // Even lengths.
        // i is the 2nd middle element.
        for (int i = 1; i < s.size(); i += 1) {
            for (int sideLength = 0; ((i - sideLength - 1) >= 0) && ((i + sideLength) < s.size()); sideLength += 1) {
                const auto currentStart = i - sideLength - 1;
                const auto currentEnd = i + sideLength;

                if (s[currentStart] == s[currentEnd]) {
                    const int currentLength = currentEnd - currentStart + 1;
                    if (currentLength > length) {
                        start = currentStart;
                        length = currentLength;
                    }
                } else {
                    break;
                }
            }
        }

        return s.substr(start, length);
    }
};


void test(const std::string& s, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.longestPalindrome(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("aaaa", "aaaa");
    test("babad", "bab");
    test("cbbd", "bb");
    test("a", "a");
    test("ac", "a");
    test("bbbbbbabbbb", "bbbbabbbb");

    return 0;
}
