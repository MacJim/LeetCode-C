/*
 * 105. Construct Binary Tree from Preorder and Inorder Traversal
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 */

/*
 * Tree traversal: https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion
/*
 * - First element in pre-order is root
 *   - Find root in in-order, and separate left and right sub-trees
 * - Last element in both pre-order and in-order are the right-most child
 */
// Runtime: 20 ms, faster than 78.66% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
// Memory Usage: 25.9 MB, less than 75.20% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
class Solution {
private:
    TreeNode* buildTreeRecursively(std::vector<int>& preOrder, const int preOrderStart, const int preOrderEnd, std::vector<int>& inOrder, const int inOrderStart, const int inOrderEnd) {
        if (preOrderStart > preOrderEnd) {
            // 0 node
            return nullptr;
        }
        if (preOrderEnd == preOrderStart) {
            // 1 node
            auto node = new TreeNode(preOrder[preOrderStart]);
            return node;
        }

        // Tree
        const auto& rootVal = preOrder[preOrderStart];
        auto root = new TreeNode(rootVal);

        // Find root value in left sub-tree in in-order.
        int inOrderRootIndex = inOrderStart;
        for (; inOrderRootIndex < inOrderEnd; inOrderRootIndex += 1) {
            const auto& currentVal = inOrder[inOrderRootIndex];
            if (currentVal == rootVal) {
                break;
            }
        }
        const int& inOrderLeftStartIndex = inOrderStart;
        const int inOrderLeftEndIndex = inOrderRootIndex - 1;
        const int inOrderRightStartIndex = inOrderRootIndex + 1;
        const int& inOrderRightEndIndex = inOrderEnd;

        // Find right most element of left sub-tree in pre-order.
        int leftSubTreeLen = inOrderLeftEndIndex - inOrderLeftStartIndex + 1;

        const int preOrderLeftStart = preOrderStart + 1;
        const int preOrderLeftEnd = preOrderLeftStart + leftSubTreeLen - 1;
        const int preOrderRightStart = preOrderLeftEnd + 1;
        const int& preOrderRightEnd = preOrderEnd;

        root->left = buildTreeRecursively(preOrder, preOrderLeftStart, preOrderLeftEnd, inOrder, inOrderLeftStartIndex, inOrderLeftEndIndex);
        root->right = buildTreeRecursively(preOrder, preOrderRightStart, preOrderRightEnd, inOrder, inOrderRightStartIndex, inOrderRightEndIndex);

        return root;
    }

public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        return buildTreeRecursively(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
};


void test(const std::vector<int>& preorder, const std::vector<int>& inorder, const std::string& expectedResultStr) {
    static auto solutionInstance = Solution();

    auto preorderCopy = preorder;
    auto inorderCopy = inorder;
    auto result = solutionInstance.buildTree(preorderCopy, inorderCopy);
    auto resultStr = TreeHelper::serialize(result);

    while (resultStr.back() == ',') {
        resultStr.pop_back();
    }

    if (resultStr == expectedResultStr) {
        std::cout << "[Correct] " << preorderCopy << " " << inorder << ": " << resultStr << std::endl;
    } else {
        std::cout << "[Wrong] " << preorderCopy << " " << inorder << ": " << resultStr << " (should be " << expectedResultStr << ")" << std::endl;
    }
}


int main() {
    test({3,9,20,15,7}, {9,3,15,20,7}, "3,9,20,,,15,7");
    test({1,2,4,5,3,6,7}, {4,2,5,1,6,3,7}, "1,2,3,4,5,6,7");

    return 0;
}
