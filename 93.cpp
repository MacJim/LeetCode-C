/*
 * 93. Restore IP Addresses
 * https://leetcode.com/problems/restore-ip-addresses/
 */

/*
 * Valid address:
 *
 * - At most 3 digits in each part
 * - If 3 digits, max value is 255
 * - If 2 or 3 digits, cannot start with 0
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// This might be inefficient because we're returning a lot of temporary objects.
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Restore IP Addresses.
// Memory Usage: 7.9 MB, less than 10.97% of C++ online submissions for Restore IP Addresses.
class Solution1 {
private:
    std::vector<std::string> recursion(const std::string& s, const signed char remainingParts, const size_t startIndex) {
        const auto remainingLength = s.size() - startIndex;
        if (remainingLength < remainingParts) {
            // Not enough digits.
            return {};
        }
        if (remainingParts == 0) {
            if (remainingLength == 0) {
                // This string is complete.
                return {""};
            } else {
                // Extraneous digits.
                return {};
            }
        }

        auto returnValue = std::vector<std::string>();

        // 1 digit.
        auto subResults1 = recursion(s, remainingParts - 1, startIndex + 1);
        auto prefix1 = s.substr(startIndex, 1);
        for (const auto& subResult: subResults1) {
            if (subResult.empty()) {
                // Avoid the trailing dot.
                returnValue.push_back(prefix1);
            } else {
                auto result = prefix1;
                result += ".";
                result += subResult;
                returnValue.push_back(result);
            }
        }

        // 2 digits.
        if ((remainingLength >= 2) && (s[startIndex] != '0')) {
            auto subResults2 = recursion(s, remainingParts - 1, startIndex + 2);
            auto prefix2 = s.substr(startIndex, 2);
            for (const auto& subResult: subResults2) {
                if (subResult.empty()) {
                    returnValue.push_back(prefix2);
                } else {
                    auto result = prefix2;
                    result += ".";
                    result += subResult;
                    returnValue.push_back(result);
                }
            }
        }

        // 3 digits.
        if ((remainingLength >= 3) && (s[startIndex] != '0')) {
            auto innerNumber = static_cast<int>(s[startIndex] - '0') * 100 + static_cast<int>(s[startIndex + 1] - '0') * 10 + static_cast<int>(s[startIndex + 2] - '0');
            if (innerNumber <= 255) {
                auto subResults3 = recursion(s, remainingParts - 1, startIndex + 3);
                auto prefix3 = s.substr(startIndex, 3);
                for (const auto& subResult: subResults3) {
                    if (subResult.empty()) {
                        returnValue.push_back(prefix3);
                    } else {
                        auto result = prefix3;
                        result += ".";
                        result += subResult;
                        returnValue.push_back(result);
                    }
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<std::string> restoreIpAddresses(const std::string& s) {
        if (s.size() < 4) {
            // Not enough digits.
            return {};
        }
        if (s.size() == 4) {
            return {std::string({s[0], '.', s[1], '.', s[2], '.', s[3]})};
        }

        auto returnValue = recursion(s, 4, 0);

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1: Eliminates the extra copies caused by the return values
// Runtime: 4 ms, faster than 65.55% of C++ online submissions for Restore IP Addresses.
// Memory Usage: 7 MB, less than 30.90% of C++ online submissions for Restore IP Addresses.
class Solution {
private:
    void recursion(std::vector<std::string>& returnValue, const std::string& prefix, const std::string& s, const signed char remainingParts, const size_t startIndex) {
        const auto remainingLength = s.size() - startIndex;
        if (remainingLength < remainingParts) {
            // Not enough digits.
            return;
        }
        if (remainingParts == 0) {
            if (remainingLength == 0) {
                // This string is complete.
                returnValue.push_back(prefix);
            }    // Otherwise, there are extraneous digits.

            return;
        }

        // 1 digit.
        auto prefix1 = prefix;
        if (!prefix1.empty()) {
            prefix1 += ".";
        }
        prefix1 += s.substr(startIndex, 1);

        recursion(returnValue, prefix1, s, remainingParts - 1, startIndex + 1);

        // 2 digits.
        if ((remainingLength >= 2) && (s[startIndex] != '0')) {
            auto prefix2 = prefix;
            if (!prefix2.empty()) {
                prefix2 += ".";
            }
            prefix2 += s.substr(startIndex, 2);

            recursion(returnValue, prefix2, s, remainingParts - 1, startIndex + 2);
        }

        // 3 digits.
        if ((remainingLength >= 3) && (s[startIndex] != '0')) {
            auto innerNumber = static_cast<int>(s[startIndex] - '0') * 100 + static_cast<int>(s[startIndex + 1] - '0') * 10 + static_cast<int>(s[startIndex + 2] - '0');
            if (innerNumber <= 255) {
                auto prefix3 = prefix;
                if (!prefix3.empty()) {
                    prefix3 += ".";
                }
                prefix3 += s.substr(startIndex, 3);

                recursion(returnValue, prefix3, s, remainingParts - 1, startIndex + 3);
            }
        }
    }

public:
    std::vector<std::string> restoreIpAddresses(const std::string& s) {
        if (s.size() < 4) {
            // Not enough digits.
            return {};
        }
        if (s.size() == 4) {
            return {std::string({s[0], '.', s[1], '.', s[2], '.', s[3]})};
        }

        auto returnValue = std::vector<std::string>();
        recursion(returnValue, "", s, 4, 0);

        return returnValue;
    }
};


#pragma mark - 3
/*
 * I could have used 4 indices instead of this many levels of recursion: simply just each part's validity.
 */


void test(const std::string& s, const std::vector<std::string>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.restoreIpAddresses(s);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("25525511135", {"255.255.11.135","255.255.111.35"});
    test("0000", {"0.0.0.0"});
    test("010010", {"0.10.0.10","0.100.1.0"});
    test("101023", {"1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"});
    test("000", {});

    return 0;
}
