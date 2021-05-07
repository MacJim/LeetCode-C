/*
 * 250. Count Univalue Subtrees
 * https://leetcode.com/problems/count-univalue-subtrees/
 *
 * Given a binary tree, count the number of uni-value subtrees.
 *
 * A Uni-value subtree means all nodes of the subtree have the same value.
 *
 * For example:
 * Given binary tree,

    5
   / \
  1   5
 / \   \
5   5   5

 * return 4 because of:
 *   - 3 leaf nodes
 *   - 1 subtree 5-5 of right
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
class Solution {
private:
    int recursion(TreeNode* root) {
        if ((root->left == nullptr) && (root->right == nullptr)) {
            // Leaves are always uni-value.
            return 1;
        }

        int returnValue = 0;
        bool isRootEligible = true;

        if (root->left) {
            const int leftCount = recursion(root->left);
            if (leftCount > 0) {
                returnValue += leftCount;

                if (root->left->val != root->val) {
                    isRootEligible = false;
                }
            } else {
                isRootEligible = false;
            }
        }
        if (root->right) {
            const int rightCount = recursion(root->right);
            if (rightCount > 0) {
                returnValue += rightCount;

                if (root->right->val != root->val) {
                    isRootEligible = false;
                }
            } else {
                isRootEligible = false;
            }
        }

        if (isRootEligible) {
            returnValue += 1;
        }

        return returnValue;
    }

public:
    int count(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return recursion(root);
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.count(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("5,1,5,5,5,,5", 4);
    test("2,2,2,2,2", 5);
    test("2,3,2,3,3", 4);

    test("1,2,3,4,5,6,7", 4);
    test("1,2,3,4,5,6,", 3);
    test("1,2,3,4,5", 3);
    test("1,2,3,4,", 2);
    test("1,2,3", 2);

    return 0;
}
