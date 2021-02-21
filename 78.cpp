/*
 * 78. Subsets
 * https://leetcode.com/problems/subsets/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Subsets.
// Memory Usage: 10.8 MB, less than 20.87% of C++ online submissions for Subsets.
class Solution {
private:
    void getSubSetsRecursively(std::vector<int>& nums, int i, std::vector<std::vector<int>>& returnValue, std::vector<int>& currentResult) {
        if (i >= nums.size()) {
            returnValue.push_back(currentResult);
            return;
        }

        // Without current number.
        getSubSetsRecursively(nums, i + 1, returnValue, currentResult);

        // With current number.
        currentResult.push_back(nums[i]);
        getSubSetsRecursively(nums, i + 1, returnValue, currentResult);
        currentResult.pop_back();
    }

public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        if (nums.empty()) {
            return {};
        } else if (nums.size() == 1) {
            return {{}, nums};
        }

        auto returnValue = std::vector<std::vector<int>>();
        auto currentResult = std::vector<int>();

        getSubSetsRecursively(nums, 0, returnValue, currentResult);

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.subsets(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3}, {{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3}});
    test({0}, {{}, {0}});

    return 0;
}
