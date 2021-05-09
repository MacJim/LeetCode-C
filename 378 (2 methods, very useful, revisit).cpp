/*
 * 378. Kth Smallest Element in a Sorted Matrix
 * https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Diagonal lines
// WRONG ANSWER because numbers from the next diagonal line may still be smaller than numbers in the current one.
class Solution1 {
private:
    int findInDiagonalLine(const std::vector<std::vector<int>>& matrix, const int k, const int indexSum) {
        const auto sideLength = matrix.size();

        // Insertion sort.
        auto q = std::deque<int>(k, INT_MAX);

        for (int y = 0; y < sideLength; y += 1) {
            int x = indexSum - y;
            if ((x < 0) || (x >= sideLength)) {
                continue;
            }

            for (size_t i = 0; i < q.size(); i += 1) {
                if (matrix[y][x] < q[i]) {
//                    for (int j = q.size() - 1; j > i; j -= 1) {
//                        q[j] = q[j - 1];
//                    }
//                    q[i] = matrix[y][x];

                    q.pop_back();
                    q.push_front(matrix[y][x]);

                    break;
                }
            }
        }

        return q.back();
    }

public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
        const auto sideLength = matrix.size();

        for (int length = 1; length <= sideLength; length += 1) {
            if (k <= length) {
                // In this diagonal line.
                return findInDiagonalLine(matrix, k, length - 1);
            } else {
                k -= length;
            }
        }

        for (int length = sideLength - 1; length > 0; length -= 1) {
            if (k <= length) {
                return findInDiagonalLine(matrix, k, sideLength + (sideLength - 1 - length));
            } else {
                k -= length;
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


#pragma mark - 2. Use min heap to merge `n` sorted matrix (revisit)
/*
 * Well, traditionally I simply use a recursive method to merge 2 arrays at once.
 * But this time, that method is wasteful.
 *
 * So we use a heap to achieve nlogn complexity
 */
// Runtime: 148 ms, faster than 5.40% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
// Memory Usage: 67.3 MB, less than 5.15% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Solution2 {
public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
        const auto sideLength = matrix.size();

//        auto heap = std::priority_queue<int, std::vector<int>, std::less<>>();
//        for (size_t i = 0; i < sideLength; i += 1) {
//            heap.push(matrix[i][0]);
//        }
//
//        auto indices = std::vector<size_t>(sideLength, 0);

        auto cmp = [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
            if (lhs.empty()) {
                return true;
            }
            if (rhs.empty()) {
                return false;
            }

            return lhs[0] > rhs[0];
        };
        auto heap = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(cmp)>(cmp);
        for (auto& arr: matrix) {
            heap.push(std::move(arr));
        }

        while (k > 1) {
            auto arr = heap.top();
            heap.pop();
            arr.erase(arr.begin());    // This operation is expensive and may have affected the runtime negatively.
            heap.push(std::move(arr));

            k -= 1;
        }

        return heap.top()[0];
    }
};


#pragma mark - 3. Binary search from the bottom left or top right (revisit)
/*
 * Remember that we can search such a matrix from the bottom left or top right.
 *
 * Example: start from bottom left:
 *
 * - Current number is larger than target: move up
 * - Current number is smaller than target: move down
 *
 * In this solution, we use the min (top left) and max (bottom right) values for a binary search, and figure out the position of `mid` by following the rule above.
 */
// Runtime: 20 ms, faster than 98.71% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
// Memory Usage: 13 MB, less than 87.91% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Solution {
private:
    /**
     * Get the amount of elements in the matrix that are smaller or equal to `threshold`.
     *
     * @param matrix
     * @param threshold
     * @return
     */
    int getSmallerOrEqualCount(std::vector<std::vector<int>>& matrix, const int threshold) {
        const auto sideLength = matrix.size();

        int returnValue = 0;

        int y = (sideLength - 1);
        int x = 0;

        while (x < sideLength) {    // `y >= 0` is enforced below.
            auto current = matrix[y][x];
            if (current <= threshold) {
                returnValue += (y + 1);

                x += 1;
            } else {
                if (y == 0) {
                    break;
                } else {
                    y -= 1;
                }
            }
        }

        return returnValue;
    }

public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
        int small = matrix[0][0];
        int large = matrix.back().back();

        while (small < large) {    // When small == large, our targeted number is `small` or `large`.
            int mid = (small + large) / 2;

            int smallerOrEqualCount = getSmallerOrEqualCount(matrix, mid);
//            std::cout << index;

            if (smallerOrEqualCount < k) {
                // The current `mid` value is too small.
                small = mid + 1;
            } else {
                // The current `mid` value may be correct or too large.
                large = mid;
            }
        }

        return small;
    }
};


void test(const std::vector<std::vector<int>>& matrix, const int k, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto matrixCopy = matrix;
    auto result = solutionInstance.kthSmallest(matrixCopy, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << matrix << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << matrix << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{3,4}}, 3, 3);
    test({{6}}, 1, 6);
    test({{1,5,9},{10,11,13},{12,13,15}}, 8, 13);

    for (const int i: {1,2,3,4}) {
        test({{1,2},{3,4}}, i, i);
    }

    for (const int i: {1,2,3,4,5,6,7,8,9}) {
        test({{1,2,3},{4,5,6},{7,8,9}}, i, i);
    }

    return 0;
}
