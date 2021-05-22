/*
 * 103. Binary Tree Zigzag Level Order Traversal
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
 */

#include <iostream>
#include <vector>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Zigzag Level Order Traversal.
// Memory Usage: 12 MB, less than 92.92% of C++ online submissions for Binary Tree Zigzag Level Order Traversal.
class Solution {
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>({});

        bool reverse = false;
//        auto previousNodes = std::vector<TreeNode*>();
        auto currentNodes = std::vector<TreeNode*>({root});

        while (!currentNodes.empty()) {
            auto upcomingNodes = std::vector<TreeNode*>();
            auto currentValues = std::vector<int>(currentNodes.size());

            for (size_t i = 0; i < currentNodes.size(); i += 1) {
                const auto node = currentNodes[i];

                if (node->left) {
                    upcomingNodes.push_back(node->left);
                }
                if (node->right) {
                    upcomingNodes.push_back(node->right);
                }

                if (reverse) {
                    currentValues[currentNodes.size() - i - 1] = node->val;
                } else {
                    currentValues[i] = node->val;
                }
            }

            returnValue.push_back(std::move(currentValues));

            reverse = !reverse;
//            previousNodes = std::move(currentNodes);
            currentNodes = std::move(upcomingNodes);
        }

        return returnValue;
    }
};


void test(const std::string& treeStr, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.zigzagLevelOrder(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,9,20,,,15,7", {{3},{20,9},{15,7}});
    test("1,2,3,4,5,6,7,,8,,,9,10,,11", {{1}, {3,2}, {4,5,6,7}, {11,10,9,8}});
    test("1", {{1}});
    test("", {});

    return 0;
}
