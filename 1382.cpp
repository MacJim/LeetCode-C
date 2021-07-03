/*
 * 1382. Balance a Binary Search Tree
 * https://leetcode.com/problems/balance-a-binary-search-tree/
 */

#include <iostream>
#include <vector>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Re-create the tree using in-order traversal
// Runtime: 144 ms, faster than 35.97% of C++ online submissions for Balance a Binary Search Tree.
// Memory Usage: 63.8 MB, less than 17.91% of C++ online submissions for Balance a Binary Search Tree.
class Solution {
private:
    TreeNode* createTree(const std::vector<int>& traversalResult, int start, int end) {
        if (start == end) {
            return new TreeNode(traversalResult[start]);
        } else if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        auto midNode = new TreeNode(traversalResult[mid]);
        midNode->left = createTree(traversalResult, start, mid - 1);
        midNode->right = createTree(traversalResult, mid + 1, end);

        return midNode;
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        // Traverse old tree.
        auto traversalResult = std::vector<int>();

        auto previousNodes = std::stack<TreeNode*>();

        auto initialNode = root;
        while (initialNode) {
            previousNodes.push(initialNode);
            initialNode = initialNode->left;
        }

        while (!previousNodes.empty()) {
            auto top = previousNodes.top();
            traversalResult.push_back(top->val);
            previousNodes.pop();

            if (top->right) {
                auto currentNode = top->right;
                while (currentNode) {
                    previousNodes.push(currentNode);
                    currentNode = currentNode->left;
                }
            }
        }

//        std::cout << traversalResult << std::endl;

        // Create new tree.
        auto returnValue = createTree(traversalResult, 0, traversalResult.size() - 1);

        return returnValue;
    }
};


void test(const std::string& treeStr) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto rootInOrderTraversal = TreeHelper::inOrderTraverse(root);

    auto result = solutionInstance.balanceBST(root);
    auto resultStr = TreeHelper::serialize(result);
    auto resultInOrderTraversal = TreeHelper::inOrderTraverse(result);

    if (rootInOrderTraversal == resultInOrderTraversal) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ": " << resultStr << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ": " << resultStr << std::endl;
    }
}


int main() {
    test("1,,2,,3,,4,,");

    return 0;
}
