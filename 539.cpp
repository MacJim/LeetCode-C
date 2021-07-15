/*
 * 539. Minimum Time Difference
 * https://leetcode.com/problems/minimum-time-difference/
 */

#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort
// Runtime: 12 ms, faster than 86.27% of C++ online submissions for Minimum Time Difference.
// Memory Usage: 13.3 MB, less than 89.18% of C++ online submissions for Minimum Time Difference.
class Solution {
private:
    /**
     *
     * @param t1 The smaller time string.
     * @param t2 The bigger time string.
     * @return Positive interval.
     */
    inline int getInterval(const std::string& t1, const std::string& t2) {
        int returnValue = 0;

        returnValue += 10 * 60 * (t2[0] - t1[0]);
        returnValue += 60 * (t2[1] - t1[1]);
        returnValue += 10 * (t2[3] - t1[3]);
        returnValue += (t2[4] - t1[4]);

        return returnValue;
    }

public:
    int findMinDifference(std::vector<std::string>& timePoints) {
        std::sort(timePoints.begin(), timePoints.end());

        int returnValue = INT_MAX;

        // Linear scan: get adjacent intervals.
        for (size_t i = 1; i < timePoints.size(); i += 1) {
            const int interval = getInterval(timePoints[i - 1], timePoints[i]);
            returnValue = std::min(returnValue, interval);
        }

        // Front and back.
        const int lastInterval = 24 * 60 - getInterval(timePoints.front(), timePoints.back());
        returnValue = std::min(returnValue, lastInterval);

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
/*
 * Convert time strings to integers before sorting.
 * This way, we can subtract times directly.
 */


void test(const std::vector<std::string>& timePoints, const int expectedResult) {
    auto solutionInstance = Solution();

    auto timePointsCopy = timePoints;
    auto result = solutionInstance.findMinDifference(timePointsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << timePoints << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << timePoints << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({"23:59","00:00"}, 1);
    test({"00:00","23:59","00:00"}, 0);

    return 0;
}
