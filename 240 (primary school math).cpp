/*
 * 240. Search a 2D Matrix II
 * https://leetcode.com/problems/search-a-2d-matrix-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1
// Time limit exceeded.
class Solution1 {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, const int target) {
        if (matrix.empty() || (matrix.front().empty())) {
            return false;
        }

        for (int y = (matrix.size() - 1); y >= 0; y -= 1) {
            if (matrix[y][0] > target) {
                continue;
            }

            for (int x = (matrix[y].size() - 1); x >= 0; x -= 1) {
                if (matrix[0][x] > target) {
                    continue;
                }

                if (matrix[y][x] == target) {
                    return true;
                }
            }
        }

        return false;
    }
};


#pragma mark - 2. Optimized 1: cache x and y values
// Runtime: 1560 ms, faster than 5.01% of C++ online submissions for Search a 2D Matrix II.
// Memory Usage: 219.7 MB, less than 10.65% of C++ online submissions for Search a 2D Matrix II.
class Solution2 {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, const int target) {
        if (matrix.empty() || (matrix.front().empty())) {
            return false;
        }

        auto feasibleX = std::vector<size_t>();
        auto feasibleY = std::vector<size_t>();

        for (size_t x = 0; x < matrix.front().size(); x += 1) {
            if ((matrix[0][x] == target) || (matrix.back()[x] == target)) {
                return true;
            }

            if ((matrix[0][x] < target) && (matrix.back()[x] > target)) {
                feasibleX.push_back(x);
            }
        }
        for (size_t y = 0; y < matrix.size(); y += 1) {
            if ((matrix[y][0] == target) || (matrix[y].back() == target)) {
                return true;
            }

            if ((matrix[y][0] < target) && (matrix[y].back() > target)) {
                feasibleY.push_back(y);
            }
        }

        for (const auto& y: feasibleY) {
            for (const auto& x: feasibleX) {
                if (matrix[y][x] == target) {
                    return true;
                }
            }
        }

        return false;
    }
};


#pragma mark - 3. Search from top right
/*
 * Move horizontally/vertically are guaranteed to get the number smaller/bigger.
 */
// Runtime: 64 ms, faster than 96.31% of C++ online submissions for Search a 2D Matrix II.
// Memory Usage: 14.6 MB, less than 91.73% of C++ online submissions for Search a 2D Matrix II.
class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, const int target) {
        if (matrix.empty() || (matrix.front().empty())) {
            return false;
        }

        int x = matrix.front().size() - 1;
        int y = 0;

        while ((x >= 0) && (y < matrix.size())) {
            const auto& num = matrix[y][x];
            if (num < target) {
                y += 1;
            } else if (num > target) {
                x -= 1;
            } else {
                return true;
            }
        }

        return false;
    }
};


void test(const std::vector<std::vector<int>>& matrix, const int target, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto matrixCopy = matrix;
    auto result = solutionInstance.searchMatrix(matrixCopy, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << matrix << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << matrix << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{-1, 3}}, 3, true);
    test({{-1}, {-1}}, -2, false);
    test({{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}, 5, true);
    test({{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}, 20, false);

    return 0;
}
