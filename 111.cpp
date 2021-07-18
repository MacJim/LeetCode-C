/*
 * 111. Minimum Depth of Binary Tree
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/
 */

#include <iostream>
#include <vector>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"

#include "helpers/TreeNode.hpp"


#pragma mark - 1. DFS + recursion
// Runtime: 224 ms, faster than 73.86% of C++ online submissions for Minimum Depth of Binary Tree.
// Memory Usage: 144.5 MB, less than 89.69% of C++ online submissions for Minimum Depth of Binary Tree.
class Solution {
private:
    static constexpr int MAX_HEIGHT = 100000;

private:
    int recursion(TreeNode* root, const int depthThreshold) {
        if ((!root->left) && (!root->right)) {
            // Leaf node: no child.
            return 1;
        }

        if (depthThreshold <= 0) {
            // The right sub-tree is deeper than the left subtree.
            return MAX_HEIGHT;
        }

        int leftDepth = MAX_HEIGHT;
        if (root->left) {
            leftDepth = recursion(root->left, depthThreshold - 1);
        }

        int rightDepth = MAX_HEIGHT;
        if (root->right) {
            rightDepth = recursion(root->right, std::min(depthThreshold - 1, leftDepth));
        }

        return std::min(leftDepth, rightDepth) + 1;
    }

public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return recursion(root, INT_MAX);
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.minDepth(root);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("-1,-7,9,,,-1,-7,,8,-9", 2);
    test("3,9,20,,,15,7", 2);
    test("2,,3,,4,,5,,6", 5);
    test("1,2,3,4,5", 2);

    return 0;
}
