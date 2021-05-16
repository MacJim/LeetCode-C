/*
 * 54. Spiral Matrix
 * https://leetcode.com/problems/spiral-matrix/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Layer by layer
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Spiral Matrix.
// Memory Usage: 6.8 MB, less than 58.56% of C++ online submissions for Spiral Matrix.
class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        auto returnValue = std::vector<int>();

        const int maxLayer = (std::min(matrix[0].size(), matrix.size()) - 1) / 2;    // Don't forget to -1.

        for (int currentLayer = 0; currentLayer <= maxLayer; currentLayer += 1) {
            const int leftX = currentLayer;
            const int rightX = matrix[0].size() - 1 - currentLayer;
            const int topY = currentLayer;
            const int bottomY = matrix.size() - 1 - currentLayer;

            for (int x = leftX; x <= rightX; x += 1) {
                returnValue.push_back(matrix[topY][x]);
            }
            if (topY == bottomY) {
                // Special case: this layer only has a rightward line.
                break;
            }
            for (int y = topY + 1; y <= bottomY; y += 1) {
                returnValue.push_back(matrix[y][rightX]);
            }
            if (leftX == rightX) {
                // Special case, this layer only has a downward line.
                break;
            }
            for (int x = rightX - 1; x >= leftX; x -= 1) {
                returnValue.push_back(matrix[bottomY][x]);
            }
            for (int y = bottomY - 1; y > topY; y -= 1) {
                returnValue.push_back(matrix[y][leftX]);
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& matrix, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto matrixCopy = matrix;
    auto result = solutionInstance.spiralOrder(matrixCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << matrix << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << matrix << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2,3},{4,5,6}}, {1,2,3,6,5,4});
    test({{1,2},{3,4},{5,6}}, {1,2,4,6,5,3});
    test({{1,2,3,4},{5,6,7,8}}, {1,2,3,4,8,7,6,5});

    test({{1}}, {1});
    test({{1,2},{3,4}}, {1,2,4,3});
    test({{1,2,3},{4,5,6},{7,8,9}}, {1,2,3,6,9,8,7,4,5});
    test({{1,2,3,4},{5,6,7,8},{9,10,11,12}}, {1,2,3,4,8,12,11,10,9,5,6,7});
    test({{1,2,3},{4,5,6},{7,8,9},{10,11,12}}, {1,2,3,6,9,12,11,10,7,4,5,8});

    return 0;
}
