/*
 * 39. Combination Sum
 * https://leetcode.com/problems/combination-sum/
 */

/*
 * Candidates are positive.
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Iterative (unfinished)
class Solution1 {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        auto returnValue = std::vector<std::vector<int>>();

        std::sort(candidates.begin(), candidates.end());

        int currentSum = candidates.back();
        auto its = std::vector<decltype(candidates.rbegin())>({candidates.rbegin()});

        while (!its.empty()) {
            if (currentSum == target) {
                auto nums = std::vector<int>();
                for (const auto& it: its) {
                    nums.push_back(*it);
                }
                returnValue.push_back(std::move(nums));

                auto backIt = its.back();
                its.pop_back();
                currentSum -= *backIt;
                if (backIt != candidates.rend()) {
                    backIt += 1;
                    its.push_back(backIt);
                    currentSum += *backIt;
                }
            } else if (currentSum > target) {
                auto backIt = its.back();
                its.pop_back();
                currentSum -= *backIt;
                if (backIt != candidates.rend()) {
                    backIt += 1;
                    its.push_back(backIt);
                    currentSum += *backIt;
                }
            } else {
                auto backIt = its.back();
                its.push_back(backIt);
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Recursion
// Runtime: 4 ms, faster than 95.95% of C++ online submissions for Combination Sum.
// Memory Usage: 10.7 MB, less than 96.47% of C++ online submissions for Combination Sum.
class Solution {
private:
    void combinationSumRecursively(std::vector<int>& candidates, int maxCandidateIndex, std::vector<std::vector<int>>& returnValue, std::vector<int>& previousNums, const int target) {
        for (int i = maxCandidateIndex; i >= 0; i -= 1) {
            if (candidates[i] == target) {
                previousNums.push_back(candidates[i]);

                returnValue.push_back(previousNums);

                previousNums.pop_back();
            } else if (candidates[i] < target) {
                previousNums.push_back(candidates[i]);

                combinationSumRecursively(candidates, i, returnValue, previousNums, target - candidates[i]);

                previousNums.pop_back();
            }
        }
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        auto returnValue = std::vector<std::vector<int>>();
        auto previousNums = std::vector<int>();

        std::sort(candidates.begin(), candidates.end());

        combinationSumRecursively(candidates, candidates.size() - 1, returnValue, previousNums, target);

        return returnValue;
    }
};


void test(const std::vector<int>& candidates, const int target, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto candidatesCopy = candidates;
    auto result = solutionInstance.combinationSum(candidatesCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << candidates << " " << target << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << candidates << " " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,3,6,7}, 7, {{2,2,3},{7}});
    test({2,3,5}, 8, {{2,2,2,2},{2,3,3},{3,5}});
    test({2}, 1, {});
    test({1}, 1, {{1}});
    test({1}, 2, {{1, 1}});

    return 0;
}
