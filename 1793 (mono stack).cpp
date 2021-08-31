/*
 * 1793. Maximum Score of a Good Subarray
 * https://leetcode.com/problems/maximum-score-of-a-good-subarray/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. 2 pointers (similar to the "jumping" solution of problem 84)
// Runtime: 317 ms, faster than 10.81% of C++ online submissions for Maximum Score of a Good Subarray.
// Memory Usage: 89.6 MB, less than 61.65% of C++ online submissions for Maximum Score of a Good Subarray.
class Solution1 {
public:
    int maximumScore(const std::vector<int>& nums, const int k) {
        int returnValue = nums[k];

        int left = k;
        int right = k;

        int currentNum = nums[k];

        while (currentNum != 0) {
            const int& nextLeftNum = (left == 0) ? 0 : nums[left - 1];
            const int& nextRightNum = (right == (nums.size() - 1)) ? 0 : nums[right + 1];

            if (nextLeftNum == nextRightNum) {
                if (nextLeftNum < currentNum) {
                    currentNum = nextLeftNum;
                }

                if (left != 0) {
                    left -= 1;
                }
                if (right != (nums.size() - 1)) {
                    right += 1;
                }
            } else if (nextLeftNum > nextRightNum) {
                if (nextLeftNum < currentNum) {
                    currentNum = nextLeftNum;
                }

                if (left != 0) {
                    left -= 1;
                }
            } else {
                if (nextRightNum < currentNum) {
                    currentNum = nextRightNum;
                }

                if (right != (nums.size() - 1)) {
                    right += 1;
                }
            }

            const int newValue = currentNum * (1 + right - left);
            returnValue = std::max(returnValue, newValue);
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1: Reduce outer loop count using inner loop
// Runtime: 231 ms, faster than 39.00% of C++ online submissions for Maximum Score of a Good Subarray.
// Memory Usage: 89.5 MB, less than 61.65% of C++ online submissions for Maximum Score of a Good Subarray.
class Solution {
public:
    int maximumScore(const std::vector<int>& nums, const int k) {
        int returnValue = nums[k];

        int left = k;
        int right = k;

        int currentNum = nums[k];

        while (currentNum != 0) {
            const int& nextLeftNum = (left == 0) ? 0 : nums[left - 1];
            const int& nextRightNum = (right == (nums.size() - 1)) ? 0 : nums[right + 1];

            if (nextLeftNum == nextRightNum) {
                if (nextLeftNum < currentNum) {
                    currentNum = nextLeftNum;
                }

                while ((left != 0) && (nums[left - 1] >= currentNum)) {
                    left -= 1;
                }
                while ((right != (nums.size() - 1)) && (nums[right + 1] >= currentNum)) {
                    right += 1;
                }
            } else if (nextLeftNum > nextRightNum) {
                if (nextLeftNum < currentNum) {
                    currentNum = nextLeftNum;
                }

                while ((left != 0) && (nums[left - 1] >= currentNum)) {
                    left -= 1;
                }
            } else {
                if (nextRightNum < currentNum) {
                    currentNum = nextRightNum;
                }

                while ((right != (nums.size() - 1)) && (nums[right + 1] >= currentNum)) {
                    right += 1;
                }
            }



            const int newValue = currentNum * (1 + right - left);
            returnValue = std::max(returnValue, newValue);
        }

        return returnValue;
    }
};


#pragma mark - 3. Monotonic stack (seems to be the official solution)


void test(const std::vector<int>& nums, const int k, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maximumScore(nums, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({5,5,4,5,4,1,1,1}, 0, 20);
    test({5,5,4,5,4,1,1,1}, 1, 20);
    test({1,4,3,7,4,5}, 3, 15);

    return 0;
}
