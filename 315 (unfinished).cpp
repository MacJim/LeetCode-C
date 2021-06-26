/*
 * 315. Count of Smaller Numbers After Self
 * https://leetcode.com/problems/count-of-smaller-numbers-after-self/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Log and jump to the next smaller number
// WRONG ANSWER because decreasing streaks are ignored.
class Solution1 {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {0};
        }

        auto nextSmallerIndex = std::vector<int>(nums.size(), -1);
        auto returnValue = std::vector<int>(nums.size(), 0);

        for (int i = (nums.size() - 2); i >= 0; i -= 1) {
            int nextI = i + 1;
            const int& currentNum = nums[i];

            // Jump to a smaller or equal number.
            while ((nextI != -1) && (nums[nextI] > currentNum)) {
                nextI = nextSmallerIndex[nextI];
            }

            if (nextI == -1) {
                continue;
            }

            const int& nextNum = nums[nextI];

            // Compare numbers and assign return value.
            if (nextNum < currentNum) {
                // Smaller.
                nextSmallerIndex[i] = nextI;
                returnValue[i] = returnValue[nextI] + 1;
            } else {
                // Equal.
                nextSmallerIndex[i] = nextSmallerIndex[nextI];
                returnValue[i] = returnValue[nextI];
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized brute force with jumping
// Time Limit Exceeded
class Solution2 {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {0};
        }

        auto nextNotGreaterIndex = std::vector<int>(nums.size(), INT_MAX);
        auto returnValue = std::vector<int>(nums.size(), 0);

        for (int i = (nums.size() - 2); i >= 0; i -= 1) {
            int nextI = i + 1;
            const int& currentNum = nums[i];

            // Jump to a smaller or equal number.
            while (nextI < nums.size()) {
                if (nums[nextI] >= currentNum) {
                    nextI = nextNotGreaterIndex[nextI];
                } else {
                    returnValue[i] += 1;
                    if (nextNotGreaterIndex[i] == INT_MAX) {
                        nextNotGreaterIndex[i] = nextI;
                    }

                    nextI += 1;
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Binary search + (somewhat) insertion sort
// Time Limit Exceeded (better than solution 2, though)
class Solution {
private:
    int binarySearchUpperBound(const std::vector<int>& nums, const int target, int left, int right) {
        while (left <= right) {    // Terminates when left == (right + 1)
            const int mid = (left + right) / 2;
            if (nums[mid] < target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return (left - 1);
    }

    /**
     * Moves larger numbers to the left.
     *
     * This is not a standard insertion sort.
     */
    void insert(std::vector<int>& nums, const int originalIndex, const int targetIndex) {
        auto originalNumber = nums[originalIndex];
        for (int i = originalIndex; i < targetIndex; i += 1) {
            nums[i] = nums[i + 1];
        }

        nums[targetIndex] = originalNumber;
    }

public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {0};
        }

        auto returnValue = std::vector<int>(nums.size(), 0);

        for (int i = (nums.size() - 2); i >= 0; i -= 1) {
            const int targetIndex = binarySearchUpperBound(nums, nums[i], i + 1, nums.size() - 1);
            returnValue[i] = nums.size() - 1 - targetIndex;

            insert(nums, i, targetIndex);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.countSmaller(numsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({5,2,6,1}, {2,1,1,0});
    test({5,6,1,2}, {2,2,0,0});
    test({6,6,6,6,6,6}, {0,0,0,0,0,0});
    test({5,4,1,2,3}, {4,3,0,0,0});
    test({2,1,2,1,2,1}, {3,0,2,0,1,0});

    return 0;
}
