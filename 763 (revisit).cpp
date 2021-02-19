/*
 * 763. Partition Labels
 * https://leetcode.com/problems/partition-labels/
 */

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <climits>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Wrong, unfinished
class Solution1 {
public:
    std::vector<int> partitionLabels(std::string& s) {
        if (s.empty()) {
            return {0};
        }

        auto firstOccurrences = std::array<int, 26>();
        std::fill(firstOccurrences.begin(), firstOccurrences.end(), 100);
        for (size_t i = 0; i < s.size(); i += 1) {
            if (firstOccurrences[s[i] - 'a'] == 100) {
                firstOccurrences[s[i] - 'a'] = i;
            }
        }

        auto returnValue = std::vector<int>();
        auto returnValueTotal = 0;

        for (size_t i = 0; i < s.size(); i += 1) {
            const auto& c1 = s[i];

            for (size_t j = (i + 1); j < s.size(); j += 1) {
                const auto& c2 = s[j];
                if (firstOccurrences[c2 - 'a'] < j) {
                    // It has occurred before.
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Official solution: log and find the last occurrences (revisit)
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Partition Labels.
// Memory Usage: 6.3 MB, less than 99.16% of C++ online submissions for Partition Labels.
class Solution {
public:
    std::vector<int> partitionLabels(std::string& s) {
        if (s.empty()) {
            return {0};
        }

        auto lastOccurrences = std::array<int, 26>();
        std::fill(lastOccurrences.begin(), lastOccurrences.end(), -1);
        for (int i = (s.size() - 1); i >= 0; i -= 1) {
            if (lastOccurrences[s[i] - 'a'] == -1) {
                lastOccurrences[s[i] - 'a'] = i;
            }
        }

        auto returnValue = std::vector<int>();

        int currentStart = 0;
        int currentEnd = -1;
        for (int i = 0; i < s.size(); i += 1) {
            if ((currentEnd != -1) && (i > currentEnd)) {
                returnValue.push_back(currentEnd - currentStart + 1);
                currentStart = i;
                currentEnd = -1;
            }

            const auto& c = s[i];
            currentEnd = std::max(currentEnd, lastOccurrences[c - 'a']);    // Find the last occurrence of the current character.
        }

        if (currentEnd == -1) {
            currentEnd = s.size() - 1;
        }
        returnValue.push_back(currentEnd - currentStart + 1);

        return returnValue;
    }
};


void test(const std::string& s, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.partitionLabels(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("abcde", {1,1,1,1,1});
    test("ababcbacadefegdehijhklij", {9, 7, 8});

    return 0;
}
