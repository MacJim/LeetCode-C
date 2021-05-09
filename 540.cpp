/*
 * 540. Single Element in a Sorted Array
 * https://leetcode.com/problems/single-element-in-a-sorted-array/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
// Runtime: 4 ms, faster than 97.72% of C++ online submissions for Single Element in a Sorted Array.
// Memory Usage: 11.1 MB, less than 36.95% of C++ online submissions for Single Element in a Sorted Array.
class Solution {
public:
    int singleNonDuplicate(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        // Special case: ends.
        // This reduces workloads in the main loop.
        if (nums[0] != nums[1]) {
            return nums[0];
        }
        if (nums.back() != nums[nums.size() - 2]) {
            return nums.back();
        }

        size_t start = 0;
        size_t end = nums.size() - 1;
        while (start < end) {
            const auto mid = (start + end) / 2;

            if (nums[mid] == nums[mid - 1]) {
                const auto leftLength = mid - 1 - start;

                if (leftLength % 2 == 0) {
                    // The element is on the right side.
                    start = mid + 1;
                } else {
                    // The element is on the left side.
                    end = mid - 2;
                }
            } else if (nums[mid] == nums[mid + 1]) {
                const auto leftLength = mid - start;

                if (leftLength % 2 == 0) {
                    // The element is on the right side.
                    start = mid + 2;
                } else {
                    // The element is on the left side.
                    end = mid - 1;
                }
            } else {
                // Found.
                return nums[mid];
            }
        }

        return nums[start];
    }
};


#pragma mark - 2. Alternative of 1 (not sure whether this is an optimization, but the code can be shorter)
/*
 * Note that the first occurrences always take even indices.
 */


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.singleNonDuplicate(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
//    test({1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}, 2);

    for (auto missingNum: {1,2,3,4,5,6,7,8,9,10}) {
        auto testVector = std::vector<int>();
        for (int num = 1; num <= 10; num += 1) {
            testVector.push_back(num);
            if (num != missingNum) {
                testVector.push_back(num);
            }
        }

        test(testVector, missingNum);
    }

    for (auto missingNum: {1,2,3,4,5,6,7,8,9}) {
        auto testVector = std::vector<int>();
        for (int num = 1; num <= 9; num += 1) {
            testVector.push_back(num);
            if (num != missingNum) {
                testVector.push_back(num);
            }
        }

        test(testVector, missingNum);
    }

    test({1,1,2,3,3}, 2);
    test({1,2,2,3,3,4,4,5,5}, 1);
    test({1,1,2,2,3,3,4,4,5}, 5);
    test({1,1,2,3,3,4,4,8,8}, 2);
    test({3,3,7,7,10,11,11}, 10);

    return 0;
}
