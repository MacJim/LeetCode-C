/*
 * 129. Sum Root to Leaf Numbers
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


//class Solution {
//public:
//    int sumNumbers(TreeNode* root) {
//        if (!root) {
//            return 0;
//        }
//
//        auto previousNums = std::stack<std::pair<TreeNode*, int>>();
//        previousNums.emplace(root, root->val);
//
//        while (!previousNums.empty()) {
//            const auto topNode = previousNums.top().first;
//            const int topValue = previousNums.top().second * 10;
//
//            if (topNode->left) {
//                previousNums.emplace(topNode->left, topValue + topNode->left->val);
//            }
//        }
//
//        int returnValue = 0;
//
//        return returnValue;
//    }
//};


#pragma mark - 1. Recursion
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Sum Root to Leaf Numbers.
// Memory Usage: 9.3 MB, less than 36.32% of C++ online submissions for Sum Root to Leaf Numbers.
class Solution {
private:
    int recursion(TreeNode* root, int currentValue) {
        if (root == nullptr) {
            return 0;
        }

        currentValue *= 10;
        currentValue += root->val;

        int returnValue = 0;

        if (root->left || root->right) {
            returnValue += recursion(root->left, currentValue);
            returnValue += recursion(root->right, currentValue);
        } else {
            // This is a leaf.
            returnValue = currentValue;
        }

        return returnValue;
    }

public:
    int sumNumbers(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return recursion(root, 0);
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);

    auto result = solutionInstance.sumNumbers(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("4,9,0,5,1", 1026);
    test("1,2,3", 25);

    return 0;
}
