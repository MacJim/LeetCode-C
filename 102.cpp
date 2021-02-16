/*
 * 102. Binary Tree Level Order Traversal
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 */

#include <iostream>
#include <vector>
#include <numeric>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Layer by layer
// Runtime: 4 ms, faster than 80.04% of C++ online submissions for Binary Tree Level Order Traversal.
// Memory Usage: 12.6 MB, less than 75.14% of C++ online submissions for Binary Tree Level Order Traversal.
class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        auto returnValue = std::vector<std::vector<int>>();
        auto currentValues = std::vector<int>();

        auto currentNodes = std::vector<TreeNode*>({root});
        auto nextNodes = std::vector<TreeNode*>();

        while (!currentNodes.empty()) {
            for (const auto& node: currentNodes) {
                if (node) {
                    currentValues.push_back(node->val);
                    nextNodes.push_back(node->left);
                    nextNodes.push_back(node->right);
                }
            }

            if (!currentValues.empty()) {
                returnValue.push_back(std::move(currentValues));
                currentValues = std::vector<int>();
            }

            currentNodes = std::move(nextNodes);
            nextNodes = std::vector<TreeNode*>();
        }

        return returnValue;
    }
};


void test(const std::string treeString, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeString);
    auto result = solutionInstance.levelOrder(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeString << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeString << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    const std::vector<std::vector<char>> testCase1 = {
        {'0', 'E', '0', '0'},
        {'E', '0', 'W', 'E'},
        {'0', 'E', '0', '0'}
    };
    test("3,9,20,,,15,7", {
    {3},
    {9,20},
    {15,7}
    });

    return 0;
}
