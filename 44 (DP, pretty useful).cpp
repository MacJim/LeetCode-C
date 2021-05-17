/*
 * 44. Wildcard Matching
 * https://leetcode.com/problems/wildcard-matching/
 */

#include <iostream>
#include <vector>
#include <string>


#pragma mark - 1. Recursion
// Time Limit Exceeded
class Solution1 {
private:
    bool recursion(const std::string& s, const std::string& p, size_t sStart, size_t pStart) {
        if (pStart == p.size()) {
            if (sStart == s.size()) {
                return true;
            } else {
                // p is empty, while s is not.
                return false;
            }
        }

        if (sStart == s.size()) {
            // An empty s may still match '*'.
            while (pStart < p.size()) {
                if (p[pStart] != '*') {
                    return false;
                }

                pStart += 1;
            }

            return true;
        }

        if ((s[sStart] == p[pStart]) || (p[pStart] == '?')) {
            return recursion(s, p, sStart + 1, pStart + 1);
        } else if (p[pStart] == '*') {
            // Match 0 or any positive amount of characters.
            for (size_t nextSStart = sStart; nextSStart <= s.size(); nextSStart += 1) {    // Note that the case `nextSStart == p.size()` is handled by the next layer of recursion.
                if (recursion(s, p, nextSStart, pStart + 1)) {
                    return true;
                }
            }

            return false;
        } else {
            return false;
        }
    }

public:
    bool isMatch(std::string& s, std::string& p) {
        return recursion(s, p, 0, 0);
    }
};


#pragma mark - 2. DP
// Runtime: 36 ms, faster than 60.92% of C++ online submissions for Wildcard Matching.
// Memory Usage: 6.7 MB, less than 81.48% of C++ online submissions for Wildcard Matching.
class Solution {
public:
    bool isMatch(std::string& s, std::string& p) {
        if (s.empty()) {
            // An empty string only matches '*'.
            for (const auto& currentPattern: p) {
                if (currentPattern != '*') {
                    return false;
                }
            }

            return true;
        }

        if (p.empty()) {
            // The pattern is empty, while the string is not.
            return false;
        }

        // Seems achievable using a single DP array (instead of 2 here).
        /*
         * One more index than `s`: index 0 means "no characters".
         */
        auto previous = std::vector<bool>(s.size() + 1, false);
        auto current = std::vector<bool>(s.size() + 1, false);

        // First pattern character.
        if (p[0] == '*') {
            std::fill(previous.begin(), previous.end(), true);
        } else if ((p[0] == '?') || (p[0] == s[0])) {
            previous[1] = true;
        } else {
            // The first pattern character doesn't match.
            return false;
        }

        // Upcoming pattern characters.
        for (size_t i = 1; i < p.size(); i += 1) {
            const auto& currentP = p[i];

            if (currentP == '*') {
                // Find the first `true` in `previous`.
                size_t firstTrueIndex = 0;
                while ((firstTrueIndex < previous.size()) && (!previous[firstTrueIndex])) {
                    firstTrueIndex += 1;
                }
                if (firstTrueIndex == previous.size()) {
                    // Everything in `previous` is `false`.
                    return false;
                }

                // Fill everything from the first previous true to true.
                for (size_t j = firstTrueIndex; j < current.size(); j += 1) {
                    current[j] = true;
                }
            } else if (currentP == '?') {
                // Shift `true` positions in `previous` by 1.
                for (size_t j = 1; j < previous.size(); j += 1) {
                    if (previous[j - 1]) {
                        current[j] = true;
                    }
                }
            } else {
                // Compare, and if they equal: similar to the '?' case.
                for (size_t j = 1; j < previous.size(); j += 1) {
                    if (previous[j - 1] && (s[j - 1] == currentP)) {
                        current[j] = true;
                    }
                }
            }

            std::swap(previous, current);
            std::fill(current.begin(), current.end(), false);
        }

        return previous.back();
    }
};


void test(const std::string& s, const std::string& pattern, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto pCopy = pattern;
    auto result = solutionInstance.isMatch(sCopy, pCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ", " << pattern << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ", " << pattern << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("", "***", true);
    test("", "****", true);
    test("", "**?*", false);

    test("aa", "*", true);
    test("aa", "a", false);
    test("cb", "?a", false);
    test("adceb", "*a*b", true);
    test("acdcb", "a*c?b", false);
    test("abc", "abc", true);
    test("abc", "**", true);
    test("abbcc", "*b*bc?", true);
    test("abbcc", "*b*bc", false);

    test("bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba", false);

    return 0;
}
