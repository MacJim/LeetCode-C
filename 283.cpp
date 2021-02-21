/*
 * 283. Move Zeroes
 * https://leetcode.com/problems/move-zeroes/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Swap (2 pointers)
// Runtime: 12 ms, faster than 22.45% of C++ online submissions for Move Zeroes.
// Memory Usage: 8.9 MB, less than 74.39% of C++ online submissions for Move Zeroes.
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }

        int zeroIndex = -1;

        for (int i = 0; i < nums.size(); i += 1) {
            if (nums[i] == 0) {
                if (zeroIndex == -1) {
                    zeroIndex = i;
                }
            } else {
                if (zeroIndex != -1) {
                    std::swap(nums[zeroIndex], nums[i]);
                    zeroIndex += 1;
                }
            }
        }
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = nums;
    solutionInstance.moveZeroes(result);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,1,0,2,3}, {1,2,3,0,0});
    test({0,0,0,0,1}, {1,0,0,0,0});

    return 0;
}
