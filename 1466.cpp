/*
 * 1466. Reorder Routes to Make All Paths Lead to the City Zero
 * https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Somewhat like disjoint set
// Runtime: 156 ms, faster than 99.64% of C++ online submissions for Reorder Routes to Make All Paths Lead to the City Zero.
// Memory Usage: 58.7 MB, less than 99.76% of C++ online submissions for Reorder Routes to Make All Paths Lead to the City Zero.
class Solution {
public:
    int minReorder(int n, std::vector<std::vector<int>>& connections) {
        auto visited = std::vector<bool>(n, false);
        visited[0] = true;

        int returnValue = 0;

        bool cityRemaining = true;
        while (cityRemaining) {
            cityRemaining = false;

            for (const auto& connection: connections) {
                if (!visited[connection[1]]) {
                    if (visited[connection[0]]) {
                        // This is reversed.
                        returnValue += 1;
                        visited[connection[1]] = true;
                    } else {
                        cityRemaining = true;
                    }
                } else {
                    visited[connection[0]] = true;
                }
            }
        }

        return returnValue;
    }
};


void test(const int n, const std::vector<std::vector<int>>& connections, const int expectedResult) {
    auto solutionInstance = Solution();

    auto connectionsCopy = connections;
    auto result = solutionInstance.minReorder(n, connectionsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << n << ", " << connections << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << n << ", " << connections << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(3, {{1,0},{2,0}}, 0);
    test(5, {{1,0},{1,2},{3,2},{3,4}}, 2);
    test(6, {{0,1},{1,3},{2,3},{4,0},{4,5}}, 3);

    return 0;
}
