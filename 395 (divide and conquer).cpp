/*
 * 395. Longest Substring with At Least K Repeating Characters
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Separate by disqualified numbers
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Longest Substring with At Least K Repeating Characters.
// Memory Usage: 6.6 MB, less than 55.80% of C++ online submissions for Longest Substring with At Least K Repeating Characters.
class Solution {
private:
    int returnValue = 0;

    /// [start, end]
    void recursion(const std::string& s, const int k, const int start, const int end) {
        if (start >= end) {
            // Empty interval.
            // Note that k cannot equal 1 here (already dealt with in the main function).
            return;
        }

        auto occurrences = std::unordered_map<char, int>();
        for (int i = start; i <= end; i += 1) {
            const auto& c = s[i];
            occurrences[c] += 1;
        }

        auto disqualifiedChars = std::unordered_set<char>();
        for (const auto& [c, occ]: occurrences) {
            if (occ < k) {
                disqualifiedChars.insert(c);
            }
        }

        if (disqualifiedChars.empty()) {
            // Eligible string.
            returnValue = std::max(returnValue, end - start + 1);
            return;
        }

        int nextStart = start;
        int nextEnd = start;
        for (int i = start; i <= end; i += 1) {
            const auto& c = s[i];
            if (disqualifiedChars.count(c)) {
                // Check if each char in `occurrences` has occurred for at least k times.
                recursion(s, k, nextStart, nextEnd);
                nextStart = i + 1;
            } else {
                nextEnd = i;
            }
        }

        recursion(s, k, nextStart, nextEnd);
    }

public:
    int longestSubstring(const std::string& s, const int k) {
        if (k == 1) {
            return s.size();
        }

        if (k > s.size()) {
            return 0;
        }

        recursion(s, k, 0, s.size() - 1);

        return returnValue;
    }
};


void test(const std::string& s, const int k, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.longestSubstring(s, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("aabbbbccc", 3, 7);
    test("babbbbccca", 3, 7);
    test("aaabb", 3, 3);
    test("abbbbccac", 3, 4);
    test("ababbc", 2, 5);
    test("ababab", 3, 6);
    test("abcde", 1, 5);

    return 0;
}
