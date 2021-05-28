/*
 * 189. Rotate Array
 * https://leetcode.com/problems/rotate-array/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Swap (wrong)
class Solution1 {
public:
    void rotate(std::vector<int>& nums, int k) {
        for (size_t i = 0; i < k; i += 1) {
            const size_t j = nums.size() + i - k;
            std::swap(nums[i], nums[j]);
        }
    }
};


#pragma mark - 2. Move the first `n - k` numbers
// Time Limit Exceeded
class Solution2 {
public:
    void rotate(std::vector<int>& nums, int k) {
        while (k >= nums.size()) {
            k -= nums.size();
        }
        for (int i = 0; i < (nums.size() - k); i += 1) {
            nums.push_back(nums[0]);
            nums.erase(nums.begin());
        }
    }
};


#pragma mark - 3. Combine the 2 parts
// Runtime: 28 ms, faster than 57.12% of C++ online submissions for Rotate Array.
// Memory Usage: 25.7 MB, less than 8.22% of C++ online submissions for Rotate Array.
class Solution3 {
public:
    void rotate(std::vector<int>& nums, int k) {
        while (k >= nums.size()) {
            k -= nums.size();
        }
        if (k == 0) {
            return;
        }

        auto part1Size = nums.size() - k;

        nums.insert(nums.end(), nums.begin(), nums.begin() + part1Size);
        nums.erase(nums.begin(), nums.begin() + part1Size);
    }
};


#pragma mark - 4. Reverse everything -> reverse each part (revisit)
// Runtime: 24 ms, faster than 75.33% of C++ online submissions for Rotate Array.
// Memory Usage: 24.9 MB, less than 58.72% of C++ online submissions for Rotate Array.
class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        while (k >= nums.size()) {
            k -= nums.size();
        }
        if (k == 0) {
            return;
        }

        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};


void test(const std::vector<int>& nums, const int k, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    solutionInstance.rotate(numsCopy, k);

    if (numsCopy == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << numsCopy << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << numsCopy << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1}, 2, {1});
    test({1,2}, 2, {1,2});
    test({1,2,3,4,5,6,7}, 3, {5,6,7,1,2,3,4});
    test({1,2,3,4}, 2, {3,4,1,2});

    return 0;
}
