/*
 * 1726. Tuple with Same Product
 * https://leetcode.com/problems/tuple-with-same-product/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Loop over (s1, b1) pairs
// Time Limit Exceeded (as expected, as this one is O(n^3))
class Solution {
public:
    int tupleSameProduct(std::vector<int>& nums) {
        if (nums.size() < 4) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int returnValue = 0;

        for (int s1 = 0; s1 < (nums.size() - 1); s1 += 1) {
            for (int b1 = (nums.size() - 1); (b1 - s1) >= 3; b1 -= 1) {
                const int expectedMulResult = nums[s1] * nums[b1];

                // 2 pointers.
                int s2 = s1 + 1;
                int b2 = b1 - 1;

                while (s2 < b2) {
                    const int mulResult = nums[s2] * nums[b2];
                    if (mulResult == expectedMulResult) {
                        returnValue += 8;    // Each tuple: +8 permutations

                        // Numbers are unique. So modify both.
                        s2 += 1;
                        b2 -= 1;
                    } else if (mulResult < expectedMulResult) {
                        s2 += 1;
                    } else {
                        b2 -= 1;
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Store multiplication results in a hash table
// This is O(n^2) and much better than solution 1.
// Runtime: 675 ms, faster than 35.11% of C++ online submissions for Tuple with Same Product.
// Memory Usage: 81.7 MB, less than 69.88% of C++ online submissions for Tuple with Same Product.
class Solution2 {
public:
    int tupleSameProduct(std::vector<int>& nums) {
        if (nums.size() < 4) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int returnValue = 0;

        auto mulResults = std::unordered_map<int, int>();
        for (int start = 0; start < (nums.size() - 1); start += 1) {
            for (int end = (nums.size() - 1); end > start; end -= 1) {
                const int mulResult = nums[start] * nums[end];
                mulResults[mulResult] += 1;
            }
        }

        for (const auto& [_, occurrence]: mulResults) {
            if (occurrence > 1) {
                // occurrence choose 2.
                const int currentResult = occurrence * (occurrence - 1) / 2 * 8;

                returnValue += currentResult;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.tupleSameProduct(numsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,3,4,6}, 8);
    test({1,2,4,5,10}, 16);
    test({2,3,4,6,8,12}, 40);
    test({2,3,5,7}, 0);

    return 0;
}
