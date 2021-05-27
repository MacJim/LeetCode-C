/*
 * 162. Find Peak Element
 * https://leetcode.com/problems/find-peak-element/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search: compare `mid` with adjacent elements
/*
 * It asks for O(logn) so it should be a binary search problem.
 *
 * Yes! This is the official solution!
 */
// Runtime: 4 ms, faster than 66.41% of C++ online submissions for Find Peak Element.
// Memory Usage: 8.8 MB, less than 88.99% of C++ online submissions for Find Peak Element.
class Solution {
public:
    int findPeakElement(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        // Edge cases.
        if (nums[0] > nums[1]) {
            return 0;
        }
        if (nums.back() > nums[nums.size() - 2]) {
            return (nums.size() - 1);
        }

        // Binary search.
        int left = 0;
        int right = nums.size() - 1;

        while (right > (left + 1)) {    // Terminates when `right - left == 2`.
            int mid = (left + right) / 2;    // Max length is 1000 so no overflowing here.
            int adjacent1 = mid - 1;
            int adjacent2 = mid + 1;

            if (nums[mid] < nums[adjacent1]) {
                right = mid;
            } else if (nums[mid] < nums[adjacent2]) {
                left = mid;
            } else {
                return mid;
            }
        }

        return (left + right) / 2;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findPeakElement(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,2,1}, 1);
    test({1,2,3,1}, 2);
    test({1,2,1,3,5,6,4}, 5);
    test({5,4,3,2,1,2,3,4,5}, 0);
    test({4,5,4,3,2,1,2,3,4,5}, 9);
    test({4,5,4,3,2,1,2,3,4,5,4}, 1);

    return 0;
}
