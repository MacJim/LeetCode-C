/*
 * 1679. Max Number of K-Sum Pairs
 * https://leetcode.com/problems/max-number-of-k-sum-pairs/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"


#pragma mark - 1. Hash table cache
// Runtime: 148 ms, faster than 99.04% of C++ online submissions for Max Number of K-Sum Pairs.
// Memory Usage: 65.4 MB, less than 64.47% of C++ online submissions for Max Number of K-Sum Pairs.
class Solution {
public:
    int maxOperations(std::vector<int>& nums, int k) {
        auto numsCache = std::unordered_map<int, int>();

        auto returnValue = 0;

        for (const auto& n: nums) {
            // Must use exactly 2 numbers.
//            if (n == k) {
//                returnValue += 1;
//                continue;
//            }

            const int target = k - n;
            auto prevIt = numsCache.find(target);
            if ((prevIt != numsCache.end()) && (prevIt->second > 0)) {
                prevIt->second -= 1;
                returnValue += 1;
            } else {
                auto currIt = numsCache.find(n);
                if (currIt == numsCache.end()) {
                    numsCache.emplace(n, 1);
                } else {
                    numsCache[n] += 1;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int k, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.maxOperations(numsCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << " " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << " " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4}, 5, 2);
    test({3,1,3,4,3}, 6, 1);
    test({3,1,5,1,1,1,1,1,2,2,3,2,2}, 1, 0);

    return 0;
}
