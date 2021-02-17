/*
 * 230. Kth Smallest Element in a BST
 * https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 */

#include <iostream>
#include <string>
#include <stack>

//#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. In-order traversal
// Runtime: 12 ms, faster than 97.98% of C++ online submissions for Kth Smallest Element in a BST.
// Memory Usage: 24 MB, less than 97.39% of C++ online submissions for Kth Smallest Element in a BST.
class Solution1 {
private:
    int k = 0;

    int traversedNodesCount = 0;
    TreeNode* getSmallest(TreeNode* root) {
        if (root->left) {
            const auto leftResult = getSmallest(root->left);

            if (leftResult) {
                return leftResult;
            }
        }

        traversedNodesCount += 1;
        if (traversedNodesCount == k) {
            return root;
        }

        if (root->right) {
            const auto rightResult = getSmallest(root->right);

            if (rightResult) {
                return rightResult;
            }
        }

        return nullptr;
    }

public:
    int kthSmallest(TreeNode* root, const int k) {
        this->k = k;

        return getSmallest(root)->val;
    }
};


#pragma mark - 2. Use a stack
// Runtime: 24 ms, faster than 46.35% of C++ online submissions for Kth Smallest Element in a BST.
// Memory Usage: 24.2 MB, less than 58.05% of C++ online submissions for Kth Smallest Element in a BST.
class Solution {
private:
    std::stack<TreeNode*> nodes = std::stack<TreeNode*>();

public:
    int kthSmallest(TreeNode* root, int k) {
        while (true) {
            while (root) {
                nodes.push(root);
                root = root->left;
            }

            root = nodes.top();
            nodes.pop();
            k -= 1;
            if (k == 0) {
                return root->val;
            }

            root = root->right;
        }
    }
};


void test(const std::string& treeStr, const int k, const int expectedResult) {
    // LeetCode creates separate instances for different test cases.
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.kthSmallest(root, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << " " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << " " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,1,4,,2", 1, 1);
    test("3,1,4,,2", 4, 4);
    test("3,1,4,,2", 3, 3);
    test("5,3,6,2,4,,,1", 3, 3);
    test("5,3,6,2,4,,,1", 4, 4);

    return 0;
}
