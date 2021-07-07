/*
 * 1901. Find a Peak Element II
 * https://leetcode.com/problems/find-a-peak-element-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Start from top left, find bigger number every step
// Runtime: 168 ms, faster than 40.18% of C++ online submissions for Find a Peak Element II.
// Memory Usage: 46.2 MB, less than 35.93% of C++ online submissions for Find a Peak Element II.
class Solution1 {
public:
    std::vector<int> findPeakGrid(const std::vector<std::vector<int>>& mat) {
        int x = 0;
        int y = 0;

        while (true) {
            const int& currentNum = mat[y][x];

            int rightX = x + 1;
            if (rightX < mat[0].size()) {
                const int& rightNum = mat[y][rightX];
                if (rightNum > currentNum) {
                    x = rightX;
                    continue;
                }
            }

            int bottomY = y + 1;
            if (bottomY < mat.size()) {
                const int& bottomNum = mat[bottomY][x];
                if (bottomNum > currentNum) {
                    y = bottomY;
                    continue;
                }
            }

            int leftX = x - 1;
            if (x > 0) {
                const int& leftNum = mat[y][leftX];
                if (leftNum > currentNum) {
                    x = leftX;
                    continue;
                }
            }

            int topY = y - 1;
            if (y > 0) {
                const int& topNum = mat[topY][x];
                if (topNum > currentNum) {
                    y = topY;
                    continue;
                }
            }

            return {y, x};
        }

    }
};


#pragma mark - 2. Binary search on the largest elements of each column (like 162)
// Runtime: 176 ms, faster than 15.79% of C++ online submissions for Find a Peak Element II.
// Memory Usage: 46.4 MB, less than 12.65% of C++ online submissions for Find a Peak Element II.
class Solution2 {
public:
    std::vector<int> findPeakGrid(const std::vector<std::vector<int>>& mat) {
        auto largestIndices = std::vector<int>(mat.size(), 0);

        for (int y = 0; y < mat.size(); y += 1) {
            const auto& row = mat[y];
            for (int x = 0; x < row.size(); x += 1) {
                if (row[largestIndices[y]] < row[x]) {
                    largestIndices[y] = x;
                }
            }
        }

        int leftY = 0;
        int rightY = mat.size() - 1;

        while (leftY < rightY) {    // Terminates when left == right
            int midY = (leftY + rightY) / 2;

            if (midY > 0) {
                // Compare with left adjacent.
                if (mat[midY][largestIndices[midY]] < mat[midY - 1][largestIndices[midY - 1]]) {
                    rightY = midY;
                    continue;
                }
            }

            if (midY < (mat.size() - 1)) {
                // Compare with right adjacent.
                if (mat[midY][largestIndices[midY]] < mat[midY + 1][largestIndices[midY + 1]]) {
                    leftY = midY + 1;
                    continue;
                }
            }

            // `mid` qualifies.
            return {midY, largestIndices[midY]};
        }

        // Terminated.
        return {leftY, largestIndices[leftY]};
    }
};


#pragma mark - 3. Optimize 2: Calculate biggest number of `mid` and just compare with its left and right adjacent elements
// Runtime: 172 ms, faster than 25.40% of C++ online submissions for Find a Peak Element II.
// Memory Usage: 46.2 MB, less than 35.93% of C++ online submissions for Find a Peak Element II.
class Solution {
public:
    std::vector<int> findPeakGrid(const std::vector<std::vector<int>>& mat) {
        int leftY = 0;
        int rightY = mat.size() - 1;

        int largestX = 0;

        while (leftY < rightY) {    // Terminates when left == right
            int midY = (leftY + rightY) / 2;

            for (int x = 1; x < mat[0].size(); x += 1) {
                if (mat[midY][x] > mat[midY][largestX]) {
                    largestX = x;
                }
            }

            if (midY > 0) {
                // Compare with left adjacent.
                if (mat[midY][largestX] < mat[midY - 1][largestX]) {
                    rightY = midY;
                    continue;
                }
            }

            if (midY < (mat.size() - 1)) {
                // Compare with right adjacent.
                if (mat[midY][largestX] < mat[midY + 1][largestX]) {
                    leftY = midY + 1;
                    continue;
                }
            }

            // `mid` qualifies.
            return {midY, largestX};
        }

        // Terminated.
        return {leftY, largestX};
    }
};


inline bool isValidResult(const std::vector<std::vector<int>>& mat, const std::vector<int>& result) {
    int x = result[1];
    int y = result[0];

    const int& currentNum = mat[y][x];

    int rightX = x + 1;
    if (rightX < mat[0].size()) {
        const int& rightNum = mat[y][rightX];
        if (rightNum > currentNum) {
            return false;
        }
    }

    int bottomY = y + 1;
    if (bottomY < mat.size()) {
        const int& bottomNum = mat[bottomY][x];
        if (bottomNum > currentNum) {
            return false;
        }
    }

    int leftX = x - 1;
    if (x > 0) {
        const int& leftNum = mat[y][leftX];
        if (leftNum > currentNum) {
            return false;
        }
    }

    int topY = y - 1;
    if (y > 0) {
        const int& topNum = mat[topY][x];
        if (topNum > currentNum) {
            return false;
        }
    }

    return true;
}


void test(const std::vector<std::vector<int>>& mat) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.findPeakGrid(mat);

    if (isValidResult(mat, result)) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << mat << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << mat << ": " << result << std::endl;
    }
}


int main() {
    test({
        {16,10,7,4,19,25,40,27,16},
        {11,21,37,47,21,13,49,11,32},
        {33,30,32,20,32,2,6,26,33},
        {30,16,14,38,23,4,19,32,39},
        {42,44,31,19,35,1,7,28,9},
        {17,47,24,49,26,24,3,26,4}});
    test({{1,4},{3,2}});
    test({{10,20,15},{21,30,14},{7,16,32}});
    test({{30,41,24,11,24},{23,14,43,18,45},{44,42,5,39,41},{11,35,47,16,11},{30,25,18,41,45}});

    return 0;
}
