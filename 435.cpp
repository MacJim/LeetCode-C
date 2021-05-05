/*
 * 435. Non-overlapping Intervals
 * https://leetcode.com/problems/non-overlapping-intervals/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort by end time
// Runtime: 16 ms, faster than 55.77% of C++ online submissions for Non-overlapping Intervals.
// Memory Usage: 10.2 MB, less than 52.16% of C++ online submissions for Non-overlapping Intervals.
class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return 0;
        }

        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
            if (lhs[1] == rhs[1]) {
                // If end times equal, sort by start time.
                // Actually I think this is not needed because a large start time will simply be ignored.
                return lhs[0] > rhs[0];
            } else {
                // First, sort by end time.
                return lhs[1] < rhs[1];
            }
        });

        int usedIntervals = 0;

        int currentEnd = INT_MIN;

        for (const auto& interval: intervals) {
            if (interval[0] >= currentEnd) {
                usedIntervals += 1;
                currentEnd = interval[1];
            }
        }

        return intervals.size() - usedIntervals;
    }
};


void test(const std::vector<std::vector<int>>& intervals, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto intervalsCopy = intervals;
    auto result = solutionInstance.eraseOverlapIntervals(intervalsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << intervals << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << intervals << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{2,3},{3,4},{-100,-2},{5,7}}, 0);
    test({{1,2},{2,3},{3,4},{1,3}}, 1);
    test({{1,2},{1,2},{1,2}}, 2);
    test({{1,2},{2,3}}, 0);
    test({{1,2},{2,3},{2,3},{3,4},{1,3}}, 2);

    return 0;
}
