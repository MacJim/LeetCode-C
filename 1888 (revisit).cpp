/*
 * 1888. Minimum Number of Flips to Make the Binary String Alternating
 * https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/
 */

#include <iostream>
#include <string>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Append s to s, and sliding window
/*
 * This is pretty similar to my "find separation point" thought, but is much simpler.
 *
 * It is slower, though.
 */
// Runtime: 52 ms, faster than 62.72% of C++ online submissions for Minimum Number of Flips to Make the Binary String Alternating.
// Memory Usage: 21.8 MB, less than 49.56% of C++ online submissions for Minimum Number of Flips to Make the Binary String Alternating.
class Solution1 {
public:
    int minFlips(std::string& s) {
        if (s.size() == 1) {
            return 0;
        }

        const int len = s.size();

        s += s;    // Append to back.

        /// Prefix sum. The 0th element is always 0.
        auto losses0 = std::vector<int>(s.size() + 1, 0);
        // Calculate 0 and 1 losses.
        for (int i = 0; i < s.size(); i += 2) {
            if (s[i] == '1') {
                losses0[i + 1] = 1;
            }
        }
        for (int i = 1; i < s.size(); i += 2) {
            if (s[i] == '0') {
                losses0[i + 1] = 1;
            }
        }
        // Calculate prefix sum.
        for (int i = 1; i < s.size(); i += 1) {
            losses0[i + 1] += losses0[i];
        }

        int returnValue = INT_MAX;

        for (int start = 0; start <= len; start += 1) {
            const int end = start + len;
            const int loss0 = losses0[end] - losses0[start];
            const int loss1 = len - loss0;
            const int smallerLoss = std::min(loss0, loss1);
            returnValue = std::min(returnValue, smallerLoss);
        }

        return returnValue;
    }
};


#pragma mark - 2. Try all separation points
// Runtime: 44 ms, faster than 73.52% of C++ online submissions for Minimum Number of Flips to Make the Binary String Alternating.
// Memory Usage: 15 MB, less than 63.17% of C++ online submissions for Minimum Number of Flips to Make the Binary String Alternating.
class Solution {
public:
    int minFlips(std::string& s) {
        if (s.size() == 1) {
            return 0;
        }

        /// Prefix sum. The 0th element is always 0.
        auto losses0 = std::vector<int>(s.size() + 1, 0);
        // Calculate 0 and 1 losses.
        for (int i = 0; i < s.size(); i += 2) {
            if (s[i] == '1') {
                losses0[i + 1] = 1;
            }
        }
        for (int i = 1; i < s.size(); i += 2) {
            if (s[i] == '0') {
                losses0[i + 1] = 1;
            }
        }
        // Calculate prefix sum.
        for (int i = 1; i < s.size(); i += 1) {
            losses0[i + 1] += losses0[i];
        }

        int returnValue = std::min(losses0.back(), static_cast<int>(s.size()) - losses0.back());    // Result for: use the string as-is without moving characters from front to back.

        /*
         * - Part 1: [front, separation]
         * - Part 2: (separation, back]
         */
        for (int separation = 1; separation <= s.size(); separation += 1) {
            const int part2Loss0 = losses0.back() - losses0[separation];

            int part1Loss0 = losses0[separation] - losses0.front();
            if (s.size() % 2) {
                // String length is odd: part 1 loss is switched.
                part1Loss0 = separation - part1Loss0;
            }

            const int loss0 = part1Loss0 + part2Loss0;
            const int loss1 = s.size() - loss0;

            const int smallerLoss = std::min(loss0, loss1);
            returnValue = std::min(returnValue, smallerLoss);
        }

        return returnValue;
    }
};


void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.minFlips(sCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("001011101", 1);
    test("10001100101000000", 5);
    test("010", 0);
    test("1110", 1);
    test("111000", 2);

    return 0;
}
