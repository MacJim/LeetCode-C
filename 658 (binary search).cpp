/*
 * 658. Find K Closest Elements
 * https://leetcode.com/problems/find-k-closest-elements/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Binary search
// WRONG ANSWER because the input numbers don't have contant intervals.
class Solution1 {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        if (arr.size() == 1) {
            return arr;
        }

        // Find x.
        int start = 0;
        int end = arr.size() - 1;
        while (start <= end) {
            const int mid = (start + end) / 2;
            if (arr[mid] == x) {
                start = mid;
                break;
            } else if (arr[mid] > x) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        // Get sub-array indices.
        int subArrStart = start - k / 2;
        int subArrEnd = start + k / 2;
        if (k % 2 == 0) {
            subArrEnd -= 1;
        }

        if (subArrStart < 0) {
            subArrEnd -= subArrStart;
            subArrStart = 0;
        } else if (subArrEnd >= arr.size()) {
            subArrStart -= (subArrEnd - arr.size() + 1);
            subArrEnd = (arr.size() - 1);
        }

        return std::vector<int>(arr.begin() + subArrStart, arr.begin() + subArrEnd + 1);
    }
};


#pragma mark - 2. Binary search and 2 pointers
// Runtime: 40 ms, faster than 61.71% of C++ online submissions for Find K Closest Elements.
// Memory Usage: 31 MB, less than 91.90% of C++ online submissions for Find K Closest Elements.
class Solution2 {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        if (arr.size() == 1) {
            return arr;
        }

        // 2 pointers.
        int subArrLeft = -1;
        int subArrRight = -1;

        // Find x.
        int start = 0;
        int end = arr.size() - 1;
        while (start < end) {
            const int mid = (start + end) / 2;
            if (arr[mid] == x) {
                // Exactly what we want to find.
                // Thus, the 2 side pointers point away from the current one.
                subArrLeft = mid - 1;
                subArrRight = mid + 1;
                break;
            } else if (arr[mid] > x) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        if (subArrLeft == -1) {
            // We didn't find the exact target, but found a larger number.
            subArrLeft = start - 1;
            subArrRight = start;
        }

        // 2 pointers.
        while ((subArrRight - subArrLeft - 1) < k) {
            if (subArrLeft == -1) {
                subArrRight += (k - (subArrRight - subArrLeft - 1));
                break;
            } else if (subArrRight == arr.size()) {
                subArrLeft -= (k - (subArrRight - subArrLeft - 1));
                break;
            }

            const auto leftAbs = abs(arr[subArrLeft] - x);
            const auto rightAbs = abs(arr[subArrRight] - x);
            if (leftAbs <= rightAbs) {
                subArrLeft -= 1;
            } else {
                subArrRight += 1;
            }
        }

        return std::vector<int>(arr.begin() + subArrLeft + 1, arr.begin() + subArrRight);
    }
};


#pragma mark - 3. Optimized 2
// Well it's the same performance as 2.
// Runtime: 40 ms, faster than 61.71% of C++ online submissions for Find K Closest Elements.
// Memory Usage: 31.1 MB, less than 80.43% of C++ online submissions for Find K Closest Elements.
class Solution {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        if (arr.size() == 1) {
            return arr;
        }

        // 2 pointers.
        int subArrLeft = -1;
        int subArrRight = -1;

        // Binary search: search for the position that's equal to or just larger than `x`.
        int left = 0;
        int right = arr.size();    // Initial value is out of bound.

        while (left < right) {    // Terminates when `left == right`.
            int mid = left + (right - left) / 2;

            if (arr[mid] == x) {
                subArrLeft = mid - 1;
                subArrRight = mid + 1;
                break;
            } else if (arr[mid] < x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        if (subArrLeft == -1) {
            subArrLeft = left - 1;
            subArrRight = left;
        }

        // 2 pointers.
        while ((subArrRight - subArrLeft - 1) < k) {
            if (subArrLeft == -1) {
                subArrRight += (k - (subArrRight - subArrLeft - 1));
                break;
            } else if (subArrRight == arr.size()) {
                subArrLeft -= (k - (subArrRight - subArrLeft - 1));
                break;
            }

            const auto leftAbs = abs(arr[subArrLeft] - x);
            const auto rightAbs = abs(arr[subArrRight] - x);
            if (leftAbs <= rightAbs) {
                subArrLeft -= 1;
            } else {
                subArrRight += 1;
            }
        }

        return std::vector<int>(arr.begin() + subArrLeft + 1, arr.begin() + subArrRight);
    }
};


void test(const std::vector<int>& arr, const int k, const int x, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto arrCopy = arr;
    auto result = solutionInstance.findClosestElements(arrCopy, k, x);

    if (result == expectedResult) {
        std::cout << "[Correct] " << arr << ", " << k << ", " << x << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << arr << ", " << k << ", " << x << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,5,5,5,5,8}, 3, 6, {5,5,5});
    test({0,5,5,5,5,8,8,8,8}, 3, 6, {5,5,5});

    test({0,2,4,9,9}, 2, 8, {9,9});

    test({0,1,1,1,2,3,6,7,8,9}, 9, 4, {0,1,1,1,2,3,6,7,8});

    test({1,2,3,4,5}, 4, 3, {1,2,3,4});
    test({1,2,3,4,5}, 4, -1, {1,2,3,4});
    test({1,2,3,4,5}, 4, 6, {2,3,4,5});

    test({1,2,3,4,5}, 3, 3, {2,3,4});
    test({1,2,3,4,5}, 3, -1, {1,2,3});
    test({1,2,3,4,5}, 3, 6, {3,4,5});

    return 0;
}
