/*
 * 259. 3Sum Smaller
 * https://leetcode.com/problems/3sum-smaller/
 *
 * Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
 *
 * For example, given nums = [-2, 0, 1, 3], and target = 2.
 * Return 2. Because there are two triplets which sums are less than 2:
 * [-2, 0, 1]
 * [-2, 0, 3]
 *
 * Follow up:
 * Could you solve it in O(n^2) runtime?
 *
 * @tag-array
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. 2 pointers
class Solution {
public:
    int threeSum(std::vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int returnValue = 0;

        for (int i1 = 0; i1 < nums.size(); i1 += 1) {
            int i2 = i1 + 1;
            int i3 = nums.size() - 1;

            while (i2 < i3) {    // Terminates when i2 == i3
                const auto sum = nums[i1] + nums[i2] + nums[i3];
                if (sum < target) {
                    returnValue += (i3 - i2);
                    i2 += 1;
                } else {
                    i3 -= 1;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int target, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.threeSum(numsCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({-2,0,1,3}, 2, 2);

    return 0;
}
