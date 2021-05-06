/*
 * 106. Construct Binary Tree from Inorder and Postorder Traversal
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion, find root first
// Runtime: 24 ms, faster than 49.63% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
// Memory Usage: 73.8 MB, less than 13.60% of C++ online submissions for Construct Binary Tree from Inorder and Postorder Traversal.
class Solution {
private:
    TreeNode* recursion(std::vector<int>& inorder, std::vector<int>& postorder) {
        if (inorder.size() == 1) {
            auto root = new TreeNode(inorder[0]);
            return root;
        }

        // Find root value in `inorder`.
        int rootVal = postorder.back();
        int inRootIndex = 0;
        while (inorder[inRootIndex] != rootVal) {
            inRootIndex += 1;
        }

        // Separate left and right sub-trees in `inorder`.
        int leftSubTreeSize = inRootIndex;
        int rightSubTreeSize = inorder.size() - inRootIndex - 1;

        TreeNode* leftSubTree = nullptr;
        TreeNode* rightSubTree = nullptr;

        if (leftSubTreeSize > 0) {
            // Although these copy operations are expensive, they are convenient.
            auto inOrderLeft = std::vector<int>(inorder.begin(), inorder.begin() + leftSubTreeSize);
            auto postOrderLeft = std::vector<int>(postorder.begin(), postorder.begin() + leftSubTreeSize);

            leftSubTree = recursion(inOrderLeft, postOrderLeft);
        }
        if (rightSubTreeSize > 0) {
            auto inOrderRight = std::vector<int>(inorder.end() - rightSubTreeSize, inorder.end());
            auto postOrderRight = std::vector<int>(postorder.end() - rightSubTreeSize - 1, postorder.end() - 1);

            rightSubTree = recursion(inOrderRight, postOrderRight);
        }

        auto rootNode = new TreeNode(rootVal);
        rootNode->left = leftSubTree;
        rootNode->right = rightSubTree;

        return rootNode;
    }

public:
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
        if (inorder.size() == 1) {
            auto root = new TreeNode(inorder[0]);
            return root;
        }

        return recursion(inorder, postorder);
    }
};


void test(const std::vector<int>& inorder, const std::vector<int>& postorder, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto inorderCopy = inorder;
    auto postorderCopy = postorder;
    auto result = solutionInstance.buildTree(inorderCopy, postorderCopy);
    auto resultStr = TreeHelper::serialize(result);

    if (resultStr.rfind(expectedResult, 0) == 0) {
        std::cout << "[Correct] " << inorder << " " << postorder << ": " << resultStr << std::endl;
    } else {
        std::cout << "[Wrong] " << inorder << " " << postorder << ": " << resultStr << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,2,4,1,5}, {3,4,2,5,1}, "1,2,5,3,4");
    test({9,3,15,20,7}, {9,15,7,20,3}, "3,9,20,,,15,7");
    test({-1}, {-1}, "-1");

    return 0;
}
