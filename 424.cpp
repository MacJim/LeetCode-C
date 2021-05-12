/*
 * 424. Longest Repeating Character Replacement
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

//#include "helpers/Operators.hpp"


#pragma mark - 1. 2 pointers, sliding window
// Runtime: 12 ms, faster than 52.52% of C++ online submissions for Longest Repeating Character Replacement.
// Memory Usage: 6.7 MB, less than 99.11% of C++ online submissions for Longest Repeating Character Replacement.
class Solution {
private:
//    static const char PLACEHOLDER = '\n';
//    int getReplacementCount
//    inline size_t getCharIndex(char c) {
//        return c - 'A';
//    }

public:
    int characterReplacement(std::string& s, int k) {
        if (s.size() == 1) {
            return 1;
        }

        int returnValue = 0;

        /// [left, right)
        int left = 0;
        int right = 0;

        // We can have more than 2 chars.
        auto charCounts = std::vector<int>(26, 0);
        /// Sum of `charCounts`.
        int sum = 0;

        while (right < s.size()) {
//            const auto sum = std::accumulate(charCounts.begin(), charCounts.end(), 0);
            const auto max = *std::max_element(charCounts.begin(), charCounts.end());
            const auto delta = sum - max;

            if (delta <= k) {
                returnValue = std::max(returnValue, sum);

                // Increase right.
                auto& rightChar = s[right];
                charCounts[rightChar - 'A'] += 1;
                right += 1;

                sum += 1;
            } else {
                // Increase left.
                auto& leftChar = s[left];
                charCounts[leftChar - 'A'] -= 1;
                left += 1;

                sum -= 1;
            }
        }

        const auto finalMax = *std::max_element(charCounts.begin(), charCounts.end());
        const auto finalDelta = sum - finalMax;
        if (finalDelta <= k) {
            returnValue = std::max(returnValue, sum);
        }

        return returnValue;
    }
};


void test(const std::string& s, const int k, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.characterReplacement(sCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("BBBBBCC", 2, 7);
    test("ABAB", 2, 4);
    test("AABABBA", 1, 4);
    test("AABBBBCCBBBBAA", 2, 10);
    test("AABBBBCCBBBBAA", 4, 12);

    test("ABAB", 0, 1);
    test("AABBBBCCC", 0, 4);
    test("AABBBBCCCCC", 0, 5);

    return 0;
}
