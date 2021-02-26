/*
 * 113. Path Sum II
 * https://leetcode.com/problems/path-sum-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


// Runtime: 12 ms, faster than 68.35% of C++ online submissions for Path Sum II.
// Memory Usage: 19.7 MB, less than 93.75% of C++ online submissions for Path Sum II.
class Solution {
private:
    void recursion(TreeNode* root, std::vector<int>& currentPath, const int targetSum, std::vector<std::vector<int>>& returnValue) {
        if (root == nullptr) {
            return;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            // This is a leaf.
            if (targetSum == root->val) {
                currentPath.push_back(root->val);
                returnValue.push_back(currentPath);
                currentPath.pop_back();
            }
        }

        const int nextSum = targetSum - root->val;
        currentPath.push_back(root->val);

        recursion(root->left, currentPath, nextSum, returnValue);
        recursion(root->right, currentPath, nextSum, returnValue);

        currentPath.pop_back();
    }

public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return {};
        }

        auto returnValue = std::vector<std::vector<int>>();
        auto currentPath = std::vector<int>();

        recursion(root, currentPath, targetSum, returnValue);

        return returnValue;
    }
};


void test(const std::string& treeStr, const int targetSum, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.pathSum(root, targetSum);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << " " << targetSum << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << " " << targetSum << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}



int main() {
    test("5,4,8,11,,13,4,7,2,,,5,1", 22, {{5,4,11,2},{5,8,4,5}});
    test("1,2,3", 4, {{1,3}});
    test("1,2,3", 5, {});

    return 0;
}
