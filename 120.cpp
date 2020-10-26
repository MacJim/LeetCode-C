/*
 * 120. Triangle
 * https://leetcode.com/problems/triangle/
 */

#include <iostream>
#include <vector>
#include <algorithm>


#pragma mark - 1. Standard O(n^2) DP
// Runtime: 8 ms, faster than 93.48% of C++ online submissions for Triangle.
// Memory Usage: 9.1 MB, less than 5.11% of C++ online submissions for Triangle.
class Solution1 {
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) {
        if (triangle.empty()) {
            return 0;
        }

        auto previousCache = std::vector<int>(1, triangle[0][0]);

        for (size_t i = 1; i < triangle.size(); i += 1) {
            const auto& currentRow = triangle.at(i);
            auto currentCache = std::vector<int>(i + 1, 0);

            currentCache[0] = previousCache[0] + currentRow[0];

            for (size_t j = 1; j < i; j += 1) {
                currentCache[j] = currentRow[j] + std::min(previousCache[j - 1], previousCache[j]);
            }

            currentCache.back() = currentRow.back() + previousCache.back();

            previousCache = std::move(currentCache);
        }

        return *std::min_element(previousCache.begin(), previousCache.end());
    }
};


#pragma mark - 2. Slightly optimized 1
// Runtime: 8 ms, faster than 93.48% of C++ online submissions for Triangle.
// Memory Usage: 8.8 MB, less than 5.11% of C++ online submissions for Triangle.
class Solution2 {
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) {
        if (triangle.empty()) {
            return 0;
        }

        auto cache = std::vector<int>(triangle.size(), 0);
        cache[0] = triangle[0][0];

        for (size_t i = 1; i < triangle.size(); i += 1) {
            const auto& currentRow = triangle.at(i);

            // Last
            cache[i] = cache[i - 1] + currentRow[i];

            // Middle (back to front)
            for (size_t j = (i - 1); j > 0; j -= 1) {
                cache[j] = currentRow[j] + std::min(cache[j - 1], cache[j]);
            }

            // First
            cache[0] += currentRow[0];
        }

        return *std::min_element(cache.begin(), cache.end());
    }
};


#pragma mark - 3. Operate on `triangle` directly with a bottom up approach.
// Runtime: 4 ms, faster than 99.87% of C++ online submissions for Triangle.
// Memory Usage: 8.9 MB, less than 5.11% of C++ online submissions for Triangle.
class Solution {
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) {
        if (triangle.empty()) {
            return 0;
        } else if (triangle.size() == 1) {
            return triangle[0][0];
        }

        for (int i = (triangle.size() - 2); i >= 0; i -= 1) {
            for (size_t j = 0; j <= i; j += 1) {
                triangle[i][j] += std::min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }

//        return (triangle[0][0] + std::min(triangle[1][0], triangle[1][1]));
        return triangle[0][0];
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<std::vector<int>> testCase1 = {
    {2},
    {3,4},
    {6,5,7},
    {4,1,8,3}
    };
    std::cout << solutionInstance.minimumTotal(testCase1) << std::endl;    // 11

    std::vector<std::vector<int>> testCase2 = {{1}};
    std::cout << solutionInstance.minimumTotal(testCase2) << std::endl;    // 1

    return 0;
}
