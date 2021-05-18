/*
 * 77. Combinations
 * https://leetcode.com/problems/combinations/
 */

#include <iostream>
#include <vector>
#include <set>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// Runtime: 20 ms, faster than 81.85% of C++ online submissions for Combinations.
// Memory Usage: 13.8 MB, less than 40.41% of C++ online submissions for Combinations.
class Solution {
private:
    void recursion(std::vector<std::vector<int>>& returnValue, const std::vector<int>& previousPrefix, int maxNum, int k) {
        if (k == 0) {
            returnValue.push_back(previousPrefix);
            return;
        }

        auto currentPrefix = previousPrefix;

        for (int currentNum = maxNum; currentNum >= k; currentNum -= 1) {
            currentPrefix.push_back(currentNum);
            recursion(returnValue, currentPrefix, currentNum - 1, k - 1);
            currentPrefix.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combine(int n, int k) {
        auto returnValue = std::vector<std::vector<int>>();

        recursion(returnValue, {}, n, k);

        return returnValue;
    }
};


void test(const int n, const int k, const std::set<std::set<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.combine(n, k);
    auto resultSet = std::set<std::set<int>>();
    for (const auto& aResult: result) {
        resultSet.insert(std::set<int>(aResult.begin(), aResult.end()));
    }

    if (resultSet == expectedResult) {
        std::cout << "[Correct] " << n << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 1, {{1}});
    test(4, 2, {{2,4},{3,4},{2,3},{1,2},{1,3},{1,4}});

    return 0;
}
