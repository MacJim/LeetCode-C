/*
 * 153. Find Minimum in Rotated Sorted Array
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
// Runtime: 4 ms, faster than 58.14% of C++ online submissions for Find Minimum in Rotated Sorted Array.
// Memory Usage: 10.3 MB, less than 16.58% of C++ online submissions for Find Minimum in Rotated Sorted Array.
class Solution1 {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums.front();
        }

        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {    // Terminates when left == (right + 1)
            int mid = (left + right) / 2;

            if (nums[right] > nums[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return nums[right];
    }
};


#pragma mark - 2. Optimizes 1: Adds termination points
/*
 * Add a termination `if` to the main `while` loop: determines whether `mid` is the rotation point.
 *
 * Although solution 2 is faster, I still prefer the more elegant solution 1.
 */
// Runtime: 12 ms, faster than 58.14% of C++ online submissions for Find Minimum in Rotated Sorted Array.
// Memory Usage: 10.1 MB, less than 64.28% of C++ online submissions for Find Minimum in Rotated Sorted Array.
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums.front();
        }

        if (nums[0] < nums.back()) {
            // Not rotated at all.
            return nums[0];
        }

        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {    // Terminates when left == (right + 1)
            int mid = (left + right) / 2;

            if (nums[mid] > nums[mid + 1]) {
                return nums[mid + 1];
            }
            if (nums[mid] < nums[mid - 1]) {
                return nums[mid];
            }

            if (nums[right] > nums[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return nums[right];
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findMin(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,4,5,1,2}, 1);
    test({4,5,6,7,0,1,2}, 0);
    test({11,13,15,17}, 11);
    test({1,2,3,4,5}, 1);
    test({5,1,2,3,4}, 1);
    test({1,2,3,4}, 1);
    test({4,1,2,3}, 1);

    return 0;
}
