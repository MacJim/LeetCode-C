/*
 * 98. Validate Binary Search Tree
 * https://leetcode.com/problems/validate-binary-search-tree/
 */

#include <iostream>

#include "helpers/TreeNode.hpp"


// MARK: - 1. Wrong answer
class Solution1 {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBSTRecursively(root);
    }

protected:
    bool isValidBSTRecursively(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        const auto& left = root->left;
        if (left) {
            if (left->val >= root->val) {    // Note: This question requires that children cannot have the same value.
                return false;
            }
        }
        const auto& right = root->right;
        if (right) {
            if (right->val <= root->val) {
                return false;
            }
        }

        if (!isValidBSTRecursively(root->left)) {
            return false;
        }
        if (!isValidBSTRecursively(root->right)) {
            return false;
        }

        return true;
    }
};


// MARK: - 2. Wrong answer
class Solution2 {
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            // As required by the question.
            return true;
        }

        // if (!isValidLeftSubtree(root->left, root->val)) {
        //     return false;
        // }
        // if (!isValidRightSubtree(root->right, root->val)) {
        //     return false;
        // }

        // return true;

        return isValidSubtree(root, root->val, root->val);
    }

protected:
    bool isValidSubtree(const TreeNode* root, const int minVal, const int maxVal) {
        if (root == nullptr) {
            return true;
        }

        if (root->left) {
            if (root->left->val >= minVal) {
                return false;
            }

            if (!isValidSubtree(root->left, root->left->val, maxVal)) {
                return false;
            }
        }

        if (root->right) {
            if (root->right->val <= maxVal) {
                return false;
            }

            if (!isValidSubtree(root->right, minVal, root->right->val)) {
                return false;
            }
        }

        return true;
    }

    // bool isValidLeftSubtree(const TreeNode* root, const int minVal) {
    //     if (root == nullptr) {
    //         return true;
    //     }

    //     if (root->val >= minVal) {
    //         return false;
    //     }

    //     if (!isValidLeftSubtree(root->left, root->val)) {
    //         return false;
    //     }
    // }

    // bool isValidRightSubtree(const TreeNode* root, const int minVal) {
    //     if (root == nullptr) {
    //         return true;
    //     }
    // }
};


// MARK: - 3
// Runtime: 8 ms, faster than 98.57% of C++ online submissions for Validate Binary Search Tree.
// Memory Usage: 21.3 MB, less than 6.25% of C++ online submissions for Validate Binary Search Tree.
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return verifyBST(root).first;
    }

protected:
    /// (min, max) of subtree.
    std::pair<bool, std::pair<int, int>> verifyBST(const TreeNode* root) {
        if (root == nullptr) {
            return std::make_pair(true, std::make_pair(INT_MIN, INT_MAX));
        }

        int min = root->val;
        int max = root->val;

        if (root->left) {
            auto vals = verifyBST(root->left);
            if (!vals.first) {
                return std::make_pair(false, std::make_pair(INT_MIN, INT_MAX));
            }

            min = vals.second.first;
            auto leftMax = vals.second.second;

            if (leftMax >= root->val) {
                return std::make_pair(false, std::make_pair(INT_MIN, INT_MAX));
            }
        }

        if (root->right) {
            auto vals = verifyBST(root->right);
            if (!vals.first) {
                return std::make_pair(false, std::make_pair(INT_MIN, INT_MAX));
            }

            auto rightMin = vals.second.first;
            max = vals.second.second;

            if (rightMin <= root->val) {
                return std::make_pair(false, std::make_pair(INT_MIN, INT_MAX));
            }
        }

        return std::make_pair(true, std::make_pair(min, max));
    }
    // // (minVal, maxVal)
    // bool isValidLeftSubtree(const TreeNode* root, const int minVal, const int maxVal) {
    //     if (root == nullptr) {
    //         return true;
    //     }

    //     if (root->left) {
    //         const auto& val = root->left->val;
    //         if ((val >= root->val) || (val >= maxVal)) {
    //             return false;
    //         }
            
    //         if (!isValidLeftSubtree(root->left, minVal, maxVal)) {
    //             return false;
    //         }
    //     }
    //     if (root->right) {
    //         const auto& val = root->right->val;
    //         if ((val <= root->val) || (val >= maxVal)) {
    //             return false;
    //         }

    //         // TODO:
    //     }
    // }

    // int leftSubtreeMax(const TreeNode* root) {
    //     if (root == nullptr) {
    //         return INT_MIN;
    //     }

    //     if (root->left) {
    //         int leftMax = leftSubtreeMax(root->left);
    //     }

    //     if (root->right) {
    //         int rightMin()
    //     }
    // }

    // int rightSubtreeMin(const TreeNode* root) {
    //     if (root == nullptr) {
    //         return INT_MAX;
    //     }
    // }
};


int main() {
    auto solutionInstance = Solution();

    auto testCase1 = TreeHelper::deserialize("2,1,3");
    std::cout << solutionInstance.isValidBST(testCase1) << std::endl;    // true

    auto testCase2 = TreeHelper::deserialize("5,1,4,,,3,6");
    std::cout << solutionInstance.isValidBST(testCase2) << std::endl;    // false

    auto testCase3 = TreeHelper::deserialize("10,5,15,,,6,20");
    std::cout << solutionInstance.isValidBST(testCase3) << std::endl;    // false


    return 0;
}
