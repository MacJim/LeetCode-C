/*
 * 939. Minimum Area Rectangle
 * https://leetcode.com/problems/minimum-area-rectangle/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Unfinished
class Solution1 {
public:
    int minAreaRect(std::vector<std::vector<int>>& points) {
        if (points.size() < 3) {
            // Not enough points.
            return 0;
        }

        int returnValue = INT_MAX;

        auto cmp = [] (const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            return (lhs[0] * lhs[0] + lhs[1] * lhs[1]) < (rhs[0] * rhs[0] + rhs[1] * rhs[1]);
        };
        std::sort(points.begin(), points.end(), cmp);

        for (int start = 0; start < points.size(); start += 1) {
            for (int end = (points.size() - 1); end > start; end -= 1) {
                const int x0 = points[start][0];
                const int y0 = points[start][1];
                const int x1 = points[end][0];
                const int y1 = points[end][1];
            }
        }

        return (returnValue == INT_MAX) ? 0 : returnValue;
    }
};


#pragma mark - 2. Intersection on sorted sets
/*
 * Note that `std::set_intersection` can only be used on ordered sets.
 */
// Runtime: 846 ms, faster than 32.77% of C++ online submissions for Minimum Area Rectangle.
// Memory Usage: 104.7 MB, less than 14.80% of C++ online submissions for Minimum Area Rectangle.
class Solution {
public:
    int minAreaRect(std::vector<std::vector<int>>& points) {
        if (points.size() < 3) {
            // Not enough points.
            return 0;
        }

        /**
         * (y, x)
         *
         * - y is unsorted
         * - x is sorted (so that we can use `std::set_intersection`)
         */
        auto occurrences = std::unordered_map<int, std::set<int>>();
        for (const auto& p: points) {
            occurrences[p[1]].insert(p[0]);
        }

        int returnValue = INT_MAX;

        // Simply try all combinations.
        for (auto it1 = occurrences.begin(); it1 != occurrences.end(); it1 ++) {
            for (auto it2 = std::next(it1); it2 != occurrences.end(); it2 ++) {
                const int yDistance = std::abs(it2->first - it1->first);

                auto xIntersection = std::vector<int>();
                std::set_intersection(it1->second.begin(), it1->second.end(), it2->second.begin(), it2->second.end(), std::back_inserter(xIntersection));

                if (xIntersection.size() > 1) {
                    // Has a possible result.
                    for (int i = 0; i < (xIntersection.size() - 1); i += 1) {
                        const int xDistance = xIntersection[i + 1] - xIntersection[i];
                        const int currentArea = yDistance * xDistance;
                        returnValue = std::min(returnValue, currentArea);
                    }
                }
            }
        }

        return (returnValue == INT_MAX) ? 0 : returnValue;
    }
};


void test(const std::vector<std::vector<int>>& points, const int expectedResult) {
    auto solutionInstance = Solution();

    auto pointsCopy = points;
    auto result = solutionInstance.minAreaRect(pointsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << points << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << points << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,1},{1,3},{3,1},{3,3},{2,2}}, 4);
    test({{1,1},{1,3},{3,1},{3,3},{2,2},{4,2},{5,2}}, 4);
    test({{1,1},{1,3},{3,1},{3,3},{2,2},{0,1},{1,0}}, 4);
    test({{1,1},{1,3},{3,1},{3,3},{2,2},{0,1},{1,0},{3,0}}, 2);

    test({{1,1},{1,3},{3,1},{3,3},{4,1},{4,3}}, 2);

    return 0;
}
