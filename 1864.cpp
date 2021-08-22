/*
 * 1864. Minimum Number of Swaps to Make the Binary String Alternating
 * https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/
 */

#include <iostream>
#include <string>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Count 0 and 1
// Runtime: 4 ms, faster than 62.62% of C++ online submissions for Minimum Number of Swaps to Make the Binary String Alternating.
// Memory Usage: 6.5 MB, less than 75.24% of C++ online submissions for Minimum Number of Swaps to Make the Binary String Alternating.
class Solution {
private:
    inline int getZeroStartCount(const std::string& s) {
        int returnValue = 0;
        for (int i = 0; i < s.size(); i += 2) {
            // 0
            if (s[i] != '0') {
                returnValue += 1;
            }
        }

        return returnValue;
    }

    inline int getOneStartCount(const std::string& s) {
        int returnValue = 0;
        for (int i = 0; i < s.size(); i += 2) {
            // 1
            if (s[i] != '1') {
                returnValue += 1;
            }
        }

        return returnValue;
    }

public:
    int minSwaps(const std::string& s) {
        int count0 = 0;
        int count1 = 0;

        for (const auto& c: s) {
            if (c == '0') {
                count0 += 1;
            } else {
                count1 += 1;
            }
        }

        if (std::abs(count0 - count1) > 1) {
            return -1;
        }

        if (count0 == count1) {
            int returnValue = std::min(getZeroStartCount(s), getOneStartCount(s));
            return returnValue;
        } else if (count0 > count1) {
            int returnValue = getZeroStartCount(s);
            return returnValue;
        } else {
            int returnValue = getOneStartCount(s);
            return returnValue;
        }
    }
};


void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.minSwaps(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("111000", 1);
    test("101", 0);
    test("1110", -1);
    test("10110101", -1);
    test("101011100", 1);
    test("111011000", 2);
    test("111110000", 2);
    test("111001100", 2);

    return 0;
}
