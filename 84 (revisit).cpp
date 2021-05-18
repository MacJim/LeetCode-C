/*
 * 84. Largest Rectangle in Histogram
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. 2 pointers: start from largest element, select larger element from each side (unfinished)
class Solution1 {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        size_t left = 0;
        for (size_t i = 0; i < heights.size(); i += 1) {
//            if (heights[i] > )
        }

        size_t right = left;

        return 0;
    }
};


#pragma mark - 2. Use the height of every index (revisit)
/*
 * Source: https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28902/5ms-O(n)-Java-solution-explained-(beats-96)
 *
 * We want to use the height of every index to form a rectangle.
 *
 * To find the width of heights at specific indices, we find the first elements on the left and right that is shorter than the current height.
 *
 * This find process is typically O(n), but we can re-use existing results by jumping to a smaller height if the side height is larger.
 */
// Runtime: 100 ms, faster than 93.81% of C++ online submissions for Largest Rectangle in Histogram.
// Memory Usage: 66.2 MB, less than 34.12% of C++ online submissions for Largest Rectangle in Histogram.
class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        if (heights.size() == 1) {
            return heights[0];
        }

        /// (left, right): length is `right - left - 1`.
        auto leftSmallerIndices = std::vector<int>(heights.size(), -1);
        auto rightSmallerIndices = std::vector<int>(heights.size(), heights.size());

        for (int i = 1; i < heights.size(); i += 1) {
            if (heights[i] == heights[i - 1]) {
                leftSmallerIndices[i] = leftSmallerIndices[i - 1];
            } else if (heights[i] > heights[i - 1]) {
                leftSmallerIndices[i] = i - 1;
            } else {
                // Re-use the previous results.
                int leftIndex = leftSmallerIndices[i - 1];
                while ((leftIndex != -1) && (heights[i] <= heights[leftIndex])) {
                    // Jumps to known smaller heights.
                    leftIndex = leftSmallerIndices[leftIndex];
                }
                leftSmallerIndices[i] = leftIndex;
            }
        }

        for (int i = (heights.size() - 2); i >= 0; i -= 1) {
            if (heights[i] == heights[i + 1]) {
                rightSmallerIndices[i] = rightSmallerIndices[i + 1];
            } else if (heights[i] > heights[i + 1]) {
                rightSmallerIndices[i] = i + 1;
            } else {
                // Re-use the previous results.
                int rightIndex = rightSmallerIndices[i + 1];
                while ((rightIndex != heights.size()) && (heights[i] <= heights[rightIndex])) {
                    // Jumps to known smaller heights.
                    rightIndex = rightSmallerIndices[rightIndex];
                }
                rightSmallerIndices[i] = rightIndex;
            }
        }

        int returnValue = 0;

        for (int i = 0; i < heights.size(); i += 1) {
            const int width = rightSmallerIndices[i] - leftSmallerIndices[i] - 1;
            const int size = width * heights[i];
            returnValue = std::max(returnValue, size);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& heights, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto heightsCopy = heights;
    auto result = solutionInstance.largestRectangleArea(heightsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << heights << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << heights << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({2,5,5,2,2,2}, 12);
    test({2,2,2,5,5,2}, 12);
    test({2,1,5,6,2,3}, 10);
    test({1,5,1,5,5,1}, 10);
    test({2,1,5,6,2,3,1,1,1,1,1,2,3,4}, 14);
    test({2,4}, 4);
    test({5,5,3,5}, 12);
    test({5,5,3,5,5}, 15);
    test({1,2,3,4,1,2,3,4}, 8);

    for (const int i: {1,2,3,4,5,6}) {
        test(std::vector<int>(i, i), i * i);
    }

    return 0;
}
