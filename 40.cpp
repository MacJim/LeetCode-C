/*
 * 40. Combination Sum II
 * https://leetcode.com/problems/combination-sum-ii/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <numeric>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// Runtime: 4 ms, faster than 92.47% of C++ online submissions for Combination Sum II.
// Memory Usage: 10.9 MB, less than 49.91% of C++ online submissions for Combination Sum II.
// Well the fast runtime was definitely unexpected because a stack-based solution should achieve better performance relatively easier.
class Solution {
private:
    std::vector<std::vector<int>> recursion(std::vector<int>& sortedCandidates, const int target, const size_t firstIndex) {
        if (firstIndex >= sortedCandidates.size()) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();

        int previousValue = -1;    // Should be positive. If I were using Python, I would have used `None` instead of `-1` here.
        for (size_t i = firstIndex; i < sortedCandidates.size(); i += 1) {
            const auto& value = sortedCandidates[i];
            if (value == previousValue) {
                // Don't produce duplicate results.
                continue;
            } else {
                previousValue = value;
            }

            if (value == target) {
                returnValue.push_back({target});
            } else if (value < target) {
                auto recursionResults = recursion(sortedCandidates, target - value, i + 1);
                for (auto& recursionResult: recursionResults) {
                    recursionResult.push_back(value);
                    returnValue.push_back(recursionResult);
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, const int target) {
        if (candidates.size() == 1) {
            if (candidates[0] == target) {
                return {{target}};
            } else {
                return {};
            }
        }

        const auto sum = std::accumulate(candidates.begin(), candidates.end(), 0);
        if (sum < target) {
            return {};
        } else if (sum == target) {
            return {candidates};
        }

        std::sort(candidates.begin(), candidates.end(), std::greater<>());    // Biggest number first.

//        int currentSum = candidates[0];
//        auto previousIndices = std::stack<size_t>({0});
//        while (!previousIndices.empty()) {
//            // Find the next
//        }

        auto returnValue = recursion(candidates, target, 0);

        return returnValue;
    }
};


void test(const std::vector<int>& candidates, const int target, const std::set<std::set<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto candidatesCopy = candidates;
    auto result = solutionInstance.combinationSum2(candidatesCopy, target);
    auto resultSet = std::set<std::set<int>>();
    for (const auto& tuple: result) {
        auto tupleSet = std::set(tuple.begin(), tuple.end());
        resultSet.insert(tupleSet);
    }

    if (resultSet == expectedResult) {
        std::cout << "[Correct] " << candidates << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << candidates << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5,6,7,8}, 9, {{1,8},{2,7},{3,6},{4,5},{1,2,6},{1,3,5},{2,3,4}});
    test({1,1,1,2,2,2}, 3, {{1,1,1},{1,2}});
    test({1,1,1,1,2,2,2,2}, 4, {{1,1,1,1},{1,1,2},{2,2}});

    test({10,1,2,7,6,1,5}, 8, {{1,1,6},{1,2,5},{1,7},{2,6}});
    test({2,5,2,1,2}, 5, {{1,2,2}, {5}});

    test({6}, 8, {});
    test({10}, 10, {{10}});
    test({1,9}, 10, {{1,9}});

    return 0;
}
