/*
 * 402. Remove K Digits
 * https://leetcode.com/problems/remove-k-digits/
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"


#pragma mark - 1
/*
 * Find the first digit that's larger than the next digit.
 * If we cannot find such a digit (self-increasing), remove from the tail.
 */
// Runtime: 28 ms, faster than 18.97% of C++ online submissions for Remove K Digits.
// Memory Usage: 6.8 MB, less than 82.47% of C++ online submissions for Remove K Digits.
class Solution {
public:
    std::string removeKdigits(std::string num, int k) {
        if (num[0] == '0') {
            // `num` does not have any leading zeros except for the zero itself.
            return "0";
        }

        if (k == num.size()) {
            return "0";
        }

        // Main loop.
        for (int remainingK = k; remainingK > 0; remainingK -= 1) {
            bool elementErased = false;

            for (size_t i = 0; i < (num.size() - 1); i += 1) {
                const auto& currentDigit = num[i];
                const auto& nextDigit = num[i + 1];

                if (currentDigit > nextDigit) {
                    // Remove the current digit.
                    num.erase(i, 1);    // This operation is very expensive :(
                    elementErased = true;
                    break;
                }
            }

            if (!elementErased) {
                // The current string is self-increasing. Remove from tail.
                num.erase(num.size() - remainingK);
                break;
            }
        }

        // Remove leading 0s.
        if (num[0] == '0') {
            size_t nonZeroIndex = 1;
            for (; (num[nonZeroIndex] == '0') && (nonZeroIndex < num.size()); nonZeroIndex += 1) {

            }

            num = num.substr(nonZeroIndex);
        }

        if (num.empty()) {
            num = "0";
        }

        return num;
    }
};


#pragma mark - 2. Optimize 1 using a separate `returnValue` string that get `push_back`ed instead of `erase`ed.


void test(const std::string& num, const int k, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

//    auto numCopy = num;
    auto result = solutionInstance.removeKdigits(num, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << num << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << num << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("0", 0, "0");
    test("123", 3, "0");
    test("1432219", 3, "1219");
    test("10200", 1, "200");
    test("12345", 1, "1234");
    test("1233332", 2, "12332");
    test("200", 1, "0");
    test("1412345", 1, "112345");
    test("1412345", 2, "11234");
    test("10", 2, "0");

    return 0;
}
