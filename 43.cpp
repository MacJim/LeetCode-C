/*
 * 43. Multiply Strings
 * https://leetcode.com/problems/multiply-strings/
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. (i1 + i2) = 0 ~ (len1 - 1 + len2 - 1 + 1)
// Runtime: 4 ms, faster than 88.94% of C++ online submissions for Multiply Strings.
// Memory Usage: 6.6 MB, less than 56.63% of C++ online submissions for Multiply Strings.
class Solution {
public:
    std::string multiply(const std::string& numStr1, const std::string& numStr2) {
        if ((numStr1 == "0") || (numStr2 == "0")) {
            return "0";
        }

        const auto len1 = numStr1.size();
        const auto len2 = numStr2.size();

        auto nums1 = std::vector<short>(len1, 0);
        auto nums2 = std::vector<short>(len2, 0);

        // Reversed order.
        for (size_t strIndex = 0; strIndex < len1; strIndex += 1) {
            size_t numIndex = len1 - strIndex - 1;
            nums1[numIndex] = static_cast<short>(numStr1[strIndex] - '0');
        }
        for (size_t strIndex = 0; strIndex < len2; strIndex += 1) {
            size_t numIndex = len2 - strIndex - 1;
            nums2[numIndex] = static_cast<short>(numStr2[strIndex] - '0');
        }

        std::string returnValue;

        int carry = 0;
        for (int indexSum = 0; indexSum <= (len1 - 1 + len2 - 1); indexSum += 1) {
            int currentResult = carry;

            for (size_t i1 = 0; (i1 <= indexSum) && (i1 < len1); i1 += 1) {
                size_t i2 = indexSum - i1;
                if (i2 >= len2) {
                    continue;
                }

                currentResult += (nums1[i1] * nums2[i2]);
            }

            if (currentResult >= 10) {
                carry = currentResult / 10;
                currentResult %= 10;
            } else {
                carry = 0;
            }

            const char currentChar = static_cast<char>('0' + currentResult);
            returnValue.push_back(currentChar);    // Add in reverse order.
        }

        // Final carry.
        if (carry) {
            const char lastChar = static_cast<char>('0' + carry);
            returnValue.push_back(lastChar);
        }

        std::reverse(returnValue.begin(), returnValue.end());

        return returnValue;
    }
};


void test(const std::string& numStr1, const std::string& numStr2, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.multiply(numStr1, numStr2);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << numStr1 << " x " << numStr2 << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << numStr1 << " x " << numStr2 << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("621", "268", "166428");
    test("123", "456", "56088");

    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto generator = std::default_random_engine(seed);
    auto distribution = std::uniform_int_distribution<int>(0, 40000);

    for (int i = 0; i < 100; i += 1) {
        auto num1 = distribution(generator);
        auto num2 = distribution(generator);
        auto result = num1 * num2;

        auto str1 = std::to_string(num1);
        auto str2 = std::to_string(num2);
        auto resultStr = std::to_string(result);

        test(str1, str2, resultStr);
    }

    return 0;
}
