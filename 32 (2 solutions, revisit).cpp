/*
 * 32. Longest Valid Parentheses
 * https://leetcode.com/problems/longest-valid-parentheses/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

#include "helpers/Operators.hpp"


#pragma mark - 1. Log sum to hash table
// WRONG ANSWER because the ")(" case is also considered valid.
class Solution1 {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        int bracketsDelta = 0;
        auto firstOccurrences = std::unordered_map<int, int>({{0, -1}});
        for (int i = 0; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c == '(') {
                bracketsDelta -= 1;
            } else {
                bracketsDelta += 1;
            }

            auto it = firstOccurrences.find(bracketsDelta);
            if (it == firstOccurrences.end()) {
                firstOccurrences[bracketsDelta] = i;
            } else {
                // Found.
                returnValue = std::max(returnValue, i - it->second);
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Tries to fix 1
// We must have ( first. So if `bracketsDelta >= 0`, we don't add to it any more.
// WRONG ANSWER because if we have a lot of leading (s, the workaround still doesn't work with ")(": check the "(((()(()" test case.
class Solution2 {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        int bracketsDelta = 0;
        auto firstOccurrences = std::unordered_map<int, int>({{0, -1}});
        for (int i = 0; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c == '(') {
                bracketsDelta -= 1;
            } else {
                if (bracketsDelta >= 0) {
                    // Too many right brackets. Reset.
                    firstOccurrences.clear();
                    bracketsDelta = 0;
                } else {
                    bracketsDelta += 1;
                }
            }

            auto it = firstOccurrences.find(bracketsDelta);
            if (it == firstOccurrences.end()) {
                firstOccurrences[bracketsDelta] = i;
            } else {
                // Found.
                returnValue = std::max(returnValue, i - it->second);
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Tries to fix 1
// We only log to `firstOccurrences` if we encounter (.
// Still cannot handle the "(((()(()" test case.
class Solution3 {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        int bracketsDelta = 0;
        auto firstOccurrences = std::unordered_map<int, int>({{0, -1}});
        for (int i = 0; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c == '(') {
                bracketsDelta -= 1;

                auto it = firstOccurrences.find(bracketsDelta);
                // Log only at left brackets.
                if (it == firstOccurrences.end()) {
                    firstOccurrences[bracketsDelta] = i;
                }
            } else {
                bracketsDelta += 1;

                auto it = firstOccurrences.find(bracketsDelta);
                // Save only at right brackets.
                if (it != firstOccurrences.end()) {
                    returnValue = std::max(returnValue, i - it->second);
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 4. Verifies 1's results using a stack
/*
 * Note that `firstOccurrences` only stores a single index for each element.
 * The initial {0, -1} index in particular will cause a lot of problems.
 * So it's crucial to reset this hash table we we encounter excessive ')'s.
 */
// WRONG ANSWER, doesn't work with "()((())()".
class Solution4 {
private:
    inline bool verifySubString(const std::string& s, int start, int end) {
//        if (start == end) {
//            return false;
//        }

        auto leftCount = 0;
        for (int i = start + 1; i <= end; i += 1) {
            if (s[i] == '(') {
                leftCount += 1;
            } else {
                if (leftCount == 0) {
                    return false;
                } else {
                    leftCount -= 1;
                }
            }
        }

        return true;
    }

public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        int bracketsDelta = 0;
        auto firstOccurrences = std::unordered_map<int, int>({{0, -1}});
        for (int i = 0; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c == '(') {
                bracketsDelta -= 1;
            } else {
                if (bracketsDelta >= 0) {
                    // Too many right brackets. Reset.
                    firstOccurrences.clear();
                    bracketsDelta = 0;
                } else {
                    bracketsDelta += 1;
                }
            }

            auto it = firstOccurrences.find(bracketsDelta);
            if (it == firstOccurrences.end()) {
                firstOccurrences[bracketsDelta] = i;
            } else {
                // Found.
                const auto currentLength = i - it->second;
                if (currentLength > returnValue) {
                    if (verifySubString(s, it->second, i)) {
                        returnValue = currentLength;
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 5. DP, outer parentheses + combine intervals
// Time Limit Exceeded
class Solution5 {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int returnValue = 0;

        auto dp = std::vector<std::vector<bool>>(s.size(), std::vector<bool>(s.size(), false));

        // Length 2.
        for (size_t i = 0; i < (s.size() - 1); i += 1) {
            if ((s[i] == '(') && (s[i + 1] == ')')) {
                dp[i][i + 1] = true;
                returnValue = 2;
            }
        }

        if (returnValue == 0) {
            // The entire string is invalid.
            return 0;
        }

        // Longer lengths.
        for (int len = 4; len <= s.size(); len += 2) {
            for (int i1 = 0; i1 < (s.size() - len + 1); i1 += 1) {
                const int i2 = i1 + len - 1;

                if (dp[i1 + 1][i2 - 1] && (s[i1] == '(') && (s[i2] == ')')) {
                    // Situation 1: outer parentheses.
                    dp[i1][i2] = true;
                    returnValue = len;
                } else {
                    // Situation 2: combine 2 intervals.
                    for (int mid = i1 + 2; mid < i2; mid += 2) {
                        if (dp[i1][mid - 1] && dp[mid][i2]) {
                            dp[i1][i2] = true;
                            returnValue = len;
                            break;
                        }
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 6. Official DP solution (revisit)
// Runtime: 4 ms, faster than 80.79% of C++ online submissions for Longest Valid Parentheses.
// Memory Usage: 7.2 MB, less than 49.75% of C++ online submissions for Longest Valid Parentheses.
class Solution6 {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        auto dp = std::vector<int>(s.size(), 0);

//        int returnValue = 0;

        // First 2 elements.
        if ((s[0] == '(') && (s[1] == ')')) {
            dp[1] = 2;
//            returnValue = 2;
        }

        // Upcoming elements.
        for (int i = 2; i < s.size(); i += 1) {
            const auto& c = s[i];
            if (c == '(') {
                // Left brackets are invalid terminations.
                continue;
            }

            if (s[i - 1] == '(') {
                // Previous: (, current: )
                dp[i] = dp[i - 2] + 2;
            } else {
                // Previous: ), current: )
                // Find the assumed earlier (
                const auto& previousLen = dp[i - 1];
                if (previousLen > 0) {
                    const int assumedLeftBracketLocation = i - previousLen - 1;
                    if ((assumedLeftBracketLocation >= 0) && (s[assumedLeftBracketLocation] == '(')) {
                        // Found an outer brackets pair.
                        dp[i] = dp[i - 1] + 2;

                        // There may be an earlier string that's connected to the current string.
                        const int previousConnectedStringLengthIndex = i - previousLen - 2;
                        if (previousConnectedStringLengthIndex >= 0) {
                            dp[i] += dp[previousConnectedStringLengthIndex];
                        }
                    }
                }
            }
        }

        return *std::max_element(dp.begin(), dp.end());
    }
};


#pragma mark - 7. Official solution, fixes 2 using a forward and a backward pass (revisit)
/*
 * Doing a forward pass and a backward pass allows us to ignore excessive leading/trailing brackets.
 */
// Runtime: 4 ms, faster than 80.79% of C++ online submissions for Longest Valid Parentheses.
// Memory Usage: 6.6 MB, less than 98.42% of C++ online submissions for Longest Valid Parentheses.
class Solution {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() < 2) {
            return 0;
        }

        int halfLength = 0;

        int leftBrackets = 0;
        int rightBrackets = 0;

        // Forward pass.
        for (auto it = s.begin(); it < s.end(); it += 1) {
            if (*it == '(') {
                leftBrackets += 1;
            } else {
                rightBrackets += 1;
            }

            if (rightBrackets > leftBrackets) {
                // Reset.
                leftBrackets = 0;
                rightBrackets = 0;
            } else if (rightBrackets == leftBrackets) {
                // Set return value.
                halfLength = std::max(halfLength, rightBrackets);
            }
        }

        // Backward pass.
        leftBrackets = 0;
        rightBrackets = 0;
        for (auto it = s.rbegin(); it < s.rend(); it += 1) {
            if (*it == '(') {
                leftBrackets += 1;
            } else {
                rightBrackets += 1;
            }

            // Note that the comparison is reversed.
            if (leftBrackets > rightBrackets) {
                // Reset.
                leftBrackets = 0;
                rightBrackets = 0;
            } else if (leftBrackets == rightBrackets) {
                // Set return value.
                halfLength = std::max(halfLength, leftBrackets);
            }
        }

        return halfLength * 2;
    }
};


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.longestValidParentheses(s);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(")(((((()())()()))()(()))(", 22);
    test(")()())", 4);
    test("()((())()", 6);

    test("(((()(()", 2);
    test("((((())(()", 4);

    test(")(", 0);
    test("(", 0);
    test("(()", 2);
    test("", 0);
    test("(()()()())", 10);

    test("((((((", 0);
    test("))))))", 0);
    test("))((((((", 0);

    test("())()()(())((()(()()(((()))((((())((()(())()())(()((((()))()(()))(())()(())(()(((((())((((((()())())(()(()((())()))(()))))))()(()))((((())()()()))()()()(((()(()())(()()(()(()()(((()))))))()()))())())((()()))))))((()))(((()((())()(()()))((())))()()())))))))()))))(()))))()))()))()((())))((()))(()))))))(((()))))))))()(()()()(())((())()))()()(())))()()))(()())()))(((()())()))((())((((()))(()(()(()()()(((())()(((((()))((()(((((())(()()))((((((((()(()(()(()(())))(())(()())())(()((((()(())((()(())))(())))()(((((()(()()(())))))))())(())(())(()()(((())))((()))(((((()))))())))()((()))()))))())))))((())(((((()()))((((())))(((()(()(())())(((()(()(()()()())))())()))((()((())())()()()(((())(((((()((((((()((()())))((((())((()(((((((()(()((()()()(()(()())(()(()()((((())))()(((()())))(()()))()(()()()()(((((())(()))))((()))())))()((((((()))())))()(()))(())))((((()())(((((()()())(((((())(()())(()))))()(()()))()))))))())))(((())(()(()()))(()))()(((())))())((((()(((()))))))()(()(()))()()(()()))))))))((()))))))(())((()((()))()))((((((()())))))(()((())((((()))))(()(()()()()(()))()()(()(()))(()()(((((((()())(())(()())((())())()(()())((())()())())(()())))())))(())())())(())((()())(((()()))()))()()))()(()(())((((((((())))()((())((()((((((((((()))))(()(((((())(()(()())())))((())())))))()))(()((()()))((()((())()()()((()(())())((())())(()()(((())))))())()()(()))()())(()(()((())))((((()()(())))())(())(()(()(())())())(()()())()(())())))(()()(((())))((()()(((())()()(()())((((()()(()())(()((((()(()()(()(()(((()((()())(()()))(()((((()(((((()))))()()))(((()((((((()(()()()()())()))(()(())))))((()(((()())())))(((()()))(()(()(((((((()()))(()(())))())()(())())(())(()))(())(()))()()(()()())))))()))()((())(((()((((((((())()()))())))((()())(", 310);

    return 0;
}
