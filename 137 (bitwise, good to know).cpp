/*
 * 137. Single Number II
 * https://leetcode.com/problems/single-number-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort
// This is O(nlogn) instead of the required O(n).
// Runtime: 8 ms, faster than 78.87% of C++ online submissions for Single Number II.
// Memory Usage: 9.4 MB, less than 99.42% of C++ online submissions for Single Number II.
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        std::sort(nums.begin(), nums.end());

        for (size_t i = 0; i < (nums.size() - 1); i += 3) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }

        return nums.back();
    }
};


#pragma mark - 2. Count bit by bit (good to know, not sure it it's useful)
/*
 * 1. Count the bits at each position
 * 2. Mod 3
 * 3. Add all resulting bits together
 */


//void test(const std::vector<int>& nums, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << nums << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    return 0;
}
