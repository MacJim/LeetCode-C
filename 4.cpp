/*
 * 4. Median of Two Sorted Arrays
 * https://leetcode.com/problems/median-of-two-sorted-arrays/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


/*
 * Brainstorm:
 *
 * - Binary search: min(nums1[0], nums2[0]) to max(nums1.back(), nums2.back())
 * - Even amount of nums: Select 2 numbers and calculate average
 * - Odd amount of nums: Select the middle number
 */


#pragma mark - 1. Unfinished and buggy
// How to deal with multiple `mid`s???
class Solution1 {
private:
    /// Returns the upper bound.
    int findLargerElementInVector(const std::vector<int>& nums, const int target) {
        int left = 0;
        int right = nums.size();

        while (left < right) {    // Terminates when `left == right`.
            const auto mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left - 1;
    }

public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if (nums1.empty()) {
            if (nums2.size() % 2 == 0) {
                double midLeft = nums2[nums2.size() / 2 - 1];
                double midRight = nums2[nums2.size() / 2];
                return (midLeft + midRight) / 2;
            } else {
                return static_cast<double>(nums2[nums2.size() / 2]);
            }
        }
        if (nums2.empty()) {
            if (nums1.size() % 2 == 0) {
                float midLeft = nums1[nums1.size() / 2 - 1];
                float midRight = nums1[nums1.size() / 2];
                return (midLeft + midRight) / 2;
            } else {
                return nums1[nums1.size() / 2];
            }
        }

        int left = std::min(nums1[0], nums2[0]);
        int right = std::max(nums1.back(), nums2.back());

        while (left <= right) {
            int mid = (left + right) / 2;

            auto i1 = findLargerElementInVector(nums1, mid);
            auto i2 = findLargerElementInVector(nums2, mid);

            const int largerCount = (static_cast<int>(nums1.size()) - i1) + (static_cast<int>(nums2.size()) - i2);
            double firstLargerElement = 0.0;
            if ((i1 >= 0) && (i1 < nums1.size())) {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    firstLargerElement = std::max(nums1[i1], nums2[i2]);
                } else {
                    firstLargerElement = nums1[i1];
                }
            } else {
                firstLargerElement = nums2[i2];
            }

            // Get rid of duplicate `mid`s.
            int midCount = 0;
            i1 -= 1;
            i2 -= 1;
            while ((i1 >= 0) && (nums1[i1] == mid)) {
                i1 -= 1;
                midCount += 1;
            }
            while ((i2 >= 0) && (nums2[i2] == mid)) {
                i2 -= 1;
                midCount += 1;
            }
            const int smallerCount = nums1.size() + nums2.size() - largerCount - midCount;
            double lastSmallerElement = 0.0;
            if ((i1 >= 0) && (i1 < nums1.size())) {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    firstLargerElement = std::min(nums1[i1], nums2[i2]);
                } else {
                    firstLargerElement = nums1[i1];
                }
            } else {
                firstLargerElement = nums2[i2];
            }

            const int delta = largerCount - smallerCount;
            if (abs(delta) <= midCount) {
                if ((nums1.size() + nums2.size()) % 2 == 1) {
                    return static_cast<double>(mid);
                } else {
                    if (delta == midCount) {
                        // More large elements.
                        return (firstLargerElement + static_cast<double>(mid)) / 2;
                    } else if (delta == -midCount) {
                        return (lastSmallerElement + static_cast<double>(mid)) / 2;
                    } else {
                        return static_cast<double>(mid);
                    }
                }
            } else if (largerCount > smallerCount) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


#pragma mark - 2. Fixes 1
// This problem is a torture. There are too many fine details to pay attention to.
// Runtime: 40 ms, faster than 21.80% of C++ online submissions for Median of Two Sorted Arrays.
// Memory Usage: 89.3 MB, less than 64.97% of C++ online submissions for Median of Two Sorted Arrays.
class Solution {
private:
    int findLargerElementInVector(const std::vector<int>& nums, int target) {
        target += 1;

        int left = 0;
        int right = nums.size();

        while (left < right) {    // Terminates when `left == right`.
            const auto mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }

public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if (nums1.empty()) {
            if (nums2.size() % 2 == 0) {
                double midLeft = nums2[nums2.size() / 2 - 1];
                double midRight = nums2[nums2.size() / 2];
                return (midLeft + midRight) / 2;
            } else {
                return static_cast<double>(nums2[nums2.size() / 2]);
            }
        }
        if (nums2.empty()) {
            if (nums1.size() % 2 == 0) {
                float midLeft = nums1[nums1.size() / 2 - 1];
                float midRight = nums1[nums1.size() / 2];
                return (midLeft + midRight) / 2;
            } else {
                return nums1[nums1.size() / 2];
            }
        }

        int left = std::min(nums1[0], nums2[0]);
        int right = std::max(nums1.back(), nums2.back());

        while (left <= right) {
            int mid = (left + right) / 2;

            auto i1 = findLargerElementInVector(nums1, mid);
            auto i2 = findLargerElementInVector(nums2, mid);

            const int largerCount = (static_cast<int>(nums1.size()) - i1) + (static_cast<int>(nums2.size()) - i2);
            double firstLargerElement = mid;
            if ((i1 >= 0) && (i1 < nums1.size())) {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    firstLargerElement = std::min(nums1[i1], nums2[i2]);
                } else {
                    firstLargerElement = nums1[i1];
                }
            } else {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    firstLargerElement = nums2[i2];
                }
            }

            // Get rid of duplicate `mid`s.
            int midCount = 0;
            i1 -= 1;
            i2 -= 1;
            while ((i1 >= 0) && (nums1[i1] == mid)) {
                i1 -= 1;
                midCount += 1;
            }
            while ((i2 >= 0) && (nums2[i2] == mid)) {
                i2 -= 1;
                midCount += 1;
            }

            const int smallerCount = nums1.size() + nums2.size() - largerCount - midCount;
            double lastSmallerElement = mid;
            if ((i1 >= 0) && (i1 < nums1.size())) {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    lastSmallerElement = std::max(nums1[i1], nums2[i2]);
                } else {
                    lastSmallerElement = nums1[i1];
                }
            } else {
                if ((i2 >= 0) && (i2 < nums2.size())) {
                    lastSmallerElement = nums2[i2];
                }
            }

            const int delta = largerCount - smallerCount;
            if (abs(delta) <= midCount) {
                // A solution is found.
                if ((nums1.size() + nums2.size()) % 2 == 1) {
                    return static_cast<double>(mid);
                } else {
                    if (midCount == 0) {
                        // `mid` doesn't exist in both arrays.
                        return (firstLargerElement + lastSmallerElement) / 2;
                    } else if (delta == midCount) {
                        // More larger elements than smaller elements.
                        return (firstLargerElement + static_cast<double>(mid)) / 2;
                    } else if (delta == -midCount) {
                        // More smaller elements than larger elements.
                        return (lastSmallerElement + static_cast<double>(mid)) / 2;
                    } else {
                        // The middle 2 elements are both `mid`.
                        return static_cast<double>(mid);
                    }
                }
            } else if (largerCount > smallerCount) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


void test(const std::vector<int>& nums1, const std::vector<int>& nums2, const double expectedResult) {
    static auto solutionInstance = Solution();

    auto nums1Copy = nums1;
    auto nums2Copy = nums2;
    auto result = solutionInstance.findMedianSortedArrays(nums1Copy, nums2Copy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums1 << ", " << nums2 << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums1 << ", " << nums2 << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3}, {}, 2.0);
    test({}, {1,3}, 2.0);
    test({1,2,3}, {}, 2.0);
    test({}, {1,2,3}, 2.0);

    test({2,2,4,4}, {2,2,4,4}, 3.0);

    test({0,0}, {0,0}, 0.0);
    test({0,0}, {0,0,0}, 0.0);
    test({0,0,0}, {0,0}, 0.0);
    test({0,0,0}, {0,0,0}, 0.0);

    test({1,2}, {3,4}, 2.5);
    test({1}, {2,3}, 2.0);
    test({1,2}, {3}, 2.0);

    test({1,3,5}, {2,4}, 3.0);

    test({1,3}, {3,4}, 3.0);
    test({1,3}, {3,4,5}, 3.0);

    test({1,3,3,3,3,3}, {3,3,3,5}, 3.0);

    return 0;
}
