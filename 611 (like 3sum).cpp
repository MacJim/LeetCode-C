/*
 * 611. Valid Triangle Number
 * https://leetcode.com/problems/valid-triangle-number/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


/*
 * Side length:
 *
 * - 0 not allowed
 * - a + b < c: Sort the input
 */


#pragma mark - 1. 2 pointers, like 3sum
// Runtime: 128 ms, faster than 19.55% of C++ online submissions for Valid Triangle Number.
// Memory Usage: 12.7 MB, less than 18.28% of C++ online submissions for Valid Triangle Number.
class Solution {
public:
    int triangleNumber(std::vector<int>& nums) {
        if (nums.size() < 3) {
            // Not enough numbers.
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int i1 = 0;
        while ((i1 < nums.size()) && (nums[i1] == 0)) {
            // 0 not allowed as side length.
            i1 += 1;
        }
        if ((nums.size() - i1) < 3) {
            // Not enough positive numbers.
            return 0;
        }

        int returnValue = 0;

        while (i1 < (nums.size() - 2)) {
            int i2 = i1 + 1;
            int i3 = i2 + 1;
            while (i3 < nums.size()) {
                const int delta = nums[i3] - nums[i2];
                if (delta < nums[i1]) {
                    // Anything between i3 and i2 can be used as i2.
                    returnValue += (i3 - i2);

                    i3 += 1;
                } else {
                    i2 += 1;
                }
            }

            i1 += 1;
        }

        return returnValue;
    }
};


#pragma mark - 2. 2 pointers + binary search
/*
 * This is O(n^2 logn) and should be slower than approach 1.
 */


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.triangleNumber(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,2,3,4}, 3);
    test({4,2,3,4}, 4);

    test({2,2,10,3,4}, 3);

    test({0,0,0,0,0,0}, 0);
    test({0,0,0,1,0,0,0}, 0);
    test({0,0,0,1,2,0,0}, 0);
    test({0,0,0,1,2,2,0}, 1);

    test({3,5,7,9}, 3);

    return 0;
}
