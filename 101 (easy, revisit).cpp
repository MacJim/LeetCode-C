/*
 * 101. Symmetric Tree
 * https://leetcode.com/problems/symmetric-tree/
 */

#include <iostream>
#include <string>
#include <stack>
#include <queue>

//#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Traversal using stack (too complicated)
// Runtime: 4 ms, faster than 84.62% of C++ online submissions for Symmetric Tree.
// Memory Usage: 16.5 MB, less than 56.35% of C++ online submissions for Symmetric Tree.
class Solution1 {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        auto leftNodes = std::stack<TreeNode*>();
        auto rightNodes = std::stack<TreeNode*>();

        auto left = root->left;
        auto right = root->right;

        if (left == right) {
            // Both nullptr
            return true;
        }

        while (left && right) {
            leftNodes.push(left);
            rightNodes.push(right);

            left = left->left;
            right = right->right;
        }

        if ((left == nullptr) && (right != nullptr)) {
            return false;
        }
        if ((left != nullptr) && (right == nullptr)) {
            return false;
        }

        while (!leftNodes.empty()) {
            left = leftNodes.top();
            right = rightNodes.top();

            if (left == right) {
                // Both nullptr
                leftNodes.pop();
                rightNodes.pop();
            } else {
                if ((left == nullptr) && (right != nullptr)) {
                    return false;
                }
                if ((left != nullptr) && (right == nullptr)) {
                    return false;
                }

                if (left->val != right->val) {
                    return false;
                }

                leftNodes.pop();
                rightNodes.pop();

                left = left->right;
                right = right->left;
                if ((left == nullptr) && (right != nullptr)) {
                    return false;
                }
                if ((left != nullptr) && (right == nullptr)) {
                    return false;
                }
                while (left && right) {
                    leftNodes.push(left);
                    rightNodes.push(right);

                    left = left->left;
                    right = right->right;
                }
            }
        }

        return true;
    }
};


#pragma mark - 2. Traversal using queue (much easier) (revisit)
// Runtime: 4 ms, faster than 84.62% of C++ online submissions for Symmetric Tree.
// Memory Usage: 16.9 MB, less than 7.45% of C++ online submissions for Symmetric Tree.
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        auto leftNodes = std::queue<TreeNode*>({root->left});
        auto rightNodes = std::queue<TreeNode*>({root->right});

        while (!leftNodes.empty()) {
            const auto& left = leftNodes.front();
            const auto& right = rightNodes.front();

            if ((left == nullptr) && (right != nullptr)) {
                return false;
            }
            if ((left != nullptr) && (right == nullptr)) {
                return false;
            }

            if (left == right) {
                leftNodes.pop();
                rightNodes.pop();
            } else if (left->val == right->val) {
                leftNodes.push(left->left);
                leftNodes.push(left->right);
                rightNodes.push(right->right);
                rightNodes.push(right->left);

                leftNodes.pop();
                rightNodes.pop();
            } else {
                // Unequal value.
                return false;
            }
        }

        return true;
    }
};


void test(const std::string& treeStr, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.isSymmetric(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("2,3,3,4,5,,4", false);
    test("9,25,25,,-95,-95,,-100,,,-15", false);
    test("1,0", false);
    test("1,2,2,3,4,4,3", true);
    test("1,2,2,,3,,3", false);

    return 0;
}
