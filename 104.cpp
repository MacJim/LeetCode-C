/*
 * 104. Maximum Depth of Binary Tree
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion, DFS
// Runtime: 4 ms, faster than 96.05% of C++ online submissions for Maximum Depth of Binary Tree.
// Memory Usage: 18.9 MB, less than 54.62% of C++ online submissions for Maximum Depth of Binary Tree.
class Solution1 {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        const int left = maxDepth(root->left);
        const int right = maxDepth(root->right);
        return std::max(left, right) + 1;
    }
};


#pragma mark - 2. BFS
// Runtime: 8 ms, faster than 80.50% of C++ online submissions for Maximum Depth of Binary Tree.
// Memory Usage: 19.2 MB, less than 47.93% of C++ online submissions for Maximum Depth of Binary Tree.
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int returnValue = 1;

        auto current = std::vector<TreeNode*>({root});
        while (!current.empty()) {
            auto next = std::vector<TreeNode*>();
            for (const auto node: current) {
                if (node->left) {
                    next.push_back(node->left);
                }
                if (node->right) {
                    next.push_back(node->right);
                }
            }

            if (next.empty()) {
                break;
            } else {
                returnValue += 1;
                current = std::move(next);
            }
        }

        return returnValue;
    }
};


void test(const std::string& treeStr, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.maxDepth(root);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("3,9,20,,,15,7", 3);
    test("1,2", 2);
    test("1,,2", 2);
    test("", 0);
    test("6", 1);

    return 0;
}
