/*
 * 124. Binary Tree Maximum Path Sum
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/
 */

/*
 * This problem really has a lot of cases.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 32 ms, faster than 54.11% of C++ online submissions for Binary Tree Maximum Path Sum.
// Memory Usage: 28.5 MB, less than 49.24% of C++ online submissions for Binary Tree Maximum Path Sum.
class Solution {
private:
    int maxSum = INT_MIN;
    int recursion(TreeNode* root) {
        if (root == nullptr) {
            return INT_MIN;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            maxSum = std::max(maxSum, root->val);

            return root->val;
        }

        const auto leftVal = recursion(root->left);
        const auto rightVal = recursion(root->right);

        int returnValue = root->val;
        maxSum = std::max(maxSum, root->val);
        if (leftVal > rightVal) {
            if (leftVal > 0) {
                returnValue += leftVal;
            }

            maxSum = std::max(maxSum, leftVal);
            maxSum = std::max(maxSum, leftVal + root->val);
            if (rightVal != INT_MIN) {
                maxSum = std::max(maxSum, leftVal + root->val + rightVal);
            }
        } else {
            if (rightVal > 0) {
                returnValue += rightVal;
            }

            maxSum = std::max(maxSum, rightVal);
            maxSum = std::max(maxSum, rightVal + root->val);
            if (leftVal != INT_MIN) {
                maxSum = std::max(maxSum, rightVal + root->val + leftVal);
            }
        }

        return returnValue;
    }

public:
    int maxPathSum(TreeNode* root) {
        recursion(root);
        return maxSum;
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.maxPathSum(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("2,-1", 2);
    test("-2,-1", -1);
    test("-3", -3);
    test("1,2,3", 6);
    test("-10,9,20,,,15,7", 42);

    return 0;
}
