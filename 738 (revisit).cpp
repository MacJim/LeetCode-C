/*
 * 738. Monotone Increasing Digits
 * https://leetcode.com/problems/monotone-increasing-digits/
 */

#include <iostream>
#include <stack>
#include <deque>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. WRONG ANSWER
// Cannot use a stack. Must see previous elements.
class Solution1 {
public:
    int monotoneIncreasingDigits(int N) {
        if (N < 10) {
            return N;
        }

        auto digits = std::stack<int>();
        while (N) {
            const int currentDigit = N % 10;
            digits.push(currentDigit);
            N = N / 10;
        }

        int previousDigit = digits.top();
        digits.pop();
        int returnValue = previousDigit * 10;

        while (!digits.empty()) {
            int currentDigit = digits.top();
            digits.pop();

            if (currentDigit < previousDigit) {
                // Previous digit minus 1. Remaining digits changed to 9.
                returnValue -= 10;

                returnValue += currentDigit;
                returnValue *= 10;

                for (int i = 0; i < digits.size(); i += 1) {
                    returnValue += 9;
                    returnValue *= 10;
                }
                returnValue /= 10;

                return returnValue;
            } else {
                returnValue += currentDigit;
                returnValue *= 10;
                previousDigit = currentDigit;
            }
        }

        returnValue /= 10;

        return returnValue;
    }
};


#pragma mark - 2. Fixed 1 (revisit, spent a long time)
/*
 * I used `deque` so that I can insert from front.
 *
 * I could have used `vector` instead of `deque` for better performance.
 */
// Runtime: 6 ms, faster than 6.84% of C++ online submissions for Monotone Increasing Digits.
// Memory Usage: 6.5 MB, less than 5.05% of C++ online submissions for Monotone Increasing Digits.
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        if (N < 10) {
            return N;
        }

        auto digits = std::deque<int>();
        while (N) {
            const int currentDigit = N % 10;
            digits.push_front(currentDigit);
            N = N / 10;
        }

        for (int i = 1; i < digits.size(); i += 1) {
            if (digits[i - 1] > digits[i]) {
                /*
                 * Search for previous equal elements:
                 *
                 * - The initial one decrease by 1
                 * - Following ones decrease by 9
                 */
                int initialIndex = i - 2;
                while (initialIndex >= 0) {
                    if (digits[initialIndex] == digits[i - 1]) {
                        initialIndex -= 1;
                    } else {
                        break;
                    }
                }
                initialIndex += 1;

                digits[initialIndex] -= 1;

                for (int j = initialIndex + 1; j < digits.size(); j += 1) {
                    digits[j] = 9;
                }

                break;
            }
        }

        int returnValue = 0;
        for (const int& digit: digits) {
            returnValue *= 10;
            returnValue += digit;
        }

        return returnValue;
    }
};


void test(const int N, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.monotoneIncreasingDigits(N);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << N << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << N << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(10, 9);
    test(1234, 1234);
    test(332, 299);
    test(3210, 2999);
    test(35432, 34999);
    test(34323, 33999);
    test(33321, 29999);

    return 0;
}
