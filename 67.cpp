/*
 * 67. Add Binary
 * https://leetcode.com/problems/add-binary/
 */

#include <iostream>
#include <string>


#pragma mark - 1
// Runtime: 4 ms, faster than 63.15% of C++ online submissions for Add Binary.
// Memory Usage: 6.1 MB, less than 97.72% of C++ online submissions for Add Binary.
class Solution {
public:
    std::string addBinary(std::string& a, std::string& b) {
        // a is always shorter than b.
        if (a.size() > b.size()) {
            std::swap(a, b);
        }

        const auto lengthDelta = b.size() - a.size();

        auto returnValue = std::string(b.size() + 1, '0');

        bool carry = false;
        for (int ai = a.size() - 1; ai >= 0; ai -= 1) {
            int bi = ai + lengthDelta;
            short current = 0;
            if (a[ai] == '1') {
                current += 1;
            }
            if (b[bi] == '1') {
                current += 1;
            }
            if (carry) {
                current += 1;
            }

            switch (current) {
                case 0:
                    carry = false;
                    break;

                case 1:
                    carry = false;
                    returnValue[bi + 1] = '1';
                    break;

                case 2:
                    carry = true;
                    break;

                case 3:
                    carry = true;
                    returnValue[bi + 1] = '1';
                    break;
            }
        }

        for (int bi = lengthDelta - 1; bi >= 0; bi -= 1) {
            if (carry && (b[bi] == '1')) {
                // Do nothing.
//                carry = true;
//                returnValue[bi] = '1';
            } else if (carry || (b[bi] == '1')) {
                carry = false;
                returnValue[bi + 1] = '1';
            } else {
                carry = false;
            }
        }

        if (carry) {
            returnValue[0] = '1';
        } else {
            returnValue = returnValue.substr(1);
        }

        return returnValue;
    }
};


void test(const std::string& a, const std::string& b, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto aCopy = a;
    auto bCopy = b;
    auto result = solutionInstance.addBinary(aCopy, bCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << a << " + " << b << " = " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << a << " + " << b << " = " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("100", "110010", "110110");
    test("11", "1", "100");
    test("1010", "1011", "10101");
    test("11111111111", "1", "100000000000");

    return 0;
}
