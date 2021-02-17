/*
 * 394. Decode String
 * https://leetcode.com/problems/decode-string/
 */

#include <iostream>
#include <string>
#include <stack>

//#include "helpers/Operators.hpp"


#pragma mark - 1. Unfinished
class Solution1 {
private:
    inline bool isNum(const char& c) {
        return ((c >= '0') && (c <= '9'));
    }

public:
    std::string decodeString(std::string& s) {
        if (s.empty()) {
            return "";
        }

        auto returnValue = std::string();

        auto currentStr = std::string();
        auto strs = std::stack<std::string>();

        int currentCount = 0;
        auto counts = std::stack<int>();

        for (const auto& c: s) {
            if (isNum(c)) {
                const int count = c - '0';
                currentCount *= 10;
                currentCount += count;
            } else if (c == '[') {
                counts.push(currentCount);
                currentCount = 0;
            } else if (c == ']') {
                const int& count = counts.top();

                auto repeatedStr = std::string();
                for (int i = 0; i < count; i += 1) {
                    repeatedStr += currentStr;
                }

                if (counts.size() == 1) {
                    // This is the closing bracket.
                    while (!strs.empty()) {
                        repeatedStr = strs.top() + repeatedStr;
                        strs.pop();
                    }

                    returnValue += repeatedStr;
                } else {
                    // This is a "sub" bracket.
                    strs.push(std::move(repeatedStr));
                }

                currentStr.clear();
                counts.pop();
            } else {
                currentStr += c;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Recursion
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decode String.
// Memory Usage: 6.5 MB, less than 71.05% of C++ online submissions for Decode String.
class Solution {
private:
    inline bool isNum(const char& c) {
        return ((c >= '0') && (c <= '9'));
    }

    /// Decode to `]` and returns the index of `]`.
    std::pair<std::string, size_t> decodeSubstring(const std::string& s, size_t start) {
        auto returnValue = std::string();

        int currentCount = 0;

        for (size_t i = start; i < s.size(); i += 1) {
            if (isNum(s[i])) {
                currentCount *= 10;
                currentCount += (s[i] - '0');
            } else if (s[i] == '[') {
                const auto subResult = decodeSubstring(s, i + 1);

                for (int j = 0; j < currentCount; j += 1) {
                    returnValue += subResult.first;
                }
                i = subResult.second;

                currentCount = 0;
            } else if (s[i] == ']') {
                // Reachable only in sub-strings (`start` is not 0) (since there's always a closing bracket).
                return std::make_pair(std::move(returnValue), i);
            } else {
                returnValue += s[i];
            }
        }

        // Reachable only if `start` is 0 (since there's no closing bracket).
        return std::make_pair(returnValue, 0);
    }

public:
    std::string decodeString(std::string& s) {
        if (s.empty()) {
            return "";
        }

        const auto returnValue = decodeSubstring(s, 0);

        return returnValue.first;
    }
};


void test(const std::string& s, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.decodeString(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3[a]2[bc]", "aaabcbc");
    test("3[a2[c]]", "accaccacc");
    test("3[a2[c2[de]]]", "acdedecdedeacdedecdedeacdedecdede");
    test("2[abc]3[cd]ef", "abcabccdcdcdef");
    test("abc3[cd]xyz", "abccdcdcdxyz");

    return 0;
}
