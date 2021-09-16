/*
 * 863. All Nodes Distance K in Binary Tree
 * https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
 */

#include <iostream>
#include <vector>
#include <stack>
#include <exception>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// Runtime: 3 ms, faster than 88.79% of C++ online submissions for All Nodes Distance K in Binary Tree.
// Memory Usage: 12.7 MB, less than 62.57% of C++ online submissions for All Nodes Distance K in Binary Tree.
class Solution {
private:
    /**
     * Get all eligible children of `root` with distance `k`.
     *
     * This function can properly handle `k == 0`.
     */
    std::vector<TreeNode*> findChildren(TreeNode* root, const int k) {
        if (!root) {
            return {};
        }

        auto currentChildren = std::vector<TreeNode*>({root});
        for (int i = 0; i < k; i += 1) {
            auto nextChildren = std::vector<TreeNode*>();

            for (const auto c: currentChildren) {
                if (c->left) {
                    nextChildren.push_back(c->left);
                }
                if (c->right) {
                    nextChildren.push_back(c->right);
                }
            }

            currentChildren = std::move(nextChildren);

            if (currentChildren.empty()) {
                // No eligible children.
                break;
            }
        }

        return currentChildren;
    }

private:
    /**
     * Find a node recursively.
     *
     * This function throws an `std::exception` when the node is found.
     */
    void findNodeRecursively(TreeNode* root, const TreeNode* target, std::vector<TreeNode*>& parents) {
        if (!root) {
            return;
        }

        if (root == target) {
            throw std::exception();
        }

        parents.push_back(root);

        if (root->left) {
            findNodeRecursively(root->left, target, parents);
        }
        if (root->right) {
            findNodeRecursively(root->right, target, parents);
        }

        parents.pop_back();
    }

public:
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        auto returnValue = std::vector<int>();

        // Target's children.
        auto targetChildren = findChildren(target, k);
        for (const auto c: targetChildren) {
            returnValue.push_back(c->val);
        }

        // Target's parents.
        /*
         * Find the node.
         *
         * Typically, I use a single stack to perform a tree walk.
         * But this time, I cannot remove an element unless both its left and right children are visited.
         *
         * ~~So I'll introduce another stack to log if its right child is visited.~~
         * No. Let's just use recursion.
         */
        auto parents = std::vector<TreeNode*>();
        try {
            findNodeRecursively(root, target, parents);
        } catch (std::exception& e) {
            // Breaks out.
        }

        if (parents.empty()) {
            // Edge case: `target` is root.
            // Actually I think this part can be removed because it's properly handled by the following `for` loop.
            return returnValue;
        }

        auto previousNode = target;
        for (int distance = 1; distance <= k; distance += 1) {
            if (parents.size() < distance) {
                break;
            }

            auto currentNode = parents[parents.size() - distance];
            if (distance == k) {
                // This is the final parent. So no need to visit its other child.
                returnValue.push_back(currentNode->val);
                break;    // This `break` is optional.
            }

            if (currentNode->left == previousNode) {
                auto rightChildren = findChildren(currentNode->right, k - distance - 1);
                for (const auto c: rightChildren) {
                    returnValue.push_back(c->val);
                }
            } else {
                auto leftChildren = findChildren(currentNode->left, k - distance - 1);
                for (const auto c: leftChildren) {
                    returnValue.push_back(c->val);
                }
            }

            previousNode = currentNode;
        }

        return returnValue;
    }
};


//void test(const std::string& treeStr, const int expectedResult) {
//    auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
//    } else {
//        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    return 0;
}
