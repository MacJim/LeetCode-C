/*
 * 217. Contains Duplicate
 * https://leetcode.com/problems/contains-duplicate/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort
// Runtime: 20 ms, faster than 87.53% of C++ online submissions for Contains Duplicate.
// Memory Usage: 15.3 MB, less than 94.68% of C++ online submissions for Contains Duplicate.
class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return false;
        }

        std::sort(nums.begin(), nums.end());

        for (size_t i = 1; i < nums.size(); i += 1) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }

        return false;
    }
};


#pragma mark - 2. Unordered map


void test(const std::vector<int>& nums, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.containsDuplicate(numsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,1}, true);
    test({1,2,3,4}, false);
    test({1,1,1,3,3,4,3,2,4,2}, true);

    return 0;
}
