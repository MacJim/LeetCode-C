/*
 * 64. Minimum Path Sum
 * https://leetcode.com/problems/minimum-path-sum/
 */

#include <iostream>
#include <vector>


// Runtime: 16 ms, faster than 33.65% of C++ online submissions for Minimum Path Sum.
// Memory Usage: 9.7 MB, less than 100.00% of C++ online submissions for Minimum Path Sum.
class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        const auto iLen = grid.size();
        if (iLen == 0) {
            return 0;
        }

        const auto jLen = grid.front().size();
        if (jLen == 0) {
            return 0;
        }

        auto row = std::vector<int>(jLen, 0);

        // First row.
        row.at(0) = grid.at(0).at(0);
        for (int j = 1; j < jLen; j += 1) {
            row.at(j) = row.at(j - 1) + grid.at(0).at(j);
        }

        // Upcoming rows.
        for (int i = 1; i < iLen; i += 1) {
            // For column.
            row.at(0) = row.at(0) + grid.at(i).at(0);
            for (int j = 1; j < jLen; j += 1) {
                row.at(j) = std::min(row.at(j - 1), row.at(j)) + grid.at(i).at(j);
            }
        }

        return row.back();
    }
};


int main() {
    auto solutionInstance = Solution();
    
    std::vector<std::vector<int>> testCase1 = {
        {1,3,1},
        {1,5,1},
        {4,2,1}
    };
    std::cout << solutionInstance.minPathSum(testCase1) << std::endl;    // 7

    std::vector<std::vector<int>> testCase2 = {
            {1,3,3},
            {1,5,1},
            {4,2,1}
    };
    std::cout << solutionInstance.minPathSum(testCase2) << std::endl;    // 9

    return 0;
}
