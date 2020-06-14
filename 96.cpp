/*
 * 96. Unique Binary Search Trees
 * https://leetcode.com/problems/unique-binary-search-trees/
 */

#include <iostream>
#include <vector>


#pragma mark - 1. Unoptimized (like Fibonacci)
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Unique Binary Search Trees.
// Memory Usage: 6.3 MB, less than 10.18% of C++ online submissions for Unique Binary Search Trees.
class Solution {
public:
    int numTrees(int n) {
        static std::vector<int> resultsCache = {1, 1, 2};

        if (n < resultsCache.size()) {
            return resultsCache.at(n);
        }

        while (resultsCache.size() <= n) {
            // Calculate next result.
            int currentResult = 0;

            const int sum = resultsCache.size() - 1;
            for (int a = 0; a <= sum; a += 1) {
                const int b = sum - a;
                currentResult += (resultsCache.at(a) * resultsCache.at(b));
            }

            resultsCache.push_back(currentResult);
        }

        return resultsCache.at(n);
    }
};


int main() {
    auto solutionInstance = Solution();

    std::cout << solutionInstance.numTrees(3) << std::endl;    // 5

    return 0;
}
