/*
 * 199. Binary Tree Right Side View
 * https://leetcode.com/problems/binary-tree-right-side-view/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Right most elements
// Wrong Answer: Also need to consider left elements if left sub-trees are deeper than the right sub-tree.
class Solution1 {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        auto returnValue = std::vector<int>();
        auto currentNode = root;
        while (currentNode != nullptr) {
            returnValue.push_back(currentNode->val);
            if (currentNode->right) {
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. BFS, layer by layer
// Runtime: 4 ms, faster than 67.20% of C++ online submissions for Binary Tree Right Side View.
// Memory Usage: 11.9 MB, less than 29.31% of C++ online submissions for Binary Tree Right Side View.
class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        auto returnValue = std::vector<int>();
        auto currentNodes = std::vector<TreeNode*>({root});
        while (!currentNodes.empty()) {
            returnValue.push_back(currentNodes.back()->val);

            auto nextNodes = std::vector<TreeNode*>();
            for (const auto node: currentNodes) {
                if (node->left) {
                    nextNodes.push_back(node->left);
                }
                if (node->right) {
                    nextNodes.push_back(node->right);
                }
            }

            currentNodes = std::move(nextNodes);
        }

        return returnValue;
    }
};


#pragma mark - 3. Recursion/traversal (saves memory): visit right then left, compare current level and `returnValue`


void test(const std::string& treeStr, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.rightSideView(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,2,3,4", {1,3,4});
    test("", {});
    test("1,2,3,,5,,4", {1, 3, 4});
    test("1,,3", {1, 3});

    return 0;
}
