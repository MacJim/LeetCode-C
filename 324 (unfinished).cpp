/*
 * 324. Wiggle Sort II
 * https://leetcode.com/problems/wiggle-sort-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort the entire array and swap
// WRONG ANSWER: Doesn't handle some duplication numbers.
class Solution1 {
public:
    void wiggleSort(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }

        std::sort(nums.begin(), nums.end());    // 1,1,1,4,5,6,7

        int left = 1;    // Big indices.
        int right = (nums.size() % 2)? (nums.size() - 1): (nums.size() - 2);    // Small indices.
        while (left < right) {
            std::swap(nums[left], nums[right]);

            left += 2;
            right -= 2;
        }
    }
};


#pragma mark - 2. Do a copy
// Wrong Answer: Again, does not handle some duplicate numbers.
class Solution {
public:
    void wiggleSort(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }

        std::sort(nums.begin(), nums.end());    // 1,1,1,4,5,6,7

        auto returnValue = std::vector<int>(nums.size(), 0);

        const auto bigCount = nums.size() / 2;
        auto smallCount = bigCount;
        if (nums.size() % 2) {
            // Odd number: one more small.
            smallCount += 1;
        }

        // Small
        for (size_t i = 0; i < smallCount; i += 1) {
            returnValue[i * 2] = nums[i];
        }

        // Big
        for (size_t i = 0; i < bigCount; i += 1) {
            returnValue[i * 2 + 1] = nums[i + smallCount];
        }

        nums = std::move(returnValue);
    }
};


#pragma mark - 3. Quick select and 3-way partitioning (unfinished, revisit)
/*
 * Quick select on the middle element.
 *
 * Quick select is `O(n)` on average.
 */
class Solution3 {
private:
    int customIndex(const int i, const int len) {
        return 0;
    }

public:
    void wiggleSort(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return;
        }

        const auto len = nums.size();

        // Quick select.
        auto midIt = nums.begin() + len / 2;
        std::nth_element(nums.begin(), midIt, nums.end());
        const int midNum = *midIt;

        int i = 0;
        int j = 0;
        int k = len - 1;

        while (j <= k) {
//            if ()
        }
    }
};


bool isValidResult(const std::vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); i += 2) {
        if (nums[i] <= nums[i - 1]) {
            return false;
        }
        if (((i + 1) < (nums.size())) && (nums[i] <= nums[i + 1])) {
            return false;
        }
    }

    return true;
}


void test(const std::vector<int>& nums) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    solutionInstance.wiggleSort(numsCopy);

    if (isValidResult(numsCopy)) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << numsCopy << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << numsCopy << std::endl;
    }
}


int main() {
    test({4,5,5,6});
    test({1,3,2,5,4});
    test({1,5,1,1,6,4});
    test({1,3,2,2,3,1});

    return 0;
}
