/*
 * 452. Minimum Number of Arrows to Burst Balloons
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort by end and find overlaps (revisit)
// Source: https://leetcode.ca/2017-02-24-452-Minimum-Number-of-Arrows-to-Burst-Balloons/
/*
 * Find out if an interval overlaps with others.
 *
 * This question is likely a reverse of 435 (which I solved on first sight).
 */
// Runtime: 124 ms, faster than 69.44% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
// Memory Usage: 34.8 MB, less than 56.30% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
class Solution {
public:
    int findMinArrowShots(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        } else if (intervals.size() == 1) {
            return 1;
        }

        std::sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            return lhs[1] < rhs[1];
        });

        int returnValue = intervals.size();
        long long minEnd = LLONG_MIN;

        for (const auto& interval: intervals) {
            if (interval[0] <= minEnd) {
                // Overlap.
                returnValue -= 1;
            } else {
                // Not overlapping. Update `minEnd`.
                minEnd = interval[1];
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& points, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto pointsCopy = points;
    auto result = solutionInstance.findMinArrowShots(pointsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << points << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << points << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1, 10}, {2, 9}, {3, 8}, {4, 7}}, 1);
    test({{10,16},{2,8},{1,6},{7,12}}, 2);
    test({{1,2},{3,4},{5,6},{7,8}}, 4);
    test({{1,2},{2,3},{3,4},{4,5}}, 2);

    return 0;
}
