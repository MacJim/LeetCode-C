/*
 * 216. Combination Sum III
 * https://leetcode.com/problems/combination-sum-iii/
 */

#include <iostream>
#include <vector>
//#include <stack>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Recursion, max number first, DFS
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Combination Sum III.
// Memory Usage: 6.4 MB, less than 53.54% of C++ online submissions for Combination Sum III.
class Solution {
private:
    void recursion(std::vector<std::vector<int>>& returnValue, std::vector<int>& currentPrefix, const int numsCount, const int maxNum, const int sum) {
        if (numsCount == 0) {
            if (sum == 0) {
                // Found a solution.
                returnValue.push_back(currentPrefix);
            } else {
                // Not a solution.
                return;
            }
        }

        if (maxNum == 0) {
            return;
        }

        if (numsCount > numsMinSum[numsCount]) {
            // Too many numbers.
            return;
        }

        for (int num = maxNum; num > 0; num -= 1) {
            const auto remainingSum = sum - num;
            if (remainingSum < 0) {
                continue;
            }

            currentPrefix.push_back(num);
            recursion(returnValue, currentPrefix, numsCount - 1, num - 1, remainingSum);
            currentPrefix.pop_back();
        }
    }

private:
    static std::vector<int> numsMinSum;

public:
    std::vector<std::vector<int>> combinationSum3(const int numsCount, const int sum) {
        if (numsCount > numsMinSum[numsCount]) {
            // Too many numbers.
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();    // I should have made `returnValue` a member of the `Solution` class, though.
        auto temp = std::vector<int>();

        recursion(returnValue, temp, numsCount, 9, sum);

        return returnValue;
    }
};

std::vector<int> Solution::numsMinSum = {0, 1, 1 + 2, 3 + 3, 6 + 4, 10 + 5, 15 + 6, 21 + 7, 28 + 8, 36 + 9};


void test(const int numsCount, const int sum, const std::set<std::set<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.combinationSum3(numsCount, sum);

    auto resultSet = std::set<std::set<int>>();
    for (const auto& nums: result) {
        auto numsSet = std::set(nums.begin(), nums.end());
        resultSet.insert(numsSet);
    }

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << numsCount << ", " << sum << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << numsCount << ", " << sum << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(3, 7, {{1,2,4}});
    test(3, 9, {{1,2,6},{1,3,5},{2,3,4}});
    test(4, 1, {});
    test(3, 2, {});
    test(9, 45, {{1,2,3,4,5,6,7,8,9}});

    return 0;
}
