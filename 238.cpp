/*
 * 238. Product of Array Except Self
 * https://leetcode.com/problems/product-of-array-except-self/
 */

/*
 * Division operation is not allowed.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Forward and backward products
// Runtime: 40 ms, faster than 5.69% of C++ online submissions for Product of Array Except Self.
// Memory Usage: 24.9 MB, less than 37.55% of C++ online submissions for Product of Array Except Self.
class Solution2 {
public:
    std::vector<int> productExceptSelf(const std::vector<int>& nums) {
        auto forwardProducts = std::vector<int>(nums.size());
        forwardProducts[0] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            forwardProducts[i] = forwardProducts[i - 1] * nums[i];
        }

        auto backwardProducts = std::vector<int>(nums.size());
        backwardProducts.back() = nums.back();
        for (int i = (nums.size() - 2); i >= 0; i -= 1) {
            backwardProducts[i] = backwardProducts[i + 1] * nums[i];
        }

        auto returnValue = std::vector<int>(nums.size());
        // Front and back elements.
        returnValue[0] = backwardProducts[1];
        returnValue.back() = forwardProducts[forwardProducts.size() - 2];

        // Middle elements.
        for (size_t i = 1; i < (nums.size() - 1); i += 1) {
            returnValue[i] = forwardProducts[i - 1] * backwardProducts[i + 1];
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1: Calculate forward product when calculating the return value
/*
 * This is the required `O(1)` extra space.
 * Note that `returnValue` doesn't count as extra space.
 */
// Runtime: 32 ms, faster than 7.55% of C++ online submissions for Product of Array Except Self.
// Memory Usage: 24 MB, less than 76.89% of C++ online submissions for Product of Array Except Self.
class Solution {
public:
    std::vector<int> productExceptSelf(const std::vector<int>& nums) {
        /// Also stores the backward products temporarily.
        auto returnValue = std::vector<int>(nums.size());
        returnValue.back() = nums.back();
        for (int i = (nums.size() - 2); i > 0; i -= 1) {    // No need to calculate `i == 0` because it gets immediately overwritten.
            returnValue[i] = returnValue[i + 1] * nums[i];
        }

        // Front element.
        int forwardProduct = nums[0];
        returnValue[0] = returnValue[1];

        // Middle elements.
        for (size_t i = 1; i < (nums.size() - 1); i += 1) {
            returnValue[i] = returnValue[i + 1] * forwardProduct;
            forwardProduct *= nums[i];
        }

        // Back element.
        returnValue.back() = forwardProduct;

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

//    auto numsCopy = nums;
    auto result = solutionInstance.productExceptSelf(nums);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4}, {24,12,8,6});
    test({-1,1,0,-3,3}, {0,0,9,0,0});

    return 0;
}
