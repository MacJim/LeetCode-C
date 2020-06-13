/*
 * 97. Interleaving String
 * https://leetcode.com/problems/interleaving-string/
 */

#include <iostream>
#include <vector>
#include <string>


#pragma mark - 1. Reserve a row & a column for "no char from this string".
// Runtime: 4 ms, faster than 78.44% of C++ online submissions for Interleaving String.
// Memory Usage: 6.2 MB, less than 88.66% of C++ online submissions for Interleaving String.
class Solution {
public:
    bool isInterleave(std::string si, std::string sj, std::string target) {
        const auto iLen = si.size();
        if (iLen == 0) {
            return (sj == target);
        }

        const auto jLen = sj.size();
        if (jLen == 0) {
            return (si == target);
        }

        const auto targetLen = target.size();
        if ((iLen + jLen) != targetLen) {
            return false;
        }

        /**
         * Stores the upcoming index in `target`.
         *
         * When the last value equals `targetLen`, returns `true`.
         *
         * The 0th row and column mean "do not add any char from string i or j".
         *
         * -1 means "not possible".
         */
        auto currentRow = std::vector<int>(iLen + 1, -1);

        // First row.
        if (si.at(0) == target.at(0)) {
            // Do not add any char from string j.
            currentRow.at(1) = 1;
        }
        if (currentRow.at(1) == 1) {
            for (size_t i = 1; i < iLen; i += 1) {
                if (si.at(i) == target.at(i)) {
                    currentRow.at(i + 1) = i + 1;
                } else {
                    break;
                }
            }
        }

        // Second row.
        size_t j = 0;

        if (sj.at(0) == target.at(0)) {
            // Do not add any char from string i.
            currentRow.at(0) = 1;
        }
        for (size_t i = 0; i < iLen; i += 1) {
            const auto& left = currentRow.at(i);
            auto& upOrCurrent = currentRow.at(i + 1);

            if ((left > 0) && (si.at(i) == target.at(left))) {
                // Compare `si` and `target`.
                upOrCurrent = left + 1;
            } else if ((upOrCurrent > 0) && (sj.at(j) == target.at(upOrCurrent))) {
                // Compare `sj` and `target`.
                upOrCurrent = upOrCurrent + 1;
            } else {
                upOrCurrent = -1;
            }
        }

        j += 1;

        // Upcoming rows.
        for (; j < jLen; j += 1) {
            // First column.
            auto& firstElement = currentRow.at(0);
            if (firstElement > 0) {
                if (sj.at(j) == target.at(firstElement)) {
                    firstElement += 1;
                } else {
                    firstElement = -1;
                }
            }

            // Upcoming columns.
            for (size_t i = 0; i < iLen; i += 1) {
                const auto& left = currentRow.at(i);
                auto& upOrCurrent = currentRow.at(i + 1);

                if ((left > 0) && (si.at(i) == target.at(left))) {
                    // Compare `si` and `target`.
                    upOrCurrent = left + 1;
                } else if ((upOrCurrent > 0) && (sj.at(j) == target.at(upOrCurrent))) {
                    // Compare `sj` and `target`.
                    upOrCurrent = upOrCurrent + 1;
                } else {
                    upOrCurrent = -1;
                }
            }
        }

        return (currentRow.back() == targetLen);
    }
};


int main() {
    auto solutionInstance = Solution();

    std::string s11 = "aabcc", s12 = "dbbca", s13 = "aadbbcbcac";
    std::cout << solutionInstance.isInterleave(s11, s12, s13) << std::endl;    // true

    std::string s21 = "aabcc", s22 = "dbbca", s23 = "aadbbbaccc";
    std::cout << solutionInstance.isInterleave(s21, s22, s23) << std::endl;    // false

    std::string s31 = "ab", s32 = "ac", s33 = "aabc";
    std::cout << solutionInstance.isInterleave(s31, s32, s33) << std::endl;    // true

    return 0;
}
