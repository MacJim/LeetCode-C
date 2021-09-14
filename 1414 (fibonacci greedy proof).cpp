/*
 * 1414. Find the Minimum Number of Fibonacci Numbers Whose Sum Is K
 * https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Pre-generate all Fibonacci numbers, and select the largest Fibonacci number (see proof)
/*
 * Why does choosing the largest Fibonacci number work?
 *
 * 1. No adjacent numbers
 * fib[i + 2] = fib[i] + fib[i + 1]
 * Thus, we don't use adjacent Fibonacci numbers.
 *
 * 2. No duplicate numbers
 * fib[i] * 2 = fib[i - 2] + fib[i + 1]
 * Thus, instead of choosing the same number twice, we can always choose a bigger and a smaller number.
 * Thus, even if we can use the same number for multiple times, we don't.
 *
 * 3. Sum rule
 * We know that we cannot use adjacent/duplicate numbers.
 * Thus, the biggest sum we can reach is:
 *
 * - Even numbers: fib[0] + fib[2] + ... + fib[2n] = fib[2n + 1]
 * - Odd numbers: fib[1] + fib[3] + ... + fib[2n - 1] = fib[2n] - 1
 *
 * If `k >= fib[2n + 1]` or `k >= fib[2n] - 1`, the sum of the smaller numbers won't be as large.
 */
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
// Memory Usage: 6 MB, less than 76.65% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
class Solution1 {
private:
    static std::vector<int> fibonacciNumbers;

public:
    int findMinFibonacciNumbers(int k) {
        if (k <= 3) {
            return 1;
        }

        int returnValue = 0;

        while (fibonacciNumbers.back() < k) {
            const int nextFibNum = fibonacciNumbers.back() + fibonacciNumbers.at(fibonacciNumbers.size() - 2);
            fibonacciNumbers.push_back(nextFibNum);
        }

        while (k > 0) {
            // Search the first fib num that's smaller than k.
            for (int i = (fibonacciNumbers.size() - 1); i > 0; i -= 1) {    // Use `i > 0` because numbers 1 and 1 equal.
                const int& currentNum = fibonacciNumbers[i];
                if (currentNum <= k) {
                    k -= currentNum;
                    returnValue += 1;
                }
            }
        }

        return returnValue;
    }
};

std::vector<int> Solution1::fibonacciNumbers = {1, 1, 2, 3, 5, 8, 13};


#pragma mark - 2. Optimize 1 with binary search
/*
 * Maybe we don't have enough numbers to utilize binary search.
 */
// Runtime: 13 ms, faster than 5.02% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
// Memory Usage: 6.1 MB, less than 76.65% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
class Solution {
private:
    static std::vector<int> fibonacciNumbers;

public:
    int findMinFibonacciNumbers(int k) {
        if (k <= 3) {
            return 1;
        }

        int returnValue = 0;

        while (fibonacciNumbers.back() < k) {
            const int nextFibNum = fibonacciNumbers.back() + fibonacciNumbers.at(fibonacciNumbers.size() - 2);
            fibonacciNumbers.push_back(nextFibNum);
        }

        while (k > 0) {
            // Plus 1 first to return when `midNum == k`.
            returnValue += 1;

            // Search the first fib num that's smaller than k.
            int left = 0;
            int right = fibonacciNumbers.size();
            while (left < right) {    // Terminates when `left == right`.
                int mid = (left + right) / 2;
                const int& midNum = fibonacciNumbers[mid];

                if (midNum == k) {
                    return returnValue;
                } else if (midNum < k) {
                    left = mid + 1;    // Go past the wanted value.
                } else {
                    right = mid;
                }
            }

            left -= 1;    // Go back.
            k -= fibonacciNumbers[left];
        }

        return returnValue;
    }
};

std::vector<int> Solution::fibonacciNumbers = {1, 1, 2, 3, 5, 8, 13};


void test(const int k, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findMinFibonacciNumbers(k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << k << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(7, 2);
    test(8, 1);
    test(9, 2);
    test(10, 2);
    test(11, 2);
    test(12, 3);
    test(13, 1);
    test(14, 2);
    test(15, 2);
    test(16, 2);
    test(17, 3);
    test(18, 2);
    test(19, 3);
    test(20, 3);
    test(21, 1);
    test(22, 2);

    return 0;
}
