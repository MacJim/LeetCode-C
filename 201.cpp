/*
 * 201. Bitwise AND of Numbers Range
 * https://leetcode.com/problems/bitwise-and-of-numbers-range/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Naive solution
// Obviously timed out.
class Solution1 {
public:
    int rangeBitwiseAnd(int left, int right) {
        if (left == right) {
            return left;
        }

        int returnValue = left;
        for (int num = left + 1; num <= right; num += 1) {
            returnValue &= num;
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Runtime: 228 ms, faster than 6.92% of C++ online submissions for Bitwise AND of Numbers Range.
// Memory Usage: 5.8 MB, less than 94.86% of C++ online submissions for Bitwise AND of Numbers Range.
class Solution2 {
public:
    int rangeBitwiseAnd(int left, int right) {
        if (left == right) {
            return left;
        }

        int returnValue = right;
        for (int num = left; num < right; num += 1) {    // Must use `<` to prevent integer overflow.
            returnValue &= num;
            if (returnValue == 0) {
                break;
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Judge carry
// Runtime: 4 ms, faster than 90.16% of C++ online submissions for Bitwise AND of Numbers Range.
// Memory Usage: 5.9 MB, less than 70.60% of C++ online submissions for Bitwise AND of Numbers Range.
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        if (left == right) {
            return left;
        }

        short highestBit = 0;
        int temp = right;
        while (temp) {
            highestBit += 1;
            temp >>= 1;
        }

        int returnValue = 0;

        // Highest bit.
        int highestBitNumber = 1;
        for (short i = 1; i < highestBit; i += 1) {
            highestBitNumber <<= 1;
        }
        if (left >= highestBitNumber) {
            returnValue = highestBitNumber;
        }

        // Upcoming bits.
        for (short currentBit = (highestBit - 1); currentBit >= 0; currentBit -= 1) {
            auto currentBitNumber = 1;
            for (short i = 1; i < currentBit; i += 1) {
                currentBitNumber <<= 1;
            }

            if ((right - left) < currentBitNumber) {
                /*
                 * No carry on this bit.
                 * This bit may be 1.
                 */
                if ((left & currentBitNumber) && (right & currentBitNumber)) {
                    returnValue += currentBitNumber;
                }
            }
        }

        return returnValue;
    }
};


void test(const int left, const int right, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.rangeBitwiseAnd(left, right);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << left << ", " << right << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << left << ", " << right << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(0b110, 0b111, 0b110);
    test(0b0110, 0b1001, 0);
    test(0b10001, 0b11111, 0b10000);
    test(0b010001, 0b111111, 0);
    test(5, 7, 4);
    test(0, 0, 0);
    test(1, 2147483647, 0);

    return 0;
}
