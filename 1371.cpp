/*
 * 1371. Find the Longest Substring Containing Vowels in Even Counts
 * https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
 */

#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Test each length in a rolling fashion
// Runtime: 44 ms, faster than 98.09% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
// Memory Usage: 14.1 MB, less than 99.90% of C++ online submissions for Find the Longest Substring Containing Vowels in Even Counts.
class Solution {
private:
    inline int getOccurrenceIndex(const char& c) {
        switch (c) {
            case 'a':
                return 0;

            case 'e':
                return 1;

            case 'i':
                return 2;

            case 'o':
                return 3;

            case 'u':
                return 4;

            default:
                return -1;
        }
    }

private:
    static constexpr std::array<int, 5> expectedOccurrences = {true, true, true, true, true};

public:
    int findTheLongestSubstring(const std::string& s) {
        /// `true` for even occurrences.
        auto occurrences = std::array<int, 5>({true, true, true, true, true});
        for (const auto& c: s) {
            const int occurrenceIndex = getOccurrenceIndex(c);
            if (occurrenceIndex != -1) {
                occurrences[occurrenceIndex] = !occurrences[occurrenceIndex];
            }
        }

        if (occurrences == expectedOccurrences) {
            return s.size();
        }

        for (int length = (s.size() - 1); length > 0; length -= 1) {
            if (length % 2) {
                // MARK: Backward pass
                // Remove the front element.
                int frontIndex = s.size() - length - 1;
                const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                if (frontOccurrenceIndex != -1) {
                    occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                }

                if (occurrences == expectedOccurrences) {
                    return length;
                }

                // Go backward.
                for (; frontIndex >= 0; frontIndex -= 1) {
                    const int backIndex = frontIndex + length;

                    const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                    if (frontOccurrenceIndex != -1) {
                        occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                    }

                    const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                    if (backOccurrenceIndex != -1) {
                        occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                    }

                    if (occurrences == expectedOccurrences) {
                        return length;
                    }
                }
            } else {
                // MARK: Forward pass
                // Remove from back.
                int backIndex = length;
                const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                if (backOccurrenceIndex != -1) {
                    occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                }

                if (occurrences == expectedOccurrences) {
                    return length;
                }

                // Go forward.
                for (; backIndex < s.size(); backIndex += 1) {
                    const int frontIndex = backIndex - length;

                    const int frontOccurrenceIndex = getOccurrenceIndex(s[frontIndex]);
                    if (frontOccurrenceIndex != -1) {
                        occurrences[frontOccurrenceIndex] = !occurrences[frontOccurrenceIndex];
                    }

                    const int backOccurrenceIndex = getOccurrenceIndex(s[backIndex]);
                    if (backOccurrenceIndex != -1) {
                        occurrences[backOccurrenceIndex] = !occurrences[backOccurrenceIndex];
                    }

                    if (occurrences == expectedOccurrences) {
                        return length;
                    }
                }
            }
        }

        return 0;
    }
};


void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findTheLongestSubstring(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("eleetminicoworoep", 13);
    test("leetcodeisgreat", 5);
    test("bcbcbc", 6);

    return 0;
}
