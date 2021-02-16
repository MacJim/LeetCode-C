/*
 * 114. Flatten Binary Tree to Linked List
 * https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
 */

#include <iostream>
#include <string>

#include "helpers/TreeNode.hpp"
//#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 4 ms, faster than 92.53% of C++ online submissions for Flatten Binary Tree to Linked List.
// Memory Usage: 12.5 MB, less than 95.93% of C++ online submissions for Flatten Binary Tree to Linked List.
class Solution {
private:
    TreeNode* moveOnNode(TreeNode* root) {
        if ((root->left == nullptr) && (root->right == nullptr)) {
            return root;
        }

        const auto originalLeftNode = root->left;
        const auto originalRightNode = root->right;

        if (originalLeftNode) {
            // Flatten left subtree first.
            const auto leftEndNode = moveOnNode(originalLeftNode);

            // Insert the flattened left subtree to before the right subtree.
            root->left = nullptr;
            root->right = originalLeftNode;
            leftEndNode->right = originalRightNode;

            if (originalRightNode == nullptr) {
                // No original right subtree.
                return leftEndNode;
            }
        }

        if (originalRightNode) {
            // Flatten right subtree.
            const auto rightEndNode = moveOnNode(originalRightNode);
            // The final node of the flattened right subtree is the final node in the flattened tree.
            return rightEndNode;
        }

        // This is unreachable because `root->left` and `root->right` cannot both be true.
        // Just to silence the compiler warnings.
        return nullptr;
    }

public:
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        moveOnNode(root);
    }
};


void test(const std::string& treeStr, const std::string& expectedResultStr) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    solutionInstance.flatten(root);

    auto resultStr = TreeHelper::serialize(root);
    while (resultStr.back() == ',') {
        resultStr.pop_back();
    }

    if (resultStr == expectedResultStr) {
        std::cout << "[Correct] " << treeStr << ": " << resultStr << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << resultStr << " (should be " << expectedResultStr << ")" << std::endl;
    }
}


int main() {
    test("1,2,3", "1,,2,,3");
    test("1,2,5,3,4,,6", "1,,2,,3,,4,,5,,6");
    test("", "");
    test("0", "0");

    return 0;
}
