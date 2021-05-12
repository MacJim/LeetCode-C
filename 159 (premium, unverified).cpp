/*
 * 159. Longest Substring with At Most Two Distinct Characters
 * https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
 *
 *  Given a string s , find the length of the longest substring t that contains at most 2 distinct characters.
 *
 *  Example 1:
 *  Input: "eceba"
 *  Output: 3
 *  Explanation: tis "ece" which its length is 3.
 *
 *  Example 2:
 *  Input: "ccaabbb"
 *  Output: 5
 *  Explanation: tis "aabbb" which its length is 5.
 *
 *  @tag-string
 *  @tag-2pointers
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"


#pragma mark - 1. 2 pointers
class Solution {
private:
    static const char PLACEHOLDER = '\n';

public:
    int longestSubstring(std::string& s) {
        if (s.size() < 2) {
            return s.size();
        }

        int returnValue = 0;

        // Log the 2 most recent characters and their last appearance.
        char c1 = PLACEHOLDER;
        char c2 = PLACEHOLDER;
        int lastC1Index = -1;
        int lastC2Index = -1;

        /// [left, right)
        int left = 0;
        int right = 0;

        while (right < s.size()) {
            const auto& rightChar = s[right];
            if (c1 == PLACEHOLDER) {
                // No characters yet.
                c1 = rightChar;
                lastC1Index = right;
            } else if (c1 == rightChar) {
                lastC1Index = right;
            } else if (c2 == PLACEHOLDER) {
                c2 = rightChar;
                lastC2Index = right;
            } else if (c2 == rightChar) {
                lastC2Index = right;
            } else {
                // This is a new character and needs to replace one of the previous 2.
                int currentLength = right - left;
                returnValue = std::max(returnValue, currentLength);

                if (lastC1Index < lastC2Index) {
                    left = lastC1Index + 1;

                    c1 = rightChar;
                    lastC1Index = right;
                } else {
                    left = lastC2Index + 1;

                    c2 = rightChar;
                    lastC2Index = right;
                }
            }

            right += 1;
        }

        const int lastLength = right - left;
        returnValue = std::max(returnValue, lastLength);

        return returnValue;
    }
};


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.longestSubstring(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("eceba", 3);
    test("ccaabbb", 5);
    test("accbbaaac", 5);
    test("accbbbaaaaaccbbbbb", 8);
    test("accbbbaaaaaccbbbbbbb", 9);
    test("aaabbccbbccaaa", 8);
    test("aabbccdd", 4);
    test("abbccd", 4);

    return 0;
}
