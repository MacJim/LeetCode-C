/*
 * 416. Partition Equal Subset Sum
 * https://leetcode.com/problems/partition-equal-subset-sum/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>

#include "helpers/Operators.hpp"


#pragma mark - 1. Confused
class Solution1 {
public:
    bool canPartition(std::vector<int>& nums) {
        if (nums.empty()) {
            return true;
        } else if (nums.size() == 1) {
            return false;
        }

        // Sum
        const int sum = std::accumulate(std::begin(nums), std::end(nums), 0);
        if ((sum % 2) != 0) {
            return false;
        }
        int halfSum = sum / 2;

        // Sort
        std::sort(std::begin(nums), std::end(nums));

        // Find combination from back to front.
        halfSum -= nums.back();
        if (halfSum == 0) {
            return true;
        }

//        auto usedIts = std::stack<std::reverse_iterator<std::vector<int>>()>();
//        for (auto it = std::rbegin(nums) + 1; it < std::rend(nums); it += 1) {
//            if (*it == halfSum) {
//                return true;
//            } else if (*it < halfSum) {
//                usedIts.push(it);
//            }
//        }

        auto usedNums = std::stack<size_t>();
        for (size_t i = 1; i < nums.size(); i += 1) {
            const auto& currentNum = nums[i];
            if (currentNum == halfSum) {
                return true;
            } else if (currentNum < halfSum) {
                usedNums.push(i);
            }
        }

        return false;
    }
};


#pragma mark - 2. DP for [0, sum]
// Runtime: 448 ms, faster than 27.10% of C++ online submissions for Partition Equal Subset Sum.
// Memory Usage: 9.1 MB, less than 82.81% of C++ online submissions for Partition Equal Subset Sum.
class Solution2 {
public:
    bool canPartition(std::vector<int> &nums) {
        if (nums.empty()) {
            return true;
        } else if (nums.size() == 1) {
            return false;
        }

        // Sum
        const int sum = std::accumulate(std::begin(nums), std::end(nums), 0);
        if ((sum % 2) != 0) {
            return false;
        }
        const int halfSum = sum / 2;

        // Sum DP vector.
        auto reachability = std::vector<bool>(halfSum + 1, false);
        reachability[0] = true;

        // 0
        const auto& num0 = nums[0];
        if (num0 > halfSum) {
            return false;
        }
        reachability[num0] = true;

        // 1 ~ (size - 1)
        for (size_t i = 1; i < nums.size(); i += 1) {
            const auto& num = nums[i];
            if (num > halfSum) {
                return false;
            }

            for (int j = (reachability.size() - 1); j >= 0; j -= 1) {
                if (reachability[j]) {
                    const int targetIndex = j + num;
                    if (targetIndex < reachability.size()) {
                        reachability[targetIndex] = true;
                    }
                }
            }
        }

        return reachability.back();
    }
};


#pragma mark - 3. Optimized 2
// Runtime: 432 ms, faster than 27.68% of C++ online submissions for Partition Equal Subset Sum.
// Memory Usage: 8.9 MB, less than 94.05% of C++ online submissions for Partition Equal Subset Sum.
class Solution {
public:
    bool canPartition(std::vector<int> &nums) {
        if (nums.empty()) {
            return true;
        } else if (nums.size() == 1) {
            return false;
        }

        // Sum
        const int sum = std::accumulate(std::begin(nums), std::end(nums), 0);
        if ((sum % 2) != 0) {
            return false;
        }
        const int halfSum = sum / 2;

        // Sum DP vector.
        auto reachability = std::vector<bool>(halfSum + 1, false);
        reachability[0] = true;

        for (const auto& num: nums) {
            if (num > halfSum) {
                return false;
            }

            for (int j = (reachability.size() - 1); j >= 0; j -= 1) {
                if (reachability[j]) {
                    const int targetIndex = j + num;
                    if (targetIndex < reachability.size()) {
                        reachability[targetIndex] = true;
                    }
                }
            }
        }

        return reachability.back();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<int>> testCases = {
        {1,5,11,5},    // true
        {2,2,3,5},    // false
        {1,2,3,5},    // false
        {1,1,1,1},    // true
        {1,1,1,1,1},    // false
        {2,2,2,2},    // true
        {2,2,2,2,2},    // false
    };
    for (auto testCase: testCases) {
        auto result = solutionInstance.canPartition(testCase);
        std::cout << testCase << ": " << result << std::endl;
    }

    return 0;
}
