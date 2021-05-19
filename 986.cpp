/*
 * 986. Interval List Intersections
 * https://leetcode.com/problems/interval-list-intersections/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Alternation
// Runtime: 24 ms, faster than 97.84% of C++ online submissions for Interval List Intersections.
// Memory Usage: 18.5 MB, less than 99.25% of C++ online submissions for Interval List Intersections.
class Solution {
public:
    std::vector<std::vector<int>> intervalIntersection(std::vector<std::vector<int>>& firstList, std::vector<std::vector<int>>& secondList) {
        if (firstList.empty() || secondList.empty()) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();

        size_t i1 = 0;
        size_t i2 = 0;

        while ((i1 < firstList.size()) && (i2 < secondList.size())) {
            const auto& tuple1 = firstList[i1];
            const auto& tuple2 = secondList[i2];

            auto start = std::max(tuple1[0], tuple2[0]);
            auto end = std::min(tuple1[1], tuple2[1]);
            if (end >= start) {
                returnValue.push_back({start, end});
            }

            if (tuple1[1] < tuple2[1]) {
                i1 += 1;
            } else {
                i2 += 1;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& firstList, const std::vector<std::vector<int>>& secondList, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto firstListCopy = firstList;
    auto secondListCopy = secondList;

    auto result = solutionInstance.intervalIntersection(firstListCopy, secondListCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << firstList << ", " << secondList << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << firstList << ", " << secondList << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{0,2},{5,10},{13,23},{24,25}}, {{1,5},{8,12},{15,24},{25,26}}, {{1,2},{5,5},{8,10},{15,23},{24,24},{25,25}});
    test({{1,3},{5,9}}, {}, {});
    test({}, {{4,8},{10,12}}, {});
    test({{1,7}}, {{3,10}}, {{3,7}});

    return 0;
}
