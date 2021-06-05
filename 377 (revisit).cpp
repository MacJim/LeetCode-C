/*
 * 377. Combination Sum IV
 * https://leetcode.com/problems/combination-sum-iv/
 */

/*
 * - Can use the same number multiple times
 * - Numbers are all positive because if we have negative numbers, there can be an infinite amount of solutions if some of them sum up to 0
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Recursion
// WRONG ANSWER: the program doesn't take different permutations into account.
class Solution1 {
private:
    int recursion(const std::vector<int>& nums, const size_t startIndex, const int target) {
        if (target == 0) {
            return 1;
        }
        if (startIndex == nums.size()) {
            return 0;
        }

        int returnValue = 0;

        const auto& currentNum = nums[startIndex];

        int remainingValue = target;    // Don't subtract `currentNum` for the first pass.
        while (remainingValue >= 0) {
            auto subResult = recursion(nums, startIndex + 1, remainingValue);
            returnValue += subResult;
            remainingValue -= currentNum;
        }

        return returnValue;
    }

public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end(), std::greater<>());

        auto result = recursion(nums, 0, target);

        return result;
    }
};


#pragma mark - 2. Factorials
// WRONG: Factorials can't deal with duplicate numbers.
class Solution2 {
private:
    std::vector<int> recursion(const std::vector<int>& nums, const size_t startIndex, const int target) {
        if (target == 0) {
            return {1};
        }
        if (startIndex == nums.size()) {
            return {};
        }

        auto returnValue = std::vector<int>();

        const auto& currentNum = nums[startIndex];

        int remainingValue = target;    // Don't subtract `currentNum` for the first pass.
        while (remainingValue >= 0) {
            auto subLengths = recursion(nums, startIndex + 1, remainingValue);
            for (auto& length: subLengths) {
                length += 1;
            }

            returnValue.insert(returnValue.end(), subLengths.begin(), subLengths.end());

            remainingValue -= currentNum;
        }

        return returnValue;
    }

public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end(), std::greater<>());

        auto resultLengths = recursion(nums, 0, target);

        return 0;
    }
};


#pragma mark - 3. Fixed 1
// Time Limit Exceeded.
/*
 * Use use the original order, no need to sort.
 */
class Solution3 {
private:
    int recursion(const std::vector<int>& nums, const int target) {
        if (target == 0) {
            return 1;
        }

        int returnValue = 0;

        for (const auto& num: nums) {
            const int remainingTarget = target - num;
            if (remainingTarget == 0) {
                returnValue += 1;
            } else if (remainingTarget > 0) {
                const int subResult = recursion(nums, remainingTarget);
                returnValue += subResult;
            }
        }

        return returnValue;
    }

public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        auto resultLengths = recursion(nums, target);

        return resultLengths;
    }
};


#pragma mark - 4. 3, but using a stack
// Time Limit Exceeded
class Solution4 {
public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        int returnValue = 0;

        int currentTarget = target - nums[0];
        auto currentNums = std::stack<size_t>({0});

        while (!currentNums.empty()) {
            if (currentTarget > 0) {
                currentNums.push(0);
                currentTarget -= nums[0];
            } else {
                if (currentTarget == 0) {
                    returnValue += 1;
                }

                while (!currentNums.empty() && (currentNums.top() == (nums.size() - 1))) {
                    currentTarget += nums[currentNums.top()];
                    currentNums.pop();
                }

                if (currentNums.empty()) {
                    break;
                } else {
                    const size_t nextIndex = currentNums.top() + 1;

                    currentTarget += nums[currentNums.top()];
                    currentNums.pop();

                    currentNums.push(nextIndex);
                    currentTarget -= nums[nextIndex];
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 5. Improved 3 by sorting and breaking early
// Time Limit Exceeded
class Solution5 {
private:
    int recursion(const std::vector<int>& nums, const int target) {
        if (target == 0) {
            return 1;
        }

        int returnValue = 0;

        for (const auto& num: nums) {
            const int remainingTarget = target - num;
            if (remainingTarget > 0) {
                const int subResult = recursion(nums, remainingTarget);
                returnValue += subResult;
            } else {
                if (remainingTarget == 0) {
                    returnValue += 1;
                }

                break;
            }
        }

        return returnValue;
    }

public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end());

        auto resultLengths = recursion(nums, target);

        return resultLengths;
    }
};


#pragma mark - 6. DP: traverse from 1 to target (revisit)
// Source: https://leetcode.ca/2016-12-11-377-Combination-Sum-IV/
class Solution {
public:
    int combinationSum4(std::vector<int>& nums, const int target) {
        std::sort(nums.begin(), nums.end());

        auto dp = std::vector<int>(target + 1, 0);
//        dp[0] = 1;    // dp[0] will be unused.

        for (int currentTarget = 1; currentTarget <= target; currentTarget += 1) {
            for (const auto& num: nums) {
                if (num > currentTarget) {
                    break;
                } else if (num == currentTarget) {
                    dp[currentTarget] += 1;
                } else {
                    const auto delta = currentTarget - num;
                    dp[currentTarget] += dp[delta];
                }
            }
        }

        return dp.back();
    }
};


void test(const std::vector<int>& nums, const int target, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.combinationSum4(numsCopy, target);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ", " << target << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ", " << target << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({9}, 3, 0);
    test({3,6}, 9, 3);
    test({1,2,3}, 4, 7);
    test({1,2,3,4}, 4, 8);
    test({1,2,3}, 32, 181997601);
    test({4,2,1}, 32, 39882198);
    test({10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,111}, 999, 0);

    return 0;
}
