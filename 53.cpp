/*
 * 53. Maximum Subarray
 * https://leetcode.com/problems/maximum-subarray/
 */

#include <iostream>
#include <vector>
#include <algorithm>


#pragma mark - 1. Complicated DP solution
// Runtime: 16 ms, faster than 30.35% of C++ online submissions for Maximum Subarray.
// Memory Usage: 13.4 MB, less than 13.51% of C++ online submissions for Maximum Subarray.
class Solution1 {
public:
    int maxSubArray(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 0) {
            return 0;
        } else if (len == 1) {
            return nums.front();
        }

        // First number.
        int currentSum = nums.at(0);

        int returnValue = currentSum;

        if (currentSum < 0) {
            currentSum = 0;
        }

        // Upcoming numbers.
        for (size_t i = 1; i < len; i += 1) {
            const int& num = nums.at(i);
            currentSum += num;

            returnValue = std::max(returnValue, currentSum);

            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Brief DP solution
// Runtime: 24 ms, faster than 9.44% of C++ online submissions for Maximum Subarray.
// Memory Usage: 13.6 MB, less than 5.23% of C++ online submissions for Maximum Subarray.
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 0) {
            return 0;
        } else if (len == 1) {
            return nums.front();
        }

        auto currentRow = std::vector<int>(len, 0);

        // First number.
        currentRow.at(0) = nums.at(0);

        // Upcoming numbers.
        for (size_t i = 1; i < len; i += 1) {
            const int& num = nums.at(i);

            currentRow.at(i) = std::max(num, num + currentRow.at(i - 1));
        }

        return *std::max_element(currentRow.begin(), currentRow.end());
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> testCase1 = {-2,1,-3,4,-1,2,1,-5,4};    // 6
    std::cout << solutionInstance.maxSubArray(testCase1) << std::endl;

    std::vector<int> testCase2 = {-1, -2, -3, -2, -1};    // -1
    std::cout << solutionInstance.maxSubArray(testCase2) << std::endl;

    return 0;
}
