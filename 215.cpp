/*
 * 215. Kth Largest Element in an Array
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


// Runtime: 8 ms, faster than 98.48% of C++ online submissions for Kth Largest Element in an Array.
// Memory Usage: 10 MB, less than 97.97% of C++ online submissions for Kth Largest Element in an Array.
class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end(), std::greater<>());
        return nums[k - 1];
    }
};


void test(const std::vector<int>& nums, const int k, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findKthLargest(numsCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,2,1,5,6,4}, 2, 5);
    test({3,2,3,1,2,4,5,5,6}, 4, 4);

    return 0;
}
