/*
 * 128. Longest Consecutive Sequence
 * https://leetcode.com/problems/longest-consecutive-sequence/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <random>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Official solution: Search from a middle number: use an unordered set to store existing numbers (revisit)
// I somewhat think this algorithm is O(n^2) and may not be as intuitive as the sorting solution.
// Time Limit Exceeded
/*
 * This solution is stupid.
 *
 * When `nums` is long, the `numsSet` set causes excessive memory pressure.
 */
class Solution1 {
public:
    int longestConsecutive(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        auto numsSet = std::unordered_set<int>();
        for (const auto& num: nums) {
            numsSet.insert(num);
        }

        int returnValue = 1;

        for (const auto& num: numsSet) {
            if (numsSet.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 2;

                while (numsSet.count(currentNum + 1)) {
                    currentStreak += 1;
                    currentNum += 1;
                }

                returnValue = std::max(returnValue, currentStreak);
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Sort and 2 pointers
// Runtime: 36 ms, faster than 27.48% of C++ online submissions for Longest Consecutive Sequence.
// Memory Usage: 22.3 MB, less than 5.50% of C++ online submissions for Longest Consecutive Sequence.
class Solution2 {
public:
    int longestConsecutive(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        auto returnValue = 1;    // Note that the initial return value is 1.

        std::sort(nums.begin(), nums.end());

        int left = 0;
        int right = 1;
        int currentLength = 1;    // Note that the initial length is 1.
        while (right < nums.size()) {
            if (nums[right] == nums[right - 1]) {
                right += 1;
            } else if ((nums[right] - nums[right - 1]) == 1) {
                right += 1;
                currentLength += 1;
            } else {
                returnValue = std::max(returnValue, currentLength);

                left = right;
                right = left + 1;
                currentLength = 1;
            }
        }

        returnValue = std::max(returnValue, currentLength);

        return returnValue;
    }
};


#pragma mark - 3. Optimizes 2
// A single pointer is enough.
// Runtime: 32 ms, faster than 28.05% of C++ online submissions for Longest Consecutive Sequence.
// Memory Usage: 22.2 MB, less than 5.50% of C++ online submissions for Longest Consecutive Sequence.
class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }

        auto returnValue = 1;    // Note that the initial return value is 1.

        std::sort(nums.begin(), nums.end());

        int currentLength = 1;    // Note that the initial length is 1.

        for (size_t current = 1; current < nums.size(); current += 1) {
            if (nums[current] == nums[current - 1]) {
                // Do nothing.
            } else if ((nums[current] - nums[current - 1]) == 1) {
                currentLength += 1;
            } else {
                returnValue = std::max(returnValue, currentLength);

                currentLength = 1;
            }
        }

        returnValue = std::max(returnValue, currentLength);

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto generator = std::default_random_engine(seed);
    std::shuffle(numsCopy.begin(), numsCopy.end(), generator);

    auto result = solutionInstance.longestConsecutive(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5,100,101}, 5);
    test({1,2,0,1}, 3);
    test({100,4,200,1,3,2}, 4);
    test({0,3,7,2,5,8,4,6,0,1}, 9);
    test({1,2,3,4,5,6,7,8,9}, 9);
    test({1}, 1);
    test({1,1}, 1);

    return 0;
}
