/*
 * 1609. Even Odd Tree
 * https://leetcode.com/problems/even-odd-tree/
 */

#include <iostream>
#include <vector>

#include "helpers/TreeNode.hpp"
#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Layer by layer
// Runtime: 252 ms, faster than 61.69% of C++ online submissions for Even Odd Tree.
// Memory Usage: 157 MB, less than 28.98% of C++ online submissions for Even Odd Tree.
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        bool isEvenLevel = true;
        std::vector<TreeNode*> currentLayer = {root};

        while (!currentLayer.empty()) {
            auto nextLayer = std::vector<TreeNode*>();

            if (isEvenLevel) {
                int previousValue = INT_MIN;
                for (const auto node: currentLayer) {
                    if (node->val % 2 == 0) {
                        return false;
                    }

                    if (node->val <= previousValue) {
                        return false;
                    }

                    previousValue = node->val;

                    if (node->left) {
                        nextLayer.push_back(node->left);
                    }
                    if (node->right) {
                        nextLayer.push_back(node->right);
                    }
                }
            } else {
                int previousValue = INT_MAX;
                for (const auto node: currentLayer) {
                    if (node->val % 2) {
                        return false;
                    }

                    if (node->val >= previousValue) {
                        return false;
                    }

                    previousValue = node->val;

                    if (node->left) {
                        nextLayer.push_back(node->left);
                    }
                    if (node->right) {
                        nextLayer.push_back(node->right);
                    }
                }
            }

            isEvenLevel = !isEvenLevel;
            currentLayer = std::move(nextLayer);
        }

        return true;
    }
};


void test(const std::string& treeStr, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.isEvenOddTree(root);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << treeStr << ": " << std::boolalpha << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << treeStr << ": " << std::boolalpha << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("1,10,4,3,,7,9,12,8,6,,,2", true);
    test("5,4,2,3,3,7", false);
    test("5,9,1,3,5,7", false);
    test("1", true);
    test("11,8,6,1,3,9,11,30,20,18,16,12,10,4,2,17", true);

    return 0;
}
