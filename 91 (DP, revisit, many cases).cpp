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
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decode Ways.
// Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Decode Ways.
class Solution {
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


int main() {
    auto solutionInstance = Solution();

//    std::cout << solutionInstance.getFakeFibonacciNumber(3) << std::endl;

    std::cout << solutionInstance.numDecodings("12") << std::endl;    // 2
    std::cout << solutionInstance.numDecodings("225") << std::endl;    // 3
    std::cout << solutionInstance.numDecodings("22222") << std::endl;    // 8
    std::cout << solutionInstance.numDecodings("882222") << std::endl;    // 5
    std::cout << solutionInstance.numDecodings("22422") << std::endl;    // 6
    std::cout << solutionInstance.numDecodings("10") << std::endl;    // 1
    std::cout << solutionInstance.numDecodings("0") << std::endl;    // 0
    std::cout << solutionInstance.numDecodings("100") << std::endl;    // 0
    std::cout << solutionInstance.numDecodings("110") << std::endl;    // 1
    std::cout << solutionInstance.numDecodings("101010") << std::endl;    // 1
    std::cout << solutionInstance.numDecodings("17") << std::endl;    // 2

    return 0;
}
