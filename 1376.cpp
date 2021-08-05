/*
 * 1376. Time Needed to Inform All Employees
 * https://leetcode.com/problems/time-needed-to-inform-all-employees/
 */

#include <iostream>
#include <vector>
//#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Start from leaf nodes
// Runtime: 144 ms, faster than 97.00% of C++ online submissions for Time Needed to Inform All Employees.
// Memory Usage: 92.8 MB, less than 91.97% of C++ online submissions for Time Needed to Inform All Employees.
class Solution {
public:
    int numOfMinutes(const int n, const int headID, const std::vector<int>& manager, const std::vector<int>& informTime) {
        if (n == 1) {
            return 0;
        }

        auto upwardTimes = std::vector<int>(n, -1);

        // Find leaf nodes: they don't appear in the `manager` array.
        for (const auto& m: manager) {
            if (m != -1) {    // Note: Root is -1.
                upwardTimes[m] = 0;
            }
        }

        // Iterate over leaf nodes.
        for (int i = 0; i < n; i += 1) {
            if (upwardTimes[i] == -1) {
                // This is a leaf node.
                /// Cumulative time needed from leaf to a parent.
                int currentTime = 0;

                // Calculate cumulative time for parents.
                for (int currentManager = manager[i]; currentManager != -1; currentManager = manager[currentManager]) {
                    currentTime += informTime[currentManager];

                    auto& previousTime = upwardTimes[currentManager];
                    if (currentTime <= previousTime) {
                        // Isn't the worst case time. Ignore.
                        break;
                    }

                    // Update the worst case time.
                    previousTime = currentTime;
                }
            }
        }

        return upwardTimes[headID];
    }
};


void test(const int n, const int headID, const std::vector<int>& manager, const std::vector<int>& informTime, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.numOfMinutes(n, headID, manager, informTime);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << manager << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << manager << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(4, 2, {3,3,-1,2}, {0,0,162,914}, 1076);
    test(7, 6, {1,4,4,5,6,6,-1}, {0,6,0,0,5,12,3}, 15);
    test(1, 0, {-1}, {0}, 0);
    test(6, 2, {2,2,-1,2,2,2}, {0,0,1,0,0,0}, 1);
    test(7, 6, {1,2,3,4,5,6,-1}, {0,6,5,4,3,2,1}, 21);
    test(15, 0, {-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6}, {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}, 3);

    return 0;
}
