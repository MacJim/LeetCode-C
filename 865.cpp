/*
 * 865. Smallest Subtree with all the Deepest Nodes
 * https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "helpers/TreeNode.hpp"


#pragma mark - 1. BFS. Wrong because of the lack of parent references.
class Solution1 {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        } else if ((root->left == nullptr) && (root->right == nullptr)) {
            return root;
        }

        auto currentLayerNodes = std::vector<TreeNode*>();
        auto nextLayerNodes = std::vector<TreeNode*>({root->left, root->right});

        // Go to the deepest layer.
        while (!nextLayerNodes.empty()) {
            std::swap(currentLayerNodes, nextLayerNodes);

            for (const auto node: currentLayerNodes) {
                if (node->left) {
                    nextLayerNodes.push_back(node->left);
                }
                if (node->right) {
                    nextLayerNodes.push_back(node->right);
                }
            }
        }

        // Go from the deepest layer to their common parent node.
        auto logicalEnd = std::unique(currentLayerNodes.begin(), currentLayerNodes.end());
        while (logicalEnd != currentLayerNodes.end()) {
            currentLayerNodes.erase(logicalEnd, currentLayerNodes.end());

            for (const auto& node: currentLayerNodes) {
                // Oh no. The nodes don't have references to their parents!
            }
        }

        return currentLayerNodes.front();
    }
};


#pragma mark - 2
/*
 * We know that the values are unique and that we have at most 500 values.
 * Thus, we cache the depth of every node in a map.
 */
// Runtime: 4 ms, faster than 84.97% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
// Memory Usage: 16.5 MB, less than 15.82% of C++ online submissions for Smallest Subtree with all the Deepest Nodes.
class Solution {
private:
    /**
     * (node value, depth)
     *
     * Node values are guaranteed to be unique.
     */
    std::unordered_map<short, short> cachedDepths = std::unordered_map<short, short>();

    short getDepth(TreeNode* node) {
        // Special cases.
        if (node == nullptr) {
            return 0;    // `nullptr` is 0.
        } else if ((node->left == nullptr) && (node->right == nullptr)) {
            return 1;    // Leaf is 1.
        }

        // Cached depth.
        auto cachedDepthIt = cachedDepths.find(node->val);
        if (cachedDepthIt != cachedDepths.end()) {
            return cachedDepthIt->second;
        }

        // Calculate depth from scratch.
        const short leftDepth = getDepth(node->left);
        const short rightDepth = getDepth(node->right);
        const short currentDepth = std::max(leftDepth, rightDepth) + 1;

        // Cache the result.
        cachedDepths.emplace(node->val, currentDepth);

        return currentDepth;
    }

public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        } else if ((root->left == nullptr) && (root->right == nullptr)) {
            return root;
        }

        auto currentParent = root;
        while (currentParent != nullptr) {
            auto leftDepth = getDepth(currentParent->left);
            auto rightDepth = getDepth(currentParent->right);
            if (leftDepth == rightDepth) {
                return currentParent;
            } else if (leftDepth > rightDepth) {
                currentParent = currentParent->left;
            } else {
                currentParent = currentParent->right;
            }
        }

//        auto currentNodes = std::vector<TreeNode*>({currentParent->left, currentParent->right});
//        // Find the largest node.
//        for (const auto node: currentNodes) {
//            const int currentDepth = getDepth(node);
//        }

        return root;
    }
};


void test(const std::string& serializedTree, const int expectedNodeValue) {
    static auto solutionInstance = Solution();

    auto tree = TreeHelper::deserialize(serializedTree);
    auto result = solutionInstance.subtreeWithAllDeepest(tree);

    if (result->val == expectedNodeValue) {
        std::cout << "[Possibly Correct] " << serializedTree << ": " << expectedNodeValue << std::endl;
    } else {
        std::cout << "[Wrong] " << serializedTree << ": " << result->val << " (should be " << expectedNodeValue << ")" << std::endl;
    }
}


int main() {
    test("3,5,1,6,2,0,8,,,7,4", 2);
    test("0,1,3,,2", 2);

    return 0;
}
