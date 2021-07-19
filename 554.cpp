/*
 * 554. Brick Wall
 * https://leetcode.com/problems/brick-wall/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Count occurrences
// Runtime: 40 ms, faster than 88.81% of C++ online submissions for Brick Wall.
// Memory Usage: 21.8 MB, less than 38.41% of C++ online submissions for Brick Wall.
class Solution {
public:
    int leastBricks(const std::vector<std::vector<int>>& wall) {
        // Handled by the `occurrences.empty()` case.
//        if (wall.size() == 1) {
//            if (wall[0].size() == 1) {
//                return 1;
//            } else {
//                return 0;
//            }
//        }

        auto occurrences = std::unordered_map<int, int>();

        for (const auto& layer: wall) {
            int x = 0;
            for (size_t i = 0; i < (layer.size() - 1); i += 1) {    // Ignore the final brick.
                const auto& width = layer[i];
                x += width;
                occurrences[x] += 1;
            }
        }

        if (occurrences.empty()) {
            // Edge case: all bricks are at full width (no edges at all, must pass through all bricks).
            return wall.size();
        }

//        int optimalX = -1;
        int maxOccurrence = -1;

        for (const auto& [x, occurrence]: occurrences) {
            if (occurrence > maxOccurrence) {
//                optimalX = x;
                maxOccurrence = occurrence;
            }
        }

        return wall.size() - maxOccurrence;
    }
};


void test(const std::vector<std::vector<int>>& wall, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.leastBricks(wall);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << wall << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << wall << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1}}, 2);
    test({{1},{1},{1}}, 3);

    return 0;
}
