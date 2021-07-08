/*
 * 973. K Closest Points to Origin
 * https://leetcode.com/problems/k-closest-points-to-origin/
 */

#include <iostream>
#include <vector>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort according to distance
// Runtime: 180 ms, faster than 60.81% of C++ online submissions for K Closest Points to Origin.
// Memory Usage: 49.2 MB, less than 90.43% of C++ online submissions for K Closest Points to Origin.
class Solution1 {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        if (points.size() == k) {
            return points;
        }

        std::sort(points.begin(), points.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
            const int lDistance = lhs[0] * lhs[0] + lhs[1] * lhs[1];
            const int rDistance = rhs[0] * rhs[0] + rhs[1] * rhs[1];
            return lDistance < rDistance;
        });

        points.resize(k);
        return points;
    }
};


#pragma mark - 2. Quick select (like quick sort) (revisit)
// Runtime: 120 ms, faster than 99.10% of C++ online submissions for K Closest Points to Origin.
// Memory Usage: 49.2 MB, less than 90.43% of C++ online submissions for K Closest Points to Origin.
class Solution {
private:
    inline int getDistance(const std::vector<int>& point) {
        return point[0] * point[0] + point[1] * point[1];
    }

    inline int sort(std::vector<std::vector<int>>& points, int left, int right) {
        if ((right - left) < 10) {
            /*
             * Too few elements.
             * Simply sort them (`std::sort` should use insertion sort with this few elements).
             */
            std::sort(points.begin() + left, points.begin() + right + 1, [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                const int lDistance = lhs[0] * lhs[0] + lhs[1] * lhs[1];
                const int rDistance = rhs[0] * rhs[0] + rhs[1] * rhs[1];
                return lDistance < rDistance;
            });
            return -1;
        }

        const int pivot = right;
        const int pivotDistance = getDistance(points[pivot]);

        right -= 1;
        while (true) {
            // Increase left until its value is larger than the pivot value.
            while ((left <= right) && (getDistance(points[left]) < pivotDistance)) {
                left += 1;
            }

            while ((left <= right) && (getDistance(points[right]) > pivotDistance)) {
                right -= 1;
            }

            if (left >= right) {
                // Terminate.
                std::swap(points[left], points[pivot]);
                return left;
            } else {
                std::swap(points[left], points[right]);
                left += 1;
                right -= 1;
            }
        }
    }

public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Special case.
        if (points.size() == k) {
            return points;
        }

        if (points.size() < 10) {
            /*
             * Too few elements.
             * Simply sort them (`std::sort` should use insertion sort with this few elements).
             */
            std::sort(points.begin(), points.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                const int lDistance = lhs[0] * lhs[0] + lhs[1] * lhs[1];
                const int rDistance = rhs[0] * rhs[0] + rhs[1] * rhs[1];
                return lDistance < rDistance;
            });

            points.resize(k);
            return points;
        }

        // Custom quick sort.
        int left = 0;
        int right = points.size() - 1;

        while (true) {
            int pivot = sort(points, left, right);
            if (pivot == -1) {
                // Numbers within [left, right] are sorted.
                points.resize(k);
                return points;
            } else if ((k == pivot) || (k == (pivot + 1))) {
                points.resize(k);
                return points;
            } else if (k > pivot) {
                // Need more numbers.
                left = pivot + 1;
            } else {
                // Need fewer numbers.
                right = pivot - 1;
            }
        }
    }
};


void test(const std::vector<std::vector<int>>& points, const int k, const std::set<std::vector<int>>& expectedResult) {
    auto solutionInstance = Solution();

    auto pointsCopy = points;
    auto result = solutionInstance.kClosest(pointsCopy, k);
    auto resultSet = std::set(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << points << ": " << resultSet << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << points << ": " << resultSet << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{-95,76},{17,7},{-55,-58},{53,20},{-69,-8},{-57,87},{-2,-42},{-10,-87},{-36,-57},{97,-39},{97,49}}, 5, {{17,7},{-2,-42},{53,20},{-36,-57},{-69,-8}});
    test({{68,97},{34,-84},{60,100},{2,31},{-27,-38},{-73,-74},{-55,-39},{62,91},{62,92},{-57,-67}}, 5, {{2,31},{-27,-38},{-55,-39},{-57,-67},{34,-84}});
    test({{1,3},{-2,2}}, 1, {{-2,2}});
    test({{3,3},{5,-1},{-2,4}}, 2, {{3,3},{-2,4}});

    return 0;
}
