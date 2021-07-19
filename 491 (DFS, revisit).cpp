/*
 * 491. Increasing Subsequences
 * https://leetcode.com/problems/increasing-subsequences/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DFS, use hash table to de-duplicate (revisit)
// Runtime: 52 ms, faster than 79.29% of C++ online submissions for Increasing Subsequences.
// Memory Usage: 25.5 MB, less than 57.73% of C++ online submissions for Increasing Subsequences.
class Solution {
private:
    std::vector<std::vector<int>> returnValue = std::vector<std::vector<int>>();
    std::vector<int> currentSeq = std::vector<int>();
    std::vector<int> nums;

private:
    void recursion(size_t startIndex) {
        if (currentSeq.size() > 1) {
            returnValue.push_back(currentSeq);
        }

        if (startIndex >= nums.size()) {
            return;
        }

        /// Prevents duplicating {4,4,4,4}.
        auto existingNums = std::unordered_set<int>();
        for (size_t i = startIndex; i < nums.size(); i += 1) {
            if (existingNums.count(nums[i])) {
                // Will result in duplication.
                continue;
            }

            if (currentSeq.empty() || (nums[i] >= currentSeq.back())) {
                // Larger than the previous number.
                currentSeq.push_back(nums[i]);
                recursion(i + 1);
                currentSeq.pop_back();

                existingNums.insert(nums[i]);
            }
        }
    }

public:
    std::vector<std::vector<int>> findSubsequences(std::vector<int>& nums) {
        if (nums.size() == 1) {
            // Min length is 2.
            return {};
        }

        this->nums = std::move(nums);

        recursion(0);

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::set<std::vector<int>> expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.findSubsequences(numsCopy);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({4,6,7,7}, {{4,6},{4,6,7},{4,6,7,7},{4,7},{4,7,7},{6,7},{6,7,7},{7,7}});
    test({4,4,3,2,1}, {{4,4}});
    test({4,4,4,4}, {{4,4},{4,4,4},{4,4,4,4}});

    return 0;
}
