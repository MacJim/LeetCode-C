/*
 * 719. Find K-th Smallest Pair Distance
 * https://leetcode.com/problems/find-k-th-smallest-pair-distance/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"


/*
 * Brainstorm:
 *
 * - Order doesn't matter -> can sort
 */


#pragma mark - 1. Binary search (revisit)
// Source: https://leetcode.ca/2017-11-18-719-Find-K-th-Smallest-Pair-Distance/
// Runtime: 36 ms, faster than 18.62% of C++ online submissions for Find K-th Smallest Pair Distance.
// Memory Usage: 10.1 MB, less than 74.36% of C++ online submissions for Find K-th Smallest Pair Distance.
class Solution1 {
private:
    int countSmallerOrEqualDistances(const std::vector<int>& nums, int target) {
        int returnValue = 0;
        for (size_t i = 0; i < nums.size(); i += 1) {
            // `upper_bound` itself is a binary search and only accepts an ordered array as input.
            // The amount of elements behind `nums[i]` that produce smaller or equal distances.
            // Note that the iterator returned by `upper_bound` is greater than `nums[i] + target`.
            returnValue += std::upper_bound(nums.begin(), nums.end(), nums[i] + target) - nums.begin() - i - 1;
        }
        return returnValue;
    }

public:
    int smallestDistancePair(std::vector<int>& nums, int k) {
        if (nums.size() == 2) {
            return (nums[1] - nums[0]);
        }

        std::sort(nums.begin(), nums.end());

        // Initialize boundaries.
        int left = INT_MAX;
        for (int i = 1; i < nums.size(); i += 1) {
            left = std::min(left, nums[i] - nums[i - 1]);
        }

        int right = nums.back() - nums.front();

        // Main loop: binary search.
        while (left < right) {    // Terminates when left == right
            int mid = (left + right) / 2;
            int count = countSmallerOrEqualDistances(nums, mid);
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};


#pragma mark - 2. Improves the `count` function of 1 using 2 pointers
// Source: https://leetcode.ca/2017-11-18-719-Find-K-th-Smallest-Pair-Distance/
// The "2 pointers" part is my own improvement, but I still need to revisit the binary search part.
// Runtime: 8 ms, faster than 98.14% of C++ online submissions for Find K-th Smallest Pair Distance.
// Memory Usage: 10.1 MB, less than 36.96% of C++ online submissions for Find K-th Smallest Pair Distance.
class Solution {
private:
    int countSmallerOrEqualDistances(const std::vector<int>& nums, int target) {
        int returnValue = 0;

        // Use 2 pointers.
        int left = 0;
        int right = 1;
        while (left < (nums.size() - 1)) {
            if (right == nums.size()) {
                const auto pairsCount = right - 1 - left;
                returnValue += pairsCount;

                left += 1;
                right -= 1;
            }

            if ((nums[right] - nums[left]) <= target) {
                right += 1;
            } else {
                const auto pairsCount = right - 1 - left;
                returnValue += pairsCount;

                left += 1;
            }
        }

        return returnValue;
    }

public:
    int smallestDistancePair(std::vector<int>& nums, int k) {
        if (nums.size() == 2) {
            return (nums[1] - nums[0]);
        }

        std::sort(nums.begin(), nums.end());

        // Initialize boundaries.
        int left = INT_MAX;
        for (int i = 1; i < nums.size(); i += 1) {
            left = std::min(left, nums[i] - nums[i - 1]);
        }

        int right = nums.back() - nums.front();

        // Main loop: binary search.
        while (left < right) {    // Terminates when left == right
            int mid = (left + right) / 2;
            int count = countSmallerOrEqualDistances(nums, mid);
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};


void test(const std::vector<int>& nums, const int k, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.smallestDistancePair(numsCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,1}, 1, 0);
    test({1,3,1}, 2, 2);
    test({1,3,1}, 3, 2);

    test({1,4,5,7,12}, 1, 1);
    test({1,4,5,7,12}, 2, 2);
    test({1,4,5,7,12}, 3, 3);
    test({1,4,5,7,12}, 4, 3);

    return 0;
}
