/*
 * 1110. Delete Nodes And Return Forest
 * https://leetcode.com/problems/delete-nodes-and-return-forest/
 */

/*
 * Notes:
 * 
 * - Nodes have distinct values between 1 and 1000.
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/TreeNode.hpp"


// MARK: - 1. Recursion
// Runtime: 20 ms, faster than 90.57% of C++ online submissions for Delete Nodes And Return Forest.
// Memory Usage: 19.2 MB, less than 100.00% of C++ online submissions for Delete Nodes And Return Forest.
enum class NodeType {
    // The root of a disjoint tree.
    root,
    leftChildNotRoot,
    rightChildNotRoot
};

class Solution {
private:
    // Left and right children are separated in this one, which is not optimal.
    void deleteNodesRecursively(TreeNode* parentNode, TreeNode* currentNode, NodeType nodeType, std::vector<int>& nodesToDelete, std::vector<TreeNode*>& returnValue) {
        if (currentNode == nullptr) {
            return;
        }

        auto currentNodeIteratorInNodesToDeleteArray = std::find(nodesToDelete.begin(), nodesToDelete.end(), currentNode->val);
        if (currentNodeIteratorInNodesToDeleteArray == nodesToDelete.end()) {
            // Current node not found. Keep this node.

            if (nodeType == NodeType::root) {
                // This is the root node of a disjoint tree.
                returnValue.push_back(currentNode);
            }

            deleteNodesRecursively(currentNode, currentNode->left, NodeType::leftChildNotRoot, nodesToDelete, returnValue);
            deleteNodesRecursively(currentNode, currentNode->right, NodeType::rightChildNotRoot, nodesToDelete, returnValue);

        } else {
            // Current node should be deleted.

            if (parentNode) {
                // Remove current node from parent.
                switch (nodeType) {
                case NodeType::leftChildNotRoot:
                    parentNode->left = nullptr;
                    break;

                case NodeType::rightChildNotRoot:
                    parentNode->right = nullptr;
                    break;

                default:
                    break;
                }
            }

            // Retain left and right children.
            auto leftChild = currentNode->left;
            auto rightChild = currentNode->right;

            // Delete current node.
            // delete currentNode;    // MARK: For some reason LeetCode requires this line to get commented out. Really don't know why.
            nodesToDelete.erase(currentNodeIteratorInNodesToDeleteArray);

            // Delete nodes recursively on left and right children.
            deleteNodesRecursively(nullptr, leftChild, NodeType::root, nodesToDelete, returnValue);
            deleteNodesRecursively(nullptr, rightChild, NodeType::root, nodesToDelete, returnValue);
        }
    }

    // void deleteNodesRecursively(TreeNode* currentNode, std::vector<int>& nodesToDelete, std::vector<TreeNode*>& returnValue) {
    //     if (currentNode == nullptr) {
    //         return;
    //     }

    //     // Search for current node.
    //     auto currentNodeIteratorInToDeleteArray = std::find(nodesToDelete.begin(), nodesToDelete.end(), currentNode->val);
    // }

public:
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete) {
        auto returnValue = std::vector<TreeNode*>();

        deleteNodesRecursively(nullptr, root, NodeType::root, to_delete, returnValue);

        return returnValue;
    }
};

int main() {
    auto solutionInstance = Solution();

    // auto testTree1 = TreeHelper::deserialize("1,2,3,4,5,6,7");
    // auto valuesToDelete1 = std::vector<int>({3, 5});
    // auto result1 = solutionInstance.delNodes(testTree1, valuesToDelete1);
    // for (const auto& aNode: result1) {
    //     std::cout << aNode->val << " ";
    // }
    // std::cout << std::endl;

    auto testTree2 = TreeHelper::deserialize("1,2,3,,,,4");
    auto valuesToDelete2 = std::vector<int>({2, 1});
    auto result2 = solutionInstance.delNodes(testTree2, valuesToDelete2);
    for (const auto& aNode: result2) {
        std::cout << aNode->val << " ";
    }

    
    return 0;
}
