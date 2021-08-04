/*
 * 1306. Jump Game III
 * https://leetcode.com/problems/jump-game-iii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. DFS + visited array
// Runtime: 44 ms, faster than 59.47% of C++ online submissions for Jump Game III.
// Memory Usage: 34.9 MB, less than 42.86% of C++ online submissions for Jump Game III.
class Solution1 {
private:
    bool recursion(const std::vector<int>& arr, std::vector<bool>& visited, const int start) {
        if (visited[start]) {
            return false;
        }
        visited[start] = true;

        const auto& currentVal = arr[start];
        if (currentVal == 0) {
            return true;
        }

        // Both neighbors.
        int leftIndex = start - currentVal;
        if (leftIndex >= 0) {
            const bool leftResult = recursion(arr, visited, leftIndex);
            if (leftResult) {
                return true;
            }
        }

        int rightIndex = start + currentVal;
        if (rightIndex < arr.size()) {
            const bool rightResult = recursion(arr, visited, rightIndex);
            if (rightResult) {
                return true;
            }
        }

        return false;
    }

public:
    bool canReach(const std::vector<int>& arr, const int start) {
        auto visited = std::vector<bool>(arr.size(), false);

        const auto returnValue = recursion(arr, visited, start);

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1: set value to negative instead of usig a visited array
// Runtime: 40 ms, faster than 78.40% of C++ online submissions for Jump Game III.
// Memory Usage: 34 MB, less than 54.02% of C++ online submissions for Jump Game III.
class Solution {
private:
    bool recursion(std::vector<int>& arr, const int start) {
        auto& currentVal = arr[start];

        if (currentVal < 0) {
            // Negative value: visited
            return false;
        } else if (currentVal == 0) {
            return true;
        }

        // Set to negative to mark as visited.
        // Must set before visiting left and right neighbors.
        currentVal = -currentVal;

        // Both neighbors.
        int leftIndex = start + currentVal;    // Plus because `currentVal` is now negative.
        if (leftIndex >= 0) {
            const bool leftResult = recursion(arr, leftIndex);
            if (leftResult) {
                return true;
            }
        }

        int rightIndex = start - currentVal;    // Minus because `currentVal` is now negative.
        if (rightIndex < arr.size()) {
            const bool rightResult = recursion(arr, rightIndex);
            if (rightResult) {
                return true;
            }
        }

        return false;
    }

public:
    bool canReach(std::vector<int>& arr, const int start) {
        const auto returnValue = recursion(arr, start);

        return returnValue;
    }
};


void test(const std::vector<int>& arr, const int start, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto arrCopy = arr;
    auto result = solutionInstance.canReach(arrCopy, start);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << arr << ", " << start << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << arr << ", " << start << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,1}, 0, true);
    test({0,1}, 1, true);
    test({0,2,1}, 0, true);
    test({0,2,1}, 1, false);
    test({0,2,1}, 2, false);
    test({4,2,3,0,3,1,2}, 5, true);
    test({4,2,3,0,3,1,2}, 0, true);
    test({3,0,2,1,2}, 2, false);

    return 0;
}
