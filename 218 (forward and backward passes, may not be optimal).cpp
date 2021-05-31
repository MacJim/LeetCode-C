/*
 * 218. The Skyline Problem
 * https://leetcode.com/problems/the-skyline-problem/
 */

/*
 * The `buildings` array is already sorted according to `left` -> no need for a heap.
 */

#include <iostream>
#include <vector>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Max heap + forward and backward passes
/*
 * In each pass:
 *
 * 1. Pop previous buildings in the heap
 * 2. log a height if it's larger than the largest height in the heap:
 *   1. Forward: log the new height
 *   2. Backward: log the previous height in the max heap (or 0 if the heap is empty)
 *
 * This solution may not be optimal as we may be able to sort all start and end points together.
 */
// Runtime: 44 ms, faster than 31.49% of C++ online submissions for The Skyline Problem.
// Memory Usage: 13.8 MB, less than 87.15% of C++ online submissions for The Skyline Problem.
class Solution {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
        auto returnValue = std::vector<std::vector<int>>();

        /**
         * Max heap: `lhs < rhs`.
         *
         * Sort heap according to height.
         */
        auto cmp = [] (const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
            if (lhs.first == rhs.first) {
                // Equal height.
                return lhs.second < rhs.second;
            } else {
                return lhs.first < rhs.first;
            }
        };

        // MARK: Forward pass
        /// (height, right)
        auto forwardHeap = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>(cmp);

        for (const auto& building: buildings) {
            const auto& left = building[0];
            const auto& right = building[1];
            const auto& height = building[2];

            /*
             * Pop previous buildings in the heap.
             *
             * The heap may still contain short buildings that already expired.
             * But they don't matter because they're shorter than the heap top.
             */
            if (!forwardHeap.empty()) {
                while (!forwardHeap.empty() && (forwardHeap.top().second < left)) {
                    forwardHeap.pop();
                }
            }

            if (forwardHeap.empty() || (forwardHeap.top().first < height)) {
                // An increase in height.
                // No return value is added when `forwardHeap.top().first == height`.

                // Check if `left` equals the last entry in `returnValue`.
                if (!returnValue.empty() && (returnValue.back()[0] == left)) {
                    // The same start position.
                    returnValue.back()[1] = std::max(returnValue.back()[1], height);
                } else {
                    // Add new entry to `returnValue`.
                    returnValue.push_back({left, height});
                }
            }

            // Add to heap.
            forwardHeap.emplace(height, right);
        }

        // MARK: Backward pass
        // Sort according to `right` in descending order.
        std::sort(buildings.begin(), buildings.end(), [] (const std::vector<int>& lhs, const std::vector<int>& rhs) {
            return lhs[1] > rhs[1];
        });

        /// (height, left)
        auto backwardHeap = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>(cmp);
        for (const auto& building: buildings) {
            const auto& left = building[0];
            const auto& right = building[1];
            const auto& height = building[2];

            // Pop previous buildings in the heap.
            if (!backwardHeap.empty()) {
                while (!backwardHeap.empty() && (backwardHeap.top().second > right)) {
                    backwardHeap.pop();
                }
            }

            if (backwardHeap.empty() || (backwardHeap.top().first < height)) {
                // An increase in height.
                if (backwardHeap.empty()) {
                    // Add 0 height to `returnValue`.
                    returnValue.push_back({right, 0});
                } else if (returnValue.back()[0] != right) {
                    // Add new entry to `returnValue`.
                    // Use the previous max height in the heap.
                    returnValue.push_back({right, backwardHeap.top().first});
                }
            }

            // Add to heap.
            backwardHeap.emplace(height, left);
        }

        // Sort according to value[0].
        std::sort(returnValue.begin(), returnValue.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
            return lhs[0] < rhs[0];
        });

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& buildings, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto buildingsCopy = buildings;
    auto result = solutionInstance.getSkyline(buildingsCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << buildings << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << buildings << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{0,2,3},{2,5,3}}, {{0,3},{5,0}});
    test({{0,2,3},{2,4,3},{4,6,3}}, {{0,3},{6,0}});
    test({{0,2,3},{4,5,4}}, {{0,3},{2,0},{4,4},{5,0}});
    test({{2,9,10},{2,7,15}}, {{2,15},{7,10},{9,0}});
    test({{2,9,10},{3,7,5}}, {{2,10},{9,0}});
    test({{2,9,10},{3,7,15}}, {{2,10},{3,15},{7,10},{9,0}});
    test({{2,9,10},{8,12,5}}, {{2,10},{9,5},{12,0}});
    test({{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}}, {{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}});

    return 0;
}
