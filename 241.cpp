/*
 * 241. Different Ways to Add Parentheses
 * https://leetcode.com/problems/different-ways-to-add-parentheses/
 */

/*
 * - Don't need to support division
 * - Numbers do exceed 9
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP (unfinished)
class Solution1 {
public:
    std::vector<int> diffWaysToCompute(std::string& expression) {
        if (expression.size() == 1) {
            return {static_cast<int>(expression[0] - '0')};
        }

        expression = "+" + expression;

        /**
         * Key: startIndex + endIndex * 100 (indices are always smaller than 20)
         */
        auto dp = std::unordered_map<size_t, std::vector<int>>();

        // Length 4.
        for (size_t start = 0; start < (expression.size() - 2); start += 2) {
            const size_t end = start + 3;

            const auto index = start + end * 100;

            int currentResult = 0;

            dp[index] = {};
        }

        return {};
    }
};


#pragma mark - 2. Recursion
// Wrong Answer because it doesn't take multi-digit numbers into account.
class Solution2 {
private:
    std::vector<int> recursion(const std::string& expression, size_t startIndex, size_t endIndex) {
        if (startIndex == endIndex) {
            // A single digit.
            return {expression[startIndex] - '0'};
        }

        auto returnValue = std::vector<int>();

        for (size_t midIndex = startIndex + 1; midIndex < endIndex; midIndex += 2) {    // `midIndex` always point to an operator.
//            const char& op = expression[midIndex];
            std::function<int(const int&, const int&)> op;
//            auto op = [] (const int& lhs, const int& rhs) {
//                return lhs + rhs;
//            };

            switch (expression[midIndex]) {
                case '+':
                    op = [] (const int& lhs, const int& rhs) {
                        return lhs + rhs;
                    };
                    break;

                case '-':
                    op = [] (const int& lhs, const int& rhs) {
                        return lhs - rhs;
                    };
                    break;

                default:
                    op = [] (const int& lhs, const int& rhs) {
                        return lhs * rhs;
                    };
            }

            const auto leftResults = recursion(expression, startIndex, midIndex - 1);
            const auto rightResults = recursion(expression, midIndex + 1, endIndex);

            for (const auto& leftResult: leftResults) {
                for (const auto& rightResult: rightResults) {
                    const int currentResult = op(leftResult, rightResult);
                    returnValue.push_back(currentResult);
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<int> diffWaysToCompute(const std::string& expression) {
        if (expression.size() == 1) {
            return {static_cast<int>(expression[0] - '0')};
        }

        auto returnValue = recursion(expression, 0, expression.size() - 1);

        return returnValue;
    }
};


#pragma mark - 3. Fixed 2
// Runtime: 4 ms, faster than 68.53% of C++ online submissions for Different Ways to Add Parentheses.
// Memory Usage: 11 MB, less than 53.21% of C++ online submissions for Different Ways to Add Parentheses.
class Solution {
private:
    std::vector<int> recursion(const std::vector<int>& numbers, size_t startIndex, size_t endIndex, const std::vector<std::function<int(const int&, const int&)>>& ops) {
        if (startIndex == endIndex) {
            // A single number.
            return {numbers[startIndex]};
        }

        auto returnValue = std::vector<int>();

        for (size_t opIndex = startIndex; opIndex < endIndex; opIndex += 1) {
            const auto& op = ops[opIndex];

            const auto leftResults = recursion(numbers, startIndex, opIndex, ops);
            const auto rightResults = recursion(numbers, opIndex + 1, endIndex, ops);

            for (const auto& leftResult: leftResults) {
                for (const auto& rightResult: rightResults) {
                    const int currentResult = op(leftResult, rightResult);
                    returnValue.push_back(currentResult);
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<int> diffWaysToCompute(const std::string& expression) {
        /*
         * numbers[i] and numbers[i + 1] use op[i].
         */
        auto numbers = std::vector<int>();
        auto ops = std::vector<std::function<int(const int&, const int&)>>();

        int currentNumber = expression[0] - '0';
        for (size_t i = 1; i < expression.size(); i += 1) {
            const auto& c = expression[i];

            switch (c) {
                case '+':
                    numbers.push_back(currentNumber);
                    currentNumber = 0;
                    ops.emplace_back([] (const int& lhs, const int& rhs) {
                        return lhs + rhs;
                    });
                    break;

                case '-':
                    numbers.push_back(currentNumber);
                    currentNumber = 0;
                    ops.emplace_back([] (const int& lhs, const int& rhs) {
                        return lhs - rhs;
                    });
                    break;

                case '*':
                    numbers.push_back(currentNumber);
                    currentNumber = 0;
                    ops.emplace_back([] (const int& lhs, const int& rhs) {
                        return lhs * rhs;
                    });
                    break;

                default:
                    currentNumber *= 10;
                    currentNumber += (c - '0');
            }
        }
        numbers.push_back(currentNumber);    // `currentNumber` may be 0 (valid).

        if (ops.empty()) {
            // No operators.
            return numbers;
        }

        auto returnValue = recursion(numbers, 0, numbers.size() - 1, ops);

        return returnValue;
    }
};


#pragma mark - 4. Optimize 3 by using DP or a hash table to save the sub-results


void test(const std::string& expression, std::vector<int> expectedResult) {
    static auto solutionInstance = Solution();

    auto expressionCopy = expression;
    auto result = solutionInstance.diffWaysToCompute(expressionCopy);

    auto sortedResult = result;
    std::sort(sortedResult.begin(), sortedResult.end());
    std::sort(expectedResult.begin(), expectedResult.end());

    if (sortedResult == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << expression << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << expression << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("0", {0});
    test("2-1-1", {0,2});
    test("2*3-4*5", {-34,-14,-10,-10,10});
    test("11", {11});
    test("11*11", {121});

    return 0;
}
