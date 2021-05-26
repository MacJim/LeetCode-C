/*
 * 136. Single Number
 * https://leetcode.com/problems/single-number/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <chrono>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Unordered set
// Well, an unordered set indeed uses linear runtime, but doesn't use constant extra space :(
// Runtime: 32 ms, faster than 19.70% of C++ online submissions for Single Number.
// Memory Usage: 19.9 MB, less than 21.51% of C++ online submissions for Single Number.
class Solution1 {
public:
    int singleNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        auto m = std::unordered_set<int>();
        for (const auto& num: nums) {
            if (m.count(num)) {
                m.erase(num);
            } else {
                m.insert(num);
            }
        }

        return *(m.begin());
    }
};


#pragma mark - 2. Sort
// Runtime: 24 ms, faster than 32.79% of C++ online submissions for Single Number.
// Memory Usage: 16.9 MB, less than 80.79% of C++ online submissions for Single Number.
class Solution2 {
public:
    int singleNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        std::sort(nums.begin(), nums.end());
        for (size_t i = 0; i < (nums.size() - 1); i += 2) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }

        return nums.back();
    }
};


#pragma mark - 3. Official solution: bitwise XOR (good to know, not necessary though)
/*
 * XOR counts the amount of odd bits.
 *
 * The return value will be returned because all other numbers contribute to 2 of the same bit.
 */
// Runtime: 12 ms, faster than 96.47% of C++ online submissions for Single Number.
// Memory Usage: 17 MB, less than 45.85% of C++ online submissions for Single Number.
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        int temp = 0;
        for (const auto& num: nums) {
            temp ^= num;
        }

        return temp;
    }
};


void test(std::vector<int> nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto generator = std::default_random_engine(seed);
    std::shuffle(nums.begin(), nums.end(), generator);

    auto numsCopy = nums;
    auto result = solutionInstance.singleNumber(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,2}, 1);
    test({1,1,2,2,4}, 4);
    test({1,1,2,2,3,4,4,5,5}, 3);
    test({1,1,2,2,3,3,4,5,5}, 4);
    test({1,1,2,2,3,3,4,5,5,6,6}, 4);

    return 0;
}
