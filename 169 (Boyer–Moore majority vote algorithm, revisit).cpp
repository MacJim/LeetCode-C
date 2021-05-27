/*
 * 169. Majority Element
 * https://leetcode.com/problems/majority-element/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Unordered map
// Runtime: 20 ms, faster than 46.72% of C++ online submissions for Majority Element.
// Memory Usage: 19.7 MB, less than 6.94% of C++ online submissions for Majority Element.
class Solution1 {
public:
    int majorityElement(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        const auto threshold = nums.size() / 2;

        auto occurrences = std::unordered_map<int, int>();

        for (const auto& num: nums) {
            occurrences[num] += 1;
            if (occurrences[num] > threshold) {
                return num;
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


#pragma mark - 2. Sort and 2 pointers
// Runtime: 24 ms, faster than 17.84% of C++ online submissions for Majority Element.
// Memory Usage: 19.4 MB, less than 98.81% of C++ online submissions for Majority Element.
class Solution2 {
public:
    int majorityElement(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        std::sort(nums.begin(), nums.end());

//        const auto threshold = nums.size() / 2 - 1;
        auto left = 0;
        auto right = (nums.size() - 1) / 2;
        while (true) {
            if (nums[left] == nums[right]) {
                return nums[left];
            }

            left += 1;
            right += 1;
        }
    }
};


#pragma mark - 3. Boyer–Moore majority vote algorithm (revisit)
// Runtime: 16 ms, faster than 78.81% of C++ online submissions for Majority Element.
// Memory Usage: 19.6 MB, less than 41.42% of C++ online submissions for Majority Element.
class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        int returnValue = nums[0];
        int count = 0;

        for (const auto& num: nums) {
            if (count == 0) {
                returnValue = num;
            }

            if (returnValue == num) {
                count += 1;
            } else {
                count -= 1;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.majorityElement(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,2,3}, 3);
    test({2,2,1,1,1,2,2}, 2);

    return 0;
}
