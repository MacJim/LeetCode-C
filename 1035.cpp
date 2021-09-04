/*
 * 1035. Uncrossed Lines
 * https://leetcode.com/problems/uncrossed-lines/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DP, line by line
// Runtime: 20 ms, faster than 29.69% of C++ online submissions for Uncrossed Lines.
// Memory Usage: 9.7 MB, less than 98.11% of C++ online submissions for Uncrossed Lines.
class Solution {
public:
    int maxUncrossedLines(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        auto currentValues = std::vector<int>(nums1.size(), 0);
        auto nextValues = std::vector<int>(nums1.size(), 0);

        for (const auto& num2: nums2) {
            if (nums1[0] == num2) {
                nextValues[0] = 1;
            } else {
                nextValues[0] = currentValues[0];
            }

            for (size_t i = 1; i < nums1.size(); i += 1) {
                const int& num1 = nums1[i];

                if (num1 == num2) {
                    const int useCurrentNumberValue = currentValues[i - 1] + 1;
                    nextValues[i] = std::max(currentValues[i], useCurrentNumberValue);
                } else {
                    nextValues[i] = std::max(currentValues[i], nextValues[i - 1]);
                }
            }

            std::swap(currentValues, nextValues);    // I'm really lazy here.
        }

        return currentValues.back();
    }
};


void test(const std::vector<int>& nums1, const std::vector<int>& nums2, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maxUncrossedLines(nums1, nums2);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums1 << ", " << nums2 << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums1 << ", " << nums2 << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1}, {1,3}, 1);
    test({1}, {1}, 1);
    test({1,4,2}, {1,2,4}, 2);
    test({2,5,1,2,5}, {10,5,2,1,5,2}, 3);
    test({1,3,7,1,7,5}, {1,9,2,5,1}, 2);

    return 0;
}
