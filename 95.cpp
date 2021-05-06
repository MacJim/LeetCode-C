/*
 * 95. Unique Binary Search Trees II
 * https://leetcode.com/problems/unique-binary-search-trees-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 12 ms, faster than 94.86% of C++ online submissions for Unique Binary Search Trees II.
// Memory Usage: 15.4 MB, less than 76.58% of C++ online submissions for Unique Binary Search Trees II.
class Solution {
private:
    std::vector<TreeNode*> recursion(int start, int end) {
        if (start > end) {
            return {nullptr};
        }
        if (start == end) {
            auto root = new TreeNode(start);
            return {root};
        }

        auto returnValue = std::vector<TreeNode*>();

        for (int rootValue = start; rootValue <= end; rootValue += 1) {
            auto leftSubTrees = recursion(start, rootValue - 1);
            auto rightSubTrees = recursion(rootValue + 1, end);
            for (const auto leftSubTree: leftSubTrees) {
                for (const auto rightSubTree: rightSubTrees) {
                    auto root = new TreeNode(rootValue);
                    root->left = leftSubTree;
                    root->right = rightSubTree;
                    returnValue.push_back(root);
                }
            }
        }

        return returnValue;
    }

public:
    std::vector<TreeNode*> generateTrees(int n) {
        if (n == 1) {
            auto root = new TreeNode(1);
            return {root};
        }

        return recursion(1, n);
    }
};


void test(int n) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.generateTrees(n);
    auto readableResult = std::vector<std::string>(result.size(), "");
    for (size_t i = 0; i < result.size(); i += 1) {
        readableResult[i] = TreeHelper::serialize(result[i]);
    }

    std::cout << n << " " << readableResult << std::endl;
}


int main() {
    test(1);
    test(2);
    test(3);
    test(4);

    return 0;
}
