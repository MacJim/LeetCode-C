/*
 * 80. Remove Duplicates from Sorted Array II
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
 */

#include <iostream>
#include <vector>
#include "helpers/Operators.hpp"


#pragma mark - 1. Remove from tail
// Runtime: 8 ms, faster than 77.40% of C++ online submissions for Remove Duplicates from Sorted Array II.
// Memory Usage: 11.4 MB, less than 8.42% of C++ online submissions for Remove Duplicates from Sorted Array II.
class Solution1 {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        // Last element.
        int currentNum = nums.back();
        int currentCount = 1;

        // Previous elements
        for (auto it = (nums.rbegin() + 1); it < nums.rend(); it += 1) {
//            std::cout << 1 << std::flush;
            if (*it == currentNum) {
                if (currentCount == 2) {
                    nums.erase(it.base());
                } else {
                    currentCount += 1;
                }
            } else {
                currentNum = *it;
                currentCount = 1;
            }
        }

        return nums.size();
    }
};


#pragma mark - 2. Copy from front
// Runtime: 8 ms, faster than 77.40% of C++ online submissions for Remove Duplicates from Sorted Array II.
// Memory Usage: 11.2 MB, less than 93.04% of C++ online submissions for Remove Duplicates from Sorted Array II.
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        int i = 0;

        // We know that the input is in an ascending order.
        // Thus, we can check `n > nums[i - 2]`.
        for (const auto& n: nums) {
            if ((i < 2) || (n > nums[i - 2])) {
                nums[i] = n;
                i += 1;
            }
        }

        return i;
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedNums, const int expectedLength) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.removeDuplicates(numsCopy);

    if ((result == expectedLength) && (numsCopy == expectedNums)) {
        std::cout << "[Correct] " << nums << ": " << numsCopy << ", " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << numsCopy << ", " << result << " (should be " << expectedNums << ", " << expectedLength << ")" << std::endl;
    }
}


int main() {
    test({1,1,1,2,2,3}, {1,1,2,2,3}, 5);
    test({0,0,1,1,1,1,2,3,3}, {0,0,1,1,2,3,3}, 7);

    return 0;
}
