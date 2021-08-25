/*
 * 436. Find Right Interval
 * https://leetcode.com/problems/find-right-interval/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort according to start and end
// Runtime: 72 ms, faster than 68.14% of C++ online submissions for Find Right Interval.
// Memory Usage: 24.3 MB, less than 93.17% of C++ online submissions for Find Right Interval.
class Solution1 {
public:
    std::vector<int> findRightInterval(const std::vector<std::vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return {-1};
        }

        auto startIndices = std::vector<int>(intervals.size(), 0);
        for (int i = 0; i < intervals.size(); i += 1) {
            startIndices[i] = i;
        }

        auto endIndices = startIndices;

        // Sort according to start and end indices.
        auto cmpStart = [&intervals] (const int& lhs, const int& rhs) -> bool {
            // Start positions are unique.
            // Smaller first.
            return intervals[lhs][0] < intervals[rhs][0];
        };
        std::sort(startIndices.begin(), startIndices.end(), cmpStart);

        auto cmpEnd = [&intervals] (const int& lhs, const int& rhs) -> bool {
            // End positions are not unique.
            // Bigger first.
            const auto& lEnd = intervals[lhs][1];
            const auto& rEnd = intervals[rhs][1];

            if (lEnd == rEnd) {
                return intervals[lhs][0] > intervals[rhs][0];
            } else {
                return lEnd > rEnd;
            }
        };
        std::sort(endIndices.begin(), endIndices.end(), cmpEnd);

        auto returnValue = std::vector<int>(intervals.size(), -1);
        // For each start index.
        for (const int startIndex: startIndices) {
            const int& startValue = intervals[startIndex][0];

            while ((!endIndices.empty()) && (intervals[endIndices.back()][1] <= startValue)) {
                returnValue[endIndices.back()] = startIndex;
                endIndices.pop_back();
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Sort and binary search
// This seems to be the official solution.
// Runtime: 64 ms, faster than 84.19% of C++ online submissions for Find Right Interval.
// Memory Usage: 23.7 MB, less than 99.40% of C++ online submissions for Find Right Interval.
class Solution {
public:
    std::vector<int> findRightInterval(const std::vector<std::vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return {-1};
        }

        auto startIndices = std::vector<int>(intervals.size(), 0);
        for (int i = 0; i < intervals.size(); i += 1) {
            startIndices[i] = i;
        }

        // Sort according to start indices.
        auto cmpStart = [&intervals] (const int& lhs, const int& rhs) -> bool {
            // Start positions are unique.
            // Smaller first.
            return intervals[lhs][0] < intervals[rhs][0];
        };
        std::sort(startIndices.begin(), startIndices.end(), cmpStart);

        auto returnValue = std::vector<int>(intervals.size(), -1);
        // Binary search for leftmost element.
        for (int i = 0; i < intervals.size(); i += 1) {
            const int& currentEnd = intervals[i][1];

            int left = 0;
            int right = intervals.size();    // Can be out of bounds.

            while (left < right) {    // Terminates when left == right
                int mid = (left + right) / 2;
                if (intervals[startIndices[mid]][0] >= currentEnd) {
                    right = mid;
                } else {
                    // Note +1 here: Add 1 so that we can return the correct `left`.
                    left = mid + 1;
                }
            }

            if (left != intervals.size()) {
                // It exists if it's not out of bounds.
                returnValue[i] = startIndices[left];
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& intervals, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findRightInterval(intervals);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << intervals << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << intervals << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2}}, {-1});
    test({{3,4},{2,3},{1,2}}, {-1,0,1});
    test({{1,4},{2,3},{3,4}}, {-1,2,-1});

    return 0;
}
