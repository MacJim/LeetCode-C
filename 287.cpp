/*
 * 287. Find the Duplicate Number
 * https://leetcode.com/problems/find-the-duplicate-number/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
/*
 * - Left numbers: (i + 1)
 * - Right numbers: i
 *
 * Duplicate numbers have both left and right cases.
 */
// WRONG ANSWER because this solution assumes that all numbers must exist.
// But I think in that case this solution works.
class Solution1 {
public:
    int findDuplicate(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int start = 0;
        int end = nums.size() - 1;

        while ((end - start) > 1) {
            int mid = (start + end) / 2;
            if (nums[mid] == (mid + 1)) {
                start = mid;
            } else {
                end = mid;
            }
        }

        return nums[start];
    }
};


#pragma mark - 2. Sort and scan
// Runtime: 8 ms, faster than 87.22% of C++ online submissions for Find the Duplicate Number.
// Memory Usage: 10.9 MB, less than 83.13% of C++ online submissions for Find the Duplicate Number.
class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        for (size_t i = 1; i < nums.size(); i += 1) {
            if (nums[i] == nums[i - 1]) {
                return nums[i];
            }
        }

        // This is unreachable.
        return nums[0];
    }
};


#pragma mark - 3. Unordered set


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findDuplicate(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,4,4,2,4}, 4);
    test({1,3,4,2,2}, 2);
    test({3,1,2,4,3}, 3);
    test({1,1}, 1);
    test({1,1,2}, 1);

    return 0;
}
