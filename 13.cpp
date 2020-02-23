/*
 * 13. Roman to Integer
 * https://leetcode.com/problems/roman-to-integer/
 */

/*
 * I 1
 * V 5 <- I
 * X 10 <- I
 * L 50 <- X
 * C 100 <- X
 * D 500 <- C
 * M 1000 <- C
 */

#define I_VAL 1
#define V_VAL 5
#define X_VAL 10
#define L_VAL 50
#define C_VAL 100
#define D_VAL 500
#define M_VAL 1000

#include <iostream>
#include <vector>
#include <string>


// MARK: - 1. Right to left
// Runtime: 16 ms, faster than 58.82% of C++ online submissions for Roman to Integer.
// Memory Usage: 8.4 MB, less than 72.55% of C++ online submissions for Roman to Integer.
class Solution {
public:
    int romanToInt(std::string s) {
        const auto len = s.size();
        if (len == 0) {
            return 0;
        }

        int returnValue = 0;

        int i = len - 1;    // We must use a singned variable as index because of the `i >= 0` judgements used below.

        // I
        while ((i >= 0) && (s.at(i) == 'I')) {
            i -= 1;
            returnValue += I_VAL;
        }

        // V / IV
        while ((i >= 0) && (s.at(i) == 'V')) {
            if (i == 0) {
                // Final char, no 'I' before this one.
                returnValue += V_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'I', add 4.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'I') {
                i -= 1;
                returnValue += (V_VAL - I_VAL);
            } else {
                returnValue += V_VAL;
            }
        }

        // X / IX
        while ((i >= 0) && (s.at(i) == 'X')) {
            if (i == 0) {
                // Final char, no 'I' before this one.
                returnValue += X_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'I', add 9.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'I') {
                i -= 1;
                returnValue += (X_VAL - I_VAL);
            } else {
                returnValue += X_VAL;
            }
        }

        // L / XL
        while ((i >= 0) && (s.at(i) == 'L')) {
            if (i == 0) {
                // Final char, no 'X' before this one.
                returnValue += L_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'X', add XL.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'X') {
                i -= 1;
                returnValue += (L_VAL - X_VAL);
            } else {
                returnValue += L_VAL;
            }
        }

        // C / XC
        while ((i >= 0) && (s.at(i) == 'C')) {
            if (i == 0) {
                // Final char, no 'X' before this one.
                returnValue += C_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'X', add XC.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'X') {
                i -= 1;
                returnValue += (C_VAL - X_VAL);
            } else {
                returnValue += C_VAL;
            }
        }

        // D / CD
        while ((i >= 0) && (s.at(i) == 'D')) {
            if (i == 0) {
                // Final char, no 'C' before this one.
                returnValue += D_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'C', add CD.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'C') {
                i -= 1;
                returnValue += (D_VAL - C_VAL);
            } else {
                returnValue += D_VAL;
            }
        }

        // M / CM
        while ((i >= 0) && (s.at(i) == 'M')) {
            if (i == 0) {
                // Final char, no 'C' before this one.
                returnValue += M_VAL;
                return returnValue;
            }
            
            // Read the next character. If it's 'C', add CM.
            i -= 1;
            const char& c2 = s.at(i);
            if (c2 == 'C') {
                i -= 1;
                returnValue += (M_VAL - C_VAL);
            } else {
                returnValue += M_VAL;
            }
        }

        return returnValue;
    }
};


void test(const std::string& s) {
    static auto solutionInstance = Solution();
    auto result = solutionInstance.romanToInt(s);
    std::cout << s << " -> " << result << std::endl;
}

int main() {
    const std::vector<std::string> testCases = {"III", "IV", "IX", "LVIII", "MCMXCIV"};
    for (const auto& aTestCase: testCases) {
        test(aTestCase);
    }

    return 0;
}
