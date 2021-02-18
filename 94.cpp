/*
 * 94. Binary Tree Inorder Traversal
 * https://leetcode.com/problems/binary-tree-inorder-traversal/
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 4 ms, faster than 48.47% of C++ online submissions for Binary Tree Inorder Traversal.
// Memory Usage: 8.1 MB, less than 98.74% of C++ online submissions for Binary Tree Inorder Traversal.
class Solution1 {
private:
    void traverseRecursively(TreeNode* root, std::vector<int>& returnValue) {
        if (root == nullptr) {
            return;
        }

        traverseRecursively(root->left, returnValue);

        returnValue.push_back(root->val);

        traverseRecursively(root->right, returnValue);
    }

public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        auto returnValue = std::vector<int>();
        traverseRecursively(root, returnValue);
        return returnValue;
    }
};


#pragma mark - 2. Stack
// Runtime: 4 ms, faster than 48.47% of C++ online submissions for Binary Tree Inorder Traversal.
// Memory Usage: 8.3 MB, less than 89.14% of C++ online submissions for Binary Tree Inorder Traversal.
class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        auto returnValue = std::vector<int>();

        auto leftElements = std::stack<TreeNode*>();

        while (true) {
            while (root) {
                leftElements.push(root);
                root = root->left;
            }

            if (leftElements.empty()) {
                break;
            }

            root = leftElements.top();
            leftElements.pop();
            returnValue.push_back(root->val);

            root = root->right;
        }

        return returnValue;
    }
};


void test(const std::string& treeStr, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.inorderTraversal(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,,2,3", {1, 3, 2});
    test("", {});
    test("1", {1});
    test("1,2", {2, 1});
    test("1,,2", {1, 2});
    test("1,,2,,3,,4,,5,,6", {1,2,3,4,5,6});
    test("1,2,,3,,4,,5,,6", {6,5,4,3,2,1});

    return 0;
}
