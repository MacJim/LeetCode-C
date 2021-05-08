/*
 * 81. Search in Rotated Sorted Array II
 * https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
 *
 * Like "33. Search in Rotated Sorted Array" with an additional constraint.
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"


#pragma mark - 1. Question 33 solution
// WRONG ANSWER
class Solution1 {
public:
    bool search(std::vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return (target == nums[0]);
        }

        int start = 0;
        int end = nums.size() - 1;

        while (start <= end) {
            const int mid = (start + end) / 2;

            if (nums[mid] == target) {
                return true;
            }

            if (nums[start] <= nums[mid]) {    // Must judge equal to resolve `start == mid`.
                // No turning point on the left side.
                if ((nums[start] <= target) && (target <= nums[mid])) {
                    // Search on the left side.
                    end = mid - 1;
                } else {
                    start = mid + 1;
                }
            } else {
                if ((nums[mid] <= target) && (target <= nums[end])) {
                    // Search on the right side.
                    start = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        }

        return false;
    }
};


#pragma mark - 2. Divide using the 0th element (revisit)
// Runtime: 8 ms, faster than 39.31% of C++ online submissions for Search in Rotated Sorted Array II.
// Memory Usage: 13.8 MB, less than 99.11% of C++ online submissions for Search in Rotated Sorted Array II.
/*
 * The `start` element is always a threshold for the first and second sub-arrays.
 * If it equals the mid element, increase `start`.
 */
class Solution {
public:
    bool search(std::vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return (target == nums[0]);
        }

        int start = 0;
        int end = nums.size() - 1;

        while (start <= end) {
            const int mid = (start + end) / 2;

            if (nums[mid] == target) {
                return true;
            }

            if (nums[start] == nums[mid]) {
                // This is the special case: we try to remove elements one by one to determine whether the rotation point is in the first sub-array.
                start += 1;
            } else if (nums[start] < nums[mid]) {
                if ((nums[start] <= target) && (target <= nums[mid])) {
                    end = mid - 1;
                } else {
                    start = mid + 1;
                }
            } else {
                if ((nums[mid] <= target) && (target <= nums[end])) {
                    start = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        }

        return false;
    }
};


void test(const std::vector<int>& nums, const int target, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.search(numsCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,0,1,1,1}, 0, true);
    test({1,1,1,0,1}, 0, true);

    test({1,0,1,1,1,1}, 0, true);
    test({1,0,1,1,1,1,1}, 0, true);
    test({1,0,1,1,1,1,1,1}, 0, true);

    test({1,1,0,1,1,1}, 0, true);
    test({1,1,1,0,1,1,1}, 0, true);
    test({1,1,1,1,0,1,1,1}, 0, true);

    test({1,0,0,0,1}, 1, true);

    test({2,5,6,0,0,1,2}, 0, true);
    test({2,5,6,0,0,1,2}, 3, false);

    return 0;
}
