/*
 * 171. Excel Sheet Column Number
 * https://leetcode.com/problems/excel-sheet-column-number/
 */

#include <iostream>
#include <vector>


#pragma mark - 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Excel Sheet Column Number.
// Memory Usage: 5.8 MB, less than 96.84% of C++ online submissions for Excel Sheet Column Number.
class Solution {
public:
    int titleToNumber(const std::string& columnTitle) {
        int returnValue = 0;
        int multiplier = 1;

        for (auto it = columnTitle.rbegin(); it != columnTitle.rend(); it += 1) {
            int currentValue = static_cast<int>(*it - 'A' + 1);
            currentValue *= multiplier;
            returnValue += currentValue;

            if (multiplier < 308915776) {
                // Nasty way to prevent overflow on the final letter.
                multiplier *= 26;
            }
        }

        return returnValue;
    }
};


void test(const std::string& columnTitle, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.titleToNumber(columnTitle);

    if (result == expectedResult) {
        std::cout << "[Correct] " << columnTitle << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << columnTitle << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("A", 1);
    test("AB", 28);
    test("ZY", 701);
    test("FXSHRXW", 2147483647);

    return 0;
}
