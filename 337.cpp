/*
 * 337. House Robber III
 * https://leetcode.com/problems/house-robber-iii/
 */

#include <iostream>
#include <string>
#include <algorithm>

#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 20 ms, faster than 62.90% of C++ online submissions for House Robber III.
// Memory Usage: 22.6 MB, less than 72.01% of C++ online submissions for House Robber III.
class Solution {
private:
    /**
     * @param root Root node of the sub-tree.
     * @return (max profit robbing the current node, max profit not robbing the current node)
     */
    std::pair<int, int> _rob(TreeNode* root) {
        // This is `nullptr`.
        if (root == nullptr) {
            return std::make_pair(0, 0);
        }

        // This is a leaf node.
        if ((root->left == nullptr) && (root->right == nullptr)) {
            return std::make_pair(root->val, 0);
        }

        // This is not a leaf node.
        const auto leftChildProfits = _rob(root->left);
        const auto rightChildProfits = _rob(root->right);

        // Rob the current node.
        int robProfit = root->val + leftChildProfits.second + rightChildProfits.second;    // We must not rob the previous nodes.

        // Don't rob the current node.
        int dontRobProfit = 0 + std::max(leftChildProfits.first, leftChildProfits.second) + std::max(rightChildProfits.first, rightChildProfits.second);    // We can choose to either rob or not rob the previous nodes.

        return std::make_pair(robProfit, dontRobProfit);
    }

public:
    int rob(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            return root->val;
        }

        const auto [robProfit, dontRobProfit] = _rob(root);
        return std::max(robProfit, dontRobProfit);
    }
};


void test(const std::string& serializedTree, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto rootNode = TreeHelper::deserialize(serializedTree);
    auto result = solutionInstance.rob(rootNode);

    if (result == expectedResult) {
        std::cout << "[Correct] " << serializedTree << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << serializedTree << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("4,1,,2,,3", 7);
    test("3,2,3,,3,,1", 7);
    test("3,4,5,1,3,,1", 9);

    return 0;
}
