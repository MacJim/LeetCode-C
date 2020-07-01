/*
 * 198. House Robber
 * https://leetcode.com/problems/house-robber/
 */

#include <iostream>
#include <vector>
#include <algorithm>


#pragma mark - 1. 3 variables
// Runtime: 4 ms, faster than 46.01% of C++ online submissions for House Robber.
// Memory Usage: 7.8 MB, less than 59.13% of C++ online submissions for House Robber.
class Solution1 {
public:
    int rob(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 0) {
            return 0;
        } else if (len == 1) {
            return nums.at(0);
        } else if (len == 2) {
            return std::max(nums.at(0), nums.at(1));
        }

        int num0 = nums.at(0);
        int num1 = nums.at(1);
        int num2 = nums.at(0) + nums.at(2);

        for (size_t i = 3; i < len; i += 1) {
            const int currentNum = nums.at(i) + std::max(num0, num1);

            num0 = num1;
            num1 = num2;
            num2 = currentNum;
        }

        return std::max(num1, num2);
    }
};


#pragma mark - 2. Optimized 1: 2 variables
// Runtime: 4 ms, faster than 46.01% of C++ online submissions for House Robber.
// Memory Usage: 7.6 MB, less than 95.78% of C++ online submissions for House Robber.
class Solution {
public:
    int rob(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 0) {
            return 0;
        } else if (len == 1) {
            return nums.at(0);
        } else if (len == 2) {
            return std::max(nums.at(0), nums.at(1));
        }

        int num0 = nums.at(0);
        int num1 = std::max(nums.at(0), nums.at(1));

        for (size_t i = 2; i < len; i += 1) {
            const int currentNum = std::max(nums.at(i) + num0, num1);

            num0 = num1;
            num1 = currentNum;
        }

        return std::max(num0, num1);
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> testCase1 = {1,2,3,1};
    std::cout << solutionInstance.rob(testCase1) << std::endl;    // 4

    std::vector<int> testCase2 = {2,7,9,3,1};
    std::cout << solutionInstance.rob(testCase2) << std::endl;    // 12

    std::vector<int> testCase3 = {2,1,3,9,1};
    std::cout << solutionInstance.rob(testCase3) << std::endl;    // 11

    std::vector<int> testCase4 = {1,3,1,3,100};
    std::cout << solutionInstance.rob(testCase4) << std::endl;    // 103

    return 0;
}
