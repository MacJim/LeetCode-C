/*
 * 498. Diagonal Traverse
 * https://leetcode.com/problems/diagonal-traverse/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 28 ms, faster than 74.59% of C++ online submissions for Diagonal Traverse.
// Memory Usage: 18.3 MB, less than 59.46% of C++ online submissions for Diagonal Traverse.
class Solution {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat) {
        const auto height = mat.size();
        const auto width = mat[0].size();

        auto returnValue = std::vector<int>({mat[0][0]});

        int x = 0;
        int y = 0;

        bool upRight = true;
        while ((x < (width - 1)) || (y < (height - 1))) {
            if (upRight) {
                if (x < (width - 1)) {
                    x += 1;
                } else {
                    y += 1;
                }

                while ((x >= 0) && (y < height)) {
                    returnValue.push_back(mat[y][x]);

                    x -= 1;
                    y += 1;
                }

                x += 1;
                y -= 1;

                upRight = false;
            } else {
                if (y < (height - 1)) {
                    y += 1;
                } else {
                    x += 1;
                }

                while ((x < width) && (y >= 0)) {
                    returnValue.push_back(mat[y][x]);

                    x += 1;
                    y -= 1;
                }

                x -= 1;
                y += 1;

                upRight = true;
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& mat, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto matCopy = mat;
    auto result = solutionInstance.findDiagonalOrder(matCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << mat << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << mat << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{3,4}}, {1,2,3,4});
    test({{1,2,3},{4,5,6},{7,8,9}}, {1,2,4,7,5,3,6,8,9});

    test({{0,1,2},{3,4,5},{6,7,8},{9,10,11}}, {0,1,3,6,4,2,5,7,9,10,8,11});
    test({{0,1,2,3},{4,5,6,7},{8,9,10,11}}, {0,1,4,8,5,2,3,6,9,10,7,11});

    return 0;
}
