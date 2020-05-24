/*
 * 62. Unique Paths
 * https://leetcode.com/problems/unique-paths/
 */

#include <iostream>
#include <vector>


// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Unique Paths.
// Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Unique Paths.
class Solution {
public:
    int uniquePaths(int m, int n) {
        if ((m == 1) || (n == 1)) {
            return 1;
        }

        auto lastRow = std::vector<int>(m, 1);    // The first row is always 1.
        auto currentRow = std::vector<int>(m, 1);

        for (int i = 1; i < n; i += 1) {
//            auto previousLastRow = std::move(lastRow);
//            lastRow = std::move(currentRow);
//            currentRow = std::move(previousLastRow);

            std::swap(lastRow, currentRow);

            // j = 0
            const auto& firstNumber = lastRow.at(0);
            currentRow.at(0) = firstNumber;
            // j > 0
            for (int j = 1; j < m; j += 1) {
                const auto& upNumber = lastRow.at(j);
                const auto& leftNumber = currentRow.at(j - 1);
                currentRow.at(j) = upNumber + leftNumber;
            }
        }

        return currentRow.back();
    }
};


int main() {
    auto solutionInstance = Solution();

    std::cout << solutionInstance.uniquePaths(3, 7) << std::endl;    // 28
    std::cout << solutionInstance.uniquePaths(7, 3) << std::endl;    // 28

    return 0;
}
