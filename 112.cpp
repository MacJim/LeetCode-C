/*
 * 112. Path Sum
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. WRONG ANSWER: left nodes must have no children
class Solution1 {
private:
    bool recursion(TreeNode* root, const int targetSum) {
        if (root == nullptr) {
            if (targetSum == 0) {
                return true;
            } else {
                return false;
            }
        }

        const int nextTarget = targetSum - root->val;

        const auto leftResult = recursion(root->left, nextTarget);
        const auto rightResult = recursion(root->right, nextTarget);

        return (leftResult || rightResult);
    }

public:
    bool hasPathSum(TreeNode* root, const int targetSum) {
        if (root == nullptr) {
            // As required by the question: false regardless of if targetSum is 0.
            return false;
        }

        return recursion(root, targetSum);
    }
};


#pragma mark - 2
// Runtime: 12 ms, faster than 72.11% of C++ online submissions for Path Sum.
// Memory Usage: 21.1 MB, less than 98.40% of C++ online submissions for Path Sum.
class Solution {
private:
    bool recursion(TreeNode* root, const int targetSum) {
        if (root == nullptr) {
            // This node's parent has a single child.
            return false;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            // This is a leaf node.
            if (targetSum == root->val) {
                return true;
            } else {
                return false;
            }
        }

        const int nextTarget = targetSum - root->val;

        const auto leftResult = recursion(root->left, nextTarget);
        const auto rightResult = recursion(root->right, nextTarget);

        return (leftResult || rightResult);
    }

public:
    bool hasPathSum(TreeNode* root, const int targetSum) {
        if (root == nullptr) {
            // As required by the question: false regardless of if targetSum is 0.
            return false;
        }

        return recursion(root, targetSum);
    }
};


void test(const std::string& treeStr, const int targetSum, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.hasPathSum(root, targetSum);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << " " << targetSum << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << " " << targetSum << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("5,4,8,11,,13,4,7,2,,,,1", 22, true);
    test("1,2,3", 5, false);
    test("1,2,3", 4, true);
    test("1,2", 0, false);
    test("1,2", 1, false);

    return 0;
}
