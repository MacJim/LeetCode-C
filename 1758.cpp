/*
 * 1758. Minimum Changes To Make Alternating Binary String
 * https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/
 */

#include <iostream>
#include <string>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Can either start with 0 or 1
// Runtime: 4 ms, faster than 87.77% of C++ online submissions for Minimum Changes To Make Alternating Binary String.
// Memory Usage: 6.8 MB, less than 94.47% of C++ online submissions for Minimum Changes To Make Alternating Binary String.
class Solution {
public:
    int minOperations(const std::string& s) {
        /// 010101...
        int result0 = 0;
        /// 101010...
        int result1 = 0;

        for (int i = 0; i < s.size(); i += 2) {
            if (s[i] == '1') {
                result0 += 1;
            } else {
                result1 += 1;
            }
        }
        for (int i = 1; i < s.size(); i += 2) {
            if (s[i] == '0') {
                result0 += 1;
            } else {
                result1 += 1;
            }
        }

        return std::min(result0, result1);
    }
};


#pragma mark - 2. Optimized 1
/*
 * Only need to log `result0` because `result1 == s.size() - result0`.
 */


void test(const std::string& s, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.minOperations(s);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("0100", 1);
    test("10110101", 3);
    test("10", 0);
    test("1111", 2);
    test("0000", 2);

    return 0;
}
