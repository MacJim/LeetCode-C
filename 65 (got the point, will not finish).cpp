/*
 * 65. Valid Number
 * https://leetcode.com/problems/valid-number/
 */

#include <iostream>
#include <string>
#include <vector>


class Solution {
public:
    bool isNumber(std::string s) {
        const auto len = s.size();
        if (len == 0) {
            return false;
        }

        size_t currentIndex = 0;

        currentIndex = parseSpace(s, currentIndex);
        if (currentIndex >= len) {
            return false;
        }

        currentIndex = parseSign(s, currentIndex);
        if (currentIndex >= len) {
            return false;
        }

        currentIndex = parseExponential(s, currentIndex);
        if (currentIndex == -1) {
            return false;
        }

        currentIndex = parseSpace(s, currentIndex);
        if (currentIndex == len) {
            return true;
        } else {
            return false;
        }
    }

    int parseSpace(const std::string& s, const size_t startIndex) {
        const auto len = s.size();

        size_t i = startIndex;
        while (i < len) {
            const char& c = s.at(i);
            if (c == ' ') {
                i += 1;
            } else {
                break;
            }
        }

        return i;
    }

    int parseSign(const std::string& s, const size_t startIndex) {
        const auto len = s.size();

        if (startIndex >= len) {
            return -1;
        }

        const char& c = s.at(startIndex);
        if ((c == '+') || (c == '-')) {
            return (startIndex + 1);
        } else {
            return startIndex;
        }
    }

    int parseInt(const std::string& s, const size_t startIndex) {
        const auto len = s.size();

        if (startIndex >= len) {
            return -1;
        }

        size_t i = startIndex;
        while (i < len) {
            const auto& c = s.at(i);

            int number = c - '0';
            if ((number >= 0) && (number <= 9)) {
                // This is a valid number.
                i += 1;
            } else {
                if (i == startIndex) {
                    return -1;
                } else {
                    break;
                }
            }
        }

        return i;
    }

    int parseFloat(const std::string& s, const size_t startIndex) {
        const size_t len = s.size();

        int i2 = parseInt(s, startIndex);
        if (i2 == -1) {
            // The first part is not an integer.
            return -1;
        } else if (i2 >= len) {
            return i2;
        }

        const char& dot = s.at(i2);
        if (dot == '.') {
            // Parse the next part.
            int i3 = parseInt(s, i2 + 1);
            return i3;
        } else {
            // No decimal.
            return i2;
        }
    }

    int parseExponential(const std::string& s, const size_t startIndex) {
        const auto len = s.size();

        int i2 = parseFloat(s, startIndex);
        if (i2 == -1) {
            // The first part is not a float.
            return -1;
        } else if (i2 >= len) {
            return i2;
        }

        const char& e = s.at(i2);
        if (e == 'e') {
            // Parse the next part.
            int i3 = parseSign(s, i2 + 1);
            int i4 = parseInt(s, i3);
            return i4;
        } else {
            // No exponential.
            return i2;
        }
    }
};

int main() {
    auto solutionInstance = Solution();
    std::vector<std::string> testCases = {
        ".1",    // true
        "0",
        " 0.1 ",
        "abc",
        "1 a",
        "2e10",
        " -90e3   ",
        " 1e",
        "e3",
        " 6e-1",
        " 99e2.5 ",
        "53.5e93",
        " --6 ",
        "-+3",
        "95a54e53"
    };
    for (const auto& aTestCase: testCases) {
        std::cout << aTestCase;
        auto result = solutionInstance.isNumber(aTestCase);
        if (result) {
            std::cout << " \tYES" << std::endl;
        } else {
            std::cout << " \tNO" << std::endl;
        }
    }

    return 0;
}
