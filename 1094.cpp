/*
 * 1094. Car Pooling
 * https://leetcode.com/problems/car-pooling/
 */

#include <iostream>
#include <vector>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Heap
// Runtime: 12 ms, faster than 68.53% of C++ online submissions for Car Pooling.
// Memory Usage: 9.4 MB, less than 88.18% of C++ online submissions for Car Pooling.
class Solution {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity) {
        if (trips.empty()) {
            return true;
        }

        // Sort by start positions.
        std::sort(trips.begin(), trips.end(), [] (const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            return lhs[1] < rhs[1];
        });

        // Sort bus by end positions.
        auto queueCmp = [] (const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            return lhs[2] > rhs[2];    // Remember that vector and heap sorting algorithms are reversed.
        };
        auto bus = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(queueCmp)>(queueCmp);

        for (auto& trip: trips) {
            // Disembark.
            while ((!bus.empty()) && (bus.top()[2] <= trip[1])) {
                capacity += bus.top()[0];
                bus.pop();
            }

            // Embark.
            capacity -= trip[0];
            if (capacity < 0) {
                return false;
            }

            bus.push(std::move(trip));
        }

        return true;
    }
};


#pragma mark - 2. Log each stop
/*
 * We know that we have at most 1001 stops.
 *
 * Log the embark/disembark difference at each stop.
 * If any difference is larger than `capacity`, return `false`.
 */


void test(const std::vector<std::vector<int>>& trips, const int capacity, const int expectedResult) {
    auto solutionInstance = Solution();

    auto tripsCopy = trips;
    auto result = solutionInstance.carPooling(tripsCopy, capacity);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << trips << ", " << capacity << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << trips << ", " << capacity << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{3,2,7},{3,7,9},{8,3,9}}, 11, true);
    test({{2,1,5},{3,3,7}}, 4, false);
    test({{2,1,5},{3,3,7}}, 5, true);
    test({{2,1,5},{3,5,7}}, 3, true);

    return 0;
}
