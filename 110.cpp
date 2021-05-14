/*
 * 110. Balanced Binary Tree
 * https://leetcode.com/problems/balanced-binary-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/TreeNode.hpp"
//#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
// Runtime: 8 ms, faster than 88.32% of C++ online submissions for Balanced Binary Tree.
// Memory Usage: 21 MB, less than 48.26% of C++ online submissions for Balanced Binary Tree.
class Solution {
private:
    int recursion(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        auto leftHeight = recursion(root->left);
        if (leftHeight == -1) {
            return -1;
        }

        auto rightHeight = recursion(root->right);
        if (rightHeight == -1) {
            return -1;
        }

        if (((leftHeight - rightHeight) > 1) || ((rightHeight - leftHeight) > 1)) {
            return -1;
        }

        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    bool isBalanced(TreeNode* root) {
        if (!root) {
            return true;
        }

        auto result = recursion(root);
        if (result == -1) {
            return false;
        }

        return true;
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.isBalanced(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,9,20,,,15,7", true);
    test("1,2,2,3,3,,,4,4", false);
    test("", true);

    return 0;
}
