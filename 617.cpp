/*
 * 617. Merge Two Binary Trees
 * https://leetcode.com/problems/merge-two-binary-trees/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 36 ms, faster than 85.18% of C++ online submissions for Merge Two Binary Trees.
// Memory Usage: 32.9 MB, less than 69.16% of C++ online submissions for Merge Two Binary Trees.
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if ((!t1) && (!t2)) {
            return nullptr;
        } else if (!t1) {
            return t2;
        } else if (!t2) {
            return t1;
        }

        auto root = new TreeNode(t1->val + t2->val);
        auto leftChild = mergeTrees(t1->left, t2->left);
        auto rightChild = mergeTrees(t1->right, t2->right);
        root->left = leftChild;
        root->right = rightChild;

        return root;
    }
};


#pragma mark - 2. Stack


void test(const std::string& str1, const std::string& str2, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto t1 = TreeHelper::deserialize(str1);
    auto t2 = TreeHelper::deserialize(str2);
    auto result = solutionInstance.mergeTrees(t1, t2);
    auto resultStr = TreeHelper::serialize(result);

    if (resultStr == expectedResult) {
        std::cout << "[Correct] " << str1 << " " << str2 << ": " << resultStr << std::endl;
    } else {
        std::cout << "[Wrong] " << str1 << " " << str2 << ": " << resultStr << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,3,2,5", "2,1,3,,4,,7", "3,4,5,5,4,,7");
    test("1", "1,2", "2,2");

    return 0;
}
