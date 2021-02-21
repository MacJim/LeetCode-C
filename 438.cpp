/*
 * 438. Find All Anagrams in a String
 * https://leetcode.com/problems/find-all-anagrams-in-a-string/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <array>
#include <set>

#include "helpers/Operators.hpp"


#pragma mark - 1. std::array
// Runtime: 8 ms, faster than 94.70% of C++ online submissions for Find All Anagrams in a String.
// Memory Usage: 8.3 MB, less than 95.26% of C++ online submissions for Find All Anagrams in a String.
class Solution {
public:
    std::vector<int> findAnagrams(std::string& s, std::string& p) {
        if (s.empty()) {
            return {};
        }

        auto returnValue = std::vector<int>();

        auto pOccurrences = std::array<int, 26>();
        for (const auto& c: p) {
            pOccurrences[c - 'a'] += 1;
        }

        auto sOccurrences = std::array<int, 26>();
        int currentLen = 0;
        for (int i = 0; i < s.size(); i += 1) {
            if (currentLen < p.size()) {
                currentLen += 1;
                sOccurrences[s[i] - 'a'] += 1;
            } else {
                if (sOccurrences == pOccurrences) {
                    returnValue.push_back(i - p.size());
                }
                sOccurrences[s[i - p.size()] - 'a'] -= 1;
                sOccurrences[s[i] - 'a'] += 1;
            }
        }

        if (sOccurrences == pOccurrences) {
            returnValue.push_back(s.size() - p.size());
        }

        return returnValue;
    }
};


void test(const std::string& s, const std::string& p, const std::set<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto pCopy = p;
    auto result = solutionInstance.findAnagrams(sCopy, pCopy);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << "[Correct] " << s << " " << p << ": " << resultSet << std::endl;
    } else {
        std::cout << "[Wrong] " << s << " " << p << ": " << resultSet << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("cbaebabacd", "abc", {0,6});
    test("cbaebabacdcba", "abc", {0,6,10});
    test("abab", "ab", {0,1,2});
    test("abcd", "ef", {});
    test("aaaa", "a", {0,1,2,3});

    return 0;
}
