/*
 * 373. Find K Pairs with Smallest Sums
 * https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// WRONG ANSWER: you can use the same number multiple times.
class Solution1 {
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        size_t i1 = 0;
        size_t i2 = 0;

        auto returnValue = std::vector<std::vector<int>>({{nums1[0], nums2[0]}});

        for (int j = 1; j < k; j += 1) {
            if (i1 == (nums1.size() - 1)) {
                i2 += 1;
            } else if (i2 == (nums2.size() - 1)) {
                i1 += 1;
            } else {
                const auto sum1 = nums1[i1 + 1] + nums2[i2];
                const auto sum2 = nums1[i1] + nums2[i2 + 1];
                if (sum1 >= sum2) {
                    i1 += 1;
                } else {
                    i2 += 1;
                }
            }

            returnValue.push_back({nums1[i1], nums2[i2]});
        }

        return returnValue;
    }
};


#pragma mark - 2. Log last indices
// Runtime: 4 ms, faster than 99.01% of C++ online submissions for Find K Pairs with Smallest Sums.
// Memory Usage: 9.1 MB, less than 87.13% of C++ online submissions for Find K Pairs with Smallest Sums.
class Solution {
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        auto returnValue = std::vector<std::vector<int>>();

        // Make nums1 shorter.
        // Cannot do this because the results will be reversed.
        // Maybe I can introduce a new flag for this to reverse their order before returning.
//        if (nums1.size() < nums2.size()) {
//            std::swap(nums1, nums2);
//        }

        k = std::min(k, static_cast<int>(nums1.size() * nums2.size()));

        auto lastIndices = std::vector<size_t>(nums1.size(), 0);

        for (int numIndex = 0; numIndex < k; numIndex += 1) {
            int minSum = INT_MAX;
            size_t minI1 = 0;

            for (size_t i1 = 0; i1 < lastIndices.size(); i1 += 1) {
                const size_t i2 = lastIndices[i1];
                if (i2 == nums2.size()) {
                    continue;
                }

                const int& num1 = nums1[i1];
                const int& num2 = nums2[i2];
                const int currentSum = num1 + num2;
                if (currentSum < minSum) {
                    minSum = currentSum;
                    minI1 = i1;
                }

                if (i2 == 0) {
                    break;
                }
            }

            returnValue.push_back({nums1[minI1], nums2[lastIndices[minI1]]});
            lastIndices[minI1] += 1;
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums1, const std::vector<int>& nums2, const int k, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto nums1Copy = nums1;
    auto nums2Copy = nums2;
    auto result = solutionInstance.kSmallestPairs(nums1Copy, nums2Copy, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums1 << ", " << nums2 << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums1 << ", " << nums2 << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,7,11}, {2,4,6}, 3, {{1,2},{1,4},{1,6}});
    test({1,1,2}, {1,2,3}, 2, {{1,1},{1,1}});
    test({1,2}, {3}, 3, {{1,3},{2,3}});

    return 0;
}
