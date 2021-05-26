/*
 * 150. Evaluate Reverse Polish Notation
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"


#pragma mark - 1. Stack
// Runtime: 8 ms, faster than 87.78% of C++ online submissions for Evaluate Reverse Polish Notation.
// Memory Usage: 11.8 MB, less than 87.82% of C++ online submissions for Evaluate Reverse Polish Notation.
class Solution {
public:
    int evalRPN(const std::vector<std::string>& tokens) {
        if (tokens.size() == 1) {
            return std::stoi(tokens[0]);
        }

        auto s = std::stack<int>();
        for (const auto& token: tokens) {
            if (token == "+") {
                auto rhs = s.top();
                s.pop();
                auto lhs = s.top();
                s.pop();

                auto result = lhs + rhs;
                s.push(result);
            } else if (token == "-") {
                auto rhs = s.top();
                s.pop();
                auto lhs = s.top();
                s.pop();

                auto result = lhs - rhs;
                s.push(result);
            } else if (token == "*") {
                auto rhs = s.top();
                s.pop();
                auto lhs = s.top();
                s.pop();

                auto result = lhs * rhs;
                s.push(result);
            } else if (token == "/") {
                auto rhs = s.top();
                s.pop();
                auto lhs = s.top();
                s.pop();

                auto result = lhs / rhs;
                s.push(result);
            } else {
                auto number = std::stoi(token);
                s.push(number);
            }
        }

        return s.top();
    }
};


void test(const std::vector<std::string>& tokens, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.evalRPN(tokens);

    if (result == expectedResult) {
        std::cout << "[Correct] " << tokens << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << tokens << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({"2","1","+","3","*"}, 9);
    test({"4","13","5","/","+"}, 6);
    test({"10","6","9","3","+","-11","*","/","*","17","+","5","+"}, 22);

    return 0;
}
