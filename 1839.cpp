/*
 * 1839. Longest Substring Of All Vowels in Order
 * https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. State machine
// I could have used comparison operators `<` to reduce code length.
// Runtime: 112 ms, faster than 42.02% of C++ online submissions for Longest Substring Of All Vowels in Order.
// Memory Usage: 22.2 MB, less than 99.07% of C++ online submissions for Longest Substring Of All Vowels in Order.
class Solution {
public:
    int longestBeautifulSubstring(const std::string& word) {
        if (word.size() < 5) {
            return 0;
        }

        int returnValue = 0;

        int start = -1;
        /**
         * - `\0`: Previous string is ill-formed
         * - `\n`: Has only non-vowels from [start, i)
         */
        char previousVowel = '\0';

        for (int i = 0; i < word.size(); i += 1) {
            const char& c = word[i];
            switch (c) {
                case 'a':
                    if (previousVowel == '\0') {
                        // Continue the current string.
                        previousVowel = 'a';
                        start = i;
                    } else if (previousVowel == '\n') {
                        // Continue the current string.
                        previousVowel = 'a';
                    } else if (previousVowel != 'a') {
                        // Ill-formed sub-string.
                        start = i;
                        previousVowel = 'a';
                    }
                    break;

                case 'e':
                    if ((previousVowel == 'a') || (previousVowel == 'e')) {
                        // Continue the current string.
                        previousVowel = 'e';
                    } else {
                        // Ill-formed sub-string.
                        start = -1;
                        previousVowel = '\0';
                    }
                    break;

                case 'i':
                    if ((previousVowel == 'e') || (previousVowel == 'i')) {
                        // Continue the current string.
                        previousVowel = 'i';
                    } else {
                        // Ill-formed sub-string.
                        start = -1;
                        previousVowel = '\0';
                    }
                    break;

                case 'o':
                    if ((previousVowel == 'i') || (previousVowel == 'o')) {
                        // Continue the current string.
                        previousVowel = 'o';
                    } else {
                        // Ill-formed sub-string.
                        start = -1;
                        previousVowel = '\0';
                    }
                    break;

                case 'u':
                    if ((previousVowel == 'o') || (previousVowel == 'u')) {
                        // Continue the current string.
                        previousVowel = 'u';
                        const int len = i - start + 1;
                        returnValue = std::max(returnValue, len);
                    } else {
                        // Ill-formed sub-string.
                        start = -1;
                        previousVowel = '\0';
                    }
                    break;

                default:
                    // Non-vowel.
                    if (previousVowel == '\0') {
                        // Can start with non-vowel.
                        start = i;
                        previousVowel = '\n';
                    } else if (previousVowel == 'u') {
                        // Extend.
                        const int len = i - start + 1;
                        returnValue = std::max(returnValue, len);
                    }
            }
        }

        return returnValue;
    }
};


void test(const std::string& word, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.longestBeautifulSubstring(word);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << word << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << word << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("zaeiouz", 7);
    test("zazezizozuz", 11);
    test("aeeeiiiioooauuuaeiou", 5);
    test("aeiaaioaaaaeiiiiouuuooaauuaeiu", 13);
    test("zzz", 0);
    test("aceioca", 0);
    test("bcidneuxaxo", 0);
    test("aeioaeiuxeiueiou", 0);

    return 0;
}
