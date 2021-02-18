/*
 * 437. Path Sum III
 * https://leetcode.com/problems/path-sum-iii/
 */

#include <iostream>
#include <unordered_map>

//#include "helpers/Operators.hpp"
#include "helpers/TreeNode.hpp"


#pragma mark - 1. Recursion
// Runtime: 240 ms, faster than 8.13% of C++ online submissions for Path Sum III.
// Memory Usage: 64 MB, less than 10.44% of C++ online submissions for Path Sum III.
class Solution1 {
private:
    int subPathSum(TreeNode* root, const int target, const std::unordered_map<int, int>& previousSums) {
        if (root == nullptr) {
            return 0;
        }

        auto currentSums = std::unordered_map<int, int>();

        currentSums[root->val] = 1;
        for (const auto& [sum, count]: previousSums) {
            currentSums[sum + root->val] += count;    // Use `+=` instead of `=` because `sum` may equal 0.
        }

        const int leftValue = subPathSum(root->left, target, currentSums);
        const int rightValue = subPathSum(root->right, target, currentSums);

        int returnValue = currentSums[target] + leftValue + rightValue;
        return returnValue;
    }

public:
    int pathSum(TreeNode* root, const int target) {
        if (root == nullptr) {
            return 0;
        }

        const auto previousSums = std::unordered_map<int, int>({{root->val, 1}});
        auto returnValue = subPathSum(root->left, target, previousSums) + subPathSum(root->right, target, previousSums);
        if (root->val == target) {
            returnValue += 1;
        }

        return returnValue;
    }
};


#pragma mark - 2. Use sum deltas (revisit)
// Source: https://leetcode.com/problems/path-sum-iii/discuss/141424/Python-step-by-step-walk-through.-Easy-to-understand.-Two-solutions-comparison.-%3A-)
// sum(3 ~ 4) = sum(1 ~ 4) - sum(1 ~ 2)
// Runtime: 16 ms, faster than 89.67% of C++ online submissions for Path Sum III.
// Memory Usage: 19.7 MB, less than 30.64% of C++ online submissions for Path Sum III.
class Solution {
private:
    int subPathSum(TreeNode* root, const int target, int currentSum, std::unordered_map<int, int>& previousSums) {
        if (root == nullptr) {
            return 0;
        }

        currentSum += root->val;

        int remainingDelta = currentSum - target;
        int returnValue = 0;

        if (previousSums.count(remainingDelta)) {
            returnValue += previousSums[remainingDelta];
        }

        previousSums[currentSum] += 1;

        const int leftValue = subPathSum(root->left, target, currentSum, previousSums);
        const int rightValue = subPathSum(root->right, target, currentSum, previousSums);
        returnValue = returnValue + leftValue + rightValue;

        if (previousSums[currentSum] == 1) {
            previousSums.erase(currentSum);
        } else {
            previousSums[currentSum] -= 1;
        }

        return returnValue;
    }

public:
    int pathSum(TreeNode* root, const int target) {
        auto previousSums = std::unordered_map<int, int>({{0, 1}});
        auto returnValue = subPathSum(root, target, 0, previousSums);

        return returnValue;
    }
};


void test(const std::string& treeStr, const int target, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto root = TreeHelper::deserialize(treeStr);
    auto result = solutionInstance.pathSum(root, target);

    if (result == expectedResult) {
        std::cout << "[Correct] " << treeStr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << treeStr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("", 1, 0);
    test("1", 1, 1);
    test("0,1,1",1, 4);
    test("10,5,-3,3,2,,11,3,-2,,1", 8, 3);
    test("10,5,-3,3,2,,11,3,-2,,1", 1, 2);

    return 0;
}
