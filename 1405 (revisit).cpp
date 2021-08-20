/*
 * 1405. Longest Happy String
 * https://leetcode.com/problems/longest-happy-string/
 */

#include <iostream>
#include <vector>
#include <array>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Shorten 1st longest to match 2nd longest (unfinished)
class Solution1 {
public:
    std::string longestDiverseString(int a, int b, int c) {
        auto returnValue = std::string();

        /// 0: a, 1: b, 2: c
        int i1 = 0;
        int i2 = 0;

        std::array<int, 3> counts = {a, b, c};

        while (true) {
            if ((counts[0] == counts[1]) && (counts[1] == counts[2])) {
                // 3 numbers appear for the same times.
                auto appendedString = std::string();

                if (returnValue.empty() || (returnValue.back() == 'b') || (returnValue.back() == 'c')) {
                    for (int i = 0; i < counts[0]; i += 1) {
                        appendedString += "abc";
                    }
                } else {
                    for (int i = 0; i < counts[0]; i += 1) {
                        appendedString += "bac";
                    }
                }

                break;
            }

            // Find the 2 most frequent numbers and make their occurrence equal.
            for (int i = 0; i < 3; i += 1) {
                if (counts[i] > counts[i1]) {
                    i2 = i1;
                    i1 = i;
                } else if (counts[i] > counts[i2]) {
                    i2 = i;
                }
            }

            if (counts[i1] == 0) {
                // No more characters.
                break;
            }

            if (counts[i1] == counts[i2]) {

            }
        }


        return returnValue;
    }
};


#pragma mark - 2. DP, state machine (revisit)
/*
 * Log the previous ending character to determine the current character and its length:
 *
 * - The previous and current characters must not equal
 * - If there are more remaining previous characters than the current character, set current character length to 1; otherwise, set current character length to 2
 */
// This is faster than I thought.
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Longest Happy String.
// Memory Usage: 6.1 MB, less than 70.32% of C++ online submissions for Longest Happy String.
class Solution {
public:
    std::string longestDiverseString(const int a, const int b, const int c) {
        std::array<int, 3> counts = {a, b, c};    // Just use `'a' + i` to get the target character.
        int previousMaxIndex = -1;
        auto returnValue = std::string();

        while (true) {
            /// Max index that is different from the previous max index.
            int maxIndex = -1;
            for (int i = 0; i < 3; i += 1) {
                if (i == previousMaxIndex) {
                    // Cannot have the same character twice.
                    continue;
                }

                if ((maxIndex == -1) || (counts[i] > counts[maxIndex])) {
                    maxIndex = i;
                }
            }

            if (counts[maxIndex] == 0) {
                // No more characters.
                break;
            }

            int currentCount = std::min(counts[maxIndex], 2);
            if ((previousMaxIndex != -1) && (counts[previousMaxIndex] > counts[maxIndex])) {
                // Save on current character because we need more of it.
                currentCount = 1;
            }

            counts[maxIndex] -= currentCount;

            for (int i = 0; i < currentCount; i += 1) {
                returnValue.push_back('a' + maxIndex);
            }

            previousMaxIndex = maxIndex;
        }

        return returnValue;
    }
};


bool isResultValid(const std::string& s) {
    char previousChar = '\0';
    char previousOccurrence = 0;

    for (const char& c: s) {
        if (c == previousChar) {
            if (previousOccurrence == 2) {
                return false;
            }

            previousOccurrence += 1;
        } else {
            previousChar = c;
            previousOccurrence = 1;
        }
    }

    return true;
}


void test(int a, int b, int c, const int expectedLength) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.longestDiverseString(a, b, c);

    if ((result.size() == expectedLength) && isResultValid(result)) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << a << ", " << b << ", " << c << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << a << ", " << b << ", " << c << ": " << result << " (should be length " << expectedLength << ")" << std::endl;
    }
}


int main() {
    test(2, 2, 2, 6);
    test(1, 1, 7, 8);
    test(500, 3, 0, 11);
    test(500, 3, 500, 1003);

    return 0;
}
