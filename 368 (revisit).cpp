/*
 * 368. Largest Divisible Subset
 * https://leetcode.com/problems/largest-divisible-subset/
 */

/*
 * - 1 is special and goes with everyone
 * - Find a common multiplier? No
 * - 2^n solution is impractical: max length is 1000
 * - Use bigger number to % smaller number
 * - Sorting is necessary: There are unordered test cases
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Maintain result candidates (unfinished)
// WRONG ANSWER because some elements may get missed when you add previous numbers.
class Solution1 {
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums;
        }

        std::sort(nums.begin(), nums.end());

        auto resultCandidates = std::vector<std::vector<int>>();

        for (const auto& num: nums) {
            bool candidateFound = false;
            for (auto& candidate: resultCandidates) {

            }

            if (!candidateFound) {
                resultCandidates.push_back({num});
            }
        }

        return {};
    }
};


#pragma mark - 2. Recursion
// Time Limit Exceeded
class Solution2 {
private:
    std::vector<int> recursion(const std::vector<int>& nums, size_t startIndex, std::vector<int>& currentNums) {
        if (startIndex >= nums.size()) {
            return currentNums;
        }

        int dividend = 1;
        if (!currentNums.empty()) {
            dividend = currentNums.back();
        }

        auto returnValue = currentNums;

        for (size_t i = startIndex; i < nums.size(); i += 1) {
            const auto& num = nums[i];
            if (num % dividend == 0) {
                currentNums.push_back(num);
                auto currentResult = recursion(nums, i + 1, currentNums);
                currentNums.pop_back();

                if (currentResult.size() > returnValue.size()) {
                    returnValue = currentResult;
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums;
        }

        std::sort(nums.begin(), nums.end());

        auto tempVec = std::vector<int>();

        auto returnValue = recursion(nums, 0, tempVec);

        return returnValue;
    }
};


#pragma mark - 3. Optimized 2 with cache
/*
 * This solution actually returns the numbers in reverse order.
 */
// Runtime: 96 ms, faster than 5.27% of C++ online submissions for Largest Divisible Subset.
// Memory Usage: 15.9 MB, less than 5.05% of C++ online submissions for Largest Divisible Subset.
class Solution3 {
private:
    /// Suffix cache.
    std::unordered_map<int, std::vector<int>> resultsCache;

public:
    Solution3() {
        resultsCache = std::unordered_map<int, std::vector<int>>();
    }

private:
    /// Returns the suffix instead of the full return value.
    std::vector<int> recursion(const std::vector<int>& nums, size_t startIndex, const int dividend) {
        if (startIndex >= nums.size()) {
            return {};
        }

        auto returnValue = std::vector<int>();

        if (resultsCache.count(dividend)) {
            const auto& cachedResult = resultsCache[dividend];
            returnValue.insert(returnValue.end(), cachedResult.begin(), cachedResult.end());
            return returnValue;
        }

        for (size_t i = startIndex; i < nums.size(); i += 1) {
            const auto& num = nums[i];
            if (num % dividend == 0) {
                auto currentResult = recursion(nums, i + 1, num);
                currentResult.push_back(num);

                if (currentResult.size() > returnValue.size()) {
                    returnValue = currentResult;
                }
            }
        }

        resultsCache[dividend] = returnValue;

        return returnValue;
    }

public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums;
        }

        std::sort(nums.begin(), nums.end());

        auto tempVec = std::vector<int>();

        auto returnValue = recursion(nums, 0, 1);

        return returnValue;
    }
};


#pragma mark - 4. DP + log sequence (revisit)
/*
 * Source: https://leetcode.ca/2016-12-02-368-Largest-Divisible-Subset/
 *
 * O(n^2) time.
 *
 * 1. Sort the array so that we can just do `later element % earlier element`
 * 2. Log the max subset size and next number of numbers [0, n]
 *
 * The "log next number" part is somewhat like the solution 2 ("jumping" solution) of problem 84.
 */
// Runtime: 36 ms, faster than 79.35% of C++ online submissions for Largest Divisible Subset.
// Memory Usage: 8.8 MB, less than 28.66% of C++ online submissions for Largest Divisible Subset.
class Solution {
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums;
        }

        std::sort(nums.begin(), nums.end());

        /**
         * Max subset size ending at current index.
         *
         * Of course the min length is 1.
         */
        auto lengths = std::vector<int>(nums.size(), 1);
        /// The next number in the max sequence.
        auto parents = std::vector<int>(nums.size(), 0);

        int maxLength = 0;
        int maxIndex = 0;

        // Back to front. I think front to back also works.
        for (int current = (nums.size() - 1); current >= 0; current -= 1) {
            for (int right = (current + 1); right < nums.size(); right += 1) {
                if ((nums[right] % nums[current] == 0) && (lengths[current] < (lengths[right] + 1))) {
                    lengths[current] = lengths[right] + 1;
                    parents[current] = right;
                }
            }

            if (maxLength < lengths[current]) {
                maxLength = lengths[current];
                maxIndex = current;
            }
        }

        // Return value: start from `maxLength` and `maxIndex`.
        auto returnValue = std::vector<int>();
        for (int i = 0; i < maxLength; i += 1) {
            returnValue.push_back(nums[maxIndex]);
            maxIndex = parents[maxIndex];
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::set<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.largestDivisibleSubset(numsCopy);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3}, {1,2});
    test({1,2,4,8}, {1,2,4,8});
    test({1,2,4,9}, {1,2,4});
    test({1,4,8,12,16}, {1,4,8,16});
    test({1,4,8,12,36}, {1,4,12,36});
    test({1,16,7,8,4}, {1,4,8,16});
    test({2,4,8}, {2,4,8});
    test({2,4,9}, {2,4});

    return 0;
}
