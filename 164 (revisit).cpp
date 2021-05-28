/*
 * 164. Maximum Gap
 * https://leetcode.com/problems/maximum-gap/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Log next positions (unfinished, won't finish)
class Solution1 {
public:
    int maximumGap(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        if (nums.size() == 2) {
            return abs(nums[1] - nums[0]);
        }

        /// -3: uninitialized; -2: start (smallest); -1: end (largest)
        auto next = std::vector<int>(nums.size(), -3);
        int biggestDeltaIndex = 0;

        if (nums[1] >= nums[0]) {
            next[1] = -1;
            next[0] = 1;
        } else {
            next[1] = 0;
            next[0] = -1;
            biggestDeltaIndex = 1;
        }

        for (int i = 2; i < nums.size(); i += 1) {
            const auto& num = nums[i];
        }

        return -1;
    }
};


#pragma mark - 2. Official solution: bucket sort (revisit)
// Runtime: 8 ms, faster than 60.80% of C++ online submissions for Maximum Gap.
// Memory Usage: 9 MB, less than 26.10% of C++ online submissions for Maximum Gap.
// Source: https://leetcode.com/problems/maximum-gap/discuss/50643/bucket-sort-JAVA-solution-with-explanation-O(N)-time-and-space
/*
 * We have `n` numbers.
 * The return value is larger or equal to `minReturnValue = ceil((max - min) / (n - 1))`.
 *
 * Place all numbers into buckets of interval `minReturnValue`.
 * The interval is closed on the left and open on the right.
 * For each bucket, we only log the min and max numbers.
 *
 * The return value must not come from the same bucket (because delta within the same bucket is always smaller than `minReturnValue`).
 */
class Solution {
private:
    /**
     * This implementation can cause index overflow in some cases (e.g. {100,3,2,1}).
     *
     * Thus, the `buckets` vector below has an additional index just for the largest number in those cases.
     */
    inline int getBucketID(const int& num, const int& minNum, const int& interval) {
        const int delta = num - minNum;
        return (delta / interval);
    }

public:
    int maximumGap(const std::vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        if (nums.size() == 2) {
            return abs(nums[1] - nums[0]);
        }

        // Calculate bucket intervals.
        int minNum = INT_MAX;
        int maxNum = INT_MIN;
        for (const auto& num: nums) {
            minNum = std::min(minNum, num);
            maxNum = std::max(maxNum, num);
        }

        const auto intervalsCount = nums.size() - 1;
        auto minReturnValue = static_cast<int>(ceil(static_cast<float>(maxNum - minNum) / intervalsCount));

        // Edge case: all elements equal.
        if (minReturnValue == 0) {
            return 0;
        }

        // The final bucket is exclusively reserved for the largest element that may cause index overflow in some cases.
        auto buckets = std::vector<std::pair<int, int>>(intervalsCount + 1, std::make_pair(INT_MAX, INT_MIN));

        // Place into buckets.
        for (const auto& num: nums) {
            const auto bucketID = getBucketID(num, minNum, minReturnValue);
            buckets[bucketID].first = std::min(buckets[bucketID].first, num);
            buckets[bucketID].second = std::max(buckets[bucketID].second, num);
        }

        // Sequential scan on buckets.
        auto returnValue = static_cast<int>(minReturnValue);

        auto previousFilledBucket = buckets.begin();
        while (previousFilledBucket->first == INT_MAX) {
            previousFilledBucket += 1;
        }
        for (auto it = (previousFilledBucket + 1); it != buckets.end(); it += 1) {
            if (it->first == INT_MAX) {
                continue;
            }

            const auto delta = it->first - previousFilledBucket->second;
            returnValue = std::max(returnValue, delta);

            previousFilledBucket = it;
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maximumGap(nums);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({100,3,2,1}, 97);
    test({1,1,1,1}, 0);
    test({2,1,2,2}, 1);
    test({2,6,3,4,1}, 2);
    test({3,6,9,1}, 3);
    test({5,3,2,1,4}, 1);
    test({6}, 0);
    test({6,15}, 9);

    return 0;
}
