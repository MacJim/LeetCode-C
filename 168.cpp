/*
 * 168. Excel Sheet Column Title
 * https://leetcode.com/problems/excel-sheet-column-title/
 */

#include <iostream>
#include <string>

//#include "helpers/Operators.hpp"


#pragma mark - 1. Remainder
/*
 * Note that the minimum remainder is 1 instead of 0.
 */
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Excel Sheet Column Title.
// Memory Usage: 5.9 MB, less than 59.75% of C++ online submissions for Excel Sheet Column Title.
class Solution1 {
public:
    std::string convertToTitle(int columnNumber) {
        if (columnNumber == 1) {
            return "A";
        }

        std::string returnValue;

        while (columnNumber) {
            auto lowestIndex = columnNumber % 26;
            if (lowestIndex == 0) {
                // Remainder of 'Z' is 0.
                lowestIndex = 25;
                columnNumber -= 26;    // Avoid an additional letter.
            } else {
                // 'A' ~ 'Y'.
                lowestIndex -= 1;
            }

            auto lowestLetter = static_cast<char>(lowestIndex) + 'A';
            returnValue.insert(returnValue.begin(), lowestLetter);

            columnNumber /= 26;
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Excel Sheet Column Title.
// Memory Usage: 5.8 MB, less than 59.75% of C++ online submissions for Excel Sheet Column Title.
class Solution {
public:
    std::string convertToTitle(int columnNumber) {
        if (columnNumber == 1) {
            return "A";
        }

        std::string returnValue;

        while (columnNumber) {
            columnNumber -= 1;
            auto lowestIndex = columnNumber % 26;

            auto lowestLetter = static_cast<char>(lowestIndex) + 'A';
            returnValue.insert(returnValue.begin(), lowestLetter);

            columnNumber /= 26;
        }

        return returnValue;
    }
};


void test(const int columnNumber, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.convertToTitle(columnNumber);

    if (result == expectedResult) {
        std::cout << "[Correct] " << columnNumber << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << columnNumber << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, "A");
    test(26, "Z");
    test(27, "AA");
    test(28, "AB");
    test(701, "ZY");
    test(26 * 26 + 26 + 1, "AAA");
    test(2147483647, "FXSHRXW");

    return 0;
}
