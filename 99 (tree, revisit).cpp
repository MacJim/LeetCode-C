/*
 * 99. Recover Binary Search Tree
 * https://leetcode.com/problems/recover-binary-search-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/TreeNode.hpp"


#pragma mark - 1. WRONG
/*
 * Cases:
 *
 * 1. Root is swapped with the biggest node in the left tree: root < max(left), min(right) > max(left) or right is nullptr
 * 2. Root is swapped with the smallest node in the right tree: root > min(right), min(right) > max(left) or left is nullptr
 * 3. The biggest node in the left tree is swapped with the smallest node in the right tree: min(right) < max(left), min(right) < root
 * 4. Return to upper level recursion
 */
class Solution1 {
private:
    std::pair<TreeNode*, TreeNode*> recursion(TreeNode* root) {
        if (!root) {
            return std::make_pair(nullptr, nullptr);
        }

        auto currentMin = root;
        auto currentMax = root;

        auto [leftMin, leftMax] = recursion(root->left);
        auto [rightMin, rightMax] = recursion(root->right);

        if (root->left && (root->val < leftMax->val) && ((!root->right) || (rightMin > leftMax))) {
            // Case 1.
            std::swap(root->val, leftMax->val);
            throw std::logic_error("J");
        }
        if (root->right && (root->val > rightMin->val) && ((!root->left) || (rightMin > leftMax))) {
            // Case 2.
            std::swap(root->val, rightMin->val);
            throw std::logic_error("J");
        }
        if (root->left && root->right && (rightMin < leftMax) && (rightMin < root)) {
            // Case 3.
            std::swap(leftMax->val, rightMin->val);
            throw std::logic_error("J");
        }

        // Case 4.
        if (leftMin && (leftMin->val < currentMin->val)) {
            currentMin = leftMin;
        }
        if (rightMin && (rightMin->val < currentMin->val)) {
            currentMin = rightMin;
        }
        if (leftMax && (leftMax->val > currentMax->val)) {
            currentMax = leftMax;
        }
        if (rightMax && (rightMax->val > currentMax->val)) {
            currentMax = rightMax;
        }

        return std::make_pair(currentMin, currentMax);
    }

public:
    void recoverTree(TreeNode* root) {
        try {
            recursion(root);
        } catch (std::logic_error& e) {
        }
    }
};


#pragma mark - 2. WRONG
class Solution2 {
private:
    TreeNode* recursion(TreeNode* root, TreeNode* lowerBound, TreeNode* upperBound) {
        if (!root) {
            return nullptr;
        }

        if (lowerBound) {
            if (root->val < lowerBound->val) {
                return root;
            }
        }
        if (upperBound) {
            if (root->val > upperBound->val) {
                return root;
            }
        }

        auto leftProblematicNode = recursion(root->left, nullptr, root);
        auto rightProblematicNode = recursion(root->right, root, nullptr);

        if (leftProblematicNode && rightProblematicNode) {
            std::swap(leftProblematicNode->val, rightProblematicNode->val);
            throw std::logic_error("J");
        }

        if (leftProblematicNode) {
            return leftProblematicNode;
        }
        if (rightProblematicNode) {
            return rightProblematicNode;
        }
        return nullptr;
    }

public:
    void recoverTree(TreeNode* root) {
        try {
            recursion(root, nullptr, nullptr);
        } catch (std::logic_error& e) {
        }
    }
};


#pragma mark - 3. In-order traversal (revisit)
/*
 * The in-order traversal of a correct BST should produce increasing numbers.
 */
// Source: https://leetcode.ca/2016-03-08-99-Recover-Binary-Search-Tree/
// Runtime: 24 ms, faster than 82.38% of C++ online submissions for Recover Binary Search Tree.
// Memory Usage: 57.8 MB, less than 68.19% of C++ online submissions for Recover Binary Search Tree.
class Solution {
private:
    TreeNode* n1 = nullptr;
    TreeNode* n2 = nullptr;
    /// The previous node in the in-order traversal.
    TreeNode* prev = nullptr;

    void inOrderTraversal(TreeNode* root) {
        if (!root) {
            return;
        }

        inOrderTraversal(root->left);

        if (prev && (prev->val >= root->val)) {
            if (!n1) {
                // Found the first misplaced node.
                n1 = prev;
                /*
                 * We're not sure if the second misplaced node is `root` or a later node.
                 * So we keep searching for the 2nd node.
                 *
                 * Since there are exactly 2 misplaced nodes, if we don't find a 2nd misplaced node later, `root` is the 2nd misplaced node.
                 */
                n2 = root;
            } else {
                /*
                 * Found the 2nd misplaced node.
                 * The `root` that we log previously is not a misplaced node.
                 */
                n2 = root;
            }
        }

        prev = root;

        inOrderTraversal(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        inOrderTraversal(root);

        std::swap(n1->val, n2->val);
    }
};


void test(const std::string& treeStr, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    solutionInstance.recoverTree(root);
    auto result = TreeHelper::serialize(root);

    if (result.find(expectedResult, 0) == 0) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,3,,,2", "3,1,,,2");
    test("3,1,4,,,2", "2,1,4,,,3");
    test("10,5,15,2,12,8,18,,3,,,11,14,,19", "10,5,15,2,8,12,18,,3,,,11,14,,19");

    return 0;
}
