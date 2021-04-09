/*
 * 442. Find All Duplicates in an Array
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort
// Runtime: 60 ms, faster than 36.39% of C++ online submissions for Find All Duplicates in an Array.
// Memory Usage: 33.5 MB, less than 65.43% of C++ online submissions for Find All Duplicates in an Array.
class Solution1 {
public:
    std::vector<int> findDuplicates(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return {};
        }

        auto returnValue = std::vector<int>();

        std::sort(nums.begin(), nums.end());
        for (size_t i = 1; i < nums.size(); i += 1) {
            if (nums[i] == nums[i - 1]) {
                returnValue.push_back(nums[i]);
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Use a bit array to store if each number is visited


#pragma mark - 3. Improved 2: Use number sign to represent visited (revisit)
// Runtime: 40 ms, faster than 97.67% of C++ online submissions for Find All Duplicates in an Array.
// Memory Usage: 33.6 MB, less than 28.92% of C++ online submissions for Find All Duplicates in an Array.
class Solution {
public:
    std::vector<int> findDuplicates(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return {};
        }

        auto returnValue = std::vector<int>();

        for (auto num: nums) {
            num = abs(num);

            if (nums[num - 1] < 0) {
                returnValue.push_back(num);
            } else {
                nums[num - 1] = -nums[num - 1];    // Negative: visited.
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findDuplicates(numsCopy);
    std::sort(result.begin(), result.end());

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({4,3,2,7,8,2,3,1}, {2, 3});
    test({1,1,2}, {1});

    return 0;
}
