/*
 * 1329. Sort the Matrix Diagonally
 * https://leetcode.com/problems/sort-the-matrix-diagonally/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Insertion sort
/*
 * Our data size is small, so insertion sort can be faster than others.
 */
// Runtime: 8 ms, faster than 92.47% of C++ online submissions for Sort the Matrix Diagonally.
// Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Sort the Matrix Diagonally.
class Solution {
private:
    inline void sortDiagnoal(std::vector<std::vector<int>>& mat, int startX, int startY, const size_t xSize, const size_t ySize) {
        int x = startX;
        int y = startY;

        while ((x < xSize) && (y < ySize)) {
            int previousX = startX;
            int previousY = startY;

            while ((previousY < y) && (previousX < x) && (mat[previousY][previousX] <= mat[y][x])) {
                previousX += 1;
                previousY += 1;
            }

            if (previousX == x) {
                // No need to sort.
            } else {
                // Insertion sort.
                const int currentVal = mat[y][x];

                int midX = x;
                int midY = y;
                while (midX > previousX) {
                    mat[midY][midX] = mat[midY - 1][midX - 1];

                    midX -= 1;
                    midY -= 1;
                }

                mat[previousY][previousX] = currentVal;
            }

            x += 1;
            y += 1;
        }
    }

public:
    std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>>& mat) {
        const size_t xSize = mat[0].size();
        const size_t ySize = mat.size();

        // Start from y = 0.
        for (int startX = xSize - 2; startX >= 0; startX -= 1) {
            constexpr int startY = 0;

            sortDiagnoal(mat, startX, startY, xSize, ySize);
        }

        // Start from x = 0.
        for (int startY = 1; startY < ySize; startY += 1) {
            constexpr int startX = 0;

            sortDiagnoal(mat, startX, startY, xSize, ySize);
        }

        return mat;
    }
};


void test(const std::vector<std::vector<int>>& mat, const std::vector<std::vector<int>>& expectedResult) {
    auto solutionInstance = Solution();

    auto matCopy = mat;
    auto result = solutionInstance.diagonalSort(matCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << mat << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << mat << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{3,3,1,1},{2,2,1,2},{1,1,1,2}}, {{1,1,1,1},{1,2,2,2},{1,2,3,3}});
    test({{11,25,66,1,69,7},{23,55,17,45,15,52},{75,31,36,44,58,8},{22,27,33,25,68,4},{84,28,14,11,5,50}}, {{5,17,4,1,52,7},{11,11,25,45,8,69},{14,23,25,44,58,15},{22,27,31,36,50,66},{84,28,75,33,55,68}});

    return 0;
}
