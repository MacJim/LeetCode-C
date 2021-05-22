/*
 * 107. Binary Tree Level Order Traversal II
 * https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1. Layer by layer, and reverse
// Runtime: 4 ms, faster than 80.22% of C++ online submissions for Binary Tree Level Order Traversal II.
// Memory Usage: 12.6 MB, less than 59.38% of C++ online submissions for Binary Tree Level Order Traversal II.
class Solution {
public:
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();

        auto currentNodes = std::vector<TreeNode*>({root});

        while (!currentNodes.empty()) {
            auto currentValues = std::vector<int>();
            auto nextNodes = std::vector<TreeNode*>();

            for (const auto node: currentNodes) {
                currentValues.push_back(node->val);

                if (node->left) {
                    nextNodes.push_back(node->left);
                }
                if (node->right) {
                    nextNodes.push_back(node->right);
                }
            }

            returnValue.push_back(std::move(currentValues));
            currentNodes = std::move(nextNodes);
        }

        std::reverse(returnValue.begin(), returnValue.end());

        return returnValue;
    }
};


void test(const std::string& treeStr, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.levelOrderBottom(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,9,20,,,15,7", {{15,7},{9,20},{3}});

    return 0;
}
