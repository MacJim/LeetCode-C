/*
 * 35. Search Insert Position
 * https://leetcode.com/problems/search-insert-position/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Search Insert Position.
// Memory Usage: 9.7 MB, less than 47.94% of C++ online submissions for Search Insert Position.
class Solution1 {
public:
    size_t searchInsert(std::vector<int>& nums, int target) {
        // We know that `nums` is not empty.
        if (nums.size() == 1) {
            if (target > nums[0]) {
                return 1;
            } else {
                return 0;
            }
        }

        size_t start = 0;
        size_t end = nums.size() - 1;
        if (target <= nums[start]) {
            return start;
        }
        if (target == nums[end]) {
            return end;
        } else if (target > nums[end]) {
            return (end + 1);
        }

        while ((end - start) > 1) {
            const auto mid = (end + start) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid;
            } else {
                start = mid;
            }
        }

        if (target <= nums[start]) {
            return start;
        } else {
            return (start + 1);
        }
    }
};


#pragma mark - 2. Simplified 1
class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        // We know that `nums` is not empty.
//        if (nums.size() == 1) {
//            if (target > nums[0]) {
//                return 1;
//            } else {
//                return 0;
//            }
//        }

        int start = 0;
        int end = nums.size() - 1;
//        if (target <= nums[start]) {
//            return start;
//        }
//        if (target == nums[end]) {
//            return end;
//        } else if (target > nums[end]) {
//            return (end + 1);
//        }

        // -1 and +1 here ensures we get the correct result when `start == end`.
        while (end >= start) {
            const auto mid = (end + start) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return start;
    }
};


void test(const std::vector<int>& nums, const int target, const size_t expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.searchInsert(numsCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1}, 0, 0);
    test({1}, 1, 0);
    test({1}, 2, 1);

    test({1,3}, 0, 0);
    test({1,3}, 2, 1);
    test({1,3}, 5, 2);

    for (const int i: {2,3,4,5,6,7,8,9}) {
        test({1, 10}, i, 1);
    }

    test({1,3,5,6}, 5, 2);
    test({1,3,5,6}, 2, 1);
    test({1,3,5,6}, 7, 4);
    test({1,3,5,6}, 0, 0);

    for (const int i: {0,1,2,3,4}) {
        test({0,1,2,3,4}, i, i);
    }

    for (const int i: {0,1,2,3,4,5}) {
        test({0,1,2,3,4,5}, i, i);
    }

    return 0;
}
