/*
 * 17. Letter Combinations of a Phone Number
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 */

#include <iostream>
#include <vector>
#include <string>


// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Combinations of a Phone Number.
// Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Letter Combinations of a Phone Number.
class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        const auto len = digits.size();
        if (len == 0) {
            return {};
        }

        const static std::vector<std::string> digitChars = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        // const static std::string digit2Chars = "abc";
        // const static std::string digit3Chars = "def";
        // const static std::string digit4Chars = "ghi";
        // const static std::string digit5Chars = "jkl";
        // const static std::string digit6Chars = "mno";
        // const static std::string digit7Chars = "pqrs";
        // const static std::string digit8Chars = "tuv";
        // const static std::string digit9Chars = "wxyz";

        auto returnValue = std::vector<std::string>();

        for (const auto& num: digits) {
            const size_t i = num - '2';    // 0 ~ 7, meaning 2 ~ 9.
            
            // The return value has not been initialized yet.
            if (returnValue.empty()) {
                for (const auto& c: digitChars.at(i)) {
                    auto s = std::string(1, c);
                    returnValue.push_back(std::move(s));
                }
                continue;
            }

            auto newReturnValue = std::vector<std::string>();

            for (const auto& c: digitChars.at(i)) {
                auto returnValueCopy = returnValue;
                for (auto& str: returnValueCopy) {
                    str += c;
                }

                newReturnValue.insert(newReturnValue.end(), returnValueCopy.begin(), returnValueCopy.end());
            }

            returnValue = std::move(newReturnValue);
        }

        return returnValue;
    }
};

int main() {
    auto solutionInstance = Solution();

    auto result1 = solutionInstance.letterCombinations("23");
    for (const auto& str: result1) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
