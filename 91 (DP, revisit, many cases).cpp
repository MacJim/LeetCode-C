/*
 * 91. Decode Ways
 * https://leetcode.com/problems/decode-ways/
 */

/*
 * a(x) refers to the substring [x: len).
 *
 * - Starts with 0: a(x) = 0
 * - Starts with 1, 2 (and next number is smaller than 7): a(x) = a(x - 1) + a(x - 2). Example: 1, 2, 3, 5, 8, 13, ...
 * - Starts with 3 ~ 9: a(x) = a(x - 1)
 */

#include <iostream>
#include <string>
#include <vector>

#include <assert.h>


#pragma mark - 1. This solution is WRONG because I treated 17 ~ 19 as invalid numbers.
class Solution1 {
public:
    /// 1, 2, 3, 5, ...
    int getFakeFibonacciNumber(int i) {
        static std::vector<int> fibonacciNumbers = std::vector<int>({1, 1, 2});

        auto currentIndex = fibonacciNumbers.size() - 1;
        if (currentIndex < i) {
            for (; currentIndex <= i; currentIndex += 1) {
                fibonacciNumbers.push_back(fibonacciNumbers.at(currentIndex - 1) + fibonacciNumbers.at(currentIndex));
            }
        }

        return fibonacciNumbers.at(i);
    }

public:
    int numDecodings(const std::string& s) {
        int returnValue = 1;
        int currentSmallNumberStreak = 0;

        for (const auto& c: s) {
            if (c == '0') {
                // The previous number must be a small number.
                if (currentSmallNumberStreak > 0) {
                    currentSmallNumberStreak -= 1;

                    returnValue *= getFakeFibonacciNumber(currentSmallNumberStreak);
                    currentSmallNumberStreak = 0;
                } else {
                    // The previous number is a big number. No possible cases.
                    return 0;
                }
            } else if (c <= '2') {
                // This is a small number.
                currentSmallNumberStreak += 1;
            } else {
                // This is a big number.
                if (c <= '6') {
                    currentSmallNumberStreak += 1;
                }

                if (currentSmallNumberStreak > 0) {
                    returnValue *= getFakeFibonacciNumber(currentSmallNumberStreak);
                    currentSmallNumberStreak = 0;
                }
            }
        }

        if (currentSmallNumberStreak > 0) {
            returnValue *= getFakeFibonacciNumber(currentSmallNumberStreak);
        }

        return returnValue;
    }
};


#pragma mark - 2. Log 2 values: Make use of the Fibonacci formula.
// May 2020
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decode Ways.
// Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Decode Ways.
class Solution2 {
public:
    int numDecodings(const std::string& s) {
        const auto len = s.size();

        int previous = 1;

        int previousPrevious = 1;

        // Last character.
        const auto& lastC = s.at(len - 1);
        if (lastC == '0') {
            previous = 0;
        }

        // Previous characters.
        for (int i = (len - 2); i >= 0; i -= 1) {
            const auto& c = s.at(i);
            int current = (c == '0') ? 0 : previous;    // By default, the current value equals the previous value.

            if ((c == '1') || ((c == '2') && (s.at(i + 1) < '7'))) {
                current += previousPrevious;    // Uses the formula that I have found: For 1, 2: a(x) = a(x - 1) + a(x - 2)
            }

            previousPrevious = previous;
            previous = current;
        }

        return previous;
    }
};


#pragma mark - 3. My own solution
// Feb 2021
/*
 * Current value:
 *
 * - 0: previous value must be 1 or 2
 * - 1 ~ 6: + 2 * (2 cases) + (1 case) if previous value is 1 or 2
 * - 7 ~ 9: + 2 * (2 cases) + (1 case) if previous value is 1
 *
 * Example: 2,2,2,2 -> 2,2,2,2,2
 *
 * - 1 case (ends with a 2-digit number):
 *   - 2,2,22
 *   - 22,22
 * - 2 cases (ends with a single-digit number) (equals the result of 2,2,2):
 *   - 2,2,2,2
 *   - 2,22,2
 *   - 22,2,2
 */
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decode Ways.
// Memory Usage: 6 MB, less than 98.59% of C++ online submissions for Decode Ways.
class Solution {
public:
    int numDecodings(const std::string& s) {
        if (s.empty()) {
            return 0;
        }
        if (s[0] == '0') {
            // Invalid.
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }

        /// 2 cases.
        int prevPrev = 1;
        /// 2 cases + 1 case.
        int prev = 1;

        // Index 1.
        if (s[1] == '0') {
            if ((s[0] != '1') && (s[0] != '2')) {
                // Invalid.
                return 0;
            }
        } else if (s[1] <= '6') {
            if ((s[0] == '1') || (s[0] == '2')) {
                prev = 2;
            }
        } else {
            if (s[0] == '1') {
                prev = 2;
            }
        }

        // Upcoming indices.
        for (int i = 2; i < s.size(); i += 1) {
            if (s[i] == '0') {
                if ((s[i - 1] != '1') && (s[i - 1] != '2')) {
                    // Invalid.
                    return 0;
                }
                prev = prevPrev;
                prevPrev = 0;    // Cannot separate 0.
            } else if (s[i] <= '6') {
                if ((s[i - 1] == '1') || (s[i - 1] == '2')) {
                    auto current = prevPrev + prev;    // 2 * (2 cases) + (1 case)
                    prevPrev = prev;
                    prev = current;
                } else {
                    // Interpret the current digit as a single number. Same result as `prev`.
                    prevPrev = prev;
                }
            } else {
                if (s[i - 1] == '1') {
                    auto current = prevPrev + prev;
                    prevPrev = prev;
                    prev = current;
                } else {
                    prevPrev = prev;
                }
            }
        }

        return prev;
    }
};


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.numDecodings(s);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("12", 2);
    test("225", 3);
    test("22222", 8);
    test("882222", 5);
    test("22422", 6);
    test("10", 1);
    test("0", 0);
    test("100", 0);
    test("110", 1);
    test("101010", 1);
    test("17", 2);

//    std::cout << solutionInstance.getFakeFibonacciNumber(3) << std::endl;

    return 0;
}
