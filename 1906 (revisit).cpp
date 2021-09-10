/*
 * 1906. Minimum Absolute Difference Queries
 * https://leetcode.com/problems/minimum-absolute-difference-queries/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <array>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// Not sure if there are duplicate queries.
class Solution1 {
private:
    static constexpr int QUERIES_HASH_START_MULTIPLIER = 20001;    // start * multiplier + end

public:
    std::vector<int> minDifference(const std::vector<int>& nums, const std::vector<std::vector<int>>& queries) {
        // Put queries into a hash table to speed up look-up.
        /// (start * multiplier + end, index)
        auto queriesHash = std::unordered_map<int, size_t>();
        for (size_t i = 0; i < queries.size(); i += 1) {
            const auto& q = queries[i];
            const int key = q[0] * QUERIES_HASH_START_MULTIPLIER + q[1];
            queriesHash[key] = i;
        }

        return {};
    }
};


#pragma mark - 2. Log each query's min and max
// WRONG ANSWER: We want the min delta instead of the max delta!
class Solution2 {
public:
    std::vector<int> minDifference(const std::vector<int>& nums, const std::vector<std::vector<int>>& queries) {
        // Sort the queries according to end positions.
        auto queryOrder = std::vector<size_t>(queries.size(), 0);
        for (size_t i = 1; i < queryOrder.size(); i += 1) {
            queryOrder[i] = i;
        }

        auto cmp = [&queries] (const size_t& lhs, const size_t& rhs) -> bool {
            return queries[lhs][1] < queries[rhs][1];
        };
        std::sort(queryOrder.begin(), queryOrder.end(), cmp);

        // Log min and max values for each query.
        auto minValues = std::vector<int>(queries.size(), INT_MAX);
        auto maxValues = std::vector<int>(queries.size(), INT_MIN);

        /// Entries before `queryOrderStart` in `queryOrder` are ignored.
//        size_t queryOrderStart = 0;
        for (size_t numIndex = 0; numIndex < nums.size(); numIndex += 1) {
            // Find eligible queries.
            for (size_t i = 0; i < queryOrder.size(); i += 1) {
                const auto& currentQuery = queries[queryOrder[i]];
                if ((currentQuery[0] >= numIndex) && (numIndex <= currentQuery[1])) {
                    // Eligible.
                    minValues[i] = std::min(minValues[i], nums[numIndex]);
                    maxValues[i] = std::max(maxValues[i], nums[numIndex]);
                }
            }
        }

        // Assign returnValue.
        auto returnValue = std::vector<int>(queries.size(), -1);
        for (size_t i = 0; i < queryOrder.size(); i += 1) {
            int currentValue = maxValues[i] - minValues[i];
            if (currentValue == 0) {
                currentValue = -1;
            }

            returnValue[queryOrder[i]] = currentValue;
        }

        return returnValue;
    }
};


#pragma mark - 3. Prefix sum of all numbers' occurrences (revisit)
// Source: https://leetcode.com/problems/minimum-absolute-difference-queries/discuss/1284212/Python-Cumulative-sums-solution-%2B-2Liner-explained
// Runtime: 595 ms, faster than 65.72% of C++ online submissions for Minimum Absolute Difference Queries.
// Memory Usage: 275.3 MB, less than 43.63% of C++ online submissions for Minimum Absolute Difference Queries.
class Solution {
public:
    std::vector<int> minDifference(const std::vector<int>& nums, const std::vector<std::vector<int>>& queries) {
        /// `currentOccurrences[i]` is the occurrence of `i`. `currentOccurrences[0]` is unused.
        auto currentOccurrences = std::array<int, 101>();

        /// `prefixes[0]` is an all 0 array.
        auto prefixes = std::vector<std::array<int, 101>>(1);
        prefixes.reserve(nums.size() + 1);

        for (const int& num: nums) {
            currentOccurrences[num] += 1;
            prefixes.push_back(currentOccurrences);
        }

        auto returnValue = std::vector<int>(queries.size(), INT_MAX);
        // Use prefix sum within the query interval.
        for (int i = 0; i < queries.size(); i += 1) {
            const int& start = queries[i][0];
            const int end = queries[i][1] + 1;    // Note +1 to the prefix sum index.

            int previousNum = 0;
            for (int num = 1; num < 101; num += 1) {
                const int delta = prefixes[end][num] - prefixes[start][num];
                if (delta) {
                    // This number exists between the interval.
                    if (previousNum) {
                        // We only need to calculate the delta between the nearest numbers: `num` and `previousNum`.
                        returnValue[i] = std::min(returnValue[i], num - previousNum);
                    }

                    previousNum = num;
                }
            }

            if (returnValue[i] == INT_MAX) {
                // All numbers are the same.
                returnValue[i] = -1;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<std::vector<int>>& queries, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.minDifference(nums, queries);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ", " << queries << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ", " << queries << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,4,8}, {{0,1},{1,2},{2,3},{0,3}}, {2,1,4,1});
    test({4,5,2,2,7,10}, {{2,3},{0,2},{0,5},{3,5}}, {-1,1,1,3});
    return 0;
}
