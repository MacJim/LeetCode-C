/*
 * 154. Find Minimum in Rotated Sorted Array II
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
 */

/*
 * Duplicate numbers easily defeats binary search algorithms with cases where left == mid == right, such as: {2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2} and {2, 2, 2, 0, 2, 2, 2, 2, 2 , 2, 2, 2}.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. De-duplicate on both ends
// WRONG ANSWER because there may still be duplicates on a single end.
class Solution1 {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums.front();
        }

        int left = 0;
        int right = nums.size() - 1;

        while ((left < right) && (nums[left] == nums[right])) {
            // Duplicating elements on both ends have given my enough pain.
            left += 1;
        }

        if (left == right) {
            // All elements are duplicate.
            return nums[left];
        }
        if (nums[left] < nums[right]) {
            // Smaller: not rotated at all.
            return nums[left];
        }

        while (left < right) {    // Terminates when left == right
            if (nums[left] == nums[right]) {
                while ((left < right) && (nums[left] == nums[right])) {
                    // Duplicating elements on both ends have given my enough pain.
                    left += 1;
                }
                continue;
            }

            int mid = (left + right) / 2;

//            if (nums[mid] == nums[right]) {
//                while (nums[mid] == nums[right]) {
//                    right -= 1;
//                }
//                right += 1;
//                continue;
//            }

            if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return nums[right];
    }
};


#pragma mark - 2. Move inwards when encountering duplicates (revisit)
// Source: https://leetcode.ca/2016-05-02-154-Find-Minimum-in-Rotated-Sorted-Array-II/
/*
 * Note that this method adds another termination case to the main loop: `nums[left] < nums[right]`.
 */
// Runtime: 8 ms, faster than 36.55% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
// Memory Usage: 12.4 MB, less than 6.13% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums.front();
        }

        if (nums.front() < nums.back()) {
            // No rotation at all.
            return nums.front();
        }

        int left = 0;
        int right = nums.size() - 1;

        while ((left < right) && (nums[left] >= nums[right])) {
            /*
             * Terminates when either:
             *
             * - left == right
             * - nums[left] < nums[right]: No rotation from [left, right]; this is caused by `right -= 1`
             */
            int mid = (left + right) / 2;

            if (nums[right] == nums[mid]) {
                right -= 1;    // Move inwards.
            } else if (nums[right] > nums[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        /*
         * Still, consider the 2 termination cases:
         *
         * 1. `left == right`
         * 2. nums[left] < nums[right]
         *
         * We must not use `nums[right]` because of case 2.
         */
        return nums[left];
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
    test({2,0,1,1,1}, 0);

    test({3,1,1,1}, 1);
    test({1,1,1,3}, 1);
    test({1,3,3}, 1);
    test({1,1,3}, 1);
    test({2,2,2,0,1}, 0);
    test({2,2,3,3,4,4,0,0,1,1}, 0);
    test({2,2,2,2,2,2,0,1,2}, 0);
    test({2,0,1,2,2,2,2,2,2}, 0);
    test({0,0,0,0,0,0,0}, 0);
    test({2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2}, 0);

    // Problem 153 test cases: no duplicate numbers.
    test({3,4,5,1,2}, 1);
    test({4,5,6,7,0,1,2}, 0);
    test({11,13,15,17}, 11);
    test({1,2,3,4,5}, 1);
    test({5,1,2,3,4}, 1);
    test({1,2,3,4}, 1);
    test({4,1,2,3}, 1);
    test({1,3,5}, 1);

    return 0;
}
