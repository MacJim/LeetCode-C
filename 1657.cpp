/*
 * 1657. Determine if Two Strings Are Close
 * https://leetcode.com/problems/determine-if-two-strings-are-close/
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <array>
#include <bitset>

// #include "helpers/Operators.hpp"


#pragma mark - 1. Character count statistics
// Runtime: 168 ms, faster than 33.66% of C++ online submissions for Determine if Two Strings Are Close.
// Memory Usage: 45 MB, less than 5.34% of C++ online submissions for Determine if Two Strings Are Close.
class Solution1 {
public:
    bool closeStrings(std::string& word1, std::string& word2) {
        if (word1.size() != word2.size()) {
            return false;
        }

        auto chars1 = std::unordered_set<char>(word1.begin(), word1.end());
        auto chars2 = std::unordered_set<char>(word2.begin(), word2.end());
        if (chars1 != chars2) {
            return false;
        }

        auto charCount1 = std::unordered_map<char, int>();
        auto charCount2 = std::unordered_map<char, int>();
        for (const auto& c1: word1) {
            charCount1[c1] += 1;
        }
        for (const auto& c2: word2) {
            charCount2[c2] += 1;
        }

        auto charCountVec1 = std::vector<int>();
        auto charCountVec2 = std::vector<int>();
        for (const auto& [_, count1]: charCount1) {
            charCountVec1.push_back(count1);
        }
        for (const auto& [_, count2]: charCount2) {
            charCountVec2.push_back(count2);
        }
        std::sort(charCountVec1.begin(), charCountVec1.end());
        std::sort(charCountVec2.begin(), charCountVec2.end());
        if (charCountVec1 != charCountVec2) {
            return false;
        }

        return true;
    }
};


#pragma mark - 2. Improved 1: Use array and bitset instead of sets
// We know that we only have 26 possible characters.
// Runtime: 72 ms, faster than 94.44% of C++ online submissions for Determine if Two Strings Are Close.
// Memory Usage: 16.8 MB, less than 100.00% of C++ online submissions for Determine if Two Strings Are Close.
class Solution {
public:
    bool closeStrings(std::string& word1, std::string& word2) {
        if (word1.size() != word2.size()) {
            return false;
        }

        auto charOccurrence1 = std::bitset<26>();
        auto charOccurrence2 = std::bitset<26>();

        auto charCount1 = std::array<int, 26>();
        auto charCount2 = std::array<int, 26>();

        for (const auto& c1: word1) {
            size_t i = c1 - 'a';
            charOccurrence1[i] = 1;
            charCount1[i] += 1;
        }
        for (const auto& c2: word2) {
            size_t i = c2 - 'a';
            charOccurrence2[i] = 1;
            charCount2[i] += 1;
        }

        if (charOccurrence1 != charOccurrence2) {
            return false;
        }

        std::sort(charCount1.begin(), charCount1.end());
        std::sort(charCount2.begin(), charCount2.end());
        if (charCount1 != charCount2) {
            return false;
        }

        return true;
    }
};


void test(const std::string& word1, const std::string& word2, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto wordCopy1 = word1;
    auto wordCopy2 = word2;

    auto result = solutionInstance.closeStrings(wordCopy1, wordCopy2);

    if (result == expectedResult) {
        std::cout << "[Correct] " << wordCopy1 << " " << wordCopy2 << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << wordCopy1 << " " << wordCopy2 << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("ab", "bc", false);
    test("abc", "bca", true);
    test("a", "aa", false);
    test("cabbba", "abbccc", true);
    test("cabbba", "aabbss", false);

    return 0;
}
