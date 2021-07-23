/*
 * 814. Binary Tree Pruning
 * https://leetcode.com/problems/binary-tree-pruning/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Pruning.
// Memory Usage: 9.4 MB, less than 47.56% of C++ online submissions for Binary Tree Pruning.
class Solution {
private:
    bool recursion(TreeNode* root) {
        if (!root) {
            return false;
        }

        bool leftResult = false;
        if (root->left) {
            leftResult = recursion(root->left);
        }

        bool rightResult = false;
        if (root->right) {
            rightResult = recursion(root->right);
        }

        if (root->val) {
            if (!leftResult) {
                root->left = nullptr;    // Possible memory leak here. Do I call `delete` on the left subtree?
            }
            if (!rightResult) {
                root->right = nullptr;    // Possible memory leak here.
            }

            return true;
        } else {
            if (!leftResult && !rightResult) {
                // Rely on the parent to remove the current node.
                return false;
            }

            if (!leftResult) {
                root->left = nullptr;    // Possible memory leak here. Do I call `delete` on the left subtree?
            }
            if (!rightResult) {
                root->right = nullptr;    // Possible memory leak here.
            }

            return true;
        }
    }

public:
    TreeNode* pruneTree(TreeNode* root) {
        if (recursion(root)) {
            return root;
        } else {
            return nullptr;
        }
    }
};


void test(const std::string& treeStr, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.pruneTree(root);
    auto resultStr = TreeHelper::serialize(result);

    if (resultStr.find(expectedResult) == 0) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ": " << resultStr << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ": " << resultStr << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,,0,0,1", "1,,0,,1");
    test("1,0,1,0,0,0,1", "1,,1,,1");
    test("1,1,0,1,1,0,1,0", "1,1,0,1,1,,1");
    test("0,0,0,0,0,,0,0,,0", "");

    return 0;
}
