/*
 * 10. Regular Expression Matching
 * https://leetcode.com/problems/regular-expression-matching/
 */

#include <iostream>
#include <string>
#include <vector>
#include <numeric>    // std::iota


#pragma mark - 1
// Runtime: 12 ms, faster than 51.55% of C++ online submissions for Regular Expression Matching.
// Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Regular Expression Matching.
class Solution1 {
public:
    bool isMatch(std::string s, std::string p) {
        const auto sLen = s.size();
        const auto pLen = p.size();
        if (pLen == 0) {
            return (sLen == 0);
        }

        // 1. Initial match.
        /// There is a position for an empty string.
        auto previousResults = std::vector<bool>(sLen + 1, false);

        int pIndex = pLen - 1;
//        int sIndex = sLen - 1;

        char& pChar = p.at(pIndex);

        switch (pChar) {
            case '*':
                pChar = p.at(pIndex - 1);

                if (pChar == '.') {
                    // This is the "wildcard" case. All values are legal.
                    std::iota(previousResults.begin(), previousResults.end(), true);
                } else {
                    previousResults.back() = true;    // Empty string is always legal with an asterisk.

                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        const char& sChar = s.at(i);
                        if (sChar == pChar) {
                            previousResults.at(i) = true;
                        } else {
                            break;
                        }
                    }
                }

                pIndex -= 2;
                break;

            case '.':
                if (sLen == 0) {
                    return false;
                } else {
                    previousResults.at(sLen - 1) = true;
                    pIndex -= 1;
                }
                break;

            default:    // A single char.
                if ((sLen > 0) && (s.at(sLen - 1) == pChar)) {
                    previousResults.at(sLen - 1) = true;
                    pIndex -= 1;
                } else {
                    // If no initial match was found, return false.
                    return false;
                }
                break;
        }
//        sIndex -= 1;


        // 2. Dynamic Programming.
        /*
         * i: index in s; j: index in p.
         *
         * Sources:
         * - Asterisk: 2 sources:
         *   - (i, j - 1) is true.
         *   - (i + 1, j) is true.
         * - Dot / char: 1 source:
         *   - (i + 1, j + 1) must be true.
         */
        auto currentResults = std::vector<bool>(sLen + 1, false);

        while (pIndex >= 0) {
            char& pChar = p.at(pIndex);

            switch (pChar) {
                case '*':
                    pChar = p.at(pIndex - 1);

                    if (pChar == '.') {
                        // Wildcard scenario.
                        // Find the last `true` index in `previousResults`. From that index, set `currentResults` to `true`.
                        for (int i = sLen; i >= 0; i -= 1) {
                            if (previousResults.at(i)) {
                                for (int j = i; j >= 0; j -= 1) {
                                    currentResults.at(j) = true;
                                }
                                break;
                            }
                        }
                    } else {
                        for (int i = sLen; i >= 0; i -= 1) {
                            // (i, j - 1) is true.
                            if (previousResults.at(i)) {
                                currentResults.at(i) = true;
                            }

                            // (i - 1, j) is true.
                            if ((i < sLen) && (currentResults.at(i + 1))) {
                                const auto& sChar = s.at(i);
                                if (sChar == pChar) {
                                    currentResults.at(i) = true;
                                }
                            }
                        }
                    }


                    pIndex -= 2;
                    break;

                case '.':
                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        if (previousResults.at(i + 1)) {
                            currentResults.at(i) = true;
                        }
                    }

                    pIndex -= 1;
                    break;

                default:
                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        const auto& sChar = s.at(i);

                        if (previousResults.at(i + 1)) {
                            if (sChar == pChar) {
                                currentResults.at(i) = true;
                            }
                        }
                    }
                    pIndex -= 1;
                    break;
            }

            previousResults = std::move(currentResults);
            currentResults = std::vector<bool>(sLen + 1, false);
        }

//        sIndex -= 1;

        return previousResults.front();
    }
};


#pragma mark - 2. Slightly improved 1
// Runtime: 4 ms, faster than 93.76% of C++ online submissions for Regular Expression Matching.
// Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Regular Expression Matching.
class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        const auto sLen = s.size();
        const auto pLen = p.size();
        if (pLen == 0) {
            return (sLen == 0);
        }

        // 1. Initial match.
        /// There is a position for an empty string.
        auto previousResults = std::vector<bool>(sLen + 1, false);

        int pIndex = pLen - 1;
//        int sIndex = sLen - 1;

        char& pChar = p.at(pIndex);

        switch (pChar) {
            case '*':
                pChar = p.at(pIndex - 1);

                if (pChar == '.') {
                    // This is the "wildcard" case. All values are legal.
                    std::iota(previousResults.begin(), previousResults.end(), true);
                } else {
                    previousResults.back() = true;    // Empty string is always legal with an asterisk.

                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        const char& sChar = s.at(i);
                        if (sChar == pChar) {
                            previousResults.at(i) = true;
                        } else {
                            break;
                        }
                    }
                }

                pIndex -= 2;
                break;

            case '.':
                if (sLen == 0) {
                    return false;
                } else {
                    previousResults.at(sLen - 1) = true;
                    pIndex -= 1;
                }
                break;

            default:    // A single char.
                if ((sLen > 0) && (s.at(sLen - 1) == pChar)) {
                    previousResults.at(sLen - 1) = true;
                    pIndex -= 1;
                } else {
                    // If no initial match was found, return false.
                    return false;
                }
                break;
        }
//        sIndex -= 1;


        // 2. Dynamic Programming.
        /*
         * i: index in s; j: index in p.
         *
         * Sources:
         * - Asterisk: 2 sources:
         *   - (i, j - 1) is true.
         *   - (i + 1, j) is true.
         * - Dot / char: 1 source:
         *   - (i + 1, j + 1) must be true.
         */
        std::vector<bool> currentResults;

        while (pIndex >= 0) {
            currentResults = std::vector<bool>(sLen + 1, false);

            char& pChar = p.at(pIndex);

            switch (pChar) {
                case '*':
                    pChar = p.at(pIndex - 1);

                    if (pChar == '.') {
                        // Wildcard scenario.
                        // Find the last `true` index in `previousResults`. From that index, set `currentResults` to `true`.
                        for (int i = sLen; i >= 0; i -= 1) {
                            if (previousResults.at(i)) {
                                for (int j = i; j >= 0; j -= 1) {
                                    currentResults.at(j) = true;
                                }
                                break;
                            }
                        }
                    } else {
                        for (int i = sLen; i >= 0; i -= 1) {
                            // (i, j - 1) is true.
                            if (previousResults.at(i)) {
                                currentResults.at(i) = true;
                            }

                            // (i - 1, j) is true.
                            if ((i < sLen) && (currentResults.at(i + 1))) {
                                const auto& sChar = s.at(i);
                                if (sChar == pChar) {
                                    currentResults.at(i) = true;
                                }
                            }
                        }
                    }


                    pIndex -= 2;
                    break;

                case '.':
                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        if (previousResults.at(i + 1)) {
                            currentResults.at(i) = true;
                        }
                    }

                    pIndex -= 1;
                    break;

                default:
                    for (int i = sLen - 1; i >= 0; i -= 1) {
                        const auto& sChar = s.at(i);

                        if (previousResults.at(i + 1)) {
                            if (sChar == pChar) {
                                currentResults.at(i) = true;
                            }
                        }
                    }
                    pIndex -= 1;
                    break;
            }

            previousResults = std::move(currentResults);
        }

//        sIndex -= 1;

        return previousResults.front();
    }
};


void test(const char* s, const char* p) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.isMatch(s, p);
    std::cout << s << " -> " << p << ": " << result << std::endl;
}

int main() {
    test("aa", "a");    // false
    test("bba", "c*ba*");    // false
    test("aa", "a");    // false
    test("aa", "a*");    // true
    test("aab", "c*a*b");    // true
    test("mississippi", "mis*is*p*.");    // false
    test("ab", ".*");    // true
    test("mississippi", "mis*is*ip*.");    // true

    return 0;
}
