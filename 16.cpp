/*
 * 16. 3Sum Closest
 * https://leetcode.com/problems/3sum-closest/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Brute force: Sort, select 1st and 2nd elements from the front, select the 3rd element from the back
// Runtime: 256 ms, faster than 5.32% of C++ online submissions for 3Sum Closest.
// Memory Usage: 10 MB, less than 11.37% of C++ online submissions for 3Sum Closest.
class Solution1 {
public:
    int threeSumClosest(std::vector<int>& nums, const int target) {
        if (nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());

        int minDelta = INT_MAX;
        for (size_t i1 = 0; i1 < (nums.size() - 2); i1 += 1) {
            const int remaining1 = target - nums[i1];
            for (size_t i2 = i1 + 1; i2 < (nums.size() - 1); i2 += 1) {
                const int remaining2 = remaining1 - nums[i2];
                for (size_t i3 = (nums.size() - 1); i3 > i2; i3 -= 1) {
                    const int remaining3 = remaining2 - nums[i3];
                    if (abs(remaining3) < abs(minDelta)) {
                        minDelta = remaining3;
                    }
                }
            }
        }

        return target - minDelta;
    }
};


#pragma mark - 2. Optimize 1: Binary search
// Runtime: 56 ms, faster than 9.90% of C++ online submissions for 3Sum Closest.
// Memory Usage: 9.9 MB, less than 60.64% of C++ online submissions for 3Sum Closest.
class Solution2 {
private:
    size_t binarySearch(const std::vector<int>& nums, const int target, size_t start) {
        // Find lower bound.
        // [start, end)
        size_t end = nums.size();    // Initial value is out of bound because we'll run `left -= 1` anyway.

        bool startIncreased = false;
        while (start < end) {    // Terminates when start == end
            size_t mid = (start + end) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid;
            } else {
                start = mid + 1;
                startIncreased = true;
            }
        }

        if (!startIncreased) {
            // The start number is already optimal.
            return start;
        }

        start -= 1;
        if (start == (nums.size() - 1)) {
            return start;
        } else {
            if (abs(nums[start] - target) > abs(nums[start + 1] - target)) {
                return (start + 1);
            } else {
                return start;
            }
        }
    }

public:
    int threeSumClosest(std::vector<int>& nums, const int target) {
        if (nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());

        int minDelta = INT_MAX;
        for (size_t i1 = 0; i1 < (nums.size() - 2); i1 += 1) {
            const int remaining1 = target - nums[i1];
            for (size_t i2 = i1 + 1; i2 < (nums.size() - 1); i2 += 1) {
                const int remaining2 = remaining1 - nums[i2];

                const size_t i3 = binarySearch(nums, remaining2, i2 + 1);
                const int remaining3 = remaining2 - nums[i3];
                if (abs(remaining3) < abs(minDelta)) {
                    minDelta = remaining3;
                }
            }
        }

        return target - minDelta;
    }
};


#pragma mark - 3. Try to optimize 2: terminate when remaining target is 0
// Runtime: 12 ms, faster than 54.94% of C++ online submissions for 3Sum Closest.
// Memory Usage: 9.9 MB, less than 11.37% of C++ online submissions for 3Sum Closest.
class Solution {
private:
    size_t binarySearch(const std::vector<int>& nums, const int target, size_t start) {
        // Find lower bound.
        // [start, end)
        size_t end = nums.size();    // Initial value is out of bound because we'll run `left -= 1` anyway.

        bool startIncreased = false;
        while (start < end) {    // Terminates when start == end
            size_t mid = (start + end) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid;
            } else {
                start = mid + 1;
                startIncreased = true;
            }
        }

        if (!startIncreased) {
            // The start number is already optimal.
            return start;
        }

        start -= 1;
        if (start == (nums.size() - 1)) {
            return start;
        } else {
            if (abs(nums[start] - target) > abs(nums[start + 1] - target)) {
                return (start + 1);
            } else {
                return start;
            }
        }
    }

public:
    int threeSumClosest(std::vector<int>& nums, const int target) {
        if (nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());

        int minDelta = INT_MAX;
        for (size_t i1 = 0; i1 < (nums.size() - 2); i1 += 1) {
            const int remaining1 = target - nums[i1];
            for (size_t i2 = i1 + 1; i2 < (nums.size() - 1); i2 += 1) {
                const int remaining2 = remaining1 - nums[i2];

                const size_t i3 = binarySearch(nums, remaining2, i2 + 1);
                const int remaining3 = remaining2 - nums[i3];
                if (abs(remaining3) < abs(minDelta)) {
                    minDelta = remaining3;
                }
            }

            if (minDelta == 0) {
                /*
                 * MARK:
                 *
                 * Here is the only difference between solution 2 and 3.
                 * And it resulted in a 4x speed boost.
                 *
                 * Obviously, the test cases have too many "exact 3 sums".
                 */
                break;
            }
        }

        return target - minDelta;
    }
};


void test(const std::vector<int>& nums, const int target, const int expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.threeSumClosest(numsCopy, target);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({-1,2,1,-4,3}, 1, 1);
    test({-1,2,1,-4}, 1, 2);

    return 0;
}
