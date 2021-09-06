/*
 * 316. Remove Duplicate Letters
 * https://leetcode.com/problems/remove-duplicate-letters/
 */

/*
 * Smallest in lexicographical order: compare 2 strings from the first character to the last, where a < b < c < ...
 */

#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <string>
#include <map>
#include <unordered_map>

//#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


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
class Solution2 {
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


#pragma mark - 3. Stack-based solution (revisit)
// Source: https://leetcode.com/problems/remove-duplicate-letters/discuss/76769/Java-solution-using-Stack-with-comments
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Remove Duplicate Letters.
// Memory Usage: 6.5 MB, less than 84.31% of C++ online submissions for Remove Duplicate Letters.
class Solution {
public:
    std::string removeDuplicateLetters(std::string& s) {
        if (s.size() == 1) {
            return s;
        }

        auto occurrences = std::array<int, 26>();    // Empty initializer here leads to value-initialization instead of default-initialization.
        for (const auto& c: s) {
            occurrences[c - 'a'] += 1;
        }

        auto visited = std::array<bool, 26>();
        auto currentChars = std::vector<char>();
        currentChars.reserve(26);

        for (const auto& c: s) {
            const auto index = c - 'a';

            occurrences[index] -= 1;

            if (visited[index]) {
                // Do nothing if it's already in `currentChars`.
                continue;
            }
            visited[index] = true;

            // Check the stack top: If it's a larger element that occurs later in the string, pop it.
            while ((!currentChars.empty()) && (c < currentChars.back()) && (occurrences[currentChars.back() - 'a'] != 0)) {
                visited[currentChars.back() - 'a'] = false;

                currentChars.pop_back();
            }

            currentChars.push_back(c);
        }

        auto returnValue = std::string();
        returnValue.reserve(currentChars.size());
        for (const auto& c: currentChars) {
            returnValue.push_back(c);
        }
        return returnValue;
    }
};


void test(const std::string& s, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.removeDuplicateLetters(sCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
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
