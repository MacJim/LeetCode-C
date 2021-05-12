/*
 * 76. Minimum Window Substring
 * https://leetcode.com/problems/minimum-window-substring/
 */

/*
 * - The window either doesn't exist or is unique
 * - Contains only english letters, both upper and lower cases
 */

#include <iostream>
//#include <vector>
#include <string>
#include <array>

#include "helpers/Operators.hpp"


#pragma mark - 1. Seems unoptimized
// WRONG ANSWER because it didn't take duplicate numbers into account.
class Solution1 {
private:
    inline int getOccurrencesIndex(const char& c) const {
        if (c > 'Z') {
            return 26 + (c - 'a');
        } else {
            return c - 'A';
        }
    }

    inline std::pair<int, int> getCurrentIndices(std::vector<int>& lastOccurrences) const {
        int left = -1;
        int right = -1;

        for (const auto occurrence: lastOccurrences) {
            if (occurrence == -2) {
                // This char doesn't exist in `t`.
                continue;
            } else if (occurrence == -1) {
                // This char doesn't exist in `s`.
                return std::make_pair(-1, -1);
            }

            if (left == -1) {
                left = occurrence;
            } else {
                left = std::min(left, occurrence);
            }
            right = std::max(right, occurrence);
        }

        return std::make_pair(left, right);
    }

public:
    std::string minWindow(std::string& s, std::string& t) {
        auto lastOccurrences = std::vector<int>(26 * 2, -2);
//        auto tChars = std::unordered_map<char, int>();
        for (const char& c: t) {
            lastOccurrences[getOccurrencesIndex(c)] = -1;
        }

        int left = -1;
        int right = -1;

        for (int i = 0; i < s.size(); i += 1) {
            const char& c = s[i];

            auto& lastOccurrence = lastOccurrences[getOccurrencesIndex(c)];
            if (lastOccurrence == -2) {
                // Doesn't exist in `t`.
                continue;
            }

            lastOccurrence = i;

            auto [currentLeft, currentRight] = getCurrentIndices(lastOccurrences);
            if (currentLeft == -1) {
                continue;
            } else {
                if ((left == -1) || ((currentRight - currentLeft) < (right - left))) {
                    left = currentLeft;
                    right = currentRight;
                }
            }
        }

        if (left == -1) {
            return "";
        }

        return s.substr(left, right - left + 1);
    }
};


#pragma mark - 2. Fixed 1
// Runtime: 24 ms, faster than 42.38% of C++ online submissions for Minimum Window Substring.
// Memory Usage: 7.2 MB, less than 99.85% of C++ online submissions for Minimum Window Substring.
class Solution {
private:
    inline int getOccurrencesIndex(const char& c) const {
        if (c > 'Z') {
            return 26 + (c - 'a');
        } else {
            return c - 'A';
        }
    }

public:
    std::string minWindow(std::string& s, std::string& t) {
        /// Negative values means deficit.
        auto lastOccurrences = std::vector<int>(26 * 2, INT_MAX);
        for (const char& c: t) {
            auto& lastOccurrence = lastOccurrences[getOccurrencesIndex(c)];
            if (lastOccurrence == INT_MAX) {
                lastOccurrence = -1;
            } else {
                lastOccurrence -= 1;
            }
        }

        /// [left, right)
        int bestLeft = 0;
        int bestRight = INT_MAX;

        int left = 0;
        int right = 0;

        while (right <= s.size()) {
            if (*std::min_element(lastOccurrences.begin(), lastOccurrences.end()) >= 0) {
                // Save best result.
                if ((right - left) < (bestRight - bestLeft)) {
                    bestLeft = left;
                    bestRight = right;
                }

                // Increase left.
                const char& c = s[left];

                auto& lastOccurrence = lastOccurrences[getOccurrencesIndex(c)];
                if (lastOccurrence != INT_MAX) {
                    // Does exist in `t`.
                    lastOccurrence -= 1;
                }

                left += 1;
            } else {
                if (right == s.size()) {
                    break;
                }

                // Increase `right`.
                const char& c = s[right];

                auto& lastOccurrence = lastOccurrences[getOccurrencesIndex(c)];
                if (lastOccurrence != INT_MAX) {
                    // Does exist in `t`.
                    lastOccurrence += 1;
                }

                right += 1;
            }
        }

        if (bestRight == INT_MAX) {
            return "";
        }

        return s.substr(bestLeft, bestRight - bestLeft);
    }
};


void test(const std::string& s, const std::string& t, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto tCopy = t;
    auto result = solutionInstance.minWindow(sCopy, tCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ", " << t << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ", " << t << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("ABBBBABBBABBBB", "ABBBA", "ABBBA");

    test("ABBBABBBABBB", "ABC", "");
    test("ADOBECODEBANC", "ABC", "BANC");
    test("a", "a", "a");
    test("ABBBABBBABBB", "AB", "AB");
    test("ACBBBA", "AB", "BA");

    test("a", "aa", "");
    test("aba", "aa", "aba");
    test("ababb", "bbb", "babb");
    test("abbccaa", "aaac", "abbccaa");

    return 0;
}
