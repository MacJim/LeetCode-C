/*
 * 316. Remove Duplicate Letters
 * https://leetcode.com/problems/remove-duplicate-letters/
 */

/*
 * Smallest in lexicographical order: compare 2 strings from the first character to the last, where a < b < c < ...
 */

#include <iostream>
//#include <vector>
#include <array>
#include <string>
#include <map>
#include <unordered_map>

//#include "helpers/Operators.hpp"


#pragma mark - 1. Front to back
// WRONG ANSWER.
class Solution1 {
public:
    std::string removeDuplicateLetters(std::string& s) {
        if (s.size() == 1) {
            return s;
        }

        auto indices = std::array<int, 26>();    // 26 letters.
        std::fill(indices.begin(), indices.end(), -1);

        for (int i = 0; i < s.size(); i += 1) {
            const auto& c = s[i];
            const int charID = c - 'a';

            if (indices[charID] == -1) {
                indices[charID] = i;
            } else {
                // This part is wrong.
                for (int j = 0; j < charID; j += 1) {
                    if (indices[j] > indices[charID]) {
                        indices[charID] = i;
                        break;
                    }
                }
            }
        }

        auto characterMap = std::map<int, char>();
        for (int charID = 0; charID < indices.size(); charID += 1) {
            const auto key = indices[charID];
            if (key == -1) {
                continue;
            }

            characterMap[key] = 'a' + charID;
        }

        auto returnValue = std::string();
        for (const auto& [key, value]: characterMap) {
            returnValue += value;
        }

        return returnValue;
    }
};


#pragma mark - 2. Greedy (revisit)
// Source: https://leetcode.ca/2016-10-11-316-Remove-Duplicate-Letters/
/*
 * Traverse the string from start to end:
 *
 * - While logging the smallest character seen
 * - Until we run out of any character
 */
// Runtime: 16 ms, faster than 8.12% of C++ online submissions for Remove Duplicate Letters.
// Memory Usage: 8.6 MB, less than 5.04% of C++ online submissions for Remove Duplicate Letters.
class Solution {
private:
    std::string recursion(std::string& s) {
        if (s.size() <= 1) {
            return s;
        }

        auto occurrences = std::unordered_map<char, int>();
        for (const auto& c: s) {
            occurrences[c] += 1;
        }

        size_t minElementIndex = 0;
        size_t currentIndex = 0;
        for (; currentIndex < s.size(); currentIndex += 1) {
            if (s[currentIndex] < s[minElementIndex]) {
                minElementIndex = currentIndex;
            }

            auto& currentOccurrence = occurrences[s[currentIndex]];

            currentOccurrence -= 1;
            if (currentOccurrence == 0) {
                break;
            }
        }

        auto returnValue = std::string(1, s[minElementIndex]);

        // Remove the minimum character from the remaining string.
        auto trailingString = std::string();
        for (size_t i = minElementIndex + 1; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c != s[minElementIndex]) {
                trailingString.push_back(c);
            }
        }
        const auto trailingValue = recursion(trailingString);
        returnValue += trailingValue;

        return returnValue;
    }

public:
    std::string removeDuplicateLetters(std::string& s) {
        if (s.size() == 1) {
            return s;
        }

//        auto occurrences = std::array<int, 26>();
//        std::fill(occurrences.begin(), occurrences.end(), 0);

        return recursion(s);
    }
};


void test(const std::string& s, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.removeDuplicateLetters(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("a", "a");
    test("bcabc", "abc");
    test("cbacdcbc", "acdb");
    test("cbacdcbcd", "abcd");
    test("bcbcbca", "bca");
    test("cbca", "bca");
    test("cbcbcba", "bca");

    return 0;
}
