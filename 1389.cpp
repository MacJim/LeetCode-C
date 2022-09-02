/*
 * 1389. Create Target Array in the Given Order
 * https://leetcode.com/problems/create-target-array-in-the-given-order/
 */

#include <iostream>
#include <vector>

#include "helpers/terminal_format.h"
#include "helpers/Operators.hpp"


#pragma mark - 1. Brute force
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Create Target Array in the Given Order.
// Memory Usage: 8.6 MB, less than 11.20% of C++ online submissions for Create Target Array in the Given Order.
class Solution1 {
public:
    std::vector<int> createTargetArray(const std::vector<int>& nums, const std::vector<int>& indices) {
        if (nums.size() < 2) {
            return nums;
        }

        auto returnValue = std::vector<int>();
        returnValue.reserve(nums.size());

        using index_type = std::vector<int>::size_type;
        for (index_type i = 0; i < nums.size(); i += 1) {
            returnValue.push_back(-1);
            for (index_type j = (returnValue.size() - 1); j > indices[i]; j -= 1) {
                returnValue[j] = returnValue[j - 1];
            }
            returnValue[indices[i]] = nums[i];
        }

        return returnValue;
    }
};


#pragma mark - 2. Modify `nums` in place (uses less memory)
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Create Target Array in the Given Order.
// Memory Usage: 8.4 MB, less than 83.40% of C++ online submissions for Create Target Array in the Given Order.
class Solution {
public:
    std::vector<int> createTargetArray(std::vector<int>& nums, const std::vector<int>& indices) {
        if (nums.size() < 2) {
            return nums;
        }

        using index_type = std::vector<int>::size_type;
        for (index_type i = 0; i < nums.size(); i += 1) {
            const int currentNum = nums[i];
            for (index_type j = i; j > indices[i]; j -= 1) {
                nums[j] = nums[j - 1];
            }
            nums[indices[i]] = currentNum;
        }

        return std::move(nums);
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& indices, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.createTargetArray(numsCopy, indices);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << " " << indices << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << " " << indices << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1}, {0}, {1});
    test({1, 2}, {0, 0}, {2, 1});
    test({0, 1, 2, 3, 4}, {0, 1, 2, 2, 1}, {0, 4, 1, 3, 2});
    test({1,2,3,4,0}, {0,1,2,3,0}, {0,1,2,3,4});

    return 0;
}
