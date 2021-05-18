/*
 * 90. Subsets II
 * https://leetcode.com/problems/subsets-ii/
 */

#include <iostream>
#include <vector>
#include <set>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// Runtime: 4 ms, faster than 72.39% of C++ online submissions for Subsets II.
// Memory Usage: 7.7 MB, less than 61.53% of C++ online submissions for Subsets II.
class Solution {
private:
    void recursion(std::vector<std::vector<int>>& returnValue, const std::vector<int>& nums, size_t startIndex, std::vector<int> previousStreak) {
        if (startIndex == nums.size()) {
            return;
        }

        int previousValue = INT_MAX;    // Prevent duplicate results.
        for (size_t i = startIndex; i < nums.size(); i += 1) {
            const auto& currentValue = nums[i];
            if (currentValue == previousValue) {
                // Prevent duplicate results.
                continue;
            } else {
                previousValue = currentValue;
            }

            previousStreak.push_back(currentValue);
            returnValue.push_back(previousStreak);

            recursion(returnValue, nums, i + 1, previousStreak);

            previousStreak.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {{}, nums};
        }

        std::sort(nums.begin(), nums.end());

        auto returnValue = std::vector<std::vector<int>>({{}});

        recursion(returnValue, nums, 0, {});

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::set<std::set<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.subsetsWithDup(numsCopy);
    auto resultSet = std::set<std::set<int>>();
    for (const auto& r: result) {
        resultSet.insert(std::set<int>(r.begin(), r.end()));
    }

    if (resultSet == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,2}, {{},{1},{1,2},{1,2,2},{2},{2,2}});
    test({0}, {{}, {0}});
    test({1,1,2,2}, {{},{1},{2},{1,1},{1,2},{2,2},{1,1,2},{1,2,2},{1,1,2,2}});
    test({4,4,4,1,4}, {{},{1},{1,4},{1,4,4},{1,4,4,4},{1,4,4,4,4},{4},{4,4},{4,4,4},{4,4,4,4}});

    return 0;
}
