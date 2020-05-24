/*
 * 85. Maximal Rectangle
 * https://leetcode.com/problems/maximal-rectangle/
 */

#include <iostream>
#include <vector>


#pragma mark - 1. Unfinished
class Solution1 {
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix) {
        int returnValue = 0;

        const auto iLen = matrix.size();
        const auto jLen = matrix.front().size();

        auto lastRowHorizontal = std::vector<int>(iLen, 0);
        auto currentRowHorizontal = std::vector<int>(iLen, 0);
        auto lastRowVertical = std::vector<int>(iLen, 0);
        auto currentRowVertical = std::vector<int>(iLen, 0);
        auto lastRowRectangleX = std::vector<int>(iLen, 0);
        auto currentRowRectangleX = std::vector<int>(iLen, 0);
        auto lastRowRectangleY = std::vector<int>(iLen, 0);
        auto currentRowRectangleY = std::vector<int>(iLen, 0);

        // First row.
        // j = 0
        currentRowHorizontal.at(0) = matrix.at(0).at(0) - '0';
        currentRowVertical.at(0) = currentRowHorizontal.at(0);
        currentRowRectangleX.at(0) = currentRowHorizontal.at(0);
        currentRowRectangleY.at(0) = currentRowHorizontal.at(0);

        // j > 0
        for (int j = 0; j < jLen; j += 1) {
            if (matrix.at(0).at(j) == '0') {
                currentRowHorizontal.at(j) = 0;
                currentRowVertical.at(j) = 0;
                currentRowRectangleX.at(j) = 0;
                currentRowRectangleY.at(j) = 0;
            } else {
                currentRowHorizontal.at(j) = currentRowHorizontal.at(j - 1) + 1;
                currentRowVertical.at(j) = 1;
                currentRowRectangleX.at(j) = currentRowHorizontal.at(j);
                currentRowRectangleY.at(j) = currentRowHorizontal.at(j);
            }
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            std::swap(lastRowHorizontal, currentRowHorizontal);
            std::swap(lastRowVertical, currentRowVertical);
            std::swap(lastRowRectangleX, currentRowRectangleX);

            // j = 0
            if (matrix.at(i).at(0) == '0') {
                currentRowHorizontal.at(0) = 0;
                currentRowVertical.at(0) = 0;
                currentRowRectangleX.at(0) = 0;
            } else {
                currentRowHorizontal.at(0) = 1;
                currentRowVertical.at(0) = lastRowVertical.at(0) + 1;
                currentRowRectangleX.at(0) = lastRowRectangleX.at(0) + 1;
            }

            // j > 0
            for (int j = 1; j < jLen; j += 1) {
                const auto& currentValue = matrix.at(i).at(j);

                // 1. Horizontal.
                if (currentValue == '0') {
                    currentRowHorizontal.at(j) = 0;
                    currentRowVertical.at(j) = 0;
                    currentRowRectangleX.at(j) = 0;
                } else {
                    currentRowHorizontal.at(j) = currentRowHorizontal.at(j - 1) + 1;
                    currentRowVertical.at(j) = lastRowVertical.at(j) + 1;
//                    currentRowRectangleX.at(j) = lastRowRectangleX.at(j - 1) +
                }

                // 2. Vertical.

                // 3. Rectangle.
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Only log vertical length
// Runtime: 76 ms, faster than 17.78% of C++ online submissions for Maximal Rectangle.
// Memory Usage: 10.8 MB, less than 72.22% of C++ online submissions for Maximal Rectangle.
class Solution2 {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        const auto iLen = matrix.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = matrix.front().size();
        if (jLen == 0) {
            return 0;
        }

        int returnValue = 0;

        auto lastRowVertical = std::vector<int>(jLen, 0);
        auto currentRowVertical = std::vector<int>(jLen, 0);

        // First row.
        int lastOneJ = -1;
        for (int j = 0; j < jLen; j += 1) {
            currentRowVertical.at(j) = matrix.at(0).at(j) - '0';

            if (currentRowVertical.at(j) == 1) {
                if (lastOneJ == -1) {
                    lastOneJ = j;
                    returnValue = std::max(1, returnValue);
                } else {
                    returnValue = std::max(j - lastOneJ + 1, returnValue);
                }
            } else {
                lastOneJ = -1;
            }
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            std::swap(lastRowVertical, currentRowVertical);

            // j = 0
            if (matrix.at(i).at(0) == '0') {
                currentRowVertical.at(0) = 0;
            } else {
                currentRowVertical.at(0) = lastRowVertical.at(0) + 1;

                // Consider a vertical line.
                returnValue = std::max(currentRowVertical.at(0), returnValue);
            }

            // j > 0
            /// The last j with a 1 value.
//            int lastValidJ = -1;
            for (int j = 1; j < jLen; j += 1) {
                if (matrix.at(i).at(j) == '0') {
                    currentRowVertical.at(j) = 0;
//                    lastValidJ = -1;
                    continue;
                }

                currentRowVertical.at(j) = lastRowVertical.at(j) + 1;

                // Consider a vertical line.
                returnValue = std::max(currentRowVertical.at(j), returnValue);

                // Go left and find the best rectangle.
                int minHeight = currentRowVertical.at(j);
                for (int j1 = j - 1; j1 >= 0; j1 -= 1) {
                    const auto& previousHeight = currentRowVertical.at(j1);
                    if (previousHeight == 0) {
                        break;
                    }

                    int width = j - j1 + 1;
                    minHeight = std::min(previousHeight, minHeight);
                    int size = width * minHeight;

                    returnValue = std::max(size, returnValue);
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Optimized 2
// This solution is WRONG because I only focused on width rather than height.
class Solution3 {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        const auto iLen = matrix.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = matrix.front().size();
        if (jLen == 0) {
            return 0;
        }

        int returnValue = 0;

        auto lastRowVertical = std::vector<int>(jLen, 0);
        auto currentRowVertical = std::vector<int>(jLen, 0);

        // First row.
        int lastOneJ = -1;
        for (int j = 0; j < jLen; j += 1) {
            currentRowVertical.at(j) = matrix.at(0).at(j) - '0';

            if (currentRowVertical.at(j) == 1) {
                if (lastOneJ == -1) {
                    lastOneJ = j;
                    returnValue = std::max(1, returnValue);
                } else {
                    returnValue = std::max(j - lastOneJ + 1, returnValue);
                }
            } else {
                lastOneJ = -1;
            }
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            std::swap(lastRowVertical, currentRowVertical);

            /// The last j with a 1 value.
            int lastValidJ = -1;
            /// Min height between `lastValidJ` and current `j`.
            int minHeight = -1;

            // j = 0
            if (matrix.at(i).at(0) == '0') {
                currentRowVertical.at(0) = 0;
            } else {
                currentRowVertical.at(0) = lastRowVertical.at(0) + 1;

                lastValidJ = 0;
                minHeight = currentRowVertical.at(0);

                // Consider a vertical line.
                returnValue = std::max(currentRowVertical.at(0), returnValue);
            }

            // j > 0
            for (int j = 1; j < jLen; j += 1) {
                if (matrix.at(i).at(j) == '0') {
                    currentRowVertical.at(j) = 0;
                    lastValidJ = -1;
                    minHeight = -1;
                    continue;
                }

                currentRowVertical.at(j) = lastRowVertical.at(j) + 1;

                // Consider a vertical line.
                returnValue = std::max(currentRowVertical.at(j), returnValue);

                // Find the best rectangle.
                if (lastValidJ == -1) {
                    // Do not consider a rectangle since left element is 0.
                    lastValidJ = j;
                    minHeight = currentRowVertical.at(j);
                } else {
                    // Consider a rectangle.
                    const int width = j - lastValidJ + 1;
                    minHeight = std::min(currentRowVertical.at(j), minHeight);
                    returnValue = std::max(width * minHeight, returnValue);
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 4
// Source: https://medium.com/@dreamume/leetcode-85-maximal-rectangle-5107ddda3bb
// Runtime: 44 ms, faster than 56.13% of C++ online submissions for Maximal Rectangle.
// Memory Usage: 11.1 MB, less than 61.11% of C++ online submissions for Maximal Rectangle.
class Solution {
public:
    int maximalRectangle(std::vector<std::vector<char>> &matrix) {
        const auto iLen = matrix.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = matrix.front().size();
        if (jLen == 0) {
            return 0;
        }

        int returnValue = 0;

        auto left = std::vector<int>(jLen, 0);
        auto right = std::vector<int>(jLen, jLen);
        auto height = std::vector<int>(jLen, 0);

        for (int i = 0; i < iLen; i += 1) {
            int currentLeft = 0;
            int currentRight = jLen;

            for (int j = 0; j < jLen; j += 1) {
                if (matrix.at(i).at(j) == '1') {
                    height.at(j) += 1;
                    // Crucial. Only keeps the indices of the max height.
                    // We won't lose indices of smaller heights because they are covered by other indices.
                    left.at(j) = std::max(left.at(j), currentLeft);
                } else {
                    height.at(j) = 0;
                    left.at(j) = 0;
                    currentLeft = j + 1;
                }
            }

            for (int j = (jLen - 1); j >= 0; j -= 1) {
                if (matrix.at(i).at(j) == '1') {
                    right.at(j) = std::min(right.at(j), currentRight);    // Crucial. Only keeps the indices of the max height.
                } else {
                    right.at(j) = jLen;
                    currentRight = j;
                }
            }

            for (int j = 0; j < jLen; j += 1) {
                // Big heights and small heights are covered by different indices.
                returnValue = std::max(returnValue, (right.at(j) - left.at(j)) * height.at(j));
            }
        }

        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<char>> testCase1 = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
//    std::cout << solutionInstance.maximalRectangle(testCase1) << std::endl;    // 6

    std::vector<std::vector<char>> testCase2 = {
        {'1','0','1','1','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','1','1','0'}
    };
//    std::cout << solutionInstance.maximalRectangle(testCase2) << std::endl;    // 8

    std::vector<std::vector<char>> testCase3 = {
        {'1','0','1','1','0'},
        {'1','0','0','1','1'},
        {'1','1','1','1','1'},
        {'1','0','1','1','0'}
    };
//    std::cout << solutionInstance.maximalRectangle(testCase3) << std::endl;     // 5

    std::vector<std::vector<char>> testCase4 = {{'1', '1'}};
//    std::cout << solutionInstance.maximalRectangle(testCase4) << std::endl;    // 2

    std::vector<std::vector<char>> testCase5 = {{'1'}};
//    std::cout << solutionInstance.maximalRectangle(testCase5) << std::endl;    // 1

    std::vector<std::vector<char>> testCase6 = {
        {'1', '0'},
        {'1', '0'}
    };
//    std::cout << solutionInstance.maximalRectangle(testCase6) << std::endl;    // 2

    std::vector<std::vector<char>> testCase7 = {{'0','1','1','1','1','1','1','0','1'}};
//    std::cout << solutionInstance.maximalRectangle(testCase7) << std::endl;    // 6

    std::vector<std::vector<char>> testCase8 = {
        {'0','0','1','0','0'},
        {'1','1','1','1','1'},
        {'0','0','0','0','0'},
        {'0','0','0','0','0'}
    };
    std::cout << solutionInstance.maximalRectangle(testCase8) << std::endl;    // 5


    return 0;
}
