/*
 * 1710. Maximum Units on a Truck
 * https://leetcode.com/problems/maximum-units-on-a-truck/
 */

#include <iostream>
#include <vector>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort
// Runtime: 40 ms, faster than 68.46% of C++ online submissions for Maximum Units on a Truck.
// Memory Usage: 16 MB, less than 76.24% of C++ online submissions for Maximum Units on a Truck.
class Solution {
public:
    int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
        if (boxTypes.size() == 1) {
            return std::min(boxTypes.front()[0], truckSize) * boxTypes.front()[1];
        }

        auto cmp = [] (const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            return lhs[1] > rhs[1];    // Note that vector and priority_queue comparisons are reversed.
        };
        std::sort(boxTypes.begin(), boxTypes.end(), cmp);

        int returnValue = 0;
        for (const auto& box: boxTypes) {
            const auto& boxCount = box[0];
            const auto& units = box[1];
            if (boxCount >= truckSize) {
                returnValue += truckSize * units;
                break;
            }

            returnValue += boxCount * units;
            truckSize -= boxCount;
        }

        return returnValue;
    }
};


#pragma mark - 2. Heap
// Runtime: 64 ms, faster than 31.82% of C++ online submissions for Maximum Units on a Truck.
// Memory Usage: 19.3 MB, less than 24.39% of C++ online submissions for Maximum Units on a Truck.
class Solution2 {
public:
    int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
        if (boxTypes.size() == 1) {
            return std::min(boxTypes.front()[0], truckSize) * boxTypes.front()[1];
        }

        auto cmp = [] (const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            return lhs[1] < rhs[1];    // Note that vector and priority_queue comparisons are reversed.
        };
        auto queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(cmp)>(boxTypes.begin(), boxTypes.end(), cmp);

        int returnValue = 0;
        while (!queue.empty()) {
            auto top = queue.top();
            if (top[0] >= truckSize) {
                returnValue += truckSize * top[1];
                break;
            }

            returnValue += top[0] * top[1];
            truckSize -= top[0];
            queue.pop();
        }

        return returnValue;
    }
};


#pragma mark - 3. Optimize 1: Don't sort in place; instead, sort results in a temporary 1000 element long vector (we know that unit counts are at most 1000)


void test(const std::vector<std::vector<int>>& boxTypes, int truckSize, const int expectedResult) {
    auto solutionInstance = Solution();

    auto boxTypesCopy = boxTypes;
    auto result = solutionInstance.maximumUnits(boxTypesCopy, truckSize);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << boxTypes << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << boxTypes << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,3},{2,2},{3,1}}, 4, 8);
    test({{5,10},{2,5},{4,7},{3,9}}, 10, 91);
    test({{100,3}}, 10, 30);
    test({{5,3}}, 10, 15);

    return 0;
}
